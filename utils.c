#include "pipex.h"

const char	**free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		close(i++);
}