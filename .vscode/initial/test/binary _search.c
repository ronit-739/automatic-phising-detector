#include<stdio.h>

int binary_search(int a[], int size, int low , int high, int no);


int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int index;
    
    index=binary_search(a,10,0, 10-1,7);
    printf("index=%d",index);
    return 0;
}


int binary_search(int a[], int size,int low, int high, int no){
    while(low<=high){
     int mid=low+(high-low)/2;
     if(no==mid)
     {
        return mid;
     }
     else if(no<mid)
     {
        high=mid-1;
     }
     else if(no>mid)
     {
        low=mid+1;

     }

    }


}
