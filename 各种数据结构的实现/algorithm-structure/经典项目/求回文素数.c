/**
所谓回文素数指的是，对一个整数n从左向右和从右向左读其数值都相同且n为素数，则称整数为回文素数。

对于偶数位的整数，除了11以外，都不存在回文素数。即所有的4位整数、6位整数、 8位整数…都不存在回文素数。下面列出两位和三位整数中包含的所有回文素数。

两位回文素数：11

三位回文素数：101、131、151、181、191、313、353、373、383、727、757、787、 797、 919、 929

本题要求解的问题是：求出所有不超过1000的回文素数。
*/

#include<stdio.h>

int fun(int n);

int main()
{
    int i, j, k, n, m;
    printf("不超过1000的回文数:\n");
    for(i=0; i<=9; ++i)  /*穷举第一位*/
        for(j=0; j<=9; ++j)  /*穷举第二位*/
            for(k=0; k<=9; ++k)  /*穷举第三位*/
            {
                n=i*100+j*10+k;  /*计算组成的整数*/
                m=k*100+j*10+i;  /*计算对应的反序数*/
                if(i==0 && j==0)  /*处理整数的前两位为0的情况*/
                {
                    m=m/100;
                }
                else if(i==0)  /*处理整数的第一位为0的情况*/
                {
                    m=m/10;
                }
                if(n>10 && n==m && fun(n))  /*若大于10且为回文素数，则输出*/
                {
                    printf("%d\t", n);
                }
            }
    printf("\n");
   
    return 0;
}

/*判断参数n是否为素数*/
int fun(int n)
{
    int i;
    for(i=2; i<(n-1)/2; ++i)
    {
        if(n%i == 0)
            return 0;
    }
    return 1;
}


//运行结果：

//不超过1000的回文数:
//11 101 131 151 181 191 313 353 373 383 727 757 787 797 919 929
