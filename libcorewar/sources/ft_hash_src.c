#include "libcorewar.h"

unsigned char		ft_hash_src(const char *src, size_t size)
{
	unsigned char	c;

	c = 0x42;
	while (size--)
		c = (c << 1) ^ *src++;
	return (c);
}
