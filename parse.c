#include "parse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Resposta: {"translations":[{"text":"Olá, mundo","detected_source_language":"EN"}]}

void parse_response(char *response){
    int index = 25; //25 = "
    int count_char = 0;
    int i = 0;
    char text_translate[200] = {};
    char language[100] = {};

    printf("Translation: ");
    while(count_char < 2){
        if(response[index] == '"'){
            count_char++;
        }
        //printf("%c", response[index]);
        text_translate[i] = response[index];
        index++;
        i++;
    }
    text_translate[i] = '\0';
    i = 0;
    while(text_translate[i] != '\0'){
        printf("%c", text_translate[i]);
        i++;
    }
    printf("\n");
    i = 0;
    count_char = 0;
    while(count_char < 3){
        if(response[index] == '"'){
            count_char++;
        }
        index++;
    }
    count_char = 0;
    while(count_char < 1){
        language[i] = response[index];
        if(response[index] == '"'){
            count_char++;
        }
        index++;
        i++;
       // printf("%c", response[index]);
    }
    language[i - 1] = '\0';
    i = 0;
    printf("Language: ");
    while(language[i] != '\0'){
        printf("%c", language[i]);
        i++;
    }
}

char* join_args(int argc, char *argv[], int start_index){
if (start_index >= argc) {
        return NULL; 
    }
    int total_length = 0;
    for (int i = start_index; i < argc; i++) {
        total_length += strlen(argv[i]);
    }
    total_length += (argc - start_index - 1);

    char *frase = malloc(total_length + 1);
    if (frase == NULL) {
        return NULL;
    }
    
    frase[0] = '\0';

    for (int i = start_index; i < argc; i++) {
        strcat(frase, argv[i]);
        if (i < argc - 1) {
            strcat(frase, " ");
        }
    }
    return frase;

}
