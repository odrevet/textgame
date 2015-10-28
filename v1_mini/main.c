#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"

char* strdup(const char*);

int main(void)
{
  //game vars
  got_towel = 0;
  got_babelfish = 0;

  char done = 0;
  char cmd[32];
	
  struct place* current = malloc(sizeof(struct place));
	
  current->text = strdup("Je suis dans mon lit, l'aube pointe a peine a travere les rideaux de la fenetre");
  current->funct = room_first;
	
  do{
    puts(current->text);
	
    puts("Que faire ? ");
    gets(cmd);

    if(current->funct(cmd, current) == 0)
      {
	printf("Je ne sais pas comment '%s'\n", cmd);
      }
		
  }while(done == 0);
	
  free(current->text);
  free(current);
}
