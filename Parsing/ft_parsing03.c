/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:42:29 by rimney            #+#    #+#             */
/*   Updated: 2022/12/24 21:32:53 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}


int	ft_is_an_xpm(char *line)
{
	if(ft_strncmp(line, "SO", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "WE", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "EA", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "NO", 2) == 0)
		return (1);
	else if(ft_strncmp(line, "C", 1) == 0)
		return (1);
	else if(ft_strncmp(line, "F", 1) == 0)
		return (1);
	else if (ft_strcmp(line, "\n") == 0)
		return (1);
	return (0);
}

int	ft_get_width(char **str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(str[i])
	{
		if((size_t)len < ft_strlen(str[i]))
			len = ft_strlen(str[i]);
		i++;
	}
	return (len);
}

int	ft_get_hight(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i - 1);
}

void	ft_print_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
}