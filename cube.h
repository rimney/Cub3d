/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:45 by rimney            #+#    #+#             */
/*   Updated: 2022/12/22 21:46:54 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "Get_next_line/get_next_line.h"

typedef	struct	s_cube
{
    double		P_position_x;
    double		P_posotion_y;
    char	*NO; // 0
	char	*WE; // 2
	char	*EA; // 3
	char	*SO; // 1
	int		C; // 4
	int		F; // 5
	int		*files_f;
	int		Psp; // it contains the ascii value of the direction character
	int		MapHeight;
	int		MapWidth;
	char	**Map;
	void	*mlx_init;
	void	*mlx_window;
} t_cube;

/********************** Parsing Functions **********************/

void	ft_get_NO(t_cube *cube, char *line);
void	ft_get_SO(t_cube *cube, char *line);
void	ft_get_WE(t_cube *cube, char *line);
void	ft_get_EA(t_cube *cube, char *line);
void	ft_get_xpms(t_cube *cube, char **argv);
int		*ft_files_f_init(void);
char	*ft_strjoin_1(char *str, char c);
int	ft_check_rgb_2(char *line);
int	ft_get_rgb(char *line, int i);
int	ft_count_elements(char *str, char c);
int	ft_rgb_check(char *line);
void	ft_get_C(t_cube *cube, char *line);
void	ft_get_F(t_cube *cube, char *line);
void	ft_get_CF(t_cube *cube, char **argv);
int	ft_strcmp(char *s1, char *s2);
int	ft_is_an_xpm(char *line);
int	ft_get_width(char **str);
int	ft_get_hight(char **str);
void	ft_print_2d(char **str);
void	ft_free_2d(char **str);
void	ft_parse_map_2(t_cube *cube, char *map);
void	ft_parse_map(t_cube *cube, char **argv, char *arg, int i);
char	is_a_direction(char c);
int	is_valid(char c);
int	c_is_safe(t_cube *cube, size_t i, size_t j);
int	ft_check_header_and_footer(t_cube *cube);
int	ft_check_map(t_cube *cube);
void	ft_get_player_position(t_cube *cube);
void	ft_get_map(t_cube *cube, char **argv);
void	ft_cube_values_init(t_cube *cube);
t_cube	*ft_struct_init(char **argv);
void	ft_free_parsing(t_cube *cube);
void ft_print(char *str, char *s);
void	ft_print_cube(t_cube *cube);
void	ft_exit(char *str);

#endif