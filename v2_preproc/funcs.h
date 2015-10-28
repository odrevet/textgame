#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_ROOM_FIRST      "Il fait trop noir pour voir quoi que se soit"
#define TEXT_ROOM_HILIGHTED  "Ma chambre..."

#define KEYWORD_LOOK	      "regarder"
#define KEYWORD_GO            "aller"

char got_towel;
char got_babelfish;

struct place{
  char* text;
  char (*funct)(char* cmd, struct place* current);
};

char room_first(char* cmd, struct place* current);
char room_hilighted(char* cmd, struct place* current);
char room_bathroom(char* cmd, struct place* current);
char street_in_front_house(char* cmd, struct place* current);


#endif
