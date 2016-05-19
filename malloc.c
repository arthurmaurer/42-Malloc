
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "malloc.h"

void	*mymalloc(size_t size)
{
	assert(MALLOC_SMALL_CHUNK_SIZE > MALLOC_TINY_CHUNK_SIZE);

	if (size == 0)
		return (NULL);

	return (allocate_block(size));
}
