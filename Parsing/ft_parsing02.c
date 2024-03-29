/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:42:03 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:14:17 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_count_elements(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_rgb_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && line[i] == ',' && line[i + 1] == ',')
			return (0);
		else if (line[0] == ',' || line[ft_strlen(line) - 1] == ',')
			return (0);
		else if (ft_count_elements(line, ',') != 2 || ft_check_rgb_2(line) != 3)
			return (0);
		i++;
	}
	return (1);
}

int	ft_cf_last_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9')
				|| str[i] == ',' || str[i] == 'C'
				|| str[i] == 'F' || str[i] == ' ' || str[i] == '\n'))
		{
			ft_exit("CF Error !");
		}
		i++;
	}
	return (1);
}

void	ft_get_c(t_cube *cube, char *line)
{
	int	i;

	i = 0;
	ft_cf_last_check(line);
	if (cube->files_f[4])
		ft_exit("Duplicate C RGB!");
	while (line[i])
	{
		if (!ft_rgb_check(line))
		{
			printf("RGB  Error\n");
			exit(0);
		}
		i++;
	}
	cube->c = ft_get_rgb(line);
}

void	ft_get_f(t_cube *cube, char *line)
{
	int	i;

	i = 0;
	ft_cf_last_check(line);
	if (cube->files_f[5])
		ft_exit("Duplicate F RGB!");
	while (line[i])
	{
		if (!ft_rgb_check(line))
		{
			printf("RGB Error\n");
			exit(0);
		}
		i++;
	}
	cube->f = ft_get_rgb(line);
}
