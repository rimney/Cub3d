/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:41:34 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:10:03 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_count_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_get_mid_string(char *str, char c)
{
	char	**temp;
	char	*ret;

	temp = ft_split(str, c);
	ft_texture_final_check(str);
	if (ft_count_2d(temp) > 1)
	{
		ret = ft_strdup_texture(temp[1]);
		ft_free_2d(temp);
		return (ret);
	}
	ft_free_2d(temp);
	ft_exit("file Error");
	return (NULL);
}

void	ft_get_xpms_norm(t_cube *cube, char *line, int space)
{
	if (ft_strncmp(line + space, "NO", 2) == 0)
		ft_get_no(cube, line);
	else if (ft_strncmp(line + space, "SO", 2) == 0)
		ft_get_so(cube, line);
	else if (ft_strncmp(line + space, "WE", 2) == 0)
		ft_get_we(cube, line);
	else if (ft_strncmp(line + space, "EA", 2) == 0)
		ft_get_ea(cube, line);
}

void	ft_get_xpms(t_cube *cube, char **argv)
{
	char	*line;
	int		fd;
	int		space;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("An error has been occurred when opening the file\n");
		exit(1);
	}
	while ((1))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		space = 0;
		if (line[space] == ' ' || line[space] == '\t')
		{
			while (line[space] && line[space] == ' ')
				space++;	
		}
		ft_get_xpms_norm(cube, line, space);
		free(line);
	}
}

int	*ft_files_f_init(void)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int) * 7);
	while (i < 7)
	{
		arr[i] = 0;
		i++;
	}	
	return (arr);
}
