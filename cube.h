/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:45 by rimney            #+#    #+#             */
/*   Updated: 2023/01/18 19:11:45 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define SCALE 32
# define UP_KEY 13
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "Get_next_line/get_next_line.h"
#include <math.h>

typedef struct s_img
{
	void	*img;
	int		endian;
	int		bpp;
	int		size_len;
	char	*addr;
} t_img;

typedef struct s_player
{
	double angle;
	int turndirection;
	int	walkdirection;
	double	movespeed;
	double	rotationspeed;

} t_player;

typedef struct const_t
{
	int	num_of_rays;
	double fov;
	int		height;
	int		width;
}	t_const;

typedef	struct	s_cube
{
	int test;
    double		P_position_x;
    double		P_position_y;
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
	t_img	*img;
	t_player *player;
	t_const *stable;
} t_cube;

/********************** Parsing Functions **********************/
int hasawall(int x, int y, t_cube *cube);
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
void	ft_struct_init(char **argv, t_cube *cube);
void	ft_free_parsing(t_cube *cube);
void 	ft_print(char *str, char *s);
void	ft_print_cube(t_cube *cube);
void	ft_exit(char *str);
void	ft_init_player(t_cube *cube);
void	ft_img_init(t_img *img);
void 	ft_mlx_init(t_cube *cube);
void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color);
void rectengale(int x, int y, t_cube *cube, unsigned int color);
void render_map(t_cube *cube);
int cub_draw(t_cube *cube);
void update_player(t_cube *cube);
void	init_const_vr(t_cube *cube);
int is_a_wall(int x, int y, t_cube *cube);
void ft_new_image(t_cube *cube);
void ft_draw_line(int X0, int Y0, int X1, int Y1, t_cube *cube, unsigned int color);
void	draw_circle(int x, int y, t_cube *cube, unsigned int color);
#endif