/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing05.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:44:18 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:14:58 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	c_is_safe(t_cube *cube, size_t i, size_t j)
{
	if (cube->map[j][i] && (cube->map[j][i] == '0'
		|| is_a_direction(cube->map[j][i])))
	{
		if (i >= ft_strlen(cube->map[j - 1])
			|| (i >= ft_strlen(cube->map[j + 1])))
			return (0);
		else if ((!is_valid(cube->map[j][i + 1]))
			|| (!is_valid(cube->map[j + 1][i])))
			return (0);
		else if ((!is_valid(cube->map[j][i - 1]))
			|| (!is_valid(cube->map[j - 1][i])))
			return (0);
	}
	return (1);
}

int	ft_check_header_and_footer(char **Map, t_cube *cube)
{
	int	i;

	i = 0;
	if (!Map)
		ft_exit("There's no map !!");
	while (Map[0][i])
	{
		if ((Map[0][i] != ' ' && Map[0][i] != '1' && Map[0][i] != '\t'))
			return (0);
		i++;
	}
	i = 0;
	while (Map[cube->mapheight - 1][i])
	{
		if (Map[cube->mapheight - 1][i] != '1'
			&& Map[cube->mapheight - 1][i] != ' '
			&& Map[cube->mapheight - 1][i] != '\t')
			return (0);
			i++;
	}
	return (1);
}

int	player_is_safe(char **Map, int x, int y)
{
	if ((size_t)x >= ft_strlen(Map[y - 1])
		|| ((size_t)x >= ft_strlen(Map[y + 1])))
		return (0);
	else if ((!is_valid(Map[y][x + 1]))
		|| (!is_valid(Map[y + 1][x])))
		return (0);
	else if ((!is_valid(Map[y][x - 1]))
		|| (!is_valid(Map[y - 1][x])))
		return (0);
	return (1);
}

int	ft_theres_player(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cube->map[j])
	{
		i = 0;
		while (cube->map[j][i])
		{
			if (is_a_direction(cube->map[j][i])
				&& player_is_safe(cube->map, i, j))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	ft_check_map(t_cube *cube)
{
	size_t	i;
	size_t	j;

	j = 1;
	i = 0;
	if (!ft_check_header_and_footer(cube->map, cube))
	{
		return (0);
	}
	while (cube->map[j] && (int)j < cube->mapheight)
	{
		i = 0;
		while (cube->map[j][i] && i < ft_strlen(cube->map[j]))
		{
			if (cube->map[j][i] && cube->map[j][i] == '0')
			{
				if (!c_is_safe(cube, i, j))
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cube->map[j] && (int)j < cube->mapheight)
	{
		i = 0;
		while ((size_t)i < ft_strlen(cube->map[j]))
		{
			if (is_a_direction(cube->map[j][i])
				&& !cube->p_position_x && !cube->p_position_y)
			{
				cube->psp = cube->map[j][i];
				cube->p_position_x = i;
				cube->p_position_y = j;
				i++;
			}
			if (is_a_direction(cube->map[j][i])
				&& cube->p_position_x && cube->p_position_y)
				ft_exit("Duplicate Direction");
			else
				i++;
		}
		j++;
	}
}

