#include "pipex.h"

/*bool	check_args(int argc, char **argv)
{
	if (argc < 5)
		ft_error("Wrong number of arguments", 10);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			ft_error("Wrong number of arguments", 54);
		return (true);
	}
	return (false);
}*/

bool	g_check_args(int argc, char **argv)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc < 6))
		ft_error("Wrong number of arguments", 10);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (true);
	return (false);
}

void	ft_error(char *msg, int id)
{
	if (!msg)
		perror("Error");
	else
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	close_fds();
	if (id == 127)
		free(msg);
	exit(id);
}
