/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:41:14 by rimney            #+#    #+#             */
/*   Updated: 2023/01/25 01:57:25 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	ft_get_no(t_cube *cube, char *line)
{
	if (cube->files_f[0])
		ft_exit("NO Dupicate Direction !");
	cube->no = ft_get_mid_string(line, ' ');
	cube->files_f[0] = 1;
}

void	ft_get_so(t_cube *cube, char *line)
{
	if (cube->files_f[1])
		ft_exit("SO Dupicate Direction !");
	cube->so = ft_get_mid_string(line, ' ');
	cube->files_f[1] = 1;
}

void	ft_get_we(t_cube *cube, char *line)
{
	if (cube->files_f[2])
		ft_exit("WE Dupicate Direction !");
	cube->we = ft_get_mid_string(line, ' ');
	cube->files_f[2] = 1;
}

void	ft_get_ea(t_cube *cube, char *line)
{
	if (cube->files_f[3])
		ft_exit("EA Dupicate Direction !");
	cube->ea = ft_get_mid_string(line, ' ');
	cube->files_f[3] = 1;
}
