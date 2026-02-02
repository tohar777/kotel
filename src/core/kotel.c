#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}
static int valid_package_name(const char *name)
{
    for (const char *p = name; *p; p++) {
        if (!(
            (*p >= 'a' && *p <= 'z') ||
            (*p >= 'A' && *p <= 'Z') ||
            (*p >= '0' && *p <= '9') ||
            *p == '.' || *p == '_' || *p == '-'
        )) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, const char *argv[])
{
    int ret = 1;
    lua_State *L = NULL;
    CURL *curl = NULL;

    if (argc < 3)
    {
        fprintf(stderr,
            "Usage: %s get|localget|load <org.example.name>\n",
            argv[0]);
        return 1;
    }

    if (!valid_package_name(argv[2])) {
        fprintf(stderr, "Invalid package name\n");
        return 1;
    }

    L = luaL_newstate();
    if (!L) {
        fprintf(stderr, "Failed to init Lua\n");
        goto cleanup;
    }
    luaL_openlibs(L);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "Failed to init curl\n");
        goto cleanup;
    }

    
    if (strcmp(argv[1], "get") == 0)
    {
        char url[1024];
        char filename[1024];
        char cmd[2048];

        snprintf(url, sizeof(url), "http://localhost:3000/repo/%s.tar.gz", argv[2]);
        snprintf(filename, sizeof(filename),"%s.tar.gz", argv[2]);

        printf("Getting %s...\n", argv[2]);

        FILE *fp = fopen(filename, "wb");
        if (!fp)
        {
            perror("fopen");
            goto cleanup;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        /* DEV ONLY: self-signed cert */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);
        fclose(fp);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Download failed: %s\n",
                    curl_easy_strerror(res));
            goto cleanup;
        }

        printf("Download complete\n");
        printf("executing tar...\n");
        snprintf(cmd, sizeof(cmd),
                 "tar -xzf %s", filename);

        if (system(cmd) != 0) {
            fprintf(stderr, "Extraction failed\n");
            goto cleanup;
        }
        char lua[1024];
        snprintf(lua,sizeof(lua),"%s/installer.lua",argv[2]);
        if(luaL_dofile(L,lua) == LUA_OK){
            printf("launching installer.lua\n");
        }else{
            printf("couldn't open/found installer\n");
        }
    }

   
    else if (strcmp(argv[1], "localget") == 0)
    {
        char cmd[2048];

        snprintf(cmd, sizeof(cmd),
                 "tar -xzf %s.tar.gz", argv[2]);

        if (system(cmd) != 0) {
            fprintf(stderr, "Extraction failed\n");
            goto cleanup;
        }
    }

    else if (strcmp(argv[1], "load") == 0)
    {
        char filepath[1024];
        snprintf(filepath, sizeof(filepath),
                 "./%s", argv[2]);

        if (luaL_dofile(L, filepath) != LUA_OK)
        {
            fprintf(stderr, "Lua error: %s\n",
                    lua_tostring(L, -1));
            goto cleanup;
        }
    }

    else
    {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        goto cleanup;
    }

    ret = 0;

cleanup:
    if (curl)
        curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (L)
        lua_close(L);

    return ret;
}
