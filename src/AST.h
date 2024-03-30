#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

static int now = 0;
static int nowdepth = 0;
static bool has_return = true;
static int if_block_num = 0;
static int short_count = 0;
static int while_block_num = 0;
static bool condition_return;
static bool now_func_is_int;
static std::string now_end_name;
static std::string now_entry_name;
static std::unordered_map<std::string, int> const_val;
static std::unordered_map<std::string, short> isvar_val; // 0: const, 1: variable, 2: parameter, 3: const_array, 4: para_array
static std::vector<std::vector<int>> array_size;
static std::unordered_map<std::string, bool> func_is_int;
static std::unordered_map<int, int> depfather;


// 声明
class BaseAST;
class CompUnitAST;
class FuncDefAST;
class FuncTypeAST;
class FuncParamsAST;
class FuncParamAST;
class FuncCallParamsAST;
class BlockAST;
class BlockItemAST;
class DeclAST;
class ConstDeclAST;
class BTypeAST;
class ConstDefAST;
class ConstInitValAST;
class ConstExpAST;
class VarDeclAST;
class VarDefAST;
class ArrayIndexConstExpListAST;
class ArrayIndexExpListAST;
class InitValAST;
class StmtAST;
class LValAST;
class ExpAST;
class UnaryExpAST;
class PrimaryExpAST;
class MultiExpAST;
class AddExpAST;
class RelExpAST;
class EqExpAST;
class LAndExpAST;
class LOrExpAST;


// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;

  //virtual void Dump() const = 0;
};


class CompUnitAST : public BaseAST {
 public:
    // 用智能指针管理对象
    std::vector<std::unique_ptr<FuncDefAST>> func_defs;
    std::vector<std::unique_ptr<DeclAST>> decls;

    void Dump() const;
};

class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BTypeAST> func_type;
  std::string ident;
  std::unique_ptr<BlockAST> block;
  std::unique_ptr<FuncParamsAST> func_params;

  void Dump() const;
};

class FuncParamsAST : public BaseAST {
public:
    std::vector<std::unique_ptr<FuncParamAST>> func_params;
};

class FuncParamAST : public BaseAST {
public:
    bool is_array;
    std::unique_ptr<BTypeAST> btype;
    std::string ident;
    std::vector<std::unique_ptr<ConstExpAST>> const_exps;   // a[][3]
    std::string Dump() const;
};

class BlockAST : public BaseAST {
 public:
  std::vector<std::unique_ptr<BlockItemAST>> block_items;
  int depth;
  int father;
  bool in_condition = false;
  int condition_num;
  void Dump() const;
};

class BlockItemAST : public BaseAST {
public:
    std::string type;
    std::unique_ptr<DeclAST> decl;
    std::unique_ptr<StmtAST> stmt;
    bool in_condition = false;
    int condition_num;
    int depth;
    void Dump() const;
};

class BTypeAST : public BaseAST {
public:
    std::string type;
    void Dump() const;
};

class DeclAST : public BaseAST {
public:
    bool is_const;
    bool is_global = false;
    std::unique_ptr<ConstDeclAST> const_decl;
    std::unique_ptr<VarDeclAST> var_decl;
    int depth;
    void Dump() const;
};

class ConstDeclAST : public BaseAST {
public:
    bool is_global = false;
    std::vector<std::unique_ptr<ConstDefAST>> const_defs;
    std::unique_ptr<BTypeAST> btype;
    int depth;
    void Dump() const;
};


class ConstDefAST : public BaseAST {
public:
    bool is_global = false;
    bool is_array;
    std::string ident;
    std::vector<std::unique_ptr<ConstExpAST>> const_exps; 
    std::unique_ptr<ConstInitValAST> const_init_val;
    int depth;
    void Dump() const;
    //void DumpArray(bool is_global = false) const;
};


class ConstInitValAST : public BaseAST {
public:
    bool is_exp;
    bool is_list;
    std::unique_ptr<ConstExpAST> const_exp;
    std::vector<std::unique_ptr<ConstInitValAST>> inits; 
    void getInitVal(std::string *ptr, const std::vector<int> &len) const;
    int depth;
    int Calc();
};

class ConstExpAST : public BaseAST {
public:
    std::unique_ptr<ExpAST> exp;

    int depth;
    int Calc();
};

class VarDeclAST : public BaseAST {
public:
    bool is_global = false;
    std::vector<std::unique_ptr<VarDefAST>> var_defs;
    std::unique_ptr<BTypeAST> btype;
    int depth;
    void Dump() const;
};

class VarDefAST: public BaseAST {
public:
    bool is_array;
    bool is_global = false;
    std::string ident;
    bool has_value;
    int depth;
    std::vector<std::unique_ptr<ConstExpAST>> const_exps;  
    std::unique_ptr<InitValAST> init_val;  
    void Dump() const;
};

class ArrayIndexConstExpListAST : public BaseAST {
public:
    std::vector<std::unique_ptr<ConstExpAST>> const_exps;
};

class ArrayIndexExpListAST : public BaseAST {
public:
    std::vector<std::unique_ptr<ExpAST>> exps;
};

class InitValAST : public BaseAST{
public:
    bool is_exp;
    bool is_list;
    std::unique_ptr<ExpAST> exp;
    int depth;
    std::vector<std::unique_ptr<InitValAST>> inits;
    std::string Dump() const;
    void getInitVal(std::string *ptr, const std::vector<int> &len, bool is_global = false) const;
    //int Calc();
};


class LValAST : public BaseAST {
public:
    bool is_array;
    bool is_param = false;
    std::string ident;
    int depth;
    std::vector<std::unique_ptr<ExpAST>> exps;   
    std::string Dump() const;   
    int Calc();
};

class LeValAST : public BaseAST {
public:
    bool is_array;
    std::string ident;
    int depth;
    std::vector<std::unique_ptr<ExpAST>> exps;      // exps.size() != 0 implies ARRAY
    //std::string Dump() const;   // 默认返回的是i32而非指针。
};



class StmtAST : public BaseAST {
 public:
    enum TAG {RETURN, ASSIGN, BLOCK, EXP, WHILE, BREAK, CONTINUE, IF};
    TAG tag;
    bool has_exp;
    bool has_else = false;
    bool in_condition = false;
    std::unique_ptr<ExpAST> exp;
    std::unique_ptr<LeValAST> lval;
    std::unique_ptr<BlockAST> block;
    std::unique_ptr<StmtAST> if_stmt;
    std::unique_ptr<StmtAST> else_stmt;
    std::unique_ptr<StmtAST> stmt;
    int depth;
    void Dump() const;
};



class ExpAST : public BaseAST{
  public:
    std::unique_ptr<LOrExpAST> lorexp;
    int depth;
    std::string Dump() const;
    
    int Calc();
};

class UnaryExpAST : public BaseAST{
  public:
    
    bool HasOp;
    std::unique_ptr<UnaryExpAST> unaryexp;
    char unary_op;
    std::unique_ptr<PrimaryExpAST> primaryexp;
    int depth;
    
    bool is_call = false;
    std::string ident;
    std::unique_ptr<FuncCallParamsAST> func_params;

    std::string Dump() const;
    int Calc();
};

class FuncCallParamsAST : public BaseAST {
public:
    std::vector<std::unique_ptr<ExpAST>> exps;
    //std::string Dump() const;
};

class PrimaryExpAST : public BaseAST{
  public:
    std::string type;
    std::unique_ptr<ExpAST> exp;
    int number;
    std::unique_ptr<LValAST> lval;
    int depth;
    
    std::string Dump() const;
    int Calc();
};

class MultiExpAST : public BaseAST{
  public:
    bool HasOp;
    std::unique_ptr<UnaryExpAST> unary_exp;
    std::unique_ptr<MultiExpAST> multi_exp;
    char multi_op;
    int depth;
    std::string Dump() const;
    int Calc();
};

class AddExpAST : public BaseAST {
public:
    bool HasOp;
    std::unique_ptr<MultiExpAST> multi_exp;
    std::unique_ptr<AddExpAST> add_exp;
    char add_op;
    int depth;
    std::string Dump() const;
    int Calc();
};


class EqExpAST : public BaseAST {
public:
    bool HasOp;
    std::unique_ptr<RelExpAST> rel_exp;
    std::unique_ptr<EqExpAST> eq_exp;
    char eq_op[2];
    int depth;
    std::string Dump() const;
    int Calc();
};

class RelExpAST : public BaseAST {
public:
    bool HasOp;
    std::unique_ptr<AddExpAST> add_exp;
    std::unique_ptr<RelExpAST> rel_exp;
    char rel_op[2];     // <,>,<=,>=
    int depth;
    std::string Dump() const;
    int Calc();
};

class LOrExpAST : public BaseAST {
public:
    bool HasOp;
    std::unique_ptr<LAndExpAST> l_and_exp;
    std::unique_ptr<LOrExpAST> l_or_exp;
    int depth;
    std::string Dump() const;
    int Calc();
};

class LAndExpAST : public BaseAST {
public:
    bool HasOp;
    std::unique_ptr<EqExpAST> eq_exp;
    std::unique_ptr<LAndExpAST> l_and_exp;
    int depth;
    std::string Dump() const;
    int Calc();
};

std::string get_array_type(std::vector<int> len, int i);
void store_array(std::string name,  int *init, std::vector<int> len, int* k, int i);