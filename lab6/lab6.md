# lab6

[TOC]

## lab0l (lab1 L version)

### 实现思路

- 使用`short`类型变量模拟`16bit`的寄存器
- 使用`do while`循环来模拟`BR`指令
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果，参数为预先存在寄存器中的输入

### 最终代码

```c++
short lab0l(short a, short b)
{
    short result = 0;
    do
    {
        result += a;
        b--;
    } while (b != 0);
    return result;
}
```

## lab0p (lab1 P version)

### 实现思路

- 使用`short`类型变量模拟`16bit`的寄存器
- 使用`do while`循环和`if`来模拟`BR`指令
- 使用`&`运算符模拟`AND`指令
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果，参数为预先存在寄存器中的输入

### 最终代码

```c++
short lab0p(short a, short b)
{
    short bit = 1;
    short result = 0;
    do
    {
        if ((b & bit) != 0)
            result += a;
        a += a;
        bit += bit;
    } while (bit != 0);
    return result;
}
```

## fib (lab2 fibonacci)

### 实现思路

- 使用`short`类型变量模拟`16bit`的寄存器
- 使用`do while`循环来模拟`BR`指令
- 使用`&`运算符模拟`AND`指令
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果，参数为预先存在寄存器中的输入

### 最终代码

```c++
short fib(short n)
{
    short f1 = 1, f2 = 1, f3 = 2;
    short result = 0;
    short mask = 0;
    short i = 10;
    do
    {
        mask = mask * 2;
        mask++;
        i--;
    } while (i>0);
    do
    {
        result = f1;
        short f4 = (2 * f1 + f3) & mask;
        f1 = f2;
        f2 = f3;
        f3 = f4;
        n--;
    } while (n >= 0);
    return result;
}
```

## fib-opt (lab3 fibonacci)

### 实现思路

- 使用`short`类型变量模拟`16bit`的寄存器
- 使用`do while`循环和`if`来模拟`BR`指令
- 使用`&`运算符模拟`AND`指令
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果，参数为预先存在寄存器中的输入

### 最终代码

```c++
short fib_opt(short n)
{
    short f1 = 1, f2 = 1, f3 = 2;
    short result = 0;
    n-=2;
    if(n<0) return 1;
    if(n==0) return 2;
    do
    {
        result = 2 * f1 + f3;
        f1 = f2;
        f2 = f3;
        f3 = result;
        n--;
    } while (n > 0);
    return result & 1023;
}
```

## rec (lab4 task1 rec)

### 实现思路

- 使用`short`类型数组`R[8]`参数模拟`16bit`的寄存器
- 使用`if`来模拟`BR`指令
- 使用两个函数来模拟子程序的运行与递归调用
- 使用参数`memory`模拟`x3019`处的内存
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果

### 最终代码

```c++
void rec_subroutine(short R[8], short &memory)
{
    R[2] += 1;
    R[0] += 1;
    R[1] = memory;
    R[1] += -1;
    memory = R[1];
    if (R[1] != 0)
        rec_subroutine(R, memory);
    R[2] -= 1;
}

void rec(short R[8], short &memory)
{
    R[2] = 0x300f;
    R[0] = 0;
    rec_subroutine(R, memory);
}
```

## mod (lab4 task2 mod)

### 实现思路

- 使用`short`类型变量模拟`16bit`的寄存器
- 使用`do while`循环、`if`和`三目运算符`来模拟BR指令
- 使用`&`运算符模拟`AND`指令
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果，参数为预先存在内存中的输入

### 最终代码

```c++
short mod(short num)
{
    do
    {
        short bit = 8;
        short times = 1, multiple = 0;
        do
        {
            if ((num & bit) != 0)
                multiple += times;
            bit += bit;
            times += times;
        } while (bit > 0);
        num = multiple + (num & 7);
    } while (num - 7 > 0);
    num = num == 7 ? num - 7 : num;
    return num;
}
```

## prime (lab5 prime)

### 实现思路

- 使用`short`类型变量模拟`16bit`的寄存器
- 使用`do while`循环和`if`来模拟BR指令
- 使用`return`模拟`HALT`指令
- 函数的返回值为运算的结果，参数为预先存在寄存器中的输入

### 最终代码

```c++
short prime(short num)
{
    short i = 2;
    short result = 1;
    short sqrt = 1;
    do
    {
        sqrt += 2 * i - 1;
        if (num - sqrt < 0)
            return result;
        short temp = num;
        do
        {
            temp -= i;
        } while (temp > 0);
        if (temp == 0)
            result -= 1;
        i++;
    } while (result > 0);
    return result;
}
```

## Questions

Q：how to evaluate the performance of your own high-level language programs

A：估计算法的时间空间复杂度

Q：why is a high-level language easier to write than LC3 assembly

A：高级语言更接近人类使用的自然语言和数学公式

Q：what instructions do you think need to be added to LC3? (You can think about the previous experiments and what instructions could be added to greatly simplify the previous programming)

A：右移运算

Q：how to evaluate the performance of your own high-level language programs

A：位运算的使用
