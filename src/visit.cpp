#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include "koopa.h"
#include "visit.h"
#include "string.h"
using namespace std;


const char* op2inst[] = {
    "", "", "sgt", "slt", "", "",
    "add", "sub", "mul", "div",
    "rem", "and", "or", "xor",
    "sll", "srl", "sra"
};
static int tmp_cnt = 0;
koopa_raw_slice_t params;
// std::map<koopa_raw_value_t, string> getreg;
// std::map<std::string, bool> reg_available = {{"t0", true}, {"t1", true}, {"t2", true}, {"t3", true}, {"t4", true}, 
//                                               {"t5", true}, {"t6", true}, {"t7", true}, 
//                                               {"t8", true}, {"t9", true}};

unordered_map<koopa_raw_value_t, size_t> stack_addr;
static int R, A, S, D;



// 访问 raw program
void Visit(const koopa_raw_program_t &program) {
  // 访问所有全局变量
  Visit(program.values);
  // 访问所有函数
  Visit(program.funcs);
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice) {
  for (size_t i = 0; i < slice.len; ++i) {
    auto ptr = slice.buffer[i];
    // 根据 slice 的 kind 决定将 ptr 视作何种元素
    switch (slice.kind) {
      case KOOPA_RSIK_FUNCTION:
        // 访问函数
        Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
        break;
      case KOOPA_RSIK_BASIC_BLOCK:
        // 访问基本块
        Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
        break;
      case KOOPA_RSIK_VALUE:
        // 访问指令/全局变量
        Visit(reinterpret_cast<koopa_raw_value_t>(ptr));
        break;
      default:
        // 我们暂时不会遇到其他内容, 于是不对其做任何处理
        assert(false);
    }
  }
}

// 访问函数
void Visit(const koopa_raw_function_t &func) {
  if(func->bbs.len == 0) return;
  
  cout << "  .text" << endl;
  cout << "  .globl " << func->name + 1 << endl;
  cout << func->name + 1 << ":" << endl;

  params = func->params;
  stack_addr.clear();
  S = 0;
  R = 0;
  A = 0;
  D = 0;
  alloc(func);
  int d = S + R + A;
  D = d%16 ? d + 16 - d %16: d;

  if(D)
  {
     _addi("sp", "sp", -D);
     just_stored = false;
  }
  if(R){
    _save("ra", "sp", D-4);
    }
  // 找到entry
  size_t e = 0;
  for(e = 0; e < func->bbs.len; ++e){
      auto ptr = reinterpret_cast<koopa_raw_basic_block_t>(func->bbs.buffer[e]);
      if(ptr->name && !strcmp(ptr->name, "%entry")){
          break;
      }
  }

  Visit(reinterpret_cast<koopa_raw_basic_block_t>(func->bbs.buffer[e]));

  for(size_t i = 0; i < func->bbs.len; ++i){
        if(i == e) continue;
        auto ptr = func->bbs.buffer[i];
        Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
  }
  
  cout << endl;
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb) {
  // 执行一些其他的必要操作
  if(bb->name && strcmp(bb->name, "%entry"))
    cout << bb->name + 1 << ":" << endl;
  // 访问所有指令
  Visit(bb->insts);
}

// 访问指令
void Visit(const koopa_raw_value_t &value) {
  // 根据指令类型判断后续需要如何访问
  const auto &kind = value->kind;
  switch (kind.tag) {
    case KOOPA_RVT_RETURN:
      // 访问 return 指令
      Visit(kind.data.ret); 
      break;
    case KOOPA_RVT_INTEGER:
      // 访问 integer 指令
      Visit(kind.data.integer);
      break;
    case KOOPA_RVT_BINARY:
      // 访问二元运算
      // getreg[value] = Visit(kind.data.binary);
      Visit(kind.data.binary);
      _save("t0", "sp", stack_addr[value] + A);
      break;
    case KOOPA_RVT_ALLOC:
      // 访问栈分配指令，啥都不用管
      break; 
    case KOOPA_RVT_LOAD:
      // 加载指令
      Visit(kind.data.load);
      _save("t0", "sp", stack_addr[value] + A);
      break;   
    case KOOPA_RVT_STORE:
      // 存储指令
      Visit(kind.data.store);
      break;
    case KOOPA_RVT_BRANCH:
      // 条件分支指令
      Visit(kind.data.branch);
      break;
    case KOOPA_RVT_JUMP:
      // 无条件跳转指令
      Visit(kind.data.jump);
      break;
    case KOOPA_RVT_CALL:
      // 访问函数调用
      Visit(kind.data.call);
      if(kind.data.call.callee->ty->data.function.ret->tag == KOOPA_RTT_INT32){
        _save("a0", "sp", stack_addr[value] + A);
      }
      break;
    case KOOPA_RVT_GLOBAL_ALLOC:
      // 访问全局变量
      VisitGlobalVar(value);
      break;
    case KOOPA_RVT_GET_ELEM_PTR:
        // 访问getelemptr指令
        Visit(kind.data.get_elem_ptr);
        _save("t0", "sp", stack_addr[value] + A);
        break;
    case KOOPA_RVT_GET_PTR:
        // 访问getptr指令
        Visit(kind.data.get_ptr);
        _save("t0", "sp", stack_addr[value] + A);
        break;
    default:
      // 其他类型暂时遇不到
      assert(false);
  }
}

// 访问return 
void Visit(const koopa_raw_return_t &ret) {
  if(ret.value == nullptr)
  { 
    if(R){
    _load("ra", "sp", D-4);
    }
    if(D){
      _addi("sp", "sp", D);
      just_stored = false;
    }
    cout << "  ret" << endl;
    return;
  }
  koopa_raw_value_t ret_value = ret.value;
  // 特判return一个整数情况
  if(ret_value->kind.tag == KOOPA_RVT_INTEGER){
      
      int retvalue = Visit(ret_value -> kind.data.integer);
      
      cout << "  li  a0, " << retvalue << endl;
      just_stored = false; 
  }
  else
  { 
    int i = stack_addr[ret_value] + A;
    _load("a0", "sp", i);
  }
  
  if(R){
    _load("ra", "sp", D-4);
  }
  if(D){
      _addi("sp", "sp", D);
      just_stored = false;
  }
  cout << "  ret" << endl;
}

// 访问int
int Visit(const koopa_raw_integer_t &ret) {
  return ret.value;
}

// 访问二元运算
void Visit(const koopa_raw_binary_t &value){
  koopa_raw_value_t l = value.lhs, r = value.rhs;
  string regleft = "t0", regright = "t1";
  string retreg;
  if(l->kind.tag == KOOPA_RVT_INTEGER){
        int i = Visit(l->kind.data.integer);
        //regleft = FirstUnusedReg();
        cout << "  li  " << regleft <<", " << i << endl;
        just_stored = false;
        //reg_available[regleft] = false;
    }
  // else
  //   regleft = getreg[l];
  else{
        int i = stack_addr[l] + A;
        _load(regleft, "sp", i);
    }

  if(r->kind.tag == KOOPA_RVT_INTEGER){
        int i = Visit(r->kind.data.integer);
        //regright = FirstUnusedReg();
        cout << "  li  " << regright <<", " << i << endl;
        just_stored = false;
        //reg_available[regright] = false;
    }
  else
    //regright = getreg[r];
    {
        int i = stack_addr[r] + A;
        _load(regright, "sp", i);
    }
  

   if(value.op == KOOPA_RBO_NOT_EQ){
        cout << "  xor   " << regleft << ", " << regleft << ", " << regright << endl;
        cout << "  snez  " << regleft << ", " << regleft << endl;
        just_stored = false;
        retreg = regleft;
        // reg_available[regright] = true;
        // reg_available[regleft] = false;
    }else if(value.op == KOOPA_RBO_EQ){
        cout << "  xor   " << regleft << ", " << regleft << ", " << regright << endl;
        cout << "  seqz  " << regleft << ", " << regleft << endl;
        just_stored = false;
        retreg = regleft;
        // reg_available[regright] = true;
        // reg_available[regleft] = false;
    }else if(value.op == KOOPA_RBO_GE){
        cout << "  slt   " << regleft << ", " << regleft << ", " << regright << endl;
        cout << "  seqz  " << regleft << ", " << regleft << endl;
        just_stored = false;
        retreg = regleft;
        // reg_available[regright] = true;
        // reg_available[regleft] = false;
    }else if(value.op == KOOPA_RBO_LE){
        cout << "  sgt   " << regleft << ", " << regleft << ", " << regright << endl;
        cout << "  seqz  " << regleft << ", " << regleft << endl;
        just_stored = false;
        retreg = regleft;
        // reg_available[regright] = true;
        // reg_available[regleft] = false;
    }else{
        string op = op2inst[(int)value.op];
        // reg_available[regleft] = true;
        // reg_available[regright] = true;
        // retreg = FirstUnusedReg();
        // reg_available[retreg] = false;
        retreg = regleft;
        cout << "  " << op <<"   " << retreg << ", " << regleft << ", " << regright << endl;
        just_stored = false;
    }
}

// 访问load指令
void Visit(const koopa_raw_load_t &load){
  koopa_raw_value_t src = load.src;
  int i = stack_addr[src] + A;

  if(src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
      // 全局变量
      cout << "  la  " << "t0" <<", " << src->name + 1 << endl;
      just_stored = false;
      _load("t0", "t0", 0);
  } 
  // 栈分配
  else if(src->kind.tag == KOOPA_RVT_ALLOC){
    _load("t0", "sp", i);
  }else{
    _load("t0", "sp", i);
    _load("t0", "t0", 0);
    }
}

// 访问store指令
void Visit(const koopa_raw_store_t &store){
    koopa_raw_value_t v = store.value, d = store.dest;

    int i, j;
    if(v->kind.tag == KOOPA_RVT_FUNC_ARG_REF){
        for(i = 0; i < params.len; ++i){
            if(params.buffer[i] == (void *)v)
                break;
        }
        if(i < 8){
            string reg = "a" + to_string(i);
            if(d->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
                cout << "  la  " << "t0" <<", " << d->name + 1 << endl;
                just_stored = false;
                _save(reg, "t0", 0);
            }else if(d->kind.tag == KOOPA_RVT_ALLOC){
                _save(reg, "sp", stack_addr[d] + A);
            }else{
                _load("t0", "sp", stack_addr[d] + A);
                cout << "  sw  " << reg << ", 0(t0)" << endl;
            }
            return;
        } else{
            i = (i - 8) * 4;
            _load("t0", "sp", i + D);
        }
    }
    else if(v->kind.tag == KOOPA_RVT_INTEGER){
        int i = Visit(v->kind.data.integer);
        cout << "  li  " << "t0" <<", " << i << endl;
        just_stored = false;
    } else{
        i = stack_addr[v] + A;
        _load("t0", "sp", i);
    }
    if(d->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
        cout << "  la  " << "t1" <<", " << d->name + 1 << endl;
        just_stored = false;
        _save("t0", "t1", 0);
    }
    else if(d->kind.tag == KOOPA_RVT_ALLOC){
        j = stack_addr[d] + A;
        _save("t0", "sp", j);
    }else {
        _load("t1", "sp", stack_addr[d] + A);
        _save("t0","t1", 0);
    }
    
    return;
}


// 访问branch指令
void Visit(const koopa_raw_branch_t &branch){
    auto true_bb = branch.true_bb;
    auto false_bb = branch.false_bb;
    koopa_raw_value_t v = branch.cond;
    if(v->kind.tag == KOOPA_RVT_INTEGER){
      int i = Visit(v->kind.data.integer);
      cout << "  li  " << "t0" <<", " << i << endl;
      just_stored = false;
    }else{
        int i = stack_addr[v] + A;
        _load("t0", "sp", i);
    }

    cout << "  bnez  " << "t0, " << "temp" << tmp_cnt << endl;
    cout << "  j " << string(false_bb->name + 1) << endl;
    cout << "temp" << tmp_cnt << ":" << endl;
    tmp_cnt++;
    cout << "  j " << string(true_bb->name + 1) << endl;
    just_stored = false;
    return;
}


// 访问jump指令
void Visit(const koopa_raw_jump_t &jump){
    auto name = string(jump.target->name + 1);
    cout << "  j " << name << endl;
    just_stored = false;
    return;
}


// 访问call指令
void Visit(const koopa_raw_call_t &call){
    for(int i = 0; i < call.args.len; ++i){
        koopa_raw_value_t v = (koopa_raw_value_t)call.args.buffer[i];
        int j;
        if(v->kind.tag == KOOPA_RVT_INTEGER){
            j = Visit(v->kind.data.integer);
          if(i < 8){
            string reg = "a" + to_string(i);
            cout << "  li  " << reg <<", " << j << endl;
            just_stored = false;
          } else {
              cout << "  li  " << "t0" <<", " << j << endl;
              just_stored = false;
              _save("t0", "sp", (i-8) * 4);
          }
        }
        else{
            j = stack_addr[v] + A;
            if(i < 8){
            string reg = "a" + to_string(i);
            _load(reg, "sp", j);
          } else {
            _load("t0", "sp", j);
            _save("t0", "sp", (i-8) * 4);
          }
        }
         
    }
    cout << "  call " << call.callee->name + 1 << endl;
    just_stored = false;
  
    return;
}


void Visit(const koopa_raw_get_elem_ptr_t& get_elem_ptr){
   koopa_raw_value_t src = get_elem_ptr.src, index = get_elem_ptr.index;
   size_t sz = getTypeSize(src->ty->data.pointer.base->data.array.base);
   if(src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
        cout << "  la  " << "t0" <<", " << string(src->name + 1) << endl;
        just_stored = false;
    }else if(src->kind.tag == KOOPA_RVT_ALLOC){
        size_t offset = stack_addr[src] + A;
        _addi("t0", "sp", offset);
        just_stored = false;
    } else {
        _load("t0", "sp", stack_addr[src] + A);
    }

    if(index->kind.tag == KOOPA_RVT_INTEGER){
        int j = Visit(index->kind.data.integer);
        cout << "  li  " << "t1" <<", " << j << endl;
        just_stored = false;
    } else {
        _load("t1", "sp", stack_addr[index] + A);
    }
    cout << "  li  " << "t2" <<", " << sz << endl;
    cout << "  mul  t1, t1, t2" << endl;
    cout << "  add  t0, t0, t1" << endl;
    just_stored = false;

}

void Visit(const koopa_raw_get_ptr_t& get_ptr){
   koopa_raw_value_t src = get_ptr.src, index = get_ptr.index;
   //cout<<"here1"<<endl;
   size_t sz = getTypeSize(src->ty->data.pointer.base);
   //cout<<"here2"<<endl;
   if(src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
        cout << "  la  " << "t0" <<", " << string(src->name + 1) << endl;
        just_stored = false;
    }else if(src->kind.tag == KOOPA_RVT_ALLOC){
        size_t offset = stack_addr[src] + A;
        _addi("t0", "sp", offset);
        just_stored = false;
    } else {
        _load("t0", "sp", stack_addr[src] + A);
    }

    if(index->kind.tag == KOOPA_RVT_INTEGER){
        int j = Visit(index->kind.data.integer);
        cout << "  li  " << "t1" <<", " << j << endl;
        just_stored = false;
    } else {
        _load("t1", "sp", stack_addr[index] + A);
    }
    cout << "  li  " << "t2" <<", " << sz << endl;
    cout << "  mul  t1, t1, t2" << endl;
    cout << "  add  t0, t0, t1" << endl;
    just_stored = false;
}



void parse_string(const char* str)
{
    // 解析字符串 str, 得到 Koopa IR 程序
    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(str, &program);
    assert(ret == KOOPA_EC_SUCCESS);  // 确保解析时没有出错
    // 创建一个 raw program builder, 用来构建 raw program
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    // 将 Koopa IR 程序转换为 raw program
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    // 释放 Koopa IR 程序占用的内存
    koopa_delete_program(program);

    // 处理 raw program
    Visit(raw);


    // 处理完成, 释放 raw program builder 占用的内存
    // 注意, raw program 中所有的指针指向的内存均为 raw program builder 的内存
    // 所以不要在 raw program builder 处理完毕之前释放 builder
    koopa_delete_raw_program_builder(builder);

}


// string FirstUnusedReg()
// {
//   string firstTrueKey = "No";
//   for (const auto& pair : reg_available) {
//         if (pair.second) {
//             firstTrueKey = pair.first;
//             break;
//         }
//     }
//   return firstTrueKey;
// }

// 访问全局变量
void VisitGlobalVar(koopa_raw_value_t value){
    cout << "  .data" << endl;
    cout << "  .globl " << value->name + 1 << endl;
    cout << value->name + 1 << ":" << endl;
    koopa_raw_value_t init = value->kind.data.global_alloc.init;
    auto ty = value->ty->data.pointer.base;
    if(ty->tag == KOOPA_RTT_INT32){
        if(init->kind.tag == KOOPA_RVT_ZERO_INIT){
            cout << "  .zero 4" << endl;
        } else {
            int i = Visit(init->kind.data.integer);
            cout << "  .word " << i << endl;
        }
    } else{
        // see aggragate
        if(init->kind.tag == KOOPA_RVT_ZERO_INIT){
            cout << "  .zero " << getTypeSize(ty)  << endl;
        }
        else
          InitGlobalArray(init);
    }
    cout << endl;
    return ;
}

void InitGlobalArray(koopa_raw_value_t init){
    if(init->kind.tag == KOOPA_RVT_INTEGER){
        int i = Visit(init->kind.data.integer);
        cout << "  .word " << i << endl;
    } else {
        // KOOPA_RVT_AGGREGATE
        auto elems = init->kind.data.aggregate.elems;
        for(int i = 0; i < elems.len; ++i){
            InitGlobalArray(reinterpret_cast<koopa_raw_value_t>(elems.buffer[i]));
        }
    }
}


void alloc(const koopa_raw_function_t &func){
    for(size_t i = 0; i < func->bbs.len; ++i){
        auto bb = reinterpret_cast<koopa_raw_basic_block_t>(func->bbs.buffer[i]);
        for(int j = 0; j < bb->insts.len; ++j){
            auto value = reinterpret_cast<koopa_raw_value_t>(bb->insts.buffer[j]);
            if(value->kind.tag == KOOPA_RVT_ALLOC ){
                int width = getTypeSize(value->ty->data.pointer.base);
                stack_addr[value] = S;
                S += width;
                continue;
            }
            if(value->kind.tag == KOOPA_RVT_CALL){
                koopa_raw_call_t c = value->kind.data.call;
                R = 4;
                A = max(A, max(0, ((int)c.args.len - 8 ) * 4));  
            }
            size_t width = getTypeSize(value->ty);
            if(width){
                stack_addr[value] = S;
                S += width;
            }
        }
    }
}   


// 计算类型koopa_raw_type_t的大小
size_t getTypeSize(koopa_raw_type_t ty){
    switch(ty->tag){
        case KOOPA_RTT_INT32:
            return 4;
        case KOOPA_RTT_UNIT:
            return 0;
        case KOOPA_RTT_ARRAY:
            return ty->data.array.len * getTypeSize(ty->data.array.base);
        case KOOPA_RTT_POINTER:
            return 4;
        case KOOPA_RTT_FUNCTION:
            return 0;
    }
    return 0;
}



void _load(string dst, string address, int i)
{
  if(just_stored && store_address == address && store_i == i)
  {
    just_stored = false;
    if(store_src != dst)
      cout << "  mv  " << dst << ", " << store_src << endl;
    return;
  }
  just_stored = false;
  if(i < 2048 && i > -2048)
    cout << "  lw  " << dst << ", " << i << "(" << address << ")" << endl;
  else
  {
    cout << "  li  t3, " << i << endl;
    cout << "  add t3, " << address << ", t3" << endl;
    cout << "  lw  " << dst << ", 0(t3)" << endl;
  }
}

void _save(string src, string address, int delta)
{     
    just_stored = true;
    store_address = address;
    store_i = delta;
    store_src = src;
    if(delta < 2048 && delta > -2048)
      cout << "  sw  " << src << ", " << delta << "(" << address << ")" << endl;
    else
    {
      cout << "  li  t3, " << delta << endl;
      cout << "  add t3, " << address << ", t3" << endl;
      cout << "  sw  " << src << ", 0(t3)" << endl;
    }
}

void _addi(std::string dest, std::string src , int delta)
{
  if(delta > -2048 && delta < 2048)
      cout << "  addi  " << dest << ", " << src << ", " << delta << endl;
    else
    {
      cout << "  li t3, " << delta << endl;
      cout << "  add " << dest << ", " << src << ", t3" << endl;
    }
}

