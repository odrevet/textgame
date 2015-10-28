#include <stdio.h>
#include <stdlib.h>

#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>

#include "utils.h"
#define BUFFER_SIZE 256

int main(int argc, char** argv)
{
  char done = 0;
  char has_on_cmd;
  char cmd[BUFFER_SIZE];
  char const* ret_code = "stay";
  char const* cur_funct = "root";
	
  lua_State* L;
  L = lua_open();
  luaL_openlibs(L);
	
  if (argc<2){
    printf("usage: %s <script_name>\n",argv[0]);
    return 0;
  }
	
  if (luaL_dofile(L, argv[1])!=0){
    fprintf(stderr,"%s\n",lua_tostring(L,-1));
    return 0;
  }
	
  lua_getglobal(L, "on_cmd");									//call the lua function on_cmd at each command (for user script)
  if (lua_isfunction(L,-1))has_on_cmd = 1;
  else has_on_cmd = 0;
  lua_pop(L,1);
	
  lua_pushstring(L, cur_funct);
  lua_setglobal(L, "cur_funct");
  lua_getglobal(L, cur_funct);
  if (!lua_isfunction(L,-1)) {
    puts("The game script must contains a root function where begin.");
    return EXIT_FAILURE;
  }
  lua_call(L,0,1);
  cur_funct = lua_tostring(L,-1);	
	
  do{			
    printf("> ");
    fgets(cmd, BUFFER_SIZE, stdin);
    char* lf = strchr(cmd, '\n');
    if (lf != NULL){*lf = '\0';lf=NULL;}else{flush_in();}
	
    if(has_on_cmd){
      lua_getglobal(L, "on_cmd");									//call the lua function on_cmd at each command (for user script)
      lua_pushstring(L, cmd);
      lua_call(L,1,2);
      ret_code = lua_tostring(L,-2);
      if(!strcmp(ret_code, "new_location")){
	cur_funct = lua_tostring(L,-1);
      }
    }
	
    lua_getglobal(L, cur_funct);		//get the lua function with the name of cur_funct
    lua_pushstring(L, cur_funct);		//the name is pushed to call this function later
    lua_setglobal(L, "cur_funct");		//the lua variable cur_funct is updated with the current name (for user script)
		
    if(!has_on_cmd || strcmp(ret_code, "was_cmd")){
      if (lua_isfunction(L,-1)){
	lua_pushstring(L,cmd);
	lua_call(L,1,1);
				
	const char* prev_code = ret_code;
	ret_code = lua_tostring(L,-1);
				
	if(!strcmp(ret_code, "unknow"))
	  {
	    if(strcmp(prev_code, "new_location"))printf("'%s' impossible\n", cmd);
	  }
	else if(strcmp(ret_code, "stay")){
	  cur_funct = ret_code;
	}
				
      }
      else{
	printf("Error, can't call function %s\n", cur_funct);
	lua_pop(L,1);
	done=1;
      }
    }
		
    if(!strcmp(ret_code, "quit")){
      done = 1;break;
    }
		
  }while(done == 0);
	
  return EXIT_SUCCESS;
}
