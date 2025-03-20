#include "../include/pipex.h"

static int count = 0;

void *break_malloc(size_t size)
{
	if (--count == 0)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return ((malloc)(size));
}