/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing05.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:44:18 by rimney            #+#    #+#             */
/*   Updated: 2023/01/19 18:33:38 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	c_is_safe(t_cube *cube, size_t i, size_t j)
{
	if(cube->Map[j][i] && (cube->Map[j][i] == '0' || is_a_direction(cube->Map[j][i])))
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
	while(cube->Map[cube->MapHeight - 1][i])
	{
		if(cube->Map[cube->MapHeight - 1][i] != '1' && cube->Map[cube->MapHeight - 1][i] != ' ' && cube->Map[cube->MapHeight - 1][i] != '\t')
			return (0);
			i++;
	}
	return (1);
}

int ft_theres_player(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(cube->Map[j])
	{
		i = 0;
		while(cube->Map[j][i])
		{
			if(is_a_direction(cube->Map[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
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
				cube->Psp = cube->Map[j][i];
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
	if(!ft_check_map(cube) || !ft_theres_player(cube))
		ft_exit("Map Error !");
	ft_get_player_position(cube);
}