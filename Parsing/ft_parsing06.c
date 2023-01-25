/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing06.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:44:53 by rimney            #+#    #+#             */
/*   Updated: 2023/01/25 02:26:11 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_map_final_check(t_cube *cube)
{
	int	i;
	int	j;

	i = 1;
	while (cube->map[i] && i < cube->mapheight - 1)
	{
		j = 0;
		while (cube->map[i][j])
		{
			if (cube->map[i][j] && !is_valid(cube->map[i][j])
				&& cube->map[i][j] != ' ' && cube->map[i][j] != '\t')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_cube_values_init(t_cube *cube)
{
	cube->c = 0;
	cube->f = 0;
	cube->psp = 0;
	cube->mapheight = 0;
	cube->mapwidth = 0;
	cube->p_position_x = 0;
	cube->p_position_y = 0;
	cube->map = NULL;
	cube->render = 0;
}

void	ft_free_parsing(t_cube *cube)
{
	free(cube->so);
	free(cube->no);
	free(cube->we);
	free(cube->files_f);
	free(cube->ea);
	if (cube->mapwidth)
		ft_free_2d(cube->map);
	free(cube->img);
	free(cube->player);
	free(cube->stable);
	free(cube->so_texture);
	free(cube->no_texture);
	free(cube->we_texture);
	free(cube->ea_texture);
	free(cube->texture);
	free(cube);
	system("leaks Cub3d");
	cube = NULL;
}

void	ft_print(char *str, char *s)
{
	int	i;

	i = 0;
	printf("%s", str);
	while (s[i] && s[i] != '\n')
	{
		printf("%c", s[i]);
		i++;
	}
	printf("\n");
}

char	is_a_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
