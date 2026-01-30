#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lauxlib.h>
#include <lualib.h>
#include <lua.h>
#include <curl/curl.h>

CURL* curl;
CURLcode cc;

int main(int argc,const char* argv[]){
    lua_State* L = luaL_newstate();
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(argc == 3){
        if(strcmp(argv[1],"get")==0){
            printf("getting %s...\n",argv[2]);
            char* packageID = argv[2];    

        }
        if (strcmp(argv[1],"load")){
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "./%s", argv[2]);
            if(luaL_dofile(L,filepath)==LUA_OK){
                if(curl){

                }else{
                    printf("couldn't initaize CURL");
                }
            }
            else{
                printf("%s doesn't exist or worng directory",filepath);
            }
        }else{
            printf("unknown argument!:%s",argv[1]);
        }
    }
    return 0;
}