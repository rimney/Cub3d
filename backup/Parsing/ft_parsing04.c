/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:43:41 by rimney            #+#    #+#             */
/*   Updated: 2022/12/25 23:50:41 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
	while(i < cube->MapHeight)
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