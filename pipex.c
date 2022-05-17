#include "pipex.h"

void	left_of_pipe(int *fd, char **argv, char **envp)
{
	int	input_file;

	input_file = open(argv[1], O_RDONLY, 0777);
	if (input_file == -1)
		return ;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(input_file, STDIN_FILENO);
	exec(argv[2], envp);
	close(fd[1]);
}

void	right_of_pipe(int *fd, char **argv, char **envp)
{
	int	output_file;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_file == -1)
		return ;
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(output_file, STDOUT_FILENO);
	exec(argv[3], envp);
	close(fd[0]);
}

void	exec(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;
	int	i;

	i = 0;
	cmds = ft_split(cmd, ' ');
	path = get_path(cmds[0], envp);
	if (!path)
	{
		while (cmds[i])
		{
			free(cmds[i]);
			i++;
		}
		free(cmds);
		return ;
	}
	if (execve(path, cmds, envp) == -1)
		return ;
}

char	*get_path(char *cmd, char **envp)
{
	int	i;
	char	**paths;
	char	*path_init;
	char	*path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_init = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_init, cmd);
		free(path_init);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (2);
		if (pid == 0)
			left_of_pipe(fd, argv, envp);
		waitpid(pid, NULL, 0);
		right_of_pipe(fd, argv, envp);
	}
	else
		ft_printf("Error: args to ./pipex should be: <file1> <cmd1> <cmd2> <file2>");
	return (0);
}
