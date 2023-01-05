/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:42:03 by rimney            #+#    #+#             */
/*   Updated: 2022/12/27 22:45:33 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_count_elements(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if(str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_rgb_check(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] && line[i + 1] && line[i] == ',' && line[i + 1] == ',')
			return (0);
		else if(line[0] == ',' || line[ft_strlen(line) - 1] == ',')
			return (0);
		else if(ft_count_elements(line, ',') != 2 || ft_check_rgb_2(line) != 3)
			return (0);
		
		i++;
	}
	return (1);
}

void	ft_get_C(t_cube *cube, char *line)
{
	int i;
	// int ret;

	i = 0;
	// ret = 0;
	if(cube->files_f[4])
		ft_exit("Duplicate C RGB!");
	while(line[i])
	{
		if(!ft_rgb_check(line))
		{
			printf("RGB  Error\n");
			exit(0);
		}
		i++;
	}
	cube->C = ft_get_rgb(line, i);
}

void	ft_get_F(t_cube *cube, char *line)
{
	int i;

	i = 0;

	if(cube->files_f[5])
		ft_exit("Duplicate F RGB!");
	while(line[i])
	{
		if(!ft_rgb_check(line))
		{
			printf("RGB Error\n");
			exit(0);
		}
		i++;
	}
	cube->F = ft_get_rgb(line, i);
}

void	ft_get_CF(t_cube *cube, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	(void)cube;
	while((line = get_next_line(fd)))
	{
		if(ft_strncmp(line, "C", 1) == 0)
		{
			ft_get_C(cube, line);
			cube->files_f[4] = 1;
		}
		else if(ft_strncmp(line, "F", 1) == 0)
		{
			ft_get_F(cube, line);
			cube->files_f[5] = 1;
		}
		free(line);
	}
}