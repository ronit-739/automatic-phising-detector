#include<stdio.h>
#include "levenshtein.h"
#include "blacklist.h"
int count=0;
int total_function=2;

int main()
{
    
  
    float percentage=30;


    // input 
    //samrat part say gives input in variable url;
    char url[100]; 
    printf("Enter URL:\n");
    scanf("%s", url);




    //function call and record count if suspecious count++


  
    struct result res = check_edit_distance(url);
    printf("\n\n----------First test--------------\n");
    printf("Levenshtein distance: %d\n", res.ld);

    if (res.ld == 0) {
        printf("Given domain name is real\n");
        printf("Matching safe URL: %s\n", res.matching_url);
    } else if (res.ld <= 3) {
        printf("Suspicious URL detected!\n");
        printf("Matching safe URL: %s\n", res.matching_url);
        count ++;
    } else {
        printf("Does not look suspicious.\n");
    }
   

    printf("\n\n------------Second Test------------\n");
    if (!isBlacklisted(url)) {
        printf("URL is NOT in the blacklist\n");
    } else {
        printf("URL is in the blacklist!\n");
        count ++;
    }






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
    printf("\ngiven url has  %.2f %% chance of being a phising url\n ",percentage);




    


return 0;

  
}