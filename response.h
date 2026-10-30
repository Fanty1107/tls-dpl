#ifndef RESPONSE_H
#define RESPONSE_H

#include <stddef.h>

struct Memory {
    char *response;
    size_t size;
};

size_t ResponseCallback(void *contents, size_t size,
                        size_t nmemb, void *userp);

#endif

