/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:41:14 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 00:26:20 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	ft_get_NO(t_cube *cube, char *line)
{
	if(cube->files_f[0])
		ft_exit("NO Dupicate Direction !");
	cube->NO = ft_get_mid_string(line, ' ');
	cube->files_f[0] = 1;
}

void	ft_get_SO(t_cube *cube, char *line)
{
	if(cube->files_f[1])
		ft_exit("SO Dupicate Direction !");
	cube->SO = ft_get_mid_string(line, ' ');
	cube->files_f[1] = 1;
}

void	ft_get_WE(t_cube *cube, char *line)
{
	if(cube->files_f[2])
		ft_exit("WE Dupicate Direction !");
	cube->WE = ft_get_mid_string(line, ' ');

	cube->files_f[2] = 1;
}

void	ft_get_EA(t_cube *cube, char *line)
{
	if(cube->files_f[3])
		ft_exit("EA Dupicate Direction !");
	cube->EA = ft_get_mid_string(line, ' ');
	cube->files_f[3] = 1;
}