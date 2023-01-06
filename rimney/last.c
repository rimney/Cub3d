#include "pipex.h"
#include "libft/libft.h"



char	*get_path(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (0);
}

void	ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}


char *ft_get_commandr(char *str)
{
	char *ret;
	char **temp;

	temp = ft_split(str, ' ');
	ret = ft_strdup(temp[0]);
	ft_free(temp);
	return (ret);	
}

char *split_path(char *path, char **argv)
{
	char	**minipath;
	char	*command; // will replace argv[1]
	char	*tmp;

	int i = 0;
	minipath = ft_split(path, ':');
	command = ft_get_commandr(argv[1]); // take the first argument and split it as "ls -l" so i can get only [ls]
	while(minipath[i])
	{
		if( command[0] == '/' && access(command, X_OK) == 0) // ./a.out "/bin/ls"
			return (command);
		tmp = minipath[i];
		minipath[i] = ft_strjoin(tmp, "/");
        free(tmp);
        tmp = minipath[i];
        minipath[i] = ft_strjoin(tmp, command);
		if(access(minipath[i], F_OK) == 0)
		{
			printf("%s <<\n", minipath[i]);
			return(minipath[i]);
		}
		free(tmp);
		i++;
	}
	return (0);
	printf("[%s]\n", minipath[i]);
}


int	main(int argc, char **argv, char **envp)
{
	char *path;
	char *paths;
	char **command;
	char *temp;
	path =	ft_strdup(get_path(envp));
	if(path == NULL)
	{
		printf("PATH not found !!\n"); 
		exit(0);
	}
	if(argc == 1)
		return(0);
	paths = split_path(path, argv);
	if(paths) // is path is true then i should create a 2d that contains [path_of_command][argumenst] such as "ls -l"
	{
		command = ft_split(argv[1], ' '); // [ls][-l]
		temp = command[0];
		command[0] = ft_strdup(paths); // [/bin/ls][-l]
		free(temp);
	}
	if(execve(command[0], command, envp) == -1) // execve takes 3 arguments the path of the command which is the index of 0 of the array we just made and the argumets we just added as -l
		{
			printf("%s << com\n", command[0]);
			perror("pipex : ");
			exit(0);
		}
	if(argc != 2)
		return(0);

	printf("%s\n", paths);
	free(path);
	return(0);
}

