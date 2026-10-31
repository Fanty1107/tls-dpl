#ifndef PARSE_H
#define PARSE_H

void parse_response(char *response);
char* join_args(int argc, char *argv[], int start_index);
const char* get_api();

#endif//PARSE_H
