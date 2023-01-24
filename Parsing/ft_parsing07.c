/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing07.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:08:44 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:09:00 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] && line[i] >= '0' && line[i] <= '9')
		{
			count++;
			while (line[i] && line[i] >= '0' && line[i] <= '9')
				i++;
			if ((size_t)i == ft_strlen(line))
				return (count);
		}
		i++;
	}
	return (count);
}

void	ft_get_rgb_norm(int *rgb, char *line, char **temp, int *index)
{
	int	i;

	i = -1;
	while (line[++i] && *index <= 2)
	{
		if (line[i] >= '0' && line[i] <= '9')
			*(temp) = ft_strjoin_1(*temp, line[i]);
		else
		{
			if (ft_atoi(*temp) != 0)
			{
				rgb[*index] = ft_atoi(*temp);
				*index += 1;
				free(*temp);
				*temp = ft_strdup("");
			}
		}
	}
}

int	ft_get_rgb(char *line)
{
	int		rgb[3];
	int		index;
	char	*temp;

	index = 0;
	temp = ft_strdup("");
	ft_get_rgb_norm(rgb, line, &temp, &index);
	free(temp);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		ft_exit("Check rgb value !");
	return ((rgb[0] << 16 | rgb[1] << 8) | rgb[2]);
}