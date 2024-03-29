#include "pipex.h"

void	safe_execve(char *cmd_path, char **argv, char **envp)
{
	if (execve(cmd_path, argv, envp) == -1)
		ft_error(NULL, 15);
}

void	safe_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		ft_error(NULL, 27);
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(NULL, 32);
	return (pid);
}