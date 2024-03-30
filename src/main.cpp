#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "AST.h"
#include "koopa.h"
#include "visit.h"


using namespace std;

// 声明 lexer 的输入, 以及 parser 函数
extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
  assert(argc == 5);
  auto mode = argv[1];
  auto input = argv[2];
  auto output = argv[4];

  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);

  // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  unique_ptr<BaseAST> base_ast;
  unique_ptr<CompUnitAST> ast;
  auto ret = yyparse(base_ast);
  assert(!ret);

  ast.reset((CompUnitAST *)base_ast.release());
  if(mode[1] == 'k')
  {
    freopen(output,"w",stdout);
    ast->Dump();
    fclose(stdout);
  }
  else if(mode[1] == 'r' || mode[1] == 'p'){
    freopen("strIR.txt","w",stdout);
    ast->Dump();
    fclose(stdout);
    FILE *fp=fopen("strIR.txt","r");
    char *buf=(char *)malloc(100000);
    fread(buf, 1, 100000, fp);
    freopen(output,"w",stdout);
    parse_string(buf);
    fclose(stdout);
  }

  return 0;
}
