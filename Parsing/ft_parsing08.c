/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing08.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:10:14 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:17:48 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_get_cf_norm(t_cube *cube, char *line, int *space)
{
	if (line[0] == ' ' || line[0] == '\t')
	{
		while (line[*space] && line[*space] == ' ')
			*space += 1;
	}
	if (ft_strncmp(line + *space, "C", 1) == 0)
	{
		ft_get_c(cube, line + *space);
		cube->files_f[4] = 1;
	}
	else if (ft_strncmp(line + *space, "F", 1) == 0)
	{
		ft_get_f(cube, line + *space);
		cube->files_f[5] = 1;
	}
}

void	ft_get_cf(t_cube *cube, char **argv)
{
	int		fd;
	char	*line;
	int		space;

	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		space = 0;
		ft_get_cf_norm(cube, line, &space);
		free(line);
	}
}

void	ft_get_map_norm(t_cube *cube)
{
	if (!ft_check_map(cube)
		|| !ft_theres_player(cube) || !ft_map_final_check(cube))
	{
		ft_exit("Map Error !");
	}
	ft_get_player_position(cube);
}

void	ft_get_map(t_cube *cube, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while ((1))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_is_an_xpm(line))
		{
			ft_parse_map(cube, argv, line, i);
			free(line);
			break ;
		}
		free(line);
	}
	ft_get_map_norm(cube);
}
