#include "pipex.h"

void	launch_commands(char **argv, char **envp, t_pipex *pipex)
{
	int			i;
	pid_t		pid;

	pipex->prev_output_fd = pipex->file_fds[0];
	i = 0;
	while (i < pipex->n_cmds)
	{
		if (i < pipex->n_pipes)
			safe_pipe(pipex->pipe_fds);
		pid = safe_fork();
		if (pid == 0)
			child(argv[i], envp, pipex, i == (pipex->n_cmds -1));
		else
			pipex->prev_output_fd = parent(pipex, i == (pipex->n_cmds - 1));
		i++;
	}
}

int	parent(t_pipex *pipex, bool is_last)
{
	if (is_last == false)
		safe_close(&pipex->pipe_fds[1]);
	else
		safe_close(&pipex->file_fds[1]);
	safe_close(&pipex->prev_output_fd);
	return (pipex->pipe_fds[0]);
}

void	child(char *cmd_line, char **envp, t_pipex *pipex, bool is_last)
{
	char	**cmd_args;
	char	*cmd_path;

	if (is_last == false)
		safe_close(&pipex->pipe_fds[0]);
	safe_dup2(pipex->prev_output_fd, STDIN_FILENO);
	safe_close(&pipex->prev_output_fd);
	if (is_last == false)
	{
		safe_dup2(pipex->pipe_fds[1], STDOUT_FILENO);
		safe_close(&pipex->pipe_fds[1]);
	}
	else
	{
		safe_dup2(pipex->file_fds[1], STDOUT_FILENO);
		safe_close(&pipex->file_fds[1]);
	}
	cmd_args = ft_split(cmd_line, ' ');
	cmd_path = get_cmd_path(cmd_args[0], pipex);
	safe_execve(cmd_path, cmd_args, envp);
	close_fds();
}

int	wait_for_commands(int n_cmds)
{
	int	status;
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		i++;
	}
	return (status);
}