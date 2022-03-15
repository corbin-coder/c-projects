#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include "uuid.h"


#define MAX_ID 256
//#define TABLE_SIZE 10
//int TABLE_SIZE = 10;


typedef struct person
{
  char id[MAX_ID];
  char name[MAX_ID];
  int age;
  struct person *next;
} person;



unsigned int
hash (char *id, int *len)
{
  int length = strnlen (id, MAX_ID);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++)
    {
      hash_value += id[i];
      hash_value = (hash_value * id[i]) % *len;
    }
  return hash_value;

}


void
print_table (person ** pp,int *len)
{
  printf ("printing table%d\n", *len);
  for (int i = 0; i < *len; i++)
    {
      if (pp[i] == NULL)
	{
	  printf ("\\t---\n");
	}
      else
	{
	  printf ("\t%i\t", i);
	  person *tmp = pp[i];
	  while (tmp != NULL)
	    {
	      printf ("%s -", tmp->id);
	      tmp = tmp->next;
	    }
	  printf ("\n");
	}
    }
  printf("end\n");
}


void
hash_table_insert (person ** pp, person * p, int *len)
{
  if ( p != NULL){
  char out[UUID_STR_LEN] = { 0 };
  new_uuid (out);
  strcpy (p->id, out);
  }
  int index = hash (p->id, len);
  p->next = pp[index];
  pp[index] = p;
  return;
}






void
resize_table (person ** pp,int *len)
{
  *len = *len * 2;
  pp = realloc (pp, sizeof (person *) * *len);


}

int
main ()
{
  int len = 10 ;
  person **hash_table;
  hash_table = malloc (sizeof (person *) * len);

  person kate = {.id = "",.name = "kate",.age = 15 };
  person jared = {.id = "",.name = "jared",.age = 17 };
  person mark = {.id = "",.name = "mark",.age = 19 };
  person sally = {.id = "",.name = "sally",.age = 21 };
  person eliza = {.id = "",.name = "eliza",.age = 10 };

  hash_table_insert (hash_table,&kate, &len);
  hash_table_insert (hash_table,&jared, &len);
  hash_table_insert (hash_table,&mark, &len);
  hash_table_insert (hash_table,&sally, &len);
  hash_table_insert (hash_table,&eliza, &len);

  print_table (hash_table,&len);
  //resize_table (hash_table,&len);
 // print_table (hash_table,&len);

  return 0;


}
