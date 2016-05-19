
#include <stdio.h>
#include "malloc.h"

static void	print_block(t_block *block, void *arg)
{
	char	*data;
	size_t	*total;

	if (block->free)
		return;

	total = (size_t*)arg;
	*total += block->size;
	data = get_block_data(block);
	printf("0x%p - 0x%p : %zu octets\n", data, data + block->size, block->size);
}

void		show_alloc_mem(void)
{
	t_manager	*manager;
	size_t		total;

	manager = get_manager();
	total = 0;
	printf("TINY : 0x%p\n", manager->tiny_blocks);
	iterate(manager->tiny_blocks, print_block, (void*)&total);
	printf("SMALL : 0x%p\n", manager->small_blocks);
	iterate(manager->small_blocks, print_block, (void*)&total);
	printf("LARGE : 0x%p\n", manager->large_blocks);
	iterate(manager->large_blocks, print_block, (void*)&total);
	printf("Total : %zu octets\n", total);
}