#include "funcs.h"

char room_first(char* cmd, struct place* current)
{
  if(is_in_list(KEYWORD_LOOK, cmd, ";")){
    puts(TEXT_ROOM_FIRST);
    return 1;
  }
	
  if(!strcmp(cmd, "allumer")){
    puts("Je tapotte la table de chevet, ah ! j'attrape l'interrupteur...\nLa lumiere illumine la chambre !\nJe me leve sans plus attendre. ");
    free(current->text);
    current->text = strdup(TEXT_ROOM_HILIGHTED);
    current->funct = room_hilighted;
    return 1;
  }
	
  if(!strcmp(cmd, "se lever")){
    puts("Non, je n'ai aucune envie de me cogner dans le noir");
    return 1;
  }
	
  return 0;
}

char room_hilighted(char* cmd, struct place* current)
{
  if(is_in_list(KEYWORD_LOOK, cmd, ";")){
    puts("Ma chambre, avec la porte a droite, vers le couloir, et la porte a gauche, vers la salle de bain, tout ce qu'il y a de plus habituel");
    return 1;
  }
	
  if(!strcmp(cmd, "aller a gauche") || !strcmp(cmd, "aller salle de bain")){
    free(current->text);
    current->text = strdup("La salle de bain, avec le lavabo, et la baignoire avec les serviettes qui pendent a cote. Derriere une pile de linge sale se trouve la porte vers ma chambre");
    current->funct = room_bathroom;
    return 1;
  }
	
  if(!strcmp(cmd, "aller a droite") || !strcmp(cmd, "aller couloir")){
    if(got_towel == 0){
      puts("J'ai comme l'impression d'oublier un objet banale mais qui me sera tres utile aujourd'hui... je ferai mieux de trouver quoi avant de sortir");
    }
    else{
      puts("Me voila pret a partir !! Des aventures fantastiques vous attendent dans la prochaine version ! ");
      free(current->text);
      current->text = strdup("");
      current->funct = street_in_front_house;
    }
    return 1;
  }
	
  return 0;
}

char room_bathroom(char* cmd, struct place* current)
{
  if(is_in_list(KEYWORD_LOOK, cmd, ";")){
    puts(current->text);
    return 1;
  }
	
  if(!strcmp(cmd, "prendre serviette")){
    if(got_towel == 0){
      got_towel = 1;
      puts("Ca peut toujous servir...");
    }
    else{
      puts("J'ai deja une serviette");
    }
    return 1;
  }
	
  if(!strcmp(cmd, "aller chambre")){
    puts("Enjamber la pile de ligne sale n'etait pas facile, mais me revoila dans ma chambre");
    free(current->text);
    current->text = strdup(TEXT_ROOM_HILIGHTED);
    current->funct = room_hilighted;
    return 1;
  }
	
	
  return 0;
}

char street_in_front_house(char* cmd, struct place* current)
{
  puts("FIN");
  return 0;
}
