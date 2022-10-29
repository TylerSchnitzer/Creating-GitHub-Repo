/*
    Author: Robert Powell
    robertpowell2@my.unt.edu
    2/24/2022
*/


#include <stdio.h>
#include "major1.h"

unsigned long int number;
int bitPositions;

int main()
{
    int choice;
           
    do
    {
        
        printf("Enter the menu option for the operation to perform:\n");
        printf("(1) Count Leading Zeroes\n");
        printf("(2) Endian Swap\n");
        printf("(3) Rotate-right\n");
        printf("(4) Parity\n");
        printf("(5) EXIT\n");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:{
               
                do
                {   printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
                    scanf("%lu", &number);
                } while(number > 4294967295);
                clz(number);
                break;
            }
            case 2:{
                
                do
                {   printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
                    scanf("%lu", &number);
                } while(number > 4294967295);

                /*code to print test input*/
                printf("number: %lu \n\n", number);

                //endian(number);
                break;
            }
            case 3:{
               
                do
                {   printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
                    scanf("%lu", &number);
                } while(number > 4294967295);
                do
                {   printf("Enter the number of positions to rotate-right the input (between 0 and 31, inclusively): ");
                    scanf("%d", &bitPositions);
                } while( (bitPositions < 0 ) || ( bitPositions > 31));

                /*code to print test input*/
                printf("number: %lu \n", number);
                /*code to print test input*/
                printf("bitPositions: %d \n\n", bitPositions);

                //rotate(number,bitPositions);
                break;
            }
            case 4:{
            
                do
                {   printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
                    scanf("%lu", &number);
                } while(number > 4294967295);

                /*code to print test input*/
                parity(number);
                break;
            }
            case 5:{
               
                printf("EXIT\n\n");  
                break;
            } 
            default:
                printf("Error: Invalid Option. Please try again.\n\n");
                break;
        }

    }while(choice != 5 );

}


    