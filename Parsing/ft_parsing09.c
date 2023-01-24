/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing09.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:23:07 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:24:36 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_open_file_so(t_cube *cube)
{
	int	fd;

	fd = open(cube->so, O_RDONLY);
	if (fd == -1)
		return (0);
    return (1);
}

int	ft_open_file_we(t_cube *cube)
{
	int fd;

	fd = open(cube->we, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);	
}

int	ft_open_file_no(t_cube *cube)
{
	int	fd;

	fd = open(cube->no, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);	
}

int	ft_open_file_ea(t_cube *cube)
{
	int	fd;

	fd = open(cube->ea, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);	
}
