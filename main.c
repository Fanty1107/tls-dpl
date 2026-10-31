#include "parse.h"
#include "response.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//compile with -lcurl and dont forget your api_key
int main(int argc, char *argv[]) {
    const char *api_key = getenv("DEEPL_AUTH_KEY");
    if (api_key == NULL || api_key[0] == '\0') {
        fprintf(stderr, "Define env DEEPL_AUTH_KEY.\n");
        return 1;
    }
    if(argc < 2){
        fprintf(stderr, "Enter the text arg for translate");
        return 1;
    }

    CURLcode global_result = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (global_result != CURLE_OK) {
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error on create handle curl.\n");
        curl_global_cleanup();
        return 1;
    }

    struct Memory chunk = { malloc(1), 0 };
    if (chunk.response == NULL) {
        fprintf(stderr, "Error on memory allocation.\n");
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 1;
    }
    chunk.response[0] = '\0';

    char auth_header[200];
    snprintf(auth_header, sizeof(auth_header),
             "Authorization: DeepL-Auth-Key %s", api_key);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char json_response[1024];
    const char *text = join_args(argc, argv, 1);
    const char *idioma = "PT-BR";
    snprintf(json_response, sizeof(json_response), "{\"text\":[\"%s\"],\"target_lang\":\"%s\"}",text,idioma);
    const char *json = json_response;

    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://api-free.deepl.com/v2/translate");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(json));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ResponseCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Erro na requisição: %s\n",
                curl_easy_strerror(res));
    } else {
        long http_status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);

        printf("HTTP status: %ld\n", http_status);
        parse_response(chunk.response);
        //printf("Resposta: %s\n", chunk.response);
        //Resposta: {"translations":[{"text":"Olá, mundo","detected_source_language":"EN"}]}
    }

    free(chunk.response);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return res == CURLE_OK ? 0 : 1;
}

