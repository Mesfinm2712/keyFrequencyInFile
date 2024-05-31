/*Mebea Mesfin */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct bstbSearch {
  struct bstbSearch * leftSub;
  struct bstbSearch * rightSub;
  char * key;
  float count;
} bSearch;


bSearch *  dataRead(bSearch * firstElem, FILE * fp);
void calculateFloatVal(float total, bSearch *bSearchElement) ;
void goThroughTree(void (*function)(float total, bSearch * bSearch), bSearch *searchElem) ;
float arrayFloatVal(float val);
bSearch * findElement(bSearch * root, int num, char * key);
bSearch * inputToTree(int index1, bSearch * searchVal, int index2);
bSearch * bSearchKeyFreq(char * key, int wordVal, bSearch * searchElem);

char * treeString[999];
float arrayFloat[999][999], tempArrVal[999];
int num= 0, totalArrVal[999][999];
float count = 0;


void q1Answer(char theFile[12]) //main function that calls all helper functions
{
  strcpy(theFile, "data_7.txt");
  char userInput[50];

  bSearch * firstElem = NULL;
  FILE * fp = fopen(theFile, "r");
  firstElem = dataRead(firstElem, fp);

  bSearch * searchVal = NULL;
  goThroughTree(calculateFloatVal, firstElem);
  float temp = 0;
  arrayFloatVal(temp);

  num= num- 1;
  bSearch * finalSearch = inputToTree(1,searchVal,num);


  printf("Enter a key: ");
  scanf("%s", userInput);

  int num = 0;
  findElement(finalSearch, num, userInput);

}
bSearch * findElement(bSearch * root, int num, char * key) //outputs to terminal path through tree
{
	if (root != NULL)
	{
		num = strcmp(key, root->key);

		if (num < 0) 
		{
		  printf("Compared with %s (%.2f), go left subtree.\n", root->key, root->count);
		  root->leftSub = findElement(root->leftSub,num, key);
		} 
		else if (num > 0) 
		{
		  printf("Compared with %s (%.2f), go right subtree.\n", root->key, root->count);
		  root->rightSub = findElement(root->rightSub,num, key);
		} 
		else 
		{
		  printf("Compared with %s (%.2f), found.\n", root->key, root->count);
		}
	} 
	else 
	{
		printf("%s not found.\n", key);
	}
	
	return root;
}


bSearch * dataRead(bSearch * firstElem, FILE * file) //reads data from file
{
  char input[50];
  int totalArrValNum = 0, letter = 0; 

  while ((letter = fgetc(file)) != EOF) 
  {

    if (letter != '\r' && letter != '\t' && letter != ' ' && letter != '\0' && letter != '\n') 
    {

    	input[totalArrValNum] = letter;
      	totalArrValNum = totalArrValNum + 1;
    } 
    else 
    {
    	if(totalArrValNum <= 0)
    	{
    		//continue
    	}
    	else
        { 
        	if(totalArrValNum != 0)
        	{
	        	input[totalArrValNum] = '\0';
        	}
        	int wordVal = 0;
	        firstElem = bSearchKeyFreq(input, wordVal, firstElem);
	        count = count + 1;
	        totalArrValNum = 0;
      	}
    }
  }
  fclose(file);
  return firstElem;
}

float arrayFloatVal(float minval) //get array values in float
{
  float sum = 0;
  int start = 0, count = 0, i = 0 ,j = 0, m = 0, list = 0, begVal = 0, temp = num;

  for (i = 1; i <= temp; i++) 
  {
    totalArrVal[i][i] = i;
    arrayFloat[i][i] = tempArrVal[i];
  }

  for (start = 1; start < temp; start++) 
  {

    for (i = 1; i <= temp-start; i++) 
    {
      list = 0;
      minval = 100000;
      begVal = 0;
      j = i+start;

      for (list = i; list <= j; list++) 
      {
        if (minval <= (arrayFloat[i][list-1]+arrayFloat[list+1][j]))
        {
        	//continue
        }
        else
        {
          begVal = list;
          minval= arrayFloat[i][list-1] + arrayFloat[list+1][j];
        }
      }
      if(count == 0)
      {
	      totalArrVal[i][j] = begVal;
	      sum = tempArrVal[i];
	      int temp = i + 1;

	      for(m = temp; m <= j; m++) 
	      {
	        sum = sum + tempArrVal[m];
	      }
	      arrayFloat[i][j] = minval + sum;
      }
    }
  }

  minval = arrayFloat[1][temp];


  return minval;
}
void calculateFloatVal(float total, bSearch *bSearchElement) //calcualtes main and root tables
{
	total = 0;
	total = (float)bSearchElement->count/count;
  	tempArrVal[num] = total;
  	treeString[num] = bSearchElement->key;
  	num = num + 1;
}
void goThroughTree(void (*function)(float total, bSearch * bSearch), bSearch *searchElem) //goes through the tree to get values
{
  if(searchElem == NULL) 
  {
    return;
  }
  if (searchElem->leftSub == NULL) 
  {
  	//continue
  }
  else
  {
    goThroughTree(function, searchElem->leftSub);
  }

  float total = 0;
  function(total, searchElem);

  if (searchElem->rightSub == NULL) 
  {
  	//continue
  }
  else
  {
    goThroughTree(function, searchElem->rightSub);
  }
}

bSearch * bSearchKeyFreq(char * key, int wordVal, bSearch * searchElem)//go through the keys frequencys
{

  if (searchElem != NULL)
  {
    wordVal = strcmp(key, searchElem->key);

    if (wordVal == 0) 
    {
      searchElem->count = searchElem->count + 1;
    } 
    else if (wordVal > 0) 
    {
      searchElem->rightSub = bSearchKeyFreq(key, wordVal, searchElem->rightSub);
    } 
    else 
    {
      searchElem->leftSub = bSearchKeyFreq(key, wordVal, searchElem->leftSub);
    }
  } 
  else
  {
  	  bSearch * newbSearch = (bSearch*)malloc(sizeof(bSearch));
  	  int num = strlen(key);
	  char * temp = malloc(sizeof(char)*(num+1));
	  newbSearch->rightSub = NULL;
	  newbSearch->leftSub = NULL;
	  newbSearch->count = 1;
	  strcpy(temp, key);
	  newbSearch->key = temp;
	  return newbSearch;
  }

  return searchElem;
}


bSearch * inputToTree(int index1, bSearch * searchVal, int index2)//input the values into the tree (recursively)
{

  if(index2 >= index1)
  {
  	int temp = 1;
    searchVal = (bSearch *) malloc(sizeof(bSearch));
    searchVal->count = arrayFloat[index1][index2];

    searchVal->key = malloc(sizeof(char)*(strlen(treeString[totalArrVal[index1][index2]])+temp));
    strcpy(searchVal->key, treeString[totalArrVal[index1][index2]]);

    searchVal->leftSub = inputToTree(index1,searchVal, totalArrVal[index1][index2]-temp);
    searchVal->rightSub = inputToTree(totalArrVal[index1][index2]+temp, searchVal, index2);
  }
  else
  {
    return NULL;
  }

  return searchVal;
}

