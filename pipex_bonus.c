/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 15:52:37 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/15 15:22:47 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(t_pipex *data, char *program)
{
	int		index;
	char	*path;

	index = -1;
	if (access(program, R_OK) != -1)
		return (ft_strdup(program));
	while (data->paths[++index])
	{
		path = build_path_str(data->paths[index], program);
		if (!path)
			return (NULL);
		if (access(path, R_OK) != -1)
			return (path);
		free(path);
	}
	path_error(program, data);
	return (NULL);
}

void	fetch_input_data(int argc, char **argv, char **envp, t_pipex *data)
{
	int	counter;

	data->fd1 = open(argv[1], O_RDONLY);
	data->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->args1 = (char ***)malloc(sizeof(char ***) * (argc - 3));
	if (data->fd1 == -1 || data->fd2 == -1 || !data->args1)
		quit_program("Parsing error", data);
	ft_bzero(data->args1, sizeof(char ***) * (argc - 3));
	counter = 0;
	while (counter++ < argc - 4)
	{
		data->args1[counter - 1] = ft_split(argv[counter + 1], ' ');
		if (!data->args1)
			quit_program("Failed split", data);
	}
	data->args2 = ft_split(argv[argc - 2], ' ');
	if (!data->args2)
		quit_program("Failed split 2", data);
	counter = 0;
	while (envp[counter] && ft_strncmp(envp[counter], "PATH=", 5) != 0)
		++counter;
	if (envp[counter])
		data->paths = ft_split(envp[counter] + 5, ':');
	if (!data->paths || !envp[counter])
		quit_program("Path", data);
}

int	handle_center_pipe(int infd, t_pipex *data, char **exec)
{
	int		bridge[2];
	char	*path;
	pid_t	pid;

	if (pipe(bridge) == -1)
		quit_program("Pipe", data);
	pid = fork();
	if (pid < 0)
		quit_program("Fork", data);
	if (pid == 0)
	{
		if (dup2(infd, STDIN_FILENO) < 0 || dup2(bridge[1], STDOUT_FILENO) < 0)
			quit_program("Dup2", data);
		close_multiple_fd(infd, bridge[0], bridge[1]);
		data->fd1 = -1;
		path = get_path(data, exec[0]);
		if (!path)
			quit_program("Path malloc", data);
		if (execve(path, exec, data->envp) == -1)
			quit_program("Execve", data);
		quit_program("Child proccess failure", data);
	}
	close_multiple_fd(infd, bridge[1], -1);
	return (bridge[0]);
}

int	handle_end_pipe(int inp_fd, int out_fd, t_pipex *data, char **exec)
{
	char	*path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		quit_program("Fork", data);
	if (pid == 0)
	{
		if (dup2(inp_fd, STDIN_FILENO) < 0 || dup2(out_fd, STDOUT_FILENO) < 0)
			quit_program("Dup2", data);
		close(inp_fd);
		close(out_fd);
		data->fd2 = -1;
		path = get_path(data, exec[0]);
		if (!path)
			quit_program("Path malloc", data);
		if (execve(path, exec, data->envp) == -1)
			quit_program("Execve", data);
		quit_program("Child process failure", data);
	}
	close_multiple_fd(inp_fd, out_fd, -1);
	if (waitpid(pid, &status, 0) == -1)
		quit_program("Waitpid", data);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int		return_status;
	int		stdin_fd;
	int		index;
	t_pipex	data;

	data = (t_pipex){-1, -1, NULL, NULL, envp, NULL};
	if (argc < 5)
		quit_program("Not enough arguments provided", &data);
	fetch_input_data(argc, argv, envp, &data);
	index = 0;
	stdin_fd = data.fd1;
	while (++index < argc - 3)
		stdin_fd = handle_center_pipe(stdin_fd, &data, data.args1[index - 1]);
	return_status = handle_end_pipe(stdin_fd, data.fd2, &data, data.args2);
	while (wait(NULL) > 0)
		continue ;
	clean(&data);
	return (return_status);
}
