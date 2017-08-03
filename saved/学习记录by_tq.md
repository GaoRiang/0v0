## 做一些“我在干嘛”的记录

> 大概就是用来避免九月开学回想起暑假的时候突然说不上暑假在干嘛吧。记录一下学习过程及看到的认为有用的资料。

+ 7.25-7.26
    * 忘了这两天在搞什么……大概在解决搭建环境的问题和做一些预备工作？？？
+ 7.27
    * 了解c语言程序的从文本代码到二进制可执行文件的编译过程
    * 了解gcc指令一些参数的作用，与上面有关
    * 了解文件描述符
+ 7.28
    * 对寄存器做了一些了解
        + 32位寄存器 变量
            eax:累加寄存器(accumulator)
            ebx:基地址(base)在内存寻址时存放的基地址
            ecx:计数器(counter)，是重复(REP)前缀指令和LOOP指令的内定计数器
            edx:被用来放整数除法产生的余数
            esi/edi:“源/目标索引寄存器”(source/destination index)因为在很多字符串操作指令中，DS:ESI指向源串，而ES:EDI指向目标串
            ebp:“基址指令”(BASE POINTER),它经常被用作高级语言函数的“框架函数”（frame pointer）
        + push ebp:保存当前ebp
            mov ebp,esp:EBP设为当前堆栈指针
            sub esp,xxx:预留xxx（4的倍数）字节给函数临时变量
        + esp:寄存器存放当前线程的栈顶指针（地址小）
            ebp:寄存器存放当前线程的栈底指针（地址大）
            eip:寄存器存放存放下一条CPU指令的内存地址，当CPU执行完当前的指令后，从eip寄存器中读取下一条指令的内存地址，然后继续执行

            一般寄存器：ax（累积暂存器）bx（基底暂存器）cx（计数暂存器）dx（资料暂存器）延伸是：eax ecx edx ebx

            索引寄存器：si（来源索引暂存器）di（目的索引暂存器）
            堆叠、基底指标寄存器：sp、bp延伸是：esi edi edp ebp

    * 写了一个可以根据输入的路径名创建文件夹的小程序，eg. “a/b/c/d”，如果“a/b/c/d”不存在，那么a、b、c文件夹如果不存在，则会被创建，使用了mkdir
+ 7.29
    * 变量名会在编译的时候被建立一个符号表与物理内存对应，函数名数组名指针名这些就直接代表内存地址。
        1. [变量名储存在那里，变量的储存机制是什么？](https://www.zhihu.com/question/34266997)
        2. [关于内存中的变量存储](https://zhuanlan.zhihu.com/p/26497398)

    * 函数调用&栈帧
        1. [x86-64 下函数调用及栈帧原理](https://zhuanlan.zhihu.com/p/27339191)
        2. 发现还是需要去看看csapp
    * 突然间解决了2天前的一个段错误的问题
+ 7.30
    * 对段错误多了一些了解(> <)
        + 有效地址，未对齐数据而不能正确使用该指针----->顺便了解了一下对齐：
            * 能优化cpu内存访问速度/某些硬件平台的cpu不能读取为对齐数据
            * [内存对齐的规则以及作用](http://www.cppblog.com/snailcong/archive/2009/03/16/76705.html)
        + 有效地址但无访问权限/无效地址
        + 用完堆栈/堆空间
    * gdb打印-32(%rbp)：p /x *(int *)($rbp-0x20)  或   x /w $rbp-0x20
    * 函数调用&栈帧
        1. 编译后使用gdb调试并画图，能够了解[x86-64 下函数调用及栈帧原理](https://zhuanlan.zhihu.com/p/27339191)中的例子，能够解释程序产生的寄存器变化，并且发现这篇文章写的没有很全面，包括没有解释对栈顶指针能产生影响的指令
        2. 对rsp产生影响的指令：
            + CALL: pushq rip(会使rsp-=8/上移一层)
            + popq %rbp: %rbp=旧%rbp;%rsp+=8(上移一层)
            + ret: %rsp+=8(上移一层)
            + leave: %rsp=%rbp;popq %rbp
        3. [Intel x86 Function-call Conventions - Assembly View](http://www.unixwiz.net/techtips/win32-callconv-asm.html)

    
+ 7.31
    * 看lab1的ex1-2(发现实验的练习很难……所以结合别人的博客来看)
+ 8.01
    * 看lab1的ex3-4
+ 8.02
    * 看lab1的ex5-7
    * ELF  可执行可链接格式。一种用于二进制文件、可执行文件、目标代码、共享库和核心转储格式文件。
        + 三种类型：可重定位文件(.o)、可执行文件(a.out)、共享目标文件
        + 
        
    * 再次解决ubuntu系统下合盖后电脑无法唤醒的问题失败:)可能是硬件问题
    
+ 8.03
    * 堆栈，是一种数据结构，程序的内存分配，包括stack，heap，static，text（文本常量区），二进制代码区，有栈基指针和栈顶指针，高-->低。利用pop和push实现后进先出。
    * 同一台电脑配置2个github账号的方法：
        ```
        1:$ ssh-keygen -t rsa -C "your-email-address"

        2：把id_rsa_work.pub加到你的work账号上 

        3：ssh-add -l
        
        4.如果已经把新key加到ssh agent上就不需执行下面这条指令：$ ssh-add ~/.ssh/id_rsa_work

        5：配置.ssh/config：$ vi .ssh/config

        # 加上以下内容
        #default github
        Host github.com
        HostName github.com
        IdentityFile ~/.ssh/id_rsa

        Host github_work
        HostName github.com
        IdentityFile ~/.ssh/id_rsa_work 

        ---配置完毕---


        **新建repo**
        $ git remote add origin git@github_work:xxxx/test.git
        对于当前repo设置email 和name
        $ git config  user.email "xxxx@xx.com"
        $ git config  user.name "xxxx"
        $  git clone git@github_work:xxxx/test
        ```
