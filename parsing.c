/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/20 03:14:53 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "Get_next_line/get_next_line.h"

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	ft_get_NO(t_cube *cube, char *line)
{
	if(cube->files_f[0])
		ft_exit("NO Dupicate Direction !");
	cube->NO = ft_strdup(line);
	cube->files_f[0] = 1;
}

void	ft_get_SO(t_cube *cube, char *line)
{
	if(cube->files_f[1])
		ft_exit("SO Dupicate Direction !");
	cube->SO = ft_strdup(line);
	cube->files_f[1] = 1;
}

void	ft_get_WE(t_cube *cube, char *line)
{
	if(cube->files_f[2])
		ft_exit("WE Dupicate Direction !");
	cube->WE = ft_strdup(line);
	cube->files_f[2] = 1;
}

void	ft_get_EA(t_cube *cube, char *line)
{
	if(cube->files_f[3])
		ft_exit("EA Dupicate Direction !");
	cube->EA = ft_strdup(line);
	cube->files_f[3] = 1;
}

void	ft_get_xpms(t_cube *cube, char **argv)
{
    char	*line;

	int fd;

	fd = open(argv[1], O_RDONLY);
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

int	ft_check_rgb_2(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if(line[i] && line[i] >= '0' && line[i] <= '9')
		{
			count++;
			while(line[i] >= '0' && line[i] <= '9')
				i++;
		}
		i++;
	}
	return (count);

}

int	ft_get_rgb(char *line, int i)
{
	int		rgb[3];
	int		index;
	char	*temp;

	i = 0;
	index = 0;
	temp = ft_strdup("");
	while (line[i] && index <= 2)
	{
		if(line[i] >= '0' && line[i] <= '9')
			temp = ft_strjoin_1(temp, line[i]);
		else
		{
			if(ft_atoi(temp) != 0)
			{
				rgb[index] = ft_atoi(temp);
				index++;
				free(temp);
				temp = ft_strdup("");
			}
		}
		i++;
	}
	free(temp);
	return ((rgb[0] << 16 | rgb[1] << 8) | rgb[2]);
}

int	ft_count_elements(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if(str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_rgb_check(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] && line[i + 1] && line[i] == ',' && line[i + 1] == ',')
			return (0);
		else if(line[0] == ',' || line[ft_strlen(line) - 1] == ',')
			return (0);
		else if(ft_count_elements(line, ',') != 2 || ft_check_rgb_2(line) != 3)
			return (0);
		
		i++;
	}
	return (1);
}

void	ft_get_C(t_cube *cube, char *line)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if(cube->files_f[4])
		ft_exit("Duplicate C RGB!");
	while(line[i])
	{
		if(!ft_rgb_check(line))
		{
			printf("RGB  Error\n");
			exit(0);
		}
		i++;
	}
	cube->C = ft_get_rgb(line, i);
}

void	ft_get_F(t_cube *cube, char *line)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if(cube->files_f[5])
		ft_exit("Duplicate F RGB!");
	while(line[i])
	{
		if(!ft_rgb_check(line))
		{
			printf("RGB Error\n");
			exit(0);
		}
		i++;
	}
	cube->F = ft_get_rgb(line, i);
}

void	ft_get_CF(t_cube *cube, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	(void)cube;
	while((line = get_next_line(fd)))
	{
		if(ft_strncmp(line, "C", 1) == 0)
		{
			ft_get_C(cube, line);
			cube->files_f[4] = 1;
		}
		else if(ft_strncmp(line, "F", 1) == 0)
		{
			ft_get_F(cube, line);
			cube->files_f[5] = 1;
		}
		free(line);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_is_an_xpm(char *line)
{
	if(ft_strncmp(line, "SO", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "WE", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "EA", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "NO", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "C", 1) == 0)
		return (1);
	else if(ft_strncmp(line, "F", 1) == 0)
		return (1);
	else if (ft_strcmp(line, "\n") == 0)
		return (1);
	return (0);
}

void	ft_parse_map_2(t_cube *cube, char *map)
{
	char	**TD_map;
	int		i;

	i = 0;
	TD_map = ft_split(map, '\n');
	while(TD_map[i])
	{
		printf("%s< \n", TD_map[i]);
		i++;
	}
	printf(">> %d <<\n", cube->C);
}

void	ft_parse_map(t_cube *cube, char **argv, char *arg, int i)
{
	char *line;
	char *temp;
	char *map;
	int fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while((line = get_next_line(fd)))
	{
		if(ft_strcmp(line, arg) == 0 && !i)
		{
			map = ft_strdup(arg);
			i = 1;
		}
		else if(i)
		{
			temp = map;
			map = ft_strjoin(temp, line);
			free(temp);
		}
		free(line);
	}
	 ft_parse_map_2(cube, map);
	printf("%s <\n", map);
	printf(">> %d <<\n", cube->C);
	free(map);
}

void	ft_get_map(t_cube *cube, char **argv)
{
	int fd;
	char *line;
	int i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if(!ft_is_an_xpm(line))
		{
			ft_parse_map(cube, argv, line, i);
			free(line);
			break ;
		}
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
	ft_get_map(cube, argv);
	return (cube);
}

void	ft_free_parsing(t_cube *cube)
{
	free(cube->SO);
	free(cube->NO);
	free(cube->WE);
	free(cube->files_f);
	free(cube->EA);
	free(cube);
	cube = NULL;
}

void ft_print(char *str, char *s)
{
	int i;

	i = 0;
	printf("%s", str);
	while (s[i] && s[i] != '\n')
	{
		printf("%c", s[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_cube(t_cube *cube)
{

	ft_print("NO texture file >> ", cube->NO);
	ft_print("SO texture file >> ", cube->SO);
	ft_print("EA texture file >> ", cube->EA);
	ft_print("WE texture file >>", cube->WE);
	printf("C RGB >> %d\n", cube->C);
	printf("F RGB >> %d\n", cube->F);
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
	ft_print_cube(cube);
	ft_free_parsing(cube);
    system("leaks Cub3d");
	
}