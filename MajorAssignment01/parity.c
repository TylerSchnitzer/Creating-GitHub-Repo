/******************************
 * Author: Tyler Schnitzer
 * tylerschnitzer@my.unt.edu
 * 03/1/2022
 * ***************************/

#include <stdio.h>

void parity(unsigned int num)
{
    int cnt=0; // Declare a counter to run through the 32 bit number

    printf ("Parity of %d is ", num);

    for(int i=0; i<32; i++) // make the loop incerment 32 times to get through a 32 bit number
    {
        cnt+=num%2; // Add the number if the remainder of num divided by 2
        num/=2; //then divide the num by 2
    }
    printf ("%d\n", cnt%2);    
}