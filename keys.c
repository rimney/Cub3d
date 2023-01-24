/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 03:38:39 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/24 01:31:59 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	press_key_hook(int key, t_cube *cube)
{
	if (key == 13  || key == 126)
		cube->player->walkdirection = +1;
	else if (key == 1 || key == 125)
		cube->player->walkdirection = -1;
	else if (key == 123 || key == 0)
		cube->player->turndirection = -1;
	else if (key == 124 || key == 2)
		cube->player->turndirection = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

int	release_key_hook(int key, t_cube *cube)
{
	if (key == 13 || key == 126)
		cube->player->walkdirection = 0;
	else if (key == 1 || key == 125)
		cube->player->walkdirection = 0;
	else if (key == 123 || key == 0)
		cube->player->turndirection = 0;
	else if (key == 124 || key == 2)
		cube->player->turndirection = 0;
	return (0);
}
