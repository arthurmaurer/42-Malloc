
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "malloc.h"

void	*malloc(size_t size)
{
	assert(MALLOC_SMALL_CHUNK_SIZE > MALLOC_TINY_CHUNK_SIZE);
	printf("ok\n");
	if (size == 0)
		return (NULL);

	return (allocate_block(size));
}
