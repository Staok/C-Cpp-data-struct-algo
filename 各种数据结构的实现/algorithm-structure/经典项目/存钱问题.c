//假设银行整存整取存款不同期限的月息利率为：

//0.63%  期限为1年
//0.66%  期限为2年
//0.69%  期限为3年
//0.75%  期限为5年
//84%    期限为8年

//现在已知某人手上有2000元，要求通过计算选择出一种存钱方案，使得这笔钱存入银行20年后获得的利息最多，假定银行对超出存款期限的那部分时间不付利息。

#include<stdio.h>
#include<math.h>

int main()
{
    int x1, x2, x3, x5, x8;
    int y1 = 0, y2 = 0, y3 = 0, y5 = 0, y8 = 0;
    double max=0.0, result = 0.0;  /*result变量存放最后结果*/
    /*使用for循环穷举所有可能存款方案*/
    for( x8=0; x8<=2; x8++ )
        for( x5=0; x5<=(20-8*x8)/5; x5++ )
            for( x3=0; x3<=(20-8*x8-5*x5)/3; x3++ )
                for( x2=0; x2<=(20-8*x8-5*x5-3*x3)/2; x2++ )
                {
                    x1 = 20 - 8*x8 - 5*x5 - 3*x3 - 2*x2;  /*存款期限限定条件*/
                    /*判断条件*/
                    result = 2000.0 * pow( (1+0.0063*12), x1)
                    *pow( (1+2*0.0066*12), x2)
                    *pow( (1+3*0.0069*12), x3)
                    *pow( (1+5*0.0075*12), x5)
                    *pow( (1+8*0.0084*12), x8);
                    /*y1,y2,y3,y5,y8用于记录获利最多的存放方式*/
                    if(result>max)
                    {
                        max = result;  /*max变量存放当前的最大值*/
                        y1 = x1;
                        y2 = x2;
                        y3 = x3;
                        y5 = x5;
                        y8 = x8;
                    }
                }
   
    /*输出结果*/
    printf("获得利息最多的存款方式为：\n");
    printf("8年期限的存了%d次\n", y8);
    printf("5年期限的存了%d次\n", y5);
    printf("3年期限的存了%d次\n", y3);
    printf("2年期限的存了%d次\n", y2);
    printf("1年期限的存了%d次\n", y1);
    printf("存款人最终的获得的本利合计：%0.2f\n", result);
   
    return 0;
}


//运行结果：

//获得利息最多的存款方式为：
//8年期限的存了0次
//5年期限的存了4次
//3年期限的存了0次
//2年期限的存了0次
//1年期限的存了0次
//存款人最终的获得的本利合计：8763.19
