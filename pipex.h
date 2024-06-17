/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 12:13:14 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/15 14:40:48 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define DEFAULT "\033[0m"

# include "libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	***args1;
	char	**args2;
	char	**envp;
	char	**paths;
}	t_pipex;

void	fetch_input_data(int argc, char **argv, char **envp, t_pipex *data);
void	path_error(char *program_name, t_pipex *data);
void	close_multiple_fd(int fd1, int fd2, int fd3);
void	quit_program(char *error, t_pipex *data);
void	free_split(char	**chr);
void	clean(t_pipex *data);

char	*build_path_str(char *path, char *program);
char	*get_path(t_pipex *data, char *program);

int		handle_end_pipe(int inp_fd, int out_fd, t_pipex *data, char **exec);
int		handle_center_pipe(int input_fd, t_pipex *data, char **exec);

#endif