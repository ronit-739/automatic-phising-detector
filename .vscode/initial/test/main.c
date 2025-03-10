#include<stdio.h>
#include "add.h"

int main()
{
    int a, b;
    printf("Enter two no: \n");
    scanf("%d%d",&a,&b);
    printf("sum of %d and %d is %d\n",a,b,add(a,b));
}