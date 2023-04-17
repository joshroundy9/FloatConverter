/*
ICSI 333. System Fundamentals, Spring 2023
TA: Kazi Kibria
Developer: Joshua Roundy, Student ID: 001518993                            
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pl_lib.h"
//Structure for the nodes of the linked lists below
struct node{
  float value;
  struct node *next;
  int formatted[32];
  float restored;
};
//each points to the head of one of the four linked lists
struct node *list1 = NULL;
struct node *list2 = NULL;
struct node *list3 = NULL;
struct node *list4 = NULL;
//generates as many random numbers up to 1000 according to the integer fed in
double  * generateRandomNumbers(int numberOfElements)
{
  //the array to hold each number
  static double  numbers[1000];
  srand(time(NULL));
  for(int i = 0;i<numberOfElements;i++){
  numbers[i] = -100.0 + (double )rand()/(double )(RAND_MAX/200);
  numbers[i] = floor(1000000*numbers[i])/1000000;}
  return numbers;
}
void createLists(double  *array, int numberOfElements)
{
  for(int i = 0;i<numberOfElements;i++)
  {
    //used to check if the restored value is accurate to the input (often off by ~0.000001 due to the storage method not being double precision)
    struct node *temp = (struct node*) malloc(sizeof(struct node));
    int * ieee =convertToIEEE754(array[i],temp->formatted);
    double restored =restore(ieee);
    
    //checks if the numbers are equal and reports them to stderr if not equal
    if((float)array[i] < (float)restored-0.000008 || (float)array[i] > (float)restored+0.000008)
    fprintf(stderr, "The number %f had an invalid conversion to %lf\n",array[i],restored);
    //the new head of the node 
    
    //assigns the previously determined values to the structure
      temp->value = array[i];
      temp->restored = restore(temp->formatted);
      //depending on the value of the number the structure is assigned to one of four linked lists
    if(array[i] >=1){ 
      if(list1 == NULL)
      list1 = temp;
      else {
        temp->next = list1;
        list1 = temp;}
    } else if(array[i]>0){
      if(list2 == NULL)
      list2 = temp;
      else {
        temp->next = list2;
        list2 = temp;}
    }else if(array[i]<0 && array[i]>-1){
      if(list3 == NULL)
      list3 = temp;
      else {
        temp->next = list3;
        list3 = temp;}
    }else{
      if(list4 == NULL)
      list4 = temp;
      else {
        temp->next = list4;
        list4 = temp;}
    }
  }
}
//prints all the four lists to the console (debugging only)
void printLists()
{
  printf("LIST1[");
  //node used to represent the head of each linked list when printing their values
  struct node *temp = list1;
  while(temp!=NULL)
  {
    printf(" %f",temp->value);
    temp = temp->next;
  }
  printf("]\n");
  printf("LIST2[");
  temp = list2;
  while(temp!=NULL)
  {
    printf(" %f",temp->value);
    temp = temp->next;
  }
  printf("]\n");
  printf("LIST3[");
  temp = list3;
  while(temp!=NULL)
  {
    printf(" %f",temp->value);
    temp = temp->next;
  }
  printf("]\n");
  printf("LIST4[");
  temp = list4;
  while(temp!=NULL)
  {
    printf(" %f",temp->value);
    temp = temp->next;
  }
  printf("]\n");
}
int main(int argc, char *argv[])
{
    printf("PROGRAM START:\n");
    //asks how many numbers to be generated and added to the lists
    if(argc != 3) 
    {
      printf("\nMust have 2 arguments 1: the # of random numbers to generate and 2: the file extension to be used.\n");
      return 1;
    }
    //pointer used as the error message if strtod fails
    char *p;
    //the number of random numbers requested in the command line arguments
    int numOfRandoms = (int)strtod(argv[1],&p);
    if(numOfRandoms <1 || numOfRandoms>1000)
    {
      printf("\nNumber of randoms generated must be between 1 and 1000.\n");
      return 1;
    }
    //ask the user for an extension to add to the names of the four files.
    //the base name of each extension
    char neg[20] = "neg", pos[20] = "pos", neg_frac[20] = "neg_frac", pos_frac[20] = "pos_frac";
    //string used to take on the value for the file extension
    char ext[10];
    //copies the data from the second argument asking for the file extension to the previously defined ext string
    strcpy(ext,argv[2]);
    //concatenates each base name with the file extension given
    strcat(neg,ext);strcat(pos,ext);strcat(neg_frac,ext);strcat(pos_frac,ext);


    //int numbersGenerated = (int)getInput();
    //generate random -100.0 to +100.0
    double  *numbers; 
    numbers= generateRandomNumbers(numOfRandoms);
    /*for each random generated, add it to one of four linked lists: 
      positive numbers >1 negative numbers < -1 positive fractions and negative fractions*/
      //nodes must contain the number, and the output of project 1 stored in a structure.
    createLists(numbers,numOfRandoms);

   //printLists();
    //puts the data in the files
    //save the linked lists to the four respective files
    FILE *f1ptr,*f2ptr,*f3ptr,*f4ptr; // pointers to each of the four respective files.
    f1ptr = fopen(pos,"w");f2ptr = fopen(pos_frac,"w");f3ptr = fopen(neg_frac,"w");f4ptr = fopen(neg,"w");
    while(list1 != NULL)
    { fprintf(f1ptr,"%f\n",list1->value);printIEEE754ToFile(f1ptr,list1->formatted);fprintf(f1ptr,"%f\n",list1->restored);
      list1 = list1->next;}
    fclose(f1ptr);
    while(list2 != NULL)
    { fprintf(f2ptr,"%f\n",list2->value);printIEEE754ToFile(f2ptr,list2->formatted);fprintf(f2ptr,"%f\n",list2->restored);
      list2 = list2->next;}
    fclose(f2ptr);
    while(list3 != NULL)
    { fprintf(f3ptr,"%f\n",list3->value);printIEEE754ToFile(f3ptr,list3->formatted);fprintf(f3ptr,"%f\n",list3->restored);
      list3 = list3->next;}
    fclose(f3ptr);
    while(list4 != NULL)
    { fprintf(f4ptr,"%f\n",list4->value);printIEEE754ToFile(f4ptr,list4->formatted);fprintf(f4ptr,"%f\n",list4->restored);
      list4 = list4->next;}
    fclose(f4ptr);
    
    
    
    printf("SUCCESS: Check for files neg, pos, pos_frac, and neg_frac\nin the same directory as this program with the extension %s.\n",ext);
    return 0;
}