#include "response.h"

#include <stdlib.h>
#include <string.h>

size_t ResponseCallback(void *contents, size_t size,
                        size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + totalSize + 1);
    if (ptr == NULL)
        return 0;

    mem->response = ptr;
    memcpy(mem->response + mem->size, contents, totalSize);
    mem->size += totalSize;
    mem->response[mem->size] = '\0';

    return totalSize;
}

