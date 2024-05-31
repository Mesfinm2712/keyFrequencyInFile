
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q1Answer(char theFile[12]);
void q2Answer(char theFile[12]);

int main(int argc, char const *argv[]) 
{
  //q1
  char theFile[12];
  printf("Q1\n______________________\n");
  q1Answer(theFile);//does q1(in q1.c file)

  //q2
  printf("Q2\n______________________\n");
  q2Answer(theFile);//does q2(in q2.c file)
  return 0;
}
