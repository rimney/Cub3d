/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:43:41 by rimney            #+#    #+#             */
/*   Updated: 2023/01/25 01:57:57 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_parse_map_2(t_cube *cube, char *map)
{
	char	**td_map;
	int		i;

	i = 0;
	td_map = ft_split(map, '\n');
	cube->mapwidth = ft_get_width(td_map);
	cube->mapheight = ft_get_hight(td_map);
	cube->map = malloc(sizeof(char *) * (cube->mapheight + 2));
	if (!cube->map)
		ft_exit("allocation error\n");
	while (i < cube->mapheight)
	{
		cube->map[i] = ft_strdup(td_map[i]);
		i++;
	}
	cube->map[i] = NULL;
	ft_free_2d(td_map);
}

void	ft_set_i(char *line, char **map, int *i, char *arg)
{
	if (ft_strcmp(line, arg) == 0 && *i == 0)
	{
		*map = ft_strdup(arg);
		*i = 1;
	}
}

void	ft_parse_map(t_cube *cube, char **argv, char *arg, int i)
{
	char	*line;
	char	*temp;
	char	*map;
	int		fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_set_i(line, &map, &i, arg);
		if (i)
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

int	is_valid(char c)
{
	if (c == '1' || c == '0' || c == 'S' || c == 'W' || c == 'E' || c == 'N')
		return (1);
	else
		return (0);
}
