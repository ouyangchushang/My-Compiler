%code requires {
  #include <memory>
  #include <string>
  #include "AST.h"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "AST.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

using namespace std;

%}

// 定义 parser 函数和错误处理函数的附加参数

%parse-param { std::unique_ptr<BaseAST> &ast }

// yylval 的定义, 我们把它定义成了一个联合体 (union)
%union {
  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
  char char_val;
}

// lexer 返回的所有 token 种类的声明
%token INT VOID RETURN LESS_EQ GREAT_EQ EQUAL NOT_EQUAL AND OR CONST IF ELSE WHILE BREAK CONTINUE
%token <str_val> IDENT
%token <int_val> INT_CONST

// 非终结符的类型定义
%type <ast_val> FuncDef FuncParams FuncParam Block Stmt Exp PrimaryExp UnaryExp MultiExp AddExp RelExp EqExp LAndExp LOrExp Decl ConstDecl BType ConstDef ConstInitVal ConstInitValList BlockItem LVal LeVal ConstExp BlockItemList ConstDefList VarDefList VarDef VarDecl InitVal InitValList MatchedStmt OpenStmt GlobalFuncVarList GlobalFuncVar FuncCallParams ArrayIndexConstExpList ArrayIndexExpList
%type <int_val> Number 
%type <char_val> UnaryOp BinaryAddOp BinaryMultiOp BinaryRelOp

%%

CompUnit
  : GlobalFuncVarList {
    auto comp_unit = unique_ptr<CompUnitAST>((CompUnitAST *)$1);
    ast = move(comp_unit);
  }
  ;

GlobalFuncVarList
  : GlobalFuncVar {
    $$ = $1;
  } 
  ;

GlobalFuncVarList
  : GlobalFuncVar GlobalFuncVarList{
    auto comp_unit = new CompUnitAST();
    auto comp1 = unique_ptr<CompUnitAST>((CompUnitAST *)$1);
    auto comp2 = unique_ptr<CompUnitAST>((CompUnitAST *)$2);
    for(auto &f : comp1->func_defs){
        comp_unit->func_defs.emplace_back(f.release());
    }
    for(auto &f : comp2->func_defs){
        comp_unit->func_defs.emplace_back(f.release());
    }
    for(auto &d : comp1->decls){
        comp_unit->decls.emplace_back(d.release());
    }
    for(auto &d : comp2->decls){
        comp_unit->decls.emplace_back(d.release());
    }
    $$ = comp_unit;
  } 
  ;

GlobalFuncVar
  : Decl {
    auto comp_unit = new CompUnitAST();
    comp_unit->decls.emplace_back((DeclAST *)$1);
    $$ = comp_unit;
  }
  ;

GlobalFuncVar
  : FuncDef {
    auto comp_unit = new CompUnitAST();
    comp_unit->func_defs.emplace_back((FuncDefAST *)$1);
    $$ = comp_unit;
  } 
  ;
  

FuncDef
  : BType IDENT '(' FuncParams ')' Block {
    auto func_def = new FuncDefAST();
    func_def->func_type = unique_ptr<BTypeAST>((BTypeAST *)$1);
    func_def->ident = *unique_ptr<string>($2);
    func_def->func_params = unique_ptr<FuncParamsAST>((FuncParamsAST *)$4);
    func_def->block = unique_ptr<BlockAST>((BlockAST *)$6);
    $$ = func_def;
  }
  ;

FuncParams
  : {
    auto funcparam = new FuncParamsAST();
    $$ = funcparam;
  }
  ;

FuncParams
  : FuncParam {
    auto func_params = new FuncParamsAST();
    func_params->func_params.emplace_back((FuncParamAST *)$1);
    $$ = func_params;
  }
  ;

FuncParams
  : FuncParam ',' FuncParams {
    auto func_params_ast = new FuncParamsAST();
    func_params_ast->func_params.emplace_back((FuncParamAST *)$1);
    auto params = unique_ptr<FuncParamsAST>((FuncParamsAST *)($3));
    int n = params->func_params.size();
    for(int i = 0; i < n; ++i){
        func_params_ast->func_params.emplace_back(params->func_params[i].release());
    }
    $$ = func_params_ast;
  }
  ;

FuncParam
  : BType IDENT {
    auto func_param = new FuncParamAST();
    func_param->is_array = false;
    func_param->btype.reset((BTypeAST *)$1);
    func_param->ident = *unique_ptr<string>($2);
    $$ = func_param;
  } | BType IDENT '[' ']' {
    auto func_param = new FuncParamAST();
    func_param->is_array = true;
    func_param->btype.reset((BTypeAST *)$1);
    func_param->ident = *unique_ptr<string>($2);
    $$ = func_param;
  } | BType IDENT '[' ']' ArrayIndexConstExpList {
    auto func_param = new FuncParamAST();
    func_param->is_array = true;
    func_param->btype.reset((BTypeAST *)$1);
    func_param->ident = *unique_ptr<string>($2);
    unique_ptr<ArrayIndexConstExpListAST> p((ArrayIndexConstExpListAST *)$5);
    for(auto &ce : p->const_exps){
        func_param->const_exps.emplace_back(ce.release());
    }
    $$ = func_param;
  }
  ;

BType
  : INT {
    auto type_ast = new BTypeAST();
    type_ast->type = "int";
    $$ = type_ast;
  }
  ; 

BType
  : VOID {
    auto type_ast = new BTypeAST();
    type_ast->type = "void";
    $$ = type_ast;
  }
  ;

Block
  : '{' BlockItemList '}' {
    $$ = $2;
  }
  ;

BlockItemList
  :  {
    auto block = new BlockAST();
    $$ = block;
  }
  ;

BlockItemList
  : BlockItem BlockItemList {
    auto block = new BlockAST();
    auto block_lst = unique_ptr<BlockAST>((BlockAST *)$2);
    block->block_items.emplace_back((BlockItemAST *)$1);
    int n = block_lst->block_items.size();
    for(int i = 0; i < n; ++i){
        block->block_items.emplace_back(block_lst->block_items[i].release());
    }
    $$ = block;
  }
  ;
       
BlockItem
  : Decl {
    auto block_item = new BlockItemAST();
    block_item->type = "decl";
    block_item->decl = unique_ptr<DeclAST>((DeclAST *)$1);
    $$ = block_item;
  }
  ;



BlockItem
  : Stmt {
    auto block_item = new BlockItemAST();
    block_item->type = "stmt";
    block_item->stmt = unique_ptr<StmtAST>((StmtAST *)$1);
    $$ = block_item;
  }
  ;

Decl 
  : ConstDecl {
    auto decl = new DeclAST();
    decl->is_const = true;
    decl->const_decl = unique_ptr<ConstDeclAST>((ConstDeclAST *)$1);
    $$ = decl;
  }
  ;

ConstDecl
  : CONST BType ConstDefList ';'{
    auto const_decl = (ConstDeclAST *)$3;
    const_decl->btype = unique_ptr<BTypeAST>((BTypeAST *)$2);
    $$ = const_decl;
  }
  ;

ConstDefList
  : ConstDef {
    auto const_decl = new ConstDeclAST();
    const_decl->const_defs.emplace_back((ConstDefAST *)$1);
    $$ = const_decl;
  }
  ;

ConstDefList
  : ConstDef ',' ConstDefList {
    auto const_decl = new ConstDeclAST();
    auto const_decl_2 = unique_ptr<ConstDeclAST>((ConstDeclAST *)$3);
    const_decl->const_defs.emplace_back((ConstDefAST *)$1);
    int n = const_decl_2->const_defs.size();
    for(int i = 0; i < n; ++i){
        const_decl->const_defs.emplace_back(const_decl_2->const_defs[i].release());
    }
    $$ = const_decl;
  }
  ;


ConstDef
  : IDENT '=' ConstInitVal {
    auto const_def = new ConstDefAST();
    const_def->is_array = false;
    const_def->ident = *unique_ptr<string>($1);
    const_def->const_init_val = unique_ptr<ConstInitValAST>((ConstInitValAST *)$3);
    $$ = const_def;
  }
  ;

ConstDef
  : IDENT ArrayIndexConstExpList '=' ConstInitVal {
    auto const_def = new ConstDefAST();
    unique_ptr<ArrayIndexConstExpListAST> p( (ArrayIndexConstExpListAST *)$2);
    const_def->is_array = true;
    const_def->ident = *unique_ptr<string>($1);
    for(auto &ce : p->const_exps){
        const_def->const_exps.emplace_back(ce.release());
    }
    const_def->const_init_val = unique_ptr<ConstInitValAST>((ConstInitValAST *)$4);
    $$ = const_def;
  }
  ;

ConstInitVal
  : ConstExp {
    auto const_init_val = new ConstInitValAST();
    const_init_val->is_exp = true;
    const_init_val->is_list = false;
    const_init_val->const_exp = unique_ptr<ConstExpAST>((ConstExpAST *)$1);
    $$ = const_init_val;
  } |'{' '}' {
    auto const_init_val = new ConstInitValAST();
    const_init_val->is_exp = false;
    const_init_val->is_list = true;
    $$ = const_init_val;
  } | '{' ConstInitValList '}' {
    $$ = $2;
  }
  ;

ConstInitValList
  : ConstInitVal {
    auto init_val = new ConstInitValAST();
    init_val->is_list = true;
    init_val->inits.emplace_back((ConstInitValAST *)$1);
    $$ = init_val;
  } | ConstInitValList ',' ConstInitVal {
    auto init_val = (ConstInitValAST *)$1;
    init_val->inits.emplace_back((ConstInitValAST *)$3);
    $$ = init_val;
  }
  ;


ConstExp
  : Exp {
    auto const_exp = new ConstExpAST();
    const_exp->exp = unique_ptr<ExpAST>((ExpAST *)$1);
    $$ = const_exp;
  }
  ;

ArrayIndexConstExpList
  : '[' ConstExp ']' {
    auto p = new ArrayIndexConstExpListAST();
    p->const_exps.emplace_back((ConstExpAST *)$2);
    $$ = p;
  } 
  ;
  
ArrayIndexConstExpList
  : ArrayIndexConstExpList '[' ConstExp ']' {
    auto p = (ArrayIndexConstExpListAST *)$1;
    p->const_exps.emplace_back((ConstExpAST *)$3);
    $$ = p;
  }
  ;

ArrayIndexExpList
  : '[' Exp ']' {
    auto p = new ArrayIndexExpListAST();
    p->exps.emplace_back((ExpAST *)$2);
    $$ = p;
  } 
  ;

ArrayIndexExpList
  : ArrayIndexExpList '[' Exp ']' {
    auto p = (ArrayIndexExpListAST *)$1;
    p->exps.emplace_back((ExpAST *)$3);
    $$ = p;
  }
  ;


Decl 
  : VarDecl {
    auto decl = new DeclAST();
    decl->is_const = false;
    decl->var_decl = unique_ptr<VarDeclAST>((VarDeclAST *)$1);
    $$ = decl;
  }
  ;

VarDecl
  : BType VarDefList ';' {
    auto var_decl = (VarDeclAST *)$2;
    var_decl->btype = unique_ptr<BTypeAST>((BTypeAST *) $1);
    $$ = var_decl;
  }
  ;

VarDefList
  : VarDef ',' VarDefList {
    auto var_decl = new VarDeclAST();
    auto var_decl_2 = unique_ptr<VarDeclAST>((VarDeclAST *)$3);
    var_decl->var_defs.emplace_back((VarDefAST *)$1);
    int n = var_decl_2->var_defs.size();
    for(int i = 0; i < n; ++i){
        var_decl->var_defs.emplace_back(var_decl_2->var_defs[i].release());
    }
    $$ = var_decl;
  }
  ;

VarDefList
  : VarDef {
    auto var_decl = new VarDeclAST();
    var_decl->var_defs.emplace_back((VarDefAST *)$1);
    $$ = var_decl;
  }
  ;

VarDef
  : IDENT {
    auto var_def = new VarDefAST();
    var_def->is_array = false;
    var_def->ident = *unique_ptr<string>($1);
    var_def->has_value = false;
    $$ = var_def;
  } 
  ;

VarDef
  : IDENT '=' InitVal {
    auto var_def = new VarDefAST();
    var_def->is_array = false;
    var_def->ident = *unique_ptr<string>($1);
    var_def->has_value = true;
    var_def->init_val = unique_ptr<InitValAST>((InitValAST *)$3);
    $$ = var_def;
  }
  ;

VarDef
  : IDENT ArrayIndexConstExpList {
    auto var_def = new VarDefAST();
    var_def->is_array = true;
    var_def->ident = *unique_ptr<string>($1);
    var_def->has_value = false;
    unique_ptr<ArrayIndexConstExpListAST> p((ArrayIndexConstExpListAST *)$2);
    for(auto &ce : p->const_exps){
        var_def->const_exps.emplace_back(ce.release());
    }
    $$ = var_def;
  }
  ; 

VarDef
  : IDENT ArrayIndexConstExpList '=' InitVal {
    auto var_def = new VarDefAST();
    var_def->is_array = true;
    var_def->has_value = true;
    var_def->ident = *unique_ptr<string>($1);
    unique_ptr<ArrayIndexConstExpListAST> p((ArrayIndexConstExpListAST *)$2);
    for(auto &ce : p->const_exps){
        var_def->const_exps.emplace_back(ce.release());
    }
    var_def->init_val = unique_ptr<InitValAST>((InitValAST *)$4);
    $$ = var_def;
  }
  ;

InitVal
  : Exp{
    auto init_val = new InitValAST();
    init_val->is_exp = true;
    init_val->is_list = false;
    init_val->exp.reset((ExpAST *)$1);
    $$ = init_val;
  } | '{' '}' {
    auto init_val = new InitValAST();
    init_val->is_exp = false;
    init_val->is_list = true;
    $$ = init_val;
  } | '{' InitValList '}' {
    $$ = $2;
  }
  ;

InitValList
  : InitVal {
    auto init_val = new InitValAST();
    init_val->inits.emplace_back((InitValAST *)$1);
    $$ = init_val;
  } | InitValList ',' InitVal {
    auto init_val = (InitValAST *)$1;
    init_val->inits.emplace_back((InitValAST *)$3);
    $$ = init_val;
  }
  ;

Stmt
  : OpenStmt {
     $$ = $1;
  }
  ;

Stmt
  : MatchedStmt {
     $$ = $1;
  }
  ;


MatchedStmt
  : RETURN Exp ';' {
    auto stmt_ast = new StmtAST();
    stmt_ast->tag = StmtAST::RETURN;
    stmt_ast->has_exp = true;
    stmt_ast->exp = unique_ptr<ExpAST>((ExpAST*)$2);
    $$ = stmt_ast;
  }
  ;


MatchedStmt
  : RETURN  ';' {
    auto stmt = new StmtAST();
    stmt->has_exp = false;
    stmt->tag = StmtAST::RETURN;
    $$ = stmt;
  }
  ;

MatchedStmt 
  : LeVal '=' Exp ';' {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::ASSIGN;
    stmt->has_exp = true;
    stmt->exp.reset((ExpAST *) $3);
    stmt->lval.reset((LeValAST *) $1);
    $$ = stmt;
  }
  ;

MatchedStmt
  : Block {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::BLOCK;
    stmt->block.reset((BlockAST *)$1);
    $$ = stmt;
  }
  ;

MatchedStmt
  : ';' {
    auto stmt = new StmtAST();
    stmt->has_exp = false;
    stmt->tag = StmtAST::EXP;
    $$ = stmt;
  }
  ;

MatchedStmt
  : Exp ';' {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::EXP;
    stmt->has_exp = true;
    stmt->exp.reset((ExpAST *)$1);
    $$ = stmt;
  }
  ;


MatchedStmt
  : IF '(' Exp ')' MatchedStmt ELSE MatchedStmt {
    auto mat_stmt = new StmtAST();
    mat_stmt->tag = StmtAST::IF;
    mat_stmt->has_exp = true;
    mat_stmt->has_else = true;      
    mat_stmt->exp.reset((ExpAST *) $3);
    mat_stmt->if_stmt.reset((StmtAST *)$5);
    mat_stmt->else_stmt.reset((StmtAST *)$7);
    $$ = mat_stmt;
  }
  ;

OpenStmt
  : WHILE '(' Exp ')' Stmt {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::WHILE;
    stmt->exp.reset((ExpAST *)$3);
    stmt->stmt.reset((StmtAST *)$5);
    $$ = stmt;
  }
  ;

MatchedStmt
  : BREAK ';' {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::BREAK;
    $$ = stmt;
  }
  ;

MatchedStmt
  : CONTINUE ';' {
    auto stmt = new StmtAST();
    stmt->tag = StmtAST::CONTINUE;
    $$ = stmt;
  }
  ;

OpenStmt
  : IF '(' Exp ')' Stmt {
    auto open_stmt = new StmtAST();
    open_stmt->tag = StmtAST::IF;
    open_stmt->has_exp = true;
    open_stmt->exp.reset((ExpAST *)$3);
    open_stmt->if_stmt.reset((StmtAST *)$5);
    $$ = open_stmt;
  } 
  ;

OpenStmt
  : IF '(' Exp ')' MatchedStmt ELSE OpenStmt {
    auto open_stmt = new StmtAST();
    open_stmt->tag = StmtAST::IF;
    open_stmt ->has_exp = true;
    open_stmt->exp.reset((ExpAST *)$3);
    open_stmt->if_stmt.reset((StmtAST *)$5);
    open_stmt->has_else = true;
    open_stmt->else_stmt.reset((StmtAST *)$7);
    $$ = open_stmt;
  }
  ;


LVal
  : IDENT {
    auto lval = new LValAST();
    lval->is_array = false;
    lval->ident = *unique_ptr<string>($1);
    $$ = lval;
  } | IDENT ArrayIndexExpList {
    auto lval = new LValAST();
    unique_ptr<ArrayIndexExpListAST> p((ArrayIndexExpListAST *)$2);
    lval->is_array = true;
    lval->ident = *unique_ptr<string>($1);
    for(auto &e : p->exps){
        lval->exps.emplace_back(e.release());
    }
    $$ = lval;
  }
  ;

LeVal
  : IDENT {
    auto lval = new LeValAST();
    lval->is_array = false;
    lval->ident = *unique_ptr<string>($1);
    $$ = lval;
  }  | IDENT ArrayIndexExpList {
    auto lval = new LeValAST();
    unique_ptr<ArrayIndexExpListAST> p((ArrayIndexExpListAST *)$2);
    lval->is_array = true;
    lval->ident = *unique_ptr<string>($1);
    for(auto &e : p->exps){
        lval->exps.emplace_back(e.release());
    }
    $$ = lval;
  }
  ;


Exp
  : LOrExp {
    auto exp_ast = new ExpAST();
    exp_ast->lorexp = unique_ptr<LOrExpAST>((LOrExpAST*)$1);
    $$ = exp_ast;
  }
  ;

UnaryExp
  : PrimaryExp {
    auto unaryexp_ast = new UnaryExpAST();
    unaryexp_ast->HasOp = false;
    unaryexp_ast->primaryexp = unique_ptr<PrimaryExpAST>((PrimaryExpAST*)$1);
    $$ = unaryexp_ast;
  }
  ;

UnaryExp
  : UnaryOp UnaryExp {
    auto unaryexp_ast = new UnaryExpAST();
    unaryexp_ast->HasOp = true;
    unaryexp_ast->unary_op = $1;
    unaryexp_ast->unaryexp = unique_ptr<UnaryExpAST>((UnaryExpAST*)$2);
    $$ = unaryexp_ast;
  }
  ;

UnaryExp
  : IDENT '(' ')' {
    auto unary_exp = new UnaryExpAST();
    unary_exp->is_call = true;
    unary_exp->ident = *unique_ptr<string>($1);
    $$ = unary_exp;
  } 
  ;

UnaryExp
  : IDENT '(' FuncCallParams ')' {
    auto unary_exp = new UnaryExpAST();
    unary_exp->is_call = true;
    unary_exp->ident = *unique_ptr<string>($1);
    unary_exp->func_params.reset((FuncCallParamsAST *)$3);
    $$ = unary_exp;
  }
  ;

FuncCallParams
  : Exp {
    auto params = new FuncCallParamsAST();
    params->exps.emplace_back((ExpAST *)$1);
    $$ = params;
  } 
  ;
  
FuncCallParams
  : Exp ',' FuncCallParams {
    auto params = new FuncCallParamsAST();
    params->exps.emplace_back((ExpAST *)$1);
    auto p2 = unique_ptr<FuncCallParamsAST>((FuncCallParamsAST *)$3);
    int n = p2->exps.size();
    for(int i = 0; i < n; ++i){
        params->exps.emplace_back(p2->exps[i].release());
    }
    $$ = params;
  }
  ;

PrimaryExp
  : '(' Exp ')'{
    auto primaryexp_ast=new PrimaryExpAST();
    primaryexp_ast->type = "exp";
    primaryexp_ast->exp = unique_ptr<ExpAST>((ExpAST*)$2);
    $$ = primaryexp_ast;
  }
  ;

PrimaryExp
  : Number {
    auto primaryexp_ast=new PrimaryExpAST();
    primaryexp_ast->type = "number";
    primaryexp_ast->number = $1;
    $$ = primaryexp_ast;
  }
  ;
  
PrimaryExp 
  : LVal {
    auto primary_exp = new PrimaryExpAST();
    primary_exp->type = "lval";
    primary_exp->lval =  unique_ptr<LValAST>((LValAST *)$1);
    $$ = primary_exp;
  }
  ;


MultiExp
  : UnaryExp{
    auto multi_exp = new MultiExpAST();
    multi_exp->HasOp = false;
    multi_exp->unary_exp = unique_ptr<UnaryExpAST>((UnaryExpAST *)$1);
    $$ = multi_exp;
  }
  ;

MultiExp
  : MultiExp BinaryMultiOp UnaryExp{
    auto multi_exp = new MultiExpAST();
    multi_exp->HasOp = true;
    multi_exp->multi_exp = unique_ptr<MultiExpAST>((MultiExpAST *)$1);
    multi_exp->unary_exp = unique_ptr<UnaryExpAST>((UnaryExpAST *)$3);
    multi_exp->multi_op = $2;
    $$ = multi_exp;
  }
  ;

AddExp 
  : MultiExp {
    auto add_exp = new AddExpAST();
    add_exp->HasOp = false;
    add_exp->multi_exp = unique_ptr<MultiExpAST>((MultiExpAST *)$1);
    $$ = add_exp;
  }
  ;

AddExp 
  : AddExp BinaryAddOp MultiExp {
    auto add_exp = new AddExpAST();
    add_exp->HasOp = true;
    add_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)$1);
    add_exp->multi_exp = unique_ptr<MultiExpAST>((MultiExpAST *)$3);
    add_exp->add_op = $2;
    $$ = add_exp;
  }
  ;

RelExp 
  : AddExp{
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = false;
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)$1);
    $$ = rel_exp;
  }
  ;

RelExp 
  : RelExp BinaryRelOp AddExp{
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = true;
    rel_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)$1);
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)$3);
    rel_exp->rel_op[0] = $2;
    rel_exp->rel_op[1] = 0;
    $$ = rel_exp;
  }
  ;

RelExp 
  : RelExp LESS_EQ AddExp{
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = true;
    rel_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)$1);
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)$3);
    rel_exp->rel_op[0] = '<';
    rel_exp->rel_op[1] = '=';
    $$ = rel_exp;
  }
  ;

RelExp 
  : RelExp GREAT_EQ AddExp{
    auto rel_exp = new RelExpAST();
    rel_exp->HasOp = true;
    rel_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)$1);
    rel_exp->add_exp = unique_ptr<AddExpAST>((AddExpAST *)$3);
    rel_exp->rel_op[0] = '>';
    rel_exp->rel_op[1] = '=';
    $$ = rel_exp;
  }
  ;

EqExp 
  : RelExp{
    auto eq_exp = new EqExpAST();
    eq_exp->HasOp = false;
    eq_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)$1);
    $$ = eq_exp;
  }
  ;

EqExp 
  : EqExp EQUAL RelExp{
    auto eq_exp = new EqExpAST();
    eq_exp->HasOp = true;
    eq_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)$1);
    eq_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)$3);
    eq_exp->eq_op[0] = '=';
    eq_exp->eq_op[1] = '=';
    $$ = eq_exp;
  }
  ;

EqExp 
  : EqExp NOT_EQUAL RelExp{
    auto eq_exp = new EqExpAST();
    eq_exp->HasOp = true;
    eq_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)$1);
    eq_exp->rel_exp = unique_ptr<RelExpAST>((RelExpAST *)$3);
    eq_exp->eq_op[0] = '!';
    eq_exp->eq_op[1] = '=';
    $$ = eq_exp;
  }
  ;

LAndExp
  : EqExp {
    auto l_and_exp = new LAndExpAST();
    l_and_exp->HasOp = false;
    l_and_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)$1);
    $$ = l_and_exp;
  }
  ;

LAndExp
  : LAndExp AND EqExp{
    auto l_and_exp = new LAndExpAST();
    l_and_exp->HasOp = true;
    l_and_exp->l_and_exp = unique_ptr<LAndExpAST>((LAndExpAST *)$1);
    l_and_exp->eq_exp = unique_ptr<EqExpAST>((EqExpAST *)$3);
    $$ = l_and_exp;
  }
  ;

LOrExp
  : LAndExp {
    auto l_or_exp = new LOrExpAST();
    l_or_exp->HasOp = false;
    l_or_exp->l_and_exp = unique_ptr<LAndExpAST>((LAndExpAST *)$1);
    $$ = l_or_exp;
  }
  ;

LOrExp
  : LOrExp OR LAndExp {
    auto l_or_exp = new LOrExpAST();
    l_or_exp->HasOp = true;
    l_or_exp->l_or_exp = unique_ptr<LOrExpAST>((LOrExpAST *)$1);
    l_or_exp->l_and_exp = unique_ptr<LAndExpAST>((LAndExpAST *)$3);
    $$ = l_or_exp;
  }
  ;

Number
  : INT_CONST {
    $$ = $1;
  }
  ;

UnaryOp
  : '+' {
    $$ = '+';
  }
  ;

UnaryOp
  : '-' {
    $$ = '-';
  }
  ;

UnaryOp
  : '!' {
    $$ = '!';
  }
  ;

BinaryAddOp
  : '+'{
    $$ = '+';
  }
  ;

BinaryAddOp
  : '-'{
    $$ = '-';
  }
  ;

BinaryMultiOp
  : '*'{
    $$ = '*';
  }
  ;

BinaryMultiOp
  : '/'{
    $$ = '/';
  }
  ;

BinaryMultiOp
  : '%'{
    $$ = '%';
  }
  ;

BinaryRelOp
  : '<'{
    $$ = '<';
  }
  ;

BinaryRelOp
  : '>'{
    $$ = '>';
  }
  ;



%%

// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
// void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
//     extern int yylineno;    // defined and maintained in lex
//     extern char *yytext;    // defined and maintained in lex
//     int len= strlen(yytext);
//     int i;
//     char buf[512]={0};
//     for (i=0;i<len;++i)
//     {
//         sprintf(buf,"%s%d ",buf,yytext[i]);
//     }
//     fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", s, buf, yylineno);
// }
void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
