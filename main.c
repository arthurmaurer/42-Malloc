
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

int		main()
{
	void *a;

	a = mymalloc(sizeof(char) * 40);
	strcpy(a, "salut ca va ?");
	printf("%s\n", (char*)a);

	show_alloc_mem_ex();
	system("pause");

	return (EXIT_SUCCESS);
}
