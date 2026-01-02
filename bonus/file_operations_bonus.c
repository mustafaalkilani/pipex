#include "../pipx.h"
#include "../libft/libft.h"

int	open_output_file_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	return (fd);
}