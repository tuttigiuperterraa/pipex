/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:21:58 by nromito           #+#    #+#             */
/*   Updated: 2024/03/05 07:50:49 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "libft/libft.h"

typedef struct s_pipex
{
    int		n_cmds;
	int		n_pipes;
	int		file_fds[2];
	int		pipe_fds[2];
	int		prev_output_fd;
	char	**path;
}	t_pipex;

//cmds
void		launch_commands(char **argv, char **envp, t_pipex *pipex);
int			parent(t_pipex *pipex, bool is_last);
void		child(char *cmd_line, char **envp, t_pipex *pipex, bool is_last);
int			wait_for_commands(int n_cmds);
//errors_and_checks
bool		g_check_args(int argc, char **argv);
void		ft_error(char *msg, int id);
//safe_funcs
int			safe_open(char *file, int flags, int mode);
void		safe_close(int *fd);
void		safe_dup2(int old_fd, int new_fd);
void		safe_wait(int *status);
int			safe_access(char *file, int mode);
//safe_funcs2
void		safe_execve(char *cmd, char **argv, char **envp);
void		safe_pipe(int pipe_fds[2]);
int			safe_fork(void);
//init_pipex
int			create_heredoc(char *limiter);
void		menage_inout(int argc, char **argv, t_pipex *pipex, bool is_heredoc);
char		**get_path(char **envp);
char		*get_cmd_path(char *cmd_name, t_pipex *pipex);
//utils
const char	**free_matrix(char **matrix);
void		close_fds(void);

#endif