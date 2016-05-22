
#include <stdio.h>
#include <string.h>
#include "malloc.h"

static void	get_preview_hex(t_block *block)
{
	size_t	i;
	char	*data;
	char	byte[3];

	data = get_block_data(block);

	i = 0;
	while (i < block->size)
	{
		memset(byte, 0, 3);
		printf("%#02x ", data[i]);
		++i;
	}
}

static int	data_is_string(t_block *block)
{
	size_t	i;
	char	*data;
	char	c;

	data = get_block_data(block);

	i = 0;
	while (i < block->size)
	{
		c = data[i];

		if (c == '\0' && i > 0)
			return (1);
		if (c < 32 || c > 126)
			return (0);
		++i;
	}

	return (1);
}

static void	print_block(t_block *block, void *arg)
{
	printf("   --\n");
	printf("      adress:  0x%p\n", (void*)block);
	printf("      size:    %zu\n", block->size);
	printf("      status:  %s\n", (block->free) ? "free" : "reserved");

	if (!block->free)
	{
		printf("      content: ");

		if (data_is_string(block))
			printf("%s", (char*)get_block_data(block));
		else
			get_preview_hex(block);

		printf("\n");
	}

	(void)arg;
}

void	show_alloc_mem_ex()
{
	t_manager	*manager;

	manager = get_manager();
	printf("\n-- TINY BLOCKS ------------------------\n");
	iterate(manager->tiny_blocks, print_block, NULL);
	printf("---------------------------------------\n");
	printf("\n-- SMALL BLOCKS -----------------------\n");
	iterate(manager->small_blocks, print_block, NULL);
	printf("---------------------------------------\n");
	printf("\n-- LARGE BLOCKS -----------------------\n");
	iterate(manager->large_blocks, print_block, NULL);
	printf("---------------------------------------\n");
}
