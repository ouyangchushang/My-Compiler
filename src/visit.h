#pragma once
#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "koopa.h"



// 记录寄存器使用情况
//std::string FirstUnusedReg();

// 变量，用于消除相邻的无用load和store操作
static bool just_stored = false;
static std::string store_src, store_address;
static int store_i;

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice);
// 访问函数
void Visit(const koopa_raw_function_t &func);
// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb);
// 访问指令
void Visit(const koopa_raw_value_t &value);
// 访问return
void Visit(const koopa_raw_return_t &ret);
// 访问整型变量
int Visit(const koopa_raw_integer_t &ret);
// 访问二元运算
void Visit(const koopa_raw_binary_t &value);
// 访问load指令
void Visit(const koopa_raw_load_t &load);
// 访问store指令
void Visit(const koopa_raw_store_t &store);
// 访问branch指令
void Visit(const koopa_raw_branch_t &branch);
// 访问jump指令
void Visit(const koopa_raw_jump_t &jump);
// 访问call指令
void Visit(const koopa_raw_call_t &call);
// 访问getelemptr指令
void Visit(const koopa_raw_get_elem_ptr_t& get_elem_ptr);
// 访问getptr指令
void Visit(const koopa_raw_get_ptr_t& get_ptr);

// 得到对应寄存器

void parse_string(const char* str);
void alloc(const koopa_raw_function_t &func);
size_t getTypeSize(koopa_raw_type_t ty);
void VisitGlobalVar(koopa_raw_value_t value);
void InitGlobalArray(koopa_raw_value_t init);
void _load(std::string dst, std::string address, int offset);
void _save(std::string src, std::string address, int offset);
void _addi(std::string dest, std::string src , int delta);

