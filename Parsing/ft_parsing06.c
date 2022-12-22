/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing06.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:44:53 by rimney            #+#    #+#             */
/*   Updated: 2022/12/22 21:45:17 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


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
	printf("Player Px >> %f \n", cube->P_position_x);
	printf("Player Py >> %f \n", cube->P_posotion_y);
	printf("Player Psp >> %c\n", cube->Psp);
}