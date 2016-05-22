
#ifndef _MALLOC_H
# define _MALLOC_H

# include <stdio.h>

# define MALLOC_PAGE_SIZE	(getpagesize())

# define MALLOC_TINY_BLOCK_SIZE		(64)
# define MALLOC_SMALL_BLOCK_SIZE	(512)

# define MALLOC_TINY_CHUNK_SIZE		(MALLOC_PAGE_SIZE * 1)
# define MALLOC_SMALL_CHUNK_SIZE	(MALLOC_PAGE_SIZE * 16)

# define MALLOC_BLOCK_SIZE			(sizeof(t_block))
# define IS_TINY(SIZE)				(SIZE <= MALLOC_TINY_BLOCK_SIZE)
# define IS_SMALL(SIZE)				(SIZE <= MALLOC_SMALL_BLOCK_SIZE)
# define IS_LARGE(SIZE)				(SIZE > MALLOC_SMALL_BLOCK_SIZE)

# define MALLOC_PREVIEW_SIZE		250
# define MALLOC_MERGE_ON_FREE		1

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	int				free;
}					t_block;

typedef struct
{
	t_block			*tiny_blocks;
	t_block			*small_blocks;
	t_block			*large_blocks;
}					t_manager;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t nmemb, size_t size);
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);
		
t_manager			*get_manager(void);
void				*allocate_block(size_t size);
void				update_block(t_block *block, size_t size, t_block *next, int is_free);
t_block				*get_data_block(void *ptr);
void				split_block(t_block *block, size_t size);
t_block				*get_data_block(void *ptr);
void				*get_block_data(t_block *block);
void				merge_block_with_next(t_block *block);
void				merge_next_free_blocks(t_block *block);
void				iterate(t_block *block, void(*f)(t_block *, void *), void *arg);

#endif
