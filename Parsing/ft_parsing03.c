/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:42:29 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 03:02:28 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_is_an_xpm(char *line)
{
	int	space;

	space = 0;
	if (line[0] == ' ' || line[0] == '\t')
	{
		while (line[space] && (line[space] == ' ' || line[space] == '\t'))
			space++;
	}
	if (ft_strncmp(line + space, "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(line + space, "WE", 2) == 0)
		return (1);
	else if (ft_strncmp(line + space, "EA", 2) == 0)
		return (1);
	else if (ft_strncmp(line + space, "NO", 2) == 0)
		return (1);
	else if (ft_strncmp(line + space, "C", 1) == 0)
		return (1);
	else if (ft_strncmp(line + space, "F", 1) == 0)
		return (1);
	else if (ft_strcmp(line, "\n") == 0)
		return (1);
	return (0);
}

int	ft_get_width(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((size_t)len < ft_strlen(str[i]))
			len = ft_strlen(str[i]);
		i++;
	}
	return (len);
}

int	ft_get_hight(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_print_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
}
