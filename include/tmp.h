#ifndef TMP_H
#define TMP_H

#include <stddef.h>

#define malloc(x) break_malloc(x)

void *break_malloc(size_t size);

#endif