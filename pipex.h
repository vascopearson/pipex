#ifndef PIPEX_H
# define PIPEX_H

#include "printf/inc/ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h> 

void	exec(char *cmd, char **envp);
void	right_of_pipe(int *fd, char **argv, char **envp);
void	left_of_pipe(int *fd, char **argv, char **envp);
char	*get_path(char *cmd, char **envp);

#endif
