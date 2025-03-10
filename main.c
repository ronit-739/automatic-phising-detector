#include<stdio.h>

int main()
{
    int count=0;
    int total_function;
    float percentage=30;


    // input 
    //samrat part say gives input in variable a;



    //function call and record count if suspecious count++





    // suspecious score calculation
      percentage=(float)count/total_function*100;

    // checking security perceentage  
    if(percentage>0 &&  percentage <=30 )
    {  printf("\nsafe!!\n");
     
    }

    if(percentage>=31 && percentage<=60)
    {  printf("\nSuspecious!!\n");
       
    }

    if(percentage>=61 && percentage<=100)
    {  printf("\nHigh Risk\n");
       
    } 
    printf("---------------------------------------------");
    printf("\ngiven url has  %d percantage chance of being a phising url\n ");




    


return 0;

  
}