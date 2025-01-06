#include <stdio.h>

void sayhelloA(void)
{
   printf("\033[1;32m");
   printf("static-linking library routine: HelloWorld!\n");
   printf("\033[0m");
}

