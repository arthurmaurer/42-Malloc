
#include <string.h>
#include "malloc.h"

static void	*realloc_smaller(void *ptr, t_block *block, size_t size)
{
	split_block(block, size);
	return (ptr);
}

static void	*realloc_larger(void *ptr, t_block *block, size_t size)
{
	t_block	*next;
	void	*new_ptr;

	next = block->next;

	if (next != NULL && next->free && next->size + MALLOC_BLOCK_SIZE >= size)
	{
		merge_block_with_next(block);
		split_block(block, size);
		return (ptr);
	}
	else
	{
		new_ptr = allocate_block(size);
		memcpy(new_ptr, ptr, size);
		block->free = 1;
		return (new_ptr);
	}
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*block;

	if (ptr == NULL)
		return (NULL);

	block = get_data_block(ptr);

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (size == block->size)
		return (ptr);
	else if (size < block->size)
		return (realloc_smaller(ptr, block, size));
	else
		return (realloc_larger(ptr, block, size));
}
