#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include "uuid.h"		//new_uuid() comes from this file


#define MAX 256


typedef struct person
{
  char id[MAX];
  char name[MAX];
  int age;
  struct person *next;
} person;



unsigned int
get_index (char *id, int *len)
{
  int length = strnlen (id, MAX);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++)
    {
      hash_value += id[i];
      hash_value = (hash_value * id[i]) % *len;
    }
  return hash_value;

}



void
hash_table_insert (person ** hash_table, person * p, int *len)
{
  char hash_output[UUID_STR_LEN] = { 0 };
  new_uuid (hash_output);
  strcpy (p->id, hash_output);
  int index = get_index (p->id, len);
  p->next = hash_table[index];
  hash_table[index] = p;
  return;
}


void
resize_table (person ** hash_table, int *len)
{
  printf ("\n");
  printf ("start resize function\n");
  *len = *len * 2;
  hash_table = realloc (hash_table, sizeof (person *) * *len);
  person tmp_table[*len];
  int x = 0;
  for (int i = 0; i < *len; i++)
    {
      if (hash_table[i] == NULL)
	{
	  printf ("\\t---\n");
	  hash_table[i] = NULL; 
	}
      else
	{
	  person *tmp = hash_table[i];
	  while (tmp != NULL)
	    {
	      printf ("%s -", tmp->id);
	      tmp_table[x] = *tmp;
	      tmp = tmp->next;
	      x++;
	      tmp = NULL;
	    }
	  hash_table[i] = NULL;
	  printf ("\n");
	}
    }

  for (int i = 0; i < *len; i++)
    {

      int index = get_index (tmp_table[i].id, len);
      tmp_table[i].next = hash_table[index];
      hash_table[index] = &tmp_table[i];

    }

  printf ("end resize function\n");
  printf ("printing table\n");
  for (int i = 0; i < *len; i++)
    {
	  person *tmp = hash_table[i];
	  while (tmp != NULL)
	    {
	      printf ("%s -", tmp->id);
	      tmp = tmp->next;
	    }
	  printf ("\n");
    }
  printf ("end of table\n");
  return;

}


void
print_table (person ** hash_table, int *len)
{
  printf ("printing table\n");
  printf ("size of table%d\n", *len);
  for (int i = 0; i < *len; i++)
    {
      if (hash_table[i] == NULL)
	{
	  printf ("\\t---\n");
	}
      else
	{
	  person *tmp = hash_table[i];
	  while (tmp != NULL)
	    {
	      printf ("%s -", tmp->id);
	      tmp = tmp->next;
	    }
	  printf ("\n");
	}
    }
  printf ("end of table\n");
}


int
main ()
{
  int len = 10;
  person **hash_table;
  hash_table = malloc (sizeof (person *) * len);

  person kate = {.id = "",.name = "kate",.age = 15 };
  person jared = {.id = "",.name = "jared",.age = 17 };
  person mark = {.id = "",.name = "mark",.age = 19 };
  person sally = {.id = "",.name = "sally",.age = 21 };
  person eliza = {.id = "",.name = "eliza",.age = 10 };

  hash_table_insert (hash_table, &kate, &len);
  hash_table_insert (hash_table, &jared, &len);
  hash_table_insert (hash_table, &mark, &len);
  hash_table_insert (hash_table, &sally, &len);
  hash_table_insert (hash_table, &eliza, &len);

  print_table (hash_table, &len);
  resize_table (hash_table, &len);
//  print_table (hash_table,&len);

  return 0;


}
