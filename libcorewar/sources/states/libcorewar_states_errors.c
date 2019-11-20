#include "libcorewar_get_src_file.h"


void			op_er(const char *const format, char *content, char **const error, ...)
{
	va_list		args;
	int			co;
	int			li;

	
	va_start(args, file);
	ft_vasprintf(error, "%s", args);
	va_end(args);
}
