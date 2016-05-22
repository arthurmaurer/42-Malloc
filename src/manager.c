
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "malloc.h"

static void		*allocate_raw(size_t size)
{
	return (mmap(NULL, size, PROT_READ | PROT_WRITE, 
				 MAP_PRIVATE | MAP_ANON, -1, 0));
}

t_block			*get_data_block(void *ptr)
{
	t_block	*block;

	block = (t_block*)ptr;
	--block;

	return (block);
}

static size_t	get_chunk_size(size_t size)
{
	if (IS_TINY(size))
		return (MALLOC_TINY_CHUNK_SIZE);
	if (IS_SMALL(size))
		return (MALLOC_SMALL_CHUNK_SIZE);
	else
		return (size);
}

static t_block	*memory_go_to(t_block *block, size_t offset)
{
	return ((t_block*)((char*)block + offset));
}

static t_block	*allocate_chunk(size_t size)
{
	t_block	*block;
	int		page_number;
	size_t	allocation_size;

	printf("new chunk\n");
	page_number = (size + MALLOC_BLOCK_SIZE) / MALLOC_PAGE_SIZE + 1;

	allocation_size = MALLOC_PAGE_SIZE * page_number;
	printf("size: %zu\n", size);
	printf("alloc size: %zu\n", allocation_size);
	printf("page number: %i\n", page_number);
	block = allocate_raw(allocation_size);
	update_block(block, allocation_size - MALLOC_BLOCK_SIZE, NULL, 1);

	return (block);
}

static t_block	*get_block_list(size_t size)
{
	t_manager	*manager;
	t_block		**block_list;
	size_t		chunk_size;

	manager = get_manager();

	if (IS_TINY(size))
		block_list = &manager->tiny_blocks;
	else if (IS_LARGE(size))
		block_list = &manager->small_blocks;
	else
		block_list = &manager->large_blocks;

	if (*block_list == NULL)
	{
		chunk_size = get_chunk_size(size);
		*block_list = allocate_chunk(chunk_size);
	}

	return (*block_list);
}

static int		is_block_suitable(const t_block *block, size_t size)
{
	return (block->free && block->size >= size);
}

static t_block	*find_suitable_block(t_block *block, size_t size)
{
	while (block)
	{
		if (is_block_suitable(block, size))
			return (block);
		
		block = block->next;
	}

	return (NULL);
}

void		*get_block_data(t_block *block)
{
	return (block + 1);
}

static void	append_block(t_block *block_list, t_block *block)
{
	while (block_list)
	{
		if (block_list->next == NULL)
		{
			block_list->next = block;
			return ;
		}

		block_list = block_list->next;
	}
}

void	split_block(t_block *block, size_t size)
{
	t_block	*next_block;

	if (block->size > size + MALLOC_BLOCK_SIZE)
	{
		next_block = memory_go_to(block, size + MALLOC_BLOCK_SIZE);
		
		update_block(next_block, block->size - size - MALLOC_BLOCK_SIZE, block->next, 1);
		update_block(block, size, next_block, 0);
	}
	else
	{
		block->free = 0;
	}
}

void		merge_block_with_next(t_block *block)
{
	t_block	*next;

	next = block->next;

	if (next == NULL)
		return;

	block->size += next->size + MALLOC_BLOCK_SIZE;
	block->next = next->next;
}

void		merge_next_free_blocks(t_block *block)
{
	while (block != NULL && block->next != NULL)
	{
		if (!block->next->free)
			return;

		merge_block_with_next(block);
		block = block->next;
	}
}

void		update_block(t_block *block, size_t size, t_block *next, int free)
{
	block->size = size;
	block->next = next;
	block->free = free;
}

void		iterate(t_block *block, void (*f)(t_block*, void *), void *arg)
{
	while (block)
	{
		f(block, arg);
		block = block->next;
	}
}

t_manager	*get_manager(void)
{
	static t_manager	*manager;

	if (manager == NULL)
	{
		manager = allocate_raw(sizeof(t_manager));
		manager->tiny_blocks = NULL;
		manager->small_blocks = NULL;
		manager->large_blocks = NULL;
	}

	return (manager);
}

void		*allocate_block(size_t size)
{
	t_block	*block_list;
	t_block	*block;

	block_list = get_block_list(size);
	block = find_suitable_block(block_list, size);

	if (block == NULL)
	{
		block = allocate_chunk(size);
		append_block(block_list, block);
	}

	if (IS_LARGE(size))
		block->free = 0;
	else
		split_block(block, size);

	return (get_block_data(block));
}
