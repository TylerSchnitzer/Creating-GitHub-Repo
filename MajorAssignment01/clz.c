/*
    Author: Robert Powell
    robertpowell2@my.unt.edu
    2/24/2022
*/


#include <stdio.h>
#include "major1.h"

/*Function Definitions*/
void clz(unsigned int number)
{
        
    /*printf("number from function = %u\n", number);*/

    /* DO SOMETHING WITH number */
    int i;
    int count = 0;
    int foundOne = 0;


    printf("The binary for the number, %u, is: ", number);

    for(i=7; i>=0; i--)
    {
        printf("%d ", (number&(1<<i)) >> i); /*read and print the i'th bit*/

        count++; /* add one to the count for each digit */
        if( (number&(1<<i)) >> i)
        {
            foundOne = 1; /*set found a one to true */
        }

        if(foundOne)
        {
            count--; /* subract one from the count of digits once a one is found - remaining value of count is the number of leading zeroes */
        }

    }
    printf("\n"); /*print newline*/

    printf("The number of leading zeroes in %u is %d \n\n", number, count); 
   
    
}