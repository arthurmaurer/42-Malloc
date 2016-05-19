
#include <string.h>
#include "malloc.h"

void	*mycalloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	ptr = mymalloc(total_size);
	memset(ptr, 0, total_size);

	return (ptr);
}
