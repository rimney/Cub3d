/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:27:47 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:28:29 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_check_file_extensions(t_cube *cube)
{
	if (ft_strcmp(ft_strrchr(cube->so, '.'), ".xmp") != 0)
		return (0);
	if (ft_strcmp(ft_strrchr(cube->no, '.'), ".xmp") != 0)
		return (0);
	if (ft_strcmp(ft_strrchr(cube->we, '.'), ".xmp") != 0)
		return (0);
	if (ft_strcmp(ft_strrchr(cube->ea, '.'), ".xmp") != 0)
		return (0);
	return (1);
}

char	*ft_strdup_texture(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	while (((size_t)i < ft_strlen(str) - 1) && str[i] != ' ' && str[i] != '\n')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int	ft_texture_final_check(char *xpm)
{
	char	**temp;

	temp = ft_split(xpm, ' ');
	if (ft_count_2d(temp) > 2)
		ft_exit("texture error\n");
	if (temp[0])
	{
		if (ft_strcmp(temp[0], "NO") != 0
			|| ft_strcmp(temp[0], "SO") != 0
			|| ft_strcmp(temp[0], "WE") != 0 || ft_strcmp(temp[0], "EA") != 0)
		{
			ft_free_2d(temp);
			ft_exit("texture error\n");
		}
	}
	ft_free_2d(temp);
	return (1);
}

char	*ft_get_texture(char *xpm)
{
	char	**temp;
	char	*t;

	if (!ft_texture_final_check(xpm))
		return (NULL);
	t = xpm;
	temp = ft_split(xpm, ' ');
	if (!temp[1])
		ft_exit("Xpm Error\n");
	xpm = ft_strdup_texture(temp[1]);
	ft_free_2d(temp);
	free(t);
	return (xpm);
}

void	ft_get_textures(t_cube *cube)
{
	cube->no = ft_get_texture(cube->no);
	cube->so = ft_get_texture(cube->so);
	cube->we = ft_get_texture(cube->we);
	cube->ea = ft_get_texture(cube->ea);	
}
