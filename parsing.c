/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/19 20:22:19 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "Get_next_line/get_next_line.h"

void	ft_get_NO(t_cube *cube, char *line)
{
	printf("%d <<\n", cube->files_f[0]);

	if(cube->files_f[0])
	{
		printf("NO Dupicate Direction !");
		exit(0);
	}
	printf("NO XPM > %s\n", line);
	cube->NO = ft_strdup(line);
	cube->files_f[0] = 1;
}

void	ft_get_SO(t_cube *cube, char *line)
{
	if(cube->files_f[1])
	{
		printf("SO Dupicate Direction !");
		exit(0);
	}
	printf("SO XPM > %s\n", line);
	cube->SO = ft_strdup(line);
	cube->files_f[1] = 1;
}

void	ft_get_WE(t_cube *cube, char *line)
{
	if(cube->files_f[2])
	{
		printf("WE Dupicate Direction !");
		exit(0);
	}
	printf("SO XPM > %s\n", line);
	cube->WE = ft_strdup(line);
	cube->files_f[2] = 1;
}

void	ft_get_EA(t_cube *cube, char *line)
{
	if(cube->files_f[3])
	{
		printf("EA Dupicate Direction !");
		exit(0);
	}
	printf("WE XPM > %s\n", line);
	cube->EA = ft_strdup(line);
	cube->files_f[3] = 1;
}

void	ft_get_xpms(t_cube *cube, char **argv)
{
    char	*line;

	int fd;

	fd = open(argv[1], O_RDONLY);
	printf("EEEE\n");
	if (fd == -1)
	{
		printf("An error has been occurred when opening the file\n");
		exit(1);
	}
	while((line = get_next_line(fd)))
	{
		if(ft_strncmp(line, "NO", 2) == 0)
			ft_get_NO(cube, line);
		else if(ft_strncmp(line, "SO", 2) == 0)
			ft_get_SO(cube, line);
		else if(ft_strncmp(line, "WE", 2) == 0)
			ft_get_WE(cube, line);
		else if(ft_strncmp(line, "EA", 2) == 0)
			ft_get_EA(cube, line);
		free(line);
	}
}

int	*ft_files_f_init(void)
{
	int *arr;
	int i;

	i = 0;
	arr = malloc(sizeof(int) * 7);
	while(i < 7)
	{
		arr[i] = 0;
		i++;
	}	
	return (arr);
}

char	*ft_strjoin_1(char *str, char c)
{
	char	*s;
	int		i;
	int		n;

	i = 0;
	n = 0;
	s = malloc(strlen(str) + 2);
	while (str[i])
		s[n++] = str[i++];
	s[n] = c;
	s[n + 1] = 0;
	free(str);
	return (s);
}

int	ft_get_rgb(char *line)
{
	int		rgb[3];
	int		index;
	char	*temp;
	int		i;

	i = 0;
	index = 0;
	temp = ft_strdup("");
	while (line[i] && index <= 3)
	{
		if(line[i] >= '0' && line[i] <= '9')
			temp = ft_strjoin_1(temp, line[i]);
		else
		{
			rgb[index] = ft_atoi(temp);
			free(temp);
			temp = ft_strdup("");
			index++;
		}
		i++;
	}
	return ((rgb[0] << 16 | rgb[1] << 8 | rgb[2]));
}

void	ft_get_C(t_cube *cube, char *line)
{
	int i;
	// int rgb;
	int ret;

	i = 0;
	ret = 0;
	while(line[i])
	{
		if(line[i] && line[i + 1] && line[i] == ',' && line[i + 1] == ',')
		{
			printf("RGB Error !\n");
			exit(0);
		}
		i++;
	}
	cube->C = ft_get_rgb(line);
	printf("%d < rgb\n", cube->C);
}

void	ft_get_CF(t_cube *cube, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	while((line = get_next_line(fd)))
	{
		if(ft_strncmp(line, "C", 1) == 0)
			ft_get_C(cube, line);
		// else if(ft_strncmp(line, "F", 1) == 0)
		// 	ft_get_F(cube, line);
		free(line);
	}
}

t_cube	*ft_struct_init(char **argv)
{
	t_cube *cube;
	cube = malloc(sizeof(t_cube));
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	return (cube);
}

void	ft_free_parsing(t_cube *cube)
{
	free(cube->SO);
	free(cube->NO);
	free(cube->WE);
	free(cube->files_f);
	free(cube);
	free(cube->EA);
	cube = NULL;
}

int main(int argc, char **argv)
{
    t_cube *cube;

	
	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	cube = ft_struct_init(argv);
	ft_free_parsing(cube);
	// free(cube->files_f);
    system("leaks Cub3d");
	
}