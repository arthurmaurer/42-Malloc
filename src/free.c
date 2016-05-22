
#include "malloc.h"

void	free(void *ptr)
{
	t_block	*block;

	if (ptr == NULL)
		return;

	block = get_data_block(ptr);
	block->free = 1;

#ifdef MALLOC_MERGE_ON_FREE
	merge_next_free_blocks(block);
#endif
}
