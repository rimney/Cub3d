/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 03:38:39 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/21 03:52:40 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	press_key_hook(int key, t_cube *cube)
{
	if (key == 13)
		cube->player->walkdirection = +1;
	else if (key == 1)
		cube->player->walkdirection = -1;
	else if (key == 123)
		cube->player->turndirection = -1;
	else if (key == 124)
		cube->player->turndirection = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

int	release_key_hook(int key, t_cube *cube)
{
	if (key == 13)
		cube->player->walkdirection = 0;
	else if (key == 1)
		cube->player->walkdirection = 0;
	else if (key == 123)
		cube->player->turndirection = 0;
	else if (key == 124)
		cube->player->turndirection = 0;
	return (0);
}
