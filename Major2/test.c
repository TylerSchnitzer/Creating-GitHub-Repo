#include<stdio.h>
 
int main() {
   int arr1[10], arr2[10], i, length;
 
   printf("\nEnter no of elements :");
   scanf("%d", &length);
 
   //Accepting values into Array
   printf("\nEnter the array values :");
   for (i = 0; i < length; i++) {
      scanf("%d", &arr1[i]);
   }
 
   /* Copying data from array '1' to array '2' */
   for (i = 0; i < length; i++) {
      arr2[i] = arr1[i];
   }
 
   //Printing of all elements of array
   printf("The new array is :");
   for (i = 0; i < length; i++)
      printf("\n %d", arr2[i]);
 
   return (0);
}
