/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 12:08:12 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/16 13:12:07 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	path_error(char *program_name, t_pipex *data)
{
	int		length;
	char	*error;

	length = ft_strlen(program_name) + 26;
	error = (char *)malloc(sizeof(char) * length);
	if (!error)
		exit(1);
	ft_bzero(error, length);
	ft_memcpy(error, "zsh: command not found: ", 24 * sizeof(char));
	ft_memcpy(error + 24, program_name, ft_strlen(program_name) * sizeof(char));
	ft_memcpy(error + length - 2, "\n", 1);
	write(STDERR_FILENO, error, length);
	free(error);
	clean(data);
	exit(127);
}

void	clean(t_pipex *data)
{
	int	index;

	if (!data)
		return ;
	if (data->fd1 != -1)
		close(data->fd1);
	if (data->fd2 != -1)
		close(data->fd2);
	if (data->args1)
	{
		index = 0;
		while (data->args1[index])
			ft_free_split(data->args1[index++]);
		free(data->args1);
	}
	if (data->args2)
		ft_free_split(data->args2);
	if (data->paths)
		ft_free_split(data->paths);
}

void	quit_program(char *error, t_pipex *data)
{
	clean(data);
	if (errno != 0)
		perror(error);
	else
		ft_printf("%s%s%s\n", RED, error, DEFAULT);
	exit(EXIT_FAILURE);
}

char	*build_path_str(char *path, char *program)
{
	int		l1;
	int		l2;
	char	*output;

	l1 = ft_strlen(path);
	l2 = ft_strlen(program);
	output = (char *)malloc((l1 + l2 + 2) * sizeof(char));
	if (!output)
		return (NULL);
	output[l1] = '/';
	output[l1 + l2 + 1] = '\0';
	ft_memcpy(output, path, l1);
	ft_memcpy(output + l1 + 1, program, l2);
	return (output);
}

void	close_multiple_fd(int fd1, int fd2, int fd3)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
}
