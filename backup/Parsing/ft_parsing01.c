/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:41:34 by rimney            #+#    #+#             */
/*   Updated: 2022/12/22 21:42:02 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_get_xpms(t_cube *cube, char **argv)
{
    char	*line;

	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("An error has been occurred when opening the file\n");
		exit(1);
	}
	while((line = get_next_line(fd)))
	{
		if(ft_strncmp(line, "NO", 2) == 0)
			ft_get_NO(cube, line);
		else if(ft_strncmp(line, "SO", 2) == 0)
			ft_get_SO(cube, line);
		else if(ft_strncmp(line, "WE", 2) == 0)
			ft_get_WE(cube, line);
		else if(ft_strncmp(line, "EA", 2) == 0)
			ft_get_EA(cube, line);
		free(line);
	}
}

int	*ft_files_f_init(void)
{
	int *arr;
	int i;

	i = 0;
	arr = malloc(sizeof(int) * 7);
	while(i < 7)
	{
		arr[i] = 0;
		i++;
	}	
	return (arr);
}

char	*ft_strjoin_1(char *str, char c)
{
	char	*s;
	int		i;
	int		n;

	i = 0;
	n = 0;
	s = malloc(strlen(str) + 2);
	while (str[i])
		s[n++] = str[i++];
	s[n] = c;
	s[n + 1] = 0;
	free(str);
	return (s);
}

int	ft_check_rgb_2(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if(line[i] && line[i] >= '0' && line[i] <= '9')
		{
			count++;
			while(line[i] >= '0' && line[i] <= '9')
				i++;
		}
		i++;
	}
	return (count);

}

int	ft_get_rgb(char *line, int i)
{
	int		rgb[3];
	int		index;
	char	*temp;

	i = 0;
	index = 0;
	temp = ft_strdup("");
	while (line[i] && index <= 2)
	{
		if(line[i] >= '0' && line[i] <= '9')
			temp = ft_strjoin_1(temp, line[i]);
		else
		{
			if(ft_atoi(temp) != 0)
			{
				rgb[index] = ft_atoi(temp);
				index++;
				free(temp);
				temp = ft_strdup("");
			}
		}
		i++;
	}
	free(temp);
	return ((rgb[0] << 16 | rgb[1] << 8) | rgb[2]);
}