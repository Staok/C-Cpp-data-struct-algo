/**
有三个白子和三个黑子如图1所示布置：
        白	白	白	 	黑	黑	黑

游戏的目的是用最少的步数将图1中白子和黑子的位置进行交换，使得最终结果如图2所示：
黑	黑	黑	 	白	白	白

游戏的规则是：
(1) 一次只能移动一个棋子。
(2) 棋子可以向空格中移动，也可以跳过一个对方的棋子进入空格。
(3) 白色棋子只能往右移动，黑色棋子只能向左移动，不能跳过两个子。

请用计算机实现上述游戏。
*/

#include<stdio.h>
int number;
void print(int a[]);
void change(int *n, int *m);
int main()
{
    int t[7]={1,1,1,0,2,2,2};  /*初始化数组1：白子 2：黑子 0：空格*/
    int i, flag;
    print(t);
    /*若还没有完成棋子的交换则继续进行循环*/
    while(t[0]+t[1]+t[2]!=6 || t[4]+t[5]+t[6]!=3)  /*判断游戏是否结束*/
    {
        flag=1;  /*flag为棋子移动一步的标记，flag=1表示尚未移动棋子，
                  flag=0表示已经移动棋子*/
        for(i=0; flag&&i<5; i++)  /*若白子可以向右跳过黑子，则白子向右跳*/
            if(t[i]==1 && t[i+1]==2 && t[i+2]==0)
            {
                change(&t[i], &t[i+2]);
                print(t);
                flag=0;}
        for(i=0; flag&&i<5; i++)  /*若黑子可以向左跳过白子，则黑子向左跳*/
            if(t[i]==0 && t[i+1]==1 && t[i+2]==2)
            {
                change(&t[i], &t[i+2]);
                print(t);
                flag=0;
            }
        for(i=0; flag&&i<6; i++)  /*若向右移动白子不会产生阻塞,则白子向右移动*/
            if(t[i]==1 && t[i+1]==0 && (i==0||t[i-1]!=t[i+2]))
            {
                change(&t[i], &t[i+1]);
                print(t);
                flag=0;
            }
        for(i=0; flag&&i<6; i++)  /*若向左移动黑子不会产生阻塞，则黑子向左移动*/
            if(t[i]==0 && t[i+1]==2 && (i==5||t[i-1]!=t[i+2]))
            {
                change(&t[i], &t[i+1]);
                print(t);
                flag=0;
            }
    }
    return 0;
}

void print(int a[])
{
    int i;
    printf("No. %2d:………………………..\n", number++);
    printf(" ");
    for(i=0; i<=6; i++)
        printf(" | %c",a[i]==1?'*':(a[i]==2?'@':' '));
    printf(" |\n ………………………..\n\n");
}

void change(int *n, int *m)
{
    int term;
    term=*n;
    *n=*m;
    *m=term;
}



//运行结果：

/**
No.  0:………………………..
  | * | * | * |   | @ | @ | @ |
………………………..

No.  1:………………………..
  | * | * |   | * | @ | @ | @ |
………………………..

No.  2:………………………..
  | * | * | @ | * |   | @ | @ |
………………………..

No.  3:………………………..
  | * | * | @ | * | @ |   | @ |
………………………..

No.  4:………………………..
  | * | * | @ |   | @ | * | @ |
………………………..

No.  5:………………………..
  | * |   | @ | * | @ | * | @ |
………………………..

No.  6:………………………..
  |   | * | @ | * | @ | * | @ |
………………………..

No.  7:………………………..
  | @ | * |   | * | @ | * | @ |
………………………..

No.  8:………………………..
  | @ | * | @ | * |   | * | @ |
………………………..

No.  9:………………………..
  | @ | * | @ | * | @ | * |   |
………………………..

No. 10:………………………..
  | @ | * | @ | * | @ |   | * |
………………………..

No. 11:………………………..
  | @ | * | @ |   | @ | * | * |
………………………..

No. 12:………………………..
  | @ |   | @ | * | @ | * | * |
………………………..

No. 13:………………………..
  | @ | @ |   | * | @ | * | * |
………………………..

No. 14:………………………..
  | @ | @ | @ | * |   | * | * |
………………………..

No. 15:………………………..
  | @ | @ | @ |   | * | * | * |
………………………..
*/
