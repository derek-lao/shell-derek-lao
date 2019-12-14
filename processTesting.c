#include <stdio.h>
#include <stdlib.h>

int main()
{
   char ch;
   char str[100];
   char str1[100];
   printf("Enter any character \n");
   scanf("%c", &ch);
   printf("Entered character is %c \n", ch);
   printf("Enter any string ( upto 100 character ) \n");
   scanf("%s %s", &str, &str1);
   printf("Entered string is %s and %s\n", str, str1);
}
