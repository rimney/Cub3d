/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/22 20:55:18 by rimney           ###   ########.fr       */
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

int	ft_get_width(char **str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(str[i])
	{
		if((size_t)len < ft_strlen(str[i]))
			len = ft_strlen(str[i]);
		i++;
	}
	return (len);
}

int	ft_get_hight(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i - 1);
}

void	ft_print_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
}

void	ft_free_2d(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}



void	ft_parse_map_2(t_cube *cube, char *map)
{
	char	**TD_map;
	int		i;

	i = 0;
	TD_map = ft_split(map, '\n');
	cube->MapWidth = ft_get_width(TD_map);
	cube->MapHeight = ft_get_hight(TD_map);
	cube->Map = malloc(sizeof(char *) * (cube->MapHeight + 2));
	if(!cube->Map)
		ft_exit("allocation error\n");
	while(i <= cube->MapHeight)
	{
		cube->Map[i] = ft_strdup(TD_map[i]);
		i++;
	}
	cube->Map[i] = NULL;
	ft_free_2d(TD_map);
	ft_print_2d(cube->Map);
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
	free(map);
}

char	is_a_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid(char c)
{
	if (c == '1' || c == '0' || c == 'S' || c == 'W' || c == 'E' || c == 'N')
		return (1);
	else
		return (0);	
}
int	c_is_safe(t_cube *cube, size_t i, size_t j)
{
	if(cube->Map[j][i] && cube->Map[j][i] == '0')
	{
		if(i >= ft_strlen(cube->Map[j - 1]) || (i >= ft_strlen(cube->Map[j + 1])))
			return (0);
		else if((!is_valid(cube->Map[j][i + 1])) || (!is_valid(cube->Map[j + 1][i])))
			return (0);
		else if((!is_valid(cube->Map[j][i - 1])) || (!is_valid(cube->Map[j - 1][i])))
			return (0);
	}
	return (1);
}

int	ft_check_header_and_footer(t_cube *cube)
{
	int i;

	i = 0;
	while(cube->Map[0][i])
	{
		if((cube->Map[0][i] != ' ' && cube->Map[0][i] != '1' && cube->Map[0][i] != '\t'))
			return (0);
		i++;
	}
	i = 0;
	while(cube->Map[cube->MapHeight][i])
	{
		if(cube->Map[cube->MapHeight][i] != '1' && cube->Map[cube->MapHeight][i] != ' ' && cube->Map[cube->MapHeight][i] != '\t')
			return (0);
			i++;
	}
	return (1);
}

int	ft_check_map(t_cube *cube)
{
	size_t i;
	size_t j;

	j = 1;
	i = 0;
	if(!ft_check_header_and_footer(cube))
		return (0);
	while (cube->Map[j] && (int)j < cube->MapHeight)
	{
		i = 0;
		while (cube->Map[j][i] && i < ft_strlen(cube->Map[j]))
		{
			if (cube->Map[j][i] && cube->Map[j][i] == '0')
			{
				if(!c_is_safe(cube, i, j))
					return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

void	ft_get_player_position(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cube->Map[j] && (int)j < cube->MapHeight)
	{
		i = 0;
		while((size_t)i < ft_strlen(cube->Map[j]))
		{
			if(is_a_direction(cube->Map[j][i]) && !cube->P_position_x && !cube->P_posotion_y)
			{
				cube->P_position_x = i;
				cube->P_posotion_y = j;
				i++;
			}
			if(is_a_direction(cube->Map[j][i]) && cube->P_position_x && cube->P_posotion_y)
				ft_exit("Duplicate Direction");
			else
				i++;
		}
		j++;
	}
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
	if(!ft_check_map(cube))
		ft_exit("Map Error !");
	ft_get_player_position(cube);
}

void	ft_cube_values_init(t_cube *cube)
{
	cube->C = 0;
	cube->F = 0;
	cube->Psp = 0;
	cube->MapHeight = 0;
	cube->MapWidth = 0;
	cube->P_position_x = 0;
	cube->P_posotion_y = 0;
	cube->Map = NULL;
}

t_cube	*ft_struct_init(char **argv)
{
	t_cube *cube;
	cube = malloc(sizeof(t_cube));
	ft_cube_values_init(cube);
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
	if(cube->MapWidth)
		ft_free_2d(cube->Map);
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
	printf("Player Px >> %d \n", cube->P_position_x);
	printf("Player Py >> %d \n", cube->P_posotion_y);
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
    // system("leaks Cub3d");
	
}