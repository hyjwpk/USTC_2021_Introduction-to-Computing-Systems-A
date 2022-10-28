#include <iostream>
using namespace std;

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