# 关于c语言编译的各种命令的的探索

一个c语言代码从一份文本代码到二进制可执行文件经历了以下几个过程：

文本(.c)--[预处理器CPP]-->被修改的源程序(.i)--[编译器CCL]-->汇编程序文本(.s)--[汇编器AS]-->可重定位目标程序（二进制）(.o)--[链接器LD]--->可执行目标程序（二进制）

可以用gcc --help查看gcc指令信息


+ -E是对代码文本进行预处理，gcc -E t.c 可以输出预处理后的代码文本。gcc -E t.c -o t.i 可以生成预处理后的代码文本，其中包括了
那么预处理做了哪些工作？
    * 源代码：
    ```
    #include<stdio.h>
    int main() {
        printf("hello world\n");
    }
    ```
    可以看到预处理后的文件中包含了头文件stdio的所有函数声明，如果你include了一个自己写的头文件，里面的声明也会放进.i文件中。

    * 再把源代码改成：
    ```
    #include<stdio.h>
    #define a 5
    int main() {
        printf("a = %d\n", a);
        printf("hello world\n");
    }
    ```
    可以看到预处理后的代码已经自动将main函数里的a替换成5。
    ```
    int main() {
        printf("a = %d\n", 5);
        printf("hello world\n");
    }

    ```
    * 以及有条件编译：
    ```
    #include <stdio.h>
    #define a 5
    #define DEBUG 0

    int main() {
        #if DEBUG
            printf("a = %d\n", a);
        #endif
        printf("hello world\n");
    }
    ```
    预处理后：
    ```
    int main() {



        printf("hello world\n");
    }
    ```
    可用于测试程序用

    + 最后还有：
    ```
    #pragma once
    ```
    在头文件的最开始加入这条指令:保证头文件被编译一次。

+ 编译器CCL生成包含汇编语言的文本，也是在这阶段产生编译警告和错误。gcc -S t.i
+ 汇编器AS生成机器语言指令，并打包成可重定位目标程序，是二进制文件，字节编码是机器语言指令而不是字符。gcc -c t.s
+ 链接程序LD将在汇编时生成的.o文件和其他必要的.o文件组合起来，生成可执行目标文件 gcc -o t.o


1. http://blog.csdn.net/dlutbrucezhang/article/details/8753765
2. http://lxwei.github.io/posts/262.html