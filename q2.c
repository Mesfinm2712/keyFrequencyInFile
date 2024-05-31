/*Mebea Mesfin */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct SearchBST {
  struct SearchBST * leftSub;
  struct SearchBST * rightSub;
  char * key;
  float freq;
} bSearch;


void getKeyAndFreq(char str[2045][2045], char word[599][20], float freq[599], int count);
void createTree(char word[][20], float freq[], bSearch **key, int n);
bSearch * createRoot(char word[][20], float freq[], bSearch * bSearchVal);
bSearch * searchKey(bSearch **root, int num, char * key);




void q2Answer(char theFile[12])//main function that calls all helper functions
{

  strcpy(theFile, "data_7.txt");


  char string[2045] = "";
  char str[2045][2045]; 
  char temp[15000] = "";


  char filename[20];
  strcpy(filename, "data_7.txt");
  
  FILE * fptr;
  fptr = fopen(filename, "r"); 

  int count = 0;
  int i, j;
 
  while( fscanf(fptr, "%s", string) != EOF )
  {
    count++;
    strcpy(str[count], string);
  }

  for (i = 0; i < count -1 ; i++)
  {
      for (j = i + 1; j < count; j++)
      {
          if (strcmp(str[i], str[j]) > 0) 
          {
              strcpy(temp, str[i]);
              strcpy(str[i], str[j]);
              strcpy(str[j], temp);


          }
      }

  }

  strcpy(string, str[2044]);

  char tempArray[10] = "";
  char wordArray[10] = "";
  for(int i = 0; string[i] != '\0'; i++)
  {
    if(i >= 3 && i <= 8)
    {
      sprintf(tempArray, "%c", string[i]);
      strcat(wordArray, tempArray);
    }
  }
  strcpy(str[2044],wordArray);

  for (i = 0; i < count -1 ; i++)
  {
      for (j = i + 1; j < count; j++)
      {
          if (strcmp(str[i], str[j]) > 0) 
          {
              strcpy(temp, str[i]);
              strcpy(str[i], str[j]);
              strcpy(str[j], temp);
          }
      }

  }

  float freq[599];
  char word[599][20];
  getKeyAndFreq(str, word, freq, count);


  float freqAlpha[599];
  char wordAlpha[599][20];
  j = 0;
  for(i = 1; i <= 599; i++)
  {
    strcpy(wordAlpha[j], word[i]);
    freqAlpha[j] = freq[i];
    j++;
  }


  char tempVal[20];

  for(i=0;i<599;i++)
  {
      for(j=0;j<599-i-1;j++)
      {
          if(freq[j]<freq[j+1])
          {
            //freq
            float temp;
            temp=freq[j+1];
            freq[j+1]=freq[j];
            freq[j]=temp;
            //word
            strcpy(tempVal, word[j+1]);
            strcpy(word[j+1], word[j]);
            strcpy(word[j], tempVal);
          }
      }
  } 


  bSearch * root = NULL;
  root = createRoot(wordAlpha, freqAlpha, root);


  int num = 0;

  char * input = malloc(sizeof(char) * 20);
  printf("Enter a key: ");
  scanf("%s", input);
  searchKey(&root, num, input);


}
bSearch * searchKey(bSearch **root, int num, char * key) //outputs to terminal path through tree
{
  
  if ((*root) != NULL)
  {
    num = strcmp(key, (*root)->key);
    if (num > 0) 
    {
      printf("Compared with %s (%.4f), go right subtree.\n", (*root)->key, (*root)->freq);
      (*root)->rightSub = searchKey(&(*root)->rightSub, num, key);
    } 
    else if (num < 0) 
    {
      printf("Compared with %s (%.4f), go left subtree.\n", (*root)->key, (*root)->freq);
      (*root)->leftSub = searchKey(&(*root)->leftSub, num, key);
    } 
    else 
    {
      printf("Compared with %s (%.4f), found.\n", (*root)->key, (*root)->freq);
    }
  } 
  else 
  {
    printf("Not found.\n");
  }

  return (*root);
}

bSearch *createRoot(char word[][20], float freq[], bSearch * bSearchVal)//creates the root to the tree 
{

  int i = 0;
  int k = 0;
  float maxNum = freq[k];

  for (i = 0; i < 599; ++i)
  {
      if (freq[i] > maxNum)
      {
          maxNum = freq[i];
          k = i;
      }
  }
  char * node = malloc(sizeof(char)*20);
  float nodeFreq = 0;


  strcpy(node,word[k]);
  nodeFreq = freq[k];

  char wordLeft[299][20];
  char wordRight[300][20];

  float freqLeft[299];
  float freqRight[300];



  int j = 0;
  for(i = 0; i < 299; i++)
  {
    if(i != k)
    {
      strcpy(wordLeft[j], word[i]);
      freqLeft[j] = freq[i];
      j++;
    }
  }
  j = 0;
  for(i = 299; i < 599; i++)
  {

    if(i != k)
    {
      strcpy(wordRight[j], word[i]);
      freqRight[j] = freq[i];
      j++;
    }
  }

  bSearchVal= malloc(sizeof(bSearch));
  bSearchVal->key = malloc(sizeof(char) * 20);

  strcpy(bSearchVal->key, node);
  bSearchVal->freq = nodeFreq;

  free(node);
  createTree(wordLeft, freqLeft, &bSearchVal->leftSub,299);
  createTree(wordRight, freqRight, &bSearchVal->rightSub, 300);

  return bSearchVal;


}
void createTree(char word[][20], float freq[], bSearch **bSearchVal, int n)//create the rest of the tree(recursively)
{
  int i = 0;
  int k = 0;
  float maxNum = freq[k];

  for (i = 0; i < n; ++i)
  {
      if (freq[i] > maxNum)
      {
          maxNum = freq[i];
          k = i;
      }
  }
  if (n == 1)
  {
    char * node = malloc(sizeof(char)*20);
    float nodeFreq = 0;

    strcpy(node,word[k]);
    nodeFreq = freq[k];
    *bSearchVal= malloc(sizeof(bSearch));
    (*bSearchVal)->key = malloc(sizeof(char) * 20);

    strcpy((*bSearchVal)->key, node);
    (*bSearchVal)->freq = nodeFreq;
    
    free(node);

    return;
  }
  if(n == 0)
  {
    return;
  }
  char * node = malloc(sizeof(char)*20);
  float nodeFreq = 0;

  strcpy(node,word[k]);
  nodeFreq = freq[k];

  int tempLeft = (int)floor((n-1)/2);
  int tempRight = (int)ceil((n-1)/2);

  if((n-1) % 2 != 0){
    tempRight += 1;
  }

  char wordLeft[tempLeft][20];
  char wordRight[tempRight][20];

  float freqLeft[tempLeft];
  float freqRight[tempRight];

  int j = 0;
  int m = 0;
  if(k < tempLeft)
  {
    m = 1;
  }else
  {
    m = 0;
  }

  for(i = 0; i < tempLeft + m; i++)
  {
    if(i != k)
    {
      strcpy(wordLeft[j], word[i]);
      freqLeft[j] = freq[i];
      ++j;
    }
  }

  j = 0;
  for(i = tempLeft + m; i < n; i++)
  {
    if(i != k)
    {
      strcpy(wordRight[j], word[i]);
      freqRight[j] = freq[i];
      ++j;
    }
  }

  *bSearchVal= malloc(sizeof(bSearch));
  (*bSearchVal)->key = malloc(sizeof(char) * 20);

  strcpy((*bSearchVal)->key, node);
  (*bSearchVal)->freq = nodeFreq;

  free(node);

  createTree(wordLeft, freqLeft, (&(*bSearchVal)->leftSub), tempLeft);
  createTree(wordRight, freqRight, (&(*bSearchVal)->rightSub), tempRight);


}


void getKeyAndFreq(char str[2045][2045], char word[599][20], float freq[599], int count)//obtains key and its frequency
{

  int total = 0;
  int i;
  char initialWord[20];
  for(i = 0; i < count; i++)
  {
    strcpy(initialWord, str[i]);
    if(strcmp(str[i],initialWord) == 0)
    {
      total++;
    }
    else
    {

    }
  }
  int value = 0;  
  float c;
  int j;
  int counterInArray = 0;
  for(i=1; i<count; i++)
  {
      c=1;
      counterInArray++;

      for(j=i+1; j<count; j++)
      {

           if(strcmp(str[i],str[j]) == 0)
           {
              c++;
           }
           else
           {
            break;
           }
      }
    
      c = c / count;

      if(strcmp(str[i], str[i-1]) == 0)
      {
      }
      else
      {
        value++;
        if(c > 1)
        {

          freq[value]=c;
          strcpy(word[value],str[i]);
        }
        else
        {   
          freq[value]=c;
          strcpy(word[value],str[i]);

        }


      }


              
  }

}





