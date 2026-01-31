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
        /*if(strcmp(argv[1],"get")==0){
            printf("getting %s...\n",argv[2]);
            char* packageID = argv[2];
            char* data[4096];
            snprintf(packageID,sizeof(packageID),"https://localhost:9080/core/%s",packageID);
            if(curl){
                    curl_easy_setopt(curl,CURLOPT_URL,packageID);
            }else{
                    printf("couldn't initaize CURL");
            }
        }*/
        if(strcmp(argv[1],"localget")){
            printf("working on %s",argv[2]);
            char* localPackage;
            snprintf(localPackage,sizeof(localPackage),"tar -xf %s.tar.gz",localPackage);

        }
        if (strcmp(argv[1],"load")){
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "./%s", argv[2]);
            if(luaL_dofile(L,filepath)==LUA_OK){
                
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