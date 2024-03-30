# sysycompiler2023

本项目实现了一个自制编译器，其识别一种名为sysY的语言（与c语言类似），首先转换为中间代码KoopaIR，并读入生成的KoopaIR代码并生成riscv汇编代码。

具体的实现原理可以见compiler-report.pdf

在系统上运行需要使用docker环境。

首先安装docker。安装完毕后, 打开系统的命令行:

如果你使用的是 macOS 或 Linux, 可以使用系统的默认终端；

如果你使用的是 Windows, 你可以打开 PowerShell。

执行 docker 可以看到帮助信息。

在系统的命令行中执行:

docker pull maxxing/compiler-dev

如果你使用的是 Linux 系统, 则上述命令可能需要 sudo 才可正常执行。

使用以下方式运行容器：

docker run -it --rm maxxing/compiler-dev bash

在docker环境中，使用以下命令进行生成KoopaIR【把sysY代码放入hello.c】
make
build/compiler -koopa 输入文件 -o 输出文件

使用以下命令生成riscv
compiler -riscv 输入文件 -o 输出文件


