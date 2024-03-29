#include "pipex.h"

int	safe_open(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		ft_error(NULL, 10);
	return (fd);
}

void	safe_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
			ft_error(NULL, 11);
		*fd = -1;
	}
}

void	safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		ft_error(NULL, 12);
}

void	safe_wait(int *status)
{
	if (wait(status) == -1)
		ft_error(NULL, 13);
}

int	safe_access(char *file, int mode)
{
	int	ret;

	ret = access(file, mode);
	if (ret == -1 && errno != ENOENT)
		ft_error(NULL, 14);
	return (ret);
}