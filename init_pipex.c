#include "pipex.h"

int	create_heredoc(char *limiter)
{
	int		hd_fd;
	char	*line;
	int		len;

	hd_fd = safe_open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (ft_strncmp(line, limiter, len) == 0)
			break ;
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	get_next_line(-1); //perchè?
	safe_close(&hd_fd);
	hd_fd = safe_open("heredoc", O_RDONLY, 0777);
	return (hd_fd);
}

void	menage_inout(int argc, char **argv, t_pipex *pipex, bool hd)
{
	if (hd)
	{
		pipex->file_fds[0] = create_heredoc(argv[2]);
		pipex->file_fds[1] = safe_open(argv[argc - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0777);
	}
	else
	{
		pipex->file_fds[0] = safe_open(argv[1], O_RDONLY, 0777);
		pipex->file_fds[1] = safe_open(argv[argc - 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0777);
	}
}

char	**get_path(char **envp)
{
	char	**path;

	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_split(*envp + 5, ':');
			return (path);
		}
		envp++;
	}
	ft_error("PATH not found in envp", 9);
	return (NULL);
}

char	*get_cmd_path(char *cmd_name, t_pipex *pipex)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (pipex->path[i])
	{
		tmp = pipex->path[i];
		pipex->path[i] = ft_strjoin(pipex->path[i], "/");
		free(tmp);
		full_path = ft_strjoin(pipex->path[i], cmd_name);
		if (safe_access(full_path, X_OK) == 0)
			return (full_path);
		free (full_path);
		i++;
	}
	ft_error(ft_strjoin("pipex: command not found: ", cmd_name), 127);
	return (NULL);
}