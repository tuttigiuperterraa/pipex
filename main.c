#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	bool	hd;
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		ft_error("Wrong number of arguments", 10);
	else
	{
		hd = g_check_args(argc, argv);
		pipex.path = get_path(envp);
		menage_inout(argc, argv, &pipex, hd);
		pipex.n_cmds = argc - 3 - hd;
		pipex.n_pipes = pipex.n_cmds - 1;
		launch_commands(argv + 2 + hd, envp, &pipex);
		status = wait_for_commands(pipex.n_cmds);
		free_matrix(pipex.path);
		close_fds();
		exit(status);
	}
}