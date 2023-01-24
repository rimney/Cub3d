/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing06.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:44:53 by rimney            #+#    #+#             */
/*   Updated: 2023/01/23 20:41:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int	ft_map_final_check(t_cube *cube)
{
	int i;
	int j;

	i = 1;
	while(cube->Map[i] && i < cube->MapHeight - 1)
	{
		j = 0;
		while(cube->Map[i][j])
		{
			if(cube->Map[i][j] && !is_valid(cube->Map[i][j]) && cube->Map[i][j] != ' ' && cube->Map[i][j] != '\t')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_cube_values_init(t_cube *cube)
{
	cube->C = 0;
	cube->F = 0;
	cube->Psp = 0;
	cube->MapHeight = 0;
	cube->MapWidth = 0;
	cube->P_position_x = 0;
	cube->P_position_y = 0;
	cube->Map = NULL;
	cube->render = 0;
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
	printf("Player Px >> %f \n", cube->P_position_x);
	printf("Player Py >> %f \n", cube->P_position_y);
	printf("Player Psp >> %c\n", cube->Psp);
}