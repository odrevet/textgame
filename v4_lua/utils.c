#include "utils.h"

void flush_in()
{
  int c = 0;
  while (c != '\n' && c != EOF){c = getchar();}
}

char is_in_list(char* word_list, char* word, char* separator)
{
  char* token;
  char* str = strdup(word_list);
  token = strtok (str, separator);
  while (token != NULL)
    {
      if(!strcmp(token, word)){
	free(str);
	return 1;
      }
      token = strtok (NULL, separator);
    }

  free(str);
  return 0;
}



