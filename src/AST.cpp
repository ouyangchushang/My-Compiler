#include "AST.h"
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "string.h"
using namespace std;

void CompUnitAST::Dump() const{
  depfather[1] = 0;
  for(auto &d : decls){
      d -> is_global = true;
      d -> Dump();
  }
  func_is_int[std::string("getint")] = true;
  func_is_int[std::string("getch")] = true;
  func_is_int[std::string("getarray")] = true;
  func_is_int[std::string("putint")] = false;
  func_is_int[std::string("putch")] = false;
  func_is_int[std::string("putarray")] = false;
  func_is_int[std::string("starttime")] = false;
  func_is_int[std::string("stoptime")] = false;

  std::cout << "decl @getint(): i32" << std:: endl;
  std::cout << "decl @getch(): i32" << std:: endl;
  std::cout << "decl @getarray(*i32): i32" << std:: endl;
  std::cout << "decl @putint(i32)" << std:: endl;
  std::cout << "decl @putch(i32)" << std:: endl;
  std::cout << "decl @putarray(i32, *i32)" << std:: endl;
  std::cout << "decl @starttime()" << std:: endl;
  std::cout << "decl @stoptime()" << std:: endl;

  int n = func_defs.size();
  for(int i = 0; i < n; ++i)
      func_defs[i]->Dump();
  }

void FuncDefAST::Dump() const {
    func_is_int[ident] = (func_type->type == "int") ? true : false;
    has_return = false;
    now_func_is_int = func_is_int[ident];
    std::vector<std::string> var_names;
    std::vector<std::string> var_types;
    block->father = 0;
    nowdepth++;
    block->depth = nowdepth;
    
    cout << "fun @" << ident << "(";
    if(func_params != nullptr){
        auto &fps = func_params->func_params;
        int n = fps.size();
        for(int i = 0; i < n; ++i){
          if(i > 0)
            cout << ", ";
          std::string paraname = fps[i]->ident + "_" + std::to_string(nowdepth);
          fps[i]->ident = '@'+paraname;
          var_names.push_back(paraname);
          if(!fps[i]->is_array){
            const_val['@'+paraname] = 0;
            isvar_val['@'+paraname] = 2;
          }
          else
          {
            std::vector<int> len;
            len.push_back(-1);
            for(auto &ce: fps[i]->const_exps){
                ce->depth = 0;
                len.push_back(ce->Calc());
            }
            isvar_val['@'+paraname] = 4;
            const_val['@'+paraname] = array_size.size();
            array_size.push_back(len);
          }

          std::string type = fps[i]->Dump();
          var_types.push_back(type);
          cout << "@" << paraname << ": " << type;

        }
    }
    cout << ")";
    if(func_type->type == "int")
      cout << ":";
    cout << " ";
    func_type -> Dump();
    cout << "{ " << endl;
    cout << "\%entry:" << endl;

    int parasize = var_names.size();
    for(int i = 0; i < parasize; i++)
    {
      std::string var = var_names[i];
      std::string store_var = '%' + var;
      std::cout << "  %" << var << " = alloc " << var_types[i] << std::endl;
      std::cout<< "  store @" << var << ", %" << var << std::endl;
    }


    block->Dump();
    if(!has_return)
    { 
      if(func_type->type == "int")
        cout << "  ret 0" << endl;
      else
        cout << "  ret" << endl;
      has_return = true;
    }
    cout << "} " << endl;
  }

string FuncParamAST::Dump() const{
    if(!is_array){
        return "i32";
    }
    string s = "i32";
    assert(isvar_val[ident] == 4);
    vector<int> len = array_size[const_val[ident]];
    for(int i: len)
    {
      if(i == -1)
        continue;
      s = "[" + s + ", " + to_string(i) + "]";
    }
    s = "*" + s;
    return s;
}


void BlockAST::Dump() const{
    int n = block_items.size();
    if(n > 0)
    {
      depfather[nowdepth] = father;
      for(int i = 0; i < n; ++i){
          block_items[i]->depth = depth;
          block_items[i]->in_condition = in_condition;
          block_items[i]->Dump();
      }
    }
  }

void BlockItemAST::Dump() const{
    if(has_return)
      return;
    if(in_condition && condition_return)
      return;
    if(type == "decl"){
        decl->depth = depth;
        decl->Dump();
    } else{
        stmt->in_condition = in_condition;
        stmt->depth = depth;
        stmt->Dump(); 
    }
}

void DeclAST::Dump() const{
    if(is_const)
      {
        const_decl->depth= depth;
        const_decl->is_global = is_global;
        const_decl->Dump();
      }
    else
      {
        var_decl->depth = depth;
        var_decl->is_global = is_global;
        var_decl->Dump();
      }
}

void BTypeAST::Dump() const{
    if(type == "int"){
        cout << "i32 ";
    }

}

void ConstDeclAST::Dump() const{
    int n = const_defs.size();
    for(int i = 0; i < n; ++i){
        const_defs[i]->depth = depth;
        const_defs[i]->is_global = is_global;
        const_defs[i]->ident = '@' + const_defs[i]->ident + "_" + std::to_string(depth);
        const_defs[i]->Dump();
    }
}

string get_array_type(std::vector<int> len, int i)
{
  int n = len.size();
  if(i == n-1)
    return "[i32, " + std::to_string(len[i]) + "]";
  return "[" + get_array_type(len, i+1) + ", " + std::to_string(len[i]) + "]";
}

void store_array(std::string name,  std::string* init, std::vector<int> len, int* k, int i)
{
  int layer_size = len[i];
  for(int j = 0; j < layer_size; j++)
  {
    if(init[*k] == "0" && i == len.size()-1)
    {
      *k = *k+1;
      continue;
    }
    int temp = now;
    now = now + 1;
    std::cout<< "  %" << temp << " = getelemptr "  << name << ", " << j << std::endl;
    string subname = "%" + std::to_string(temp);
    if(i < len.size()-1)
      store_array(subname, init, len, k, i+1);
    else
    {
      cout << "  store " << init[*k] << ", " << subname << endl;
      *k = *k + 1;
    }
  }
   
}


void ConstDefAST::Dump() const{
    if(!is_array){
      isvar_val[ident] = 0;
      const_init_val->depth = depth;
      const_val[ident] = const_init_val->Calc();
      return;
    }
    vector<int> len;
    for(auto &ce : const_exps){
        ce->depth = depth;
        len.push_back(ce->Calc());
    }
    isvar_val[ident] = 3;
    const_init_val->depth = depth;
    const_val[ident] = array_size.size();
    array_size.push_back(len);
    
    string array_type = get_array_type(len, 0);

    vector<int> record_len;
    int tot_len = 1;
    for(int i = len.size()-1; i >= 0; i--)
    {
      tot_len *= len[i];
      record_len.push_back(tot_len);
    }
    std::string* init = new string[tot_len];
    for(int i = 0; i < tot_len; ++i)
        init[i] = "0";

    const_init_val->getInitVal(init, record_len);

    if(is_global){
        string init_val = "";
        bool need_pause = false;
        for(int i = 0; i < tot_len; i++)
        {
          for(int j = 0; j < record_len.size(); j++)
            if(i % record_len[j] == 0)
              init_val = init_val + '{';
          init_val = init_val + init[i];
          if((i+1) % record_len[0])
            init_val = init_val + ", ";
          for(int j = 0; j < record_len.size(); j++)
            if((i+1) % record_len[j] == 0)
            {
              init_val = init_val + '}';
              need_pause = true;
            }
          if(need_pause && i != tot_len-1)
             init_val = init_val + ", ";
          need_pause = false;
        }
        cout << "global " << ident << " = alloc " << array_type << ", " << init_val << endl;

    } else {
        cout << "  " << ident << " = alloc "  << array_type << endl;
        int* k = new int;
        *k = 0;
        store_array(ident, init, len, k, 0);
        delete k;
    }
    return;
}


void VarDeclAST::Dump() const {
    int n = var_defs.size();
    for(int i = 0; i < n; ++i){
        var_defs[i]->depth = depth;
        var_defs[i]->is_global = is_global;
        var_defs[i]->ident = '@' + var_defs[i]->ident + "_" + std::to_string(depth);
        var_defs[i]->Dump();
    }
}


void VarDefAST::Dump() const{
    if(!is_array){
        isvar_val[ident] = 1;
        const_val[ident] = 0;
        if(is_global){
            if(!has_value){
              std::cout << "global " << ident << " = alloc i32, " << "zeroinit" << endl;
          } else {
              int v = init_val->exp->Calc();
              if(has_return)
                const_val[ident] = v;
              std::cout << "global " << ident << " = alloc i32, " << std::to_string(v) << endl;
          }
        }
       else
       {
          std::cout<< "  " << ident << " = alloc i32" << std::endl;
          if(has_value){
              init_val->depth = depth;
              string ret = init_val->Dump();
              std::cout<< "  store " << ret << ", " << ident << std::endl;
          }
       }
       return;
    }
    else
    {
      vector<int> len;
      for(auto &ce : const_exps){
        ce->depth = depth;
        len.push_back(ce->Calc());
    }
    isvar_val[ident] = 3;
    const_val[ident] = array_size.size();
    array_size.push_back(len);
    
    string array_type = get_array_type(len, 0);

    vector<int> record_len;
    int tot_len = 1;
    for(int i = len.size()-1; i >= 0; i--)
    {
      tot_len *= len[i];
      record_len.push_back(tot_len);
    }
    std::string* init = new string[tot_len];
    for(int i = 0; i < tot_len; ++i)
        init[i] = "0";

    if(has_value)
      {
        init_val->depth = depth;
        init_val->getInitVal(init, record_len, is_global);
      }


    if(is_global){
        if(!has_value || init_val->inits.size() == 0){
          std::cout << "global " << ident << " = alloc " << array_type << ", " << "zeroinit" << endl;
        }
        else{
        string init_val = "";
        bool need_pause = false;
        for(int i = 0; i < tot_len; i++)
        {
          for(int j = 0; j < record_len.size(); j++)
            if(i % record_len[j] == 0)
              init_val = init_val + '{';
          init_val = init_val + init[i];
          if((i+1) % record_len[0])
            init_val = init_val + ", ";
          for(int j = 0; j < record_len.size(); j++)
            if((i+1) % record_len[j] == 0)
            {
              init_val = init_val + '}';
              need_pause = true;
            }
          if(need_pause && i != tot_len-1)
             init_val = init_val + ", ";
          need_pause = false;
        }
        cout << "global " << ident << " = alloc " << array_type << ", " << init_val << endl;
      }
    } else {
        cout << "  " << ident << " = alloc "  << array_type << endl;
        if(init_val == nullptr) 
            return;
        int* k = new int;
        *k = 0;
        store_array(ident, init, len, k, 0);
        delete k;
    }
    return;
    }
}

void InitValAST::getInitVal(std::string* ptr, const std::vector<int> &record, bool is_global) const{
    int n = record.size();
   
    int next = 0; 

    for(auto &init_val : inits){
      init_val->depth = depth;
        if(init_val->is_exp){
            if(is_global){
                ptr[next] = to_string(init_val->exp->Calc());
                next++;
            } else{
                ptr[next] = init_val->Dump();
                next++;
            }
        } else {
            int j = 1;
            int deltaw = record[n-2];
            if(next != 0){
              for(j = 0; j <= n-1; ++j){
                  if(next % record[j] != 0)
                      break;
              }
              j--;
              deltaw = record[j];
            }
            //cout<<"here " << j<<' '<< next << endl;
            init_val->getInitVal(ptr + next, vector<int>(record.begin(), record.end()-j));
            next += deltaw;
        }
        if(next >= record[n-1]) break;
    }
}

string InitValAST::Dump() const{
    if(is_exp)
    {
      exp->depth = depth;
      return exp->Dump();
    }
    return "";
}


string LValAST::Dump() const{
  if(!is_param && (!isvar_val[ident] || has_return))
      return std::to_string(const_val[ident]);
  int temp;
  std::string name = ident;
  std::string find_name = name;
  if(is_array && is_param)
  {
    find_name = '@' + find_name.erase(0,1);
  }
  if(isvar_val[ident] == 3 || (is_array && is_param))
  {
    vector<string> index;

    for(auto &e: exps){
        e->depth = depth;
        index.push_back(e->Dump());
    }

    int k = const_val[find_name];
    vector<int> len = array_size[k];
    int n = index.size();

    bool is_para = (len[0] == -1);
    bool is_array_callee = (len.size() != n);
    for(int i = 0; i < n; i++)
    {
      if(i == 0 && is_para)
      {
        temp = now;
        now = now + 1;
        std::cout<< "  %" << temp << " = load "  << name  <<std::endl;
        name = "%" + std::to_string(temp);
      }
      temp = now;
      now = now + 1;
      if(i == 0 && !is_array_callee && is_para)
        std::cout<< "  %" << temp << " = getptr "  << name << ", " << index[i] <<std::endl;
      else if(i == n - 1 && is_array_callee && is_para)
        {std::cout<< "  %" << temp << " = getptr "  << name << ", " << index[i] <<std::endl;
        temp = now;
        now = now + 1;
        std::cout<< "  %" << temp << " = getelemptr "  << "%" << temp - 1 << ", 0" <<std::endl;
        return "%" + std::to_string(temp);}
      else
        std::cout<< "  %" << temp << " = getelemptr "  << name << ", " << index[i] <<std::endl;
      name = "%" + std::to_string(temp);
    }
    if(is_array_callee && !is_para)
    {
      temp = now;
      now = now + 1;
      std::cout<< "  %" << temp << " = getelemptr "  << name << ", " << 0 <<std::endl;
      return "%" + std::to_string(temp);
    }
  }
  
   temp = now;
   now = now + 1;
   std::cout<< "  %" << temp << " = load "  << name <<std::endl;
   return "%" + std::to_string(temp);
}



void StmtAST::Dump() const{
    if(tag == StmtAST::RETURN)
      { 
        if(has_exp)
        {
          exp->depth = depth;
          std::string b = exp -> Dump();
          cout << "  ret " << b << endl;
        }
        else
        {
          if(now_func_is_int)
            cout << "  ret 0" << endl;
          else
            cout << "  ret" << endl;
        }
        if(in_condition)
          condition_return = true;
        else        
          has_return = true;
      // int res = exp->Calc();
      }
    else if (tag == StmtAST::ASSIGN)
    {
      exp->depth = depth;
      std::string b = exp -> Dump();
      int tempdep = depth;
      while(isvar_val.find('@' + lval->ident+"_"+std::to_string(tempdep))==isvar_val.end() && tempdep > 0)tempdep=depfather[tempdep];

      if(isvar_val['@' + lval->ident+"_"+std::to_string(tempdep)] == 2 )
        std::cout<< "  store " << b << ", " << '%' + lval->ident + "_" + std::to_string(tempdep) << std::endl;
      else if(isvar_val['@' + lval->ident+"_"+std::to_string(tempdep)] == 3)
      {
          vector<string> index;
          lval->ident = '@' + lval->ident+"_"+std::to_string(tempdep);
          for(auto &e: lval->exps){
              e->depth = depth;
              index.push_back(e->Dump());
          }

          int k = const_val[lval->ident];
          vector<int> len = array_size[k];
          int temp;
          string name = lval->ident;

          assert(index.size() == len.size());
          for(int i = 0; i < index.size(); i++)
          {
            temp = now;
            now = now + 1;
            std::cout<< "  %" << temp << " = getelemptr "  << name << ", " << index[i] <<std::endl;
            name = "%" + std::to_string(temp);
          }
          std::cout<< "  store " << b << ", " << name << std::endl;
      }
      else if(isvar_val['@' + lval->ident+"_"+std::to_string(tempdep)] == 4)
      {
          vector<string> index;
          lval->ident = '%' + lval->ident+"_"+std::to_string(tempdep);
          for(auto &e: lval->exps){
              e->depth = depth;
              index.push_back(e->Dump());
          }

          int k = const_val[lval->ident];
          vector<int> len = array_size[k];
          int temp;
          string name = lval->ident;
          if(index.size()>0)
          {
            temp = now;
            now = now + 1;
            std::cout<< "  %" << temp << " = load "  << name  <<std::endl;
            name = "%" + std::to_string(temp);
            temp = now;
            now = now + 1;
            std::cout<< "  %" << temp << " = getptr "  << name << ", " << index[0] <<std::endl;
            name = "%" + std::to_string(temp);
          }
          
          for(int i = 1; i < index.size(); i++)
          {
            temp = now;
            now = now + 1;
            std::cout<< "  %" << temp << " = getelemptr "  << name << ", " << index[i] <<std::endl;
            name = "%" + std::to_string(temp);
          }
          std::cout<< "  store " << b << ", " << name << std::endl;
      }
      else
        std::cout<< "  store " << b << ", " << '@' + lval->ident + "_" + std::to_string(tempdep) << std::endl;
    }
    else if(tag == StmtAST::BLOCK){
      block->father = depth;
      nowdepth++;
      block->depth = nowdepth;
      block->in_condition = in_condition;
      block->Dump();
    }
    else if(tag == StmtAST::IF){
      exp->depth = depth;
      std::string b = exp -> Dump();
      if(has_else){
        if_stmt -> depth = depth;
        else_stmt -> depth = depth;
        if_stmt -> in_condition = true;
        else_stmt -> in_condition = true;
        int num = if_block_num++;
        std::string then_name = std::string("if_then") + std::to_string(num);
        std::string else_name = std::string("if_else") + std::to_string(num);
        std::string end_name = std::string("if_end") + std::to_string(num);
        std::cout << "  br " << b << ", \%" << then_name << ", \%" << else_name << std::endl;
        std::cout << "\%" << then_name << ":" << std::endl;
        if_stmt -> Dump();
        if(!condition_return)
          std::cout << "  jump \%" << end_name << std::endl;
        else
          condition_return = false;
        std::cout << "\%" << else_name << ":" << std::endl;
        else_stmt -> Dump();
        if(!condition_return)
          std::cout << "  jump \%" << end_name << std::endl;
        else
          condition_return = false;
        std::cout << "\%" << end_name << ":" << std::endl;
      }
      else{
        if_stmt -> depth = depth;
        if_stmt -> in_condition = true;
        int num = if_block_num++;
        std::string then_name = std::string("if_then") + std::to_string(num);
        std::string else_name = std::string("if_else") + std::to_string(num);
        std::string end_name = std::string("if_end") + std::to_string(num);
        std::cout << "  br " << b << ", \%" << then_name << ", \%" << end_name << std::endl;
        std::cout << "\%" << then_name << ":" << std::endl;
        if_stmt -> Dump();
        if(!condition_return)
          std::cout << "  jump \%" << end_name << std::endl;
        else
          condition_return = false;
        std::cout << "\%" << end_name << ":" << std::endl;
      }
    }
    else if(tag == StmtAST::WHILE){
      int num = while_block_num++;
      stmt -> in_condition = true;
      stmt -> depth = depth;
      exp -> depth = depth;
      std::string entry_name = std::string("while_entry") + std::to_string(num);
      std::string body_name = std::string("while_body") + std::to_string(num);
      std::string end_name = std::string("while_end") + std::to_string(num);
      std::cout << "  jump \%" << entry_name << std::endl;
      std::cout << "\%" << entry_name << ":" << std::endl;
      std::string cond = exp -> Dump();
      std::cout << "  br " << cond << ", \%" << body_name << ", \%" << end_name << std::endl;
      std::cout << "\%" << body_name << ":" << std::endl;
      std::string save_end_name = now_end_name;
      std::string save_entry_name = now_entry_name;
      now_end_name = end_name;
      now_entry_name = entry_name;
      stmt->Dump();
      now_entry_name = save_entry_name;
      now_end_name = save_end_name;
      if(!condition_return)
          std::cout << "  jump \%" << entry_name << std::endl;
      else
          condition_return = false;
      std::cout << "\%" << end_name << ":" << std::endl;
    }
    else if(tag == StmtAST::BREAK){
      if(!in_condition)
        return;
      std::cout << "  jump \%" << now_end_name << std::endl;
      condition_return = true;
    } 
    else if(tag == StmtAST::CONTINUE){
      if(!in_condition)
        return;
      std::cout << "  jump \%" << now_entry_name << std::endl;
      condition_return = true;
    }
    else if(tag == StmtAST::EXP)
    {
      if(has_exp){
      exp -> depth = depth;
      exp->Dump();
      }
    }
  }

string ExpAST::Dump() const{
    lorexp->depth = depth;
    return lorexp -> Dump();
  }

string UnaryExpAST::Dump() const{
    if(is_call)
    {
      if(func_is_int[ident])
      {
        int temp = now;
        now = now + 1;
        vector<string> par;
        if(func_params){
            int n = func_params->exps.size();
            for(int i = 0; i < n; ++i){
                func_params->exps[i]->depth = depth;
                par.push_back(func_params->exps[i]->Dump());
            }
        }
        cout << "  %" << temp << " = " << "call @" << ident << "(";
        int k = par.size();
        for(int i = 0; i < k; i++)
        {
          if(i>0)
            cout << ", ";
          cout << par[i];
        }
        cout << ")" << endl;
        return "%" + std::to_string(temp);
      }
      else
      {
        vector<string> par;
        if(func_params){
            int n = func_params->exps.size();
            for(int i = 0; i < n; ++i){
                func_params->exps[i]->depth = depth;
                par.push_back(func_params->exps[i]->Dump());
            }
        }
        cout << "  call @" << ident << "(";
        int k = par.size();
        for(int i = 0; i < k; i++)
        {
          if(i>0)
            cout << ", ";
          cout << par[i];
        }
        cout << ")" << endl;
        return "";
      }
    }
    if(HasOp)
    {
      unaryexp->depth = depth;
      std::string b = unaryexp->Dump();
      if(unary_op == '+')
        return b;
      else if(unary_op == '-')
      {
        std::string op = "sub";
        int temp = now;
        now = now + 1;
        cout << "  %" << temp << " = " << op << " 0, " << b << endl;
        std::string reg = "%" + std::to_string(temp);
        return reg;
      }
      else if(unary_op == '!')
      {
        std::string op = "eq";
        int temp = now;
        now = now + 1;
        cout << "  %" << temp << " = " << op << ' ' <<  b << ", 0"<< endl;
        std::string reg = "%" + std::to_string(temp);
        return reg;
      }
    }
      primaryexp->depth = depth;
      string b = primaryexp->Dump();
      return b;
  }




string PrimaryExpAST::Dump() const
    {
      if(type == "number")
      {
        return std::to_string(number);
      }
      else if(type == "exp")
      {
        exp->depth = depth;
        return exp->Dump();
      }
      else
      {
        lval->depth = depth;
        int tempdep = depth;
        while(isvar_val.find('@' + lval->ident+"_"+std::to_string(tempdep))==isvar_val.end() && tempdep > 0)tempdep=depfather[tempdep];
        if(isvar_val['@' + lval->ident+"_"+std::to_string(tempdep)] == 2 || isvar_val['@' + lval->ident+"_"+std::to_string(tempdep)] == 4)
        { lval->is_param = true;
          lval->ident = '%' + lval->ident+"_"+std::to_string(tempdep);}
        else
          lval->ident = '@' + lval->ident+"_"+std::to_string(tempdep);
        return lval->Dump();
      }
      return "";
    }


string MultiExpAST::Dump() const {
  if(HasOp)
  {
    multi_exp->depth = depth;
    unary_exp->depth = depth;
    string a = multi_exp->Dump();
    string b = unary_exp->Dump();
    int temp = now;
    now = now + 1;
    string op = multi_op == '*' ? "mul" : (multi_op == '/' ? "div" : "mod");
    cout << "  %" << temp << " = " << op << ' ' <<  a << ", " << b << endl;
    std::string reg = "%" + std::to_string(temp);
    return reg;
  }
  else
  {
    unary_exp->depth = depth;
    return unary_exp->Dump();
  }
}

string AddExpAST::Dump() const {
  if(HasOp)
  {
    add_exp->depth = depth;
    multi_exp->depth = depth;
    string a = add_exp->Dump();
    string b = multi_exp->Dump();
    int temp = now;
    now = now + 1;
    string op = add_op == '+' ? "add" : "sub";
    cout << "  %" << temp << " = " << op << ' ' <<  a << ", " << b << endl;
    std::string reg = "%" + std::to_string(temp);
    return reg;
  }
  else
  {
    multi_exp->depth = depth;
    return multi_exp->Dump();
  }
}

string RelExpAST::Dump() const {
    add_exp->depth = depth;
    if(!HasOp) return add_exp->Dump();
    rel_exp->depth = depth;
    string a = rel_exp->Dump(), b = add_exp->Dump();
    string op = rel_op[1] == '=' ? (rel_op[0] == '<' ? "le" : "ge") : (rel_op[0] == '<' ? "lt" : "gt");
    int temp = now;
    now = now + 1;
    cout << "  %" << temp << " = " << op << ' ' <<  a << ", " << b << endl;
    std::string reg = "%" + std::to_string(temp);
    return reg;
}

string EqExpAST::Dump() const {
    rel_exp->depth = depth;
    if(!HasOp) return rel_exp->Dump();
    eq_exp->depth = depth;
    string a = eq_exp->Dump(), b =rel_exp->Dump();
    string op = eq_op[0] == '=' ? "eq" : "ne";
    int temp = now;
    now = now + 1;
    cout << "  %" << temp << " = " << op << ' ' <<  a << ", " << b << endl;
    std::string reg = "%" + std::to_string(temp);
    return reg;
}

string LAndExpAST::Dump() const {
    eq_exp->depth = depth;
    if(!HasOp) return eq_exp->Dump();

    // 短路
    std::string ident = std::string("@temp") + std::to_string(short_count);
    short_count++;
    std::cout<< "  " << ident << " = alloc i32" << std::endl;
    isvar_val[ident] = 1;
    const_val[ident] = 0;
    std::cout<< "  store " << 0 << ", " << ident << std::endl;

    l_and_exp->depth = depth;
    string a = l_and_exp->Dump();
    int temp_a = now;
    now = now + 1;
    cout << "  %" << temp_a << " = " << "ne" << ' ' <<  a << ", 0" << endl;
    
    int num = if_block_num++;
    std::string then_name = std::string("then") + "_" + std::to_string(num);
    std::string end_name = std::string("end") + "_" + std::to_string(num);
    std::cout << "  br %" << temp_a << ", %" << then_name << ", %" << end_name << std::endl;
    std::cout << "%" << then_name << ":" << std::endl;

    string b = eq_exp->Dump();
    int temp_b = now;
    now = now + 1;
    cout << "  %" << temp_b << " = " << "ne" << ' ' <<  b << ", 0" << endl;

    int temp_c = now;
    now = now + 1;
    cout << "  %" << temp_c << " = " << "and" << " %" <<  temp_a << ", %" << temp_b << endl;
    std::cout << "  store " << "%" << temp_c << ", " << ident << std::endl;
    std::cout << "  jump \%" << end_name << std::endl;
    
    std::cout << "%" << end_name << ":" << std::endl;
    int temp_d = now;
    now = now + 1;
    std::cout<< "  %" << temp_d << " = load " << ident <<std::endl;

    std::string reg = "%" + std::to_string(temp_d);
    return reg;
}

string LOrExpAST::Dump() const {
    l_and_exp->depth = depth;
    if(!HasOp) return l_and_exp->Dump();

    // 短路
    std::string ident = std::string("@temp") + std::to_string(short_count);
    short_count++;
    std::cout<< "  " << ident << " = alloc i32" << std::endl;
    isvar_val[ident] = 1;
    const_val[ident] = 0;
    std::cout<< "  store " << 1 << ", " << ident << std::endl;
    
    l_or_exp->depth = depth;
    string a = l_or_exp->Dump();
    int temp_a = now;
    now = now + 1;
    cout << "  %" << temp_a << " = " << "ne" << ' ' <<  a << ", 0" << endl;

    int num = if_block_num++;
    std::string then_name = std::string("then") + "_" + std::to_string(num);
    std::string end_name = std::string("end") + "_" + std::to_string(num);
    std::cout << "  br %" << temp_a << ", %" << end_name << ", %" << then_name << std::endl;
    std::cout << "%" << then_name << ":" << std::endl;

    string b = l_and_exp->Dump();
    int temp_b = now;
    now = now + 1;
    cout << "  %" << temp_b << " = " << "ne" << ' ' <<  b << ", 0" << endl;

    int temp_c = now;
    now = now + 1;
    cout << "  %" << temp_c << " = " << "or" << " %" <<  temp_a << ", %" << temp_b << endl;
    std::cout << "  store " << "%" << temp_c << ", " << ident << std::endl;
    std::cout << "  jump \%" << end_name << std::endl;
    
    std::cout << "%" << end_name << ":" << std::endl;
    int temp_d = now;
    now = now + 1;
    std::cout<< "  %" << temp_d << " = load " << ident <<std::endl;
    std::string reg = "%" + std::to_string(temp_d);
    return reg;
}


int LOrExpAST::Calc(){
  l_and_exp->depth = depth;
  if(!HasOp) return l_and_exp->Calc();
  l_or_exp->depth = depth;
  int a = l_and_exp->Calc();
  int b = l_or_exp->Calc();
  return a || b;
}

int LAndExpAST::Calc(){
    eq_exp->depth = depth;;
    if(!HasOp) return eq_exp->Calc();
    l_and_exp->depth = depth;
    int a = l_and_exp->Calc();
    int b = eq_exp->Calc();
    return a && b; 
}

int RelExpAST::Calc(){
  add_exp->depth = depth;
  if(!HasOp) return add_exp->Calc();
  rel_exp->depth = depth;
  int a = rel_exp->Calc(), b = add_exp->Calc();
  if(rel_op[1] == '='){
      return rel_op[0] == '>' ? (a >= b) : (a <= b);
  }
  return rel_op[0] == '>' ? (a > b) : (a < b);
}

int EqExpAST::Calc(){
    rel_exp->depth = depth;
    if(!HasOp) return rel_exp->Calc();
    eq_exp->depth = depth;
    int a = eq_exp->Calc(), b = rel_exp->Calc();
    return eq_op[0] == '=' ? (a == b) : (a != b);
}

int AddExpAST::Calc(){
    multi_exp->depth = depth;
  
    if(!HasOp) return multi_exp->Calc();
    add_exp->depth = depth;
    int a = add_exp->Calc(), b = multi_exp->Calc();
    return add_op == '+' ? a + b : a - b;
}

int MultiExpAST::Calc(){
    unary_exp->depth = depth;
  
    if(!HasOp) return unary_exp->Calc();
    multi_exp->depth = depth;
    int a = multi_exp->Calc(), b = unary_exp->Calc();

    return multi_op == '*' ? a * b : (multi_op == '/' ? a / b : a % b);
}

int UnaryExpAST::Calc(){
    if(!HasOp) 
    {
      primaryexp->depth = depth;
      return primaryexp->Calc();
    }
    unaryexp->depth = depth;
    int v =unaryexp->Calc();
    if(unary_op == '+') return v;
    return unary_op == '-' ? -v : !v;
}

int PrimaryExpAST::Calc(){
  
  if(type == "number") {return number;}
  else if(type == "exp") {exp->depth = depth; return exp->Calc();}
  else {
  int tempdep = depth;
  while(isvar_val.find('@' + lval->ident+"_"+std::to_string(tempdep))==isvar_val.end() && tempdep > 0)tempdep=depfather[tempdep];
  lval->ident = '@' + lval->ident+"_"+std::to_string(tempdep);
  lval->depth = depth; 
  return lval->Calc();
  }
}

int ExpAST::Calc(){
  lorexp->depth = depth;
  return lorexp->Calc();
}

int ConstInitValAST::Calc()
{
  const_exp->depth = depth;
  return const_exp->Calc();
}

int ConstExpAST::Calc()
{
  exp->depth = depth;
  return exp->Calc();
}

int LValAST::Calc()
{
  if(!isvar_val[ident] || has_return)
    return const_val[ident];
  else
    return 0;
}


void ConstInitValAST::getInitVal(std::string*ptr, const std::vector<int> &record) const {
    int n = record.size();
    
    int next = 0; 
    for(auto &init_val : inits){
        init_val->depth = depth;
        if(init_val->is_exp){
            ptr[next] = to_string(init_val->Calc());
            next++;
        } else {
            int j = 0;
            int deltaw = record[n-2];
            if(next != 0){
              for(; j <= n-1; ++j){
                  if(next % record[j] != 0)
                      break;
              }
              j--;
              deltaw = record[j];
            }
            init_val->getInitVal(ptr + next, vector<int>(record.begin(), record.end()-j));
            next += deltaw;
        }
        if(next >= record[n-1]) break;
    }
}


