/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:45 by rimney            #+#    #+#             */
/*   Updated: 2023/01/25 02:32:42 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define SCALE 32
# define UP_KEY 13 
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define TEX_WIDTH 32
# define TEX_HEIGHT 32
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720
# include <unistd.h>
# include <limits.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "Get_next_line/get_next_line.h"
# include <math.h>

typedef struct s_render
{
	double	pdistance;
	double	dpp;
	double	projectionwallheight;
	int		wallstripeheight;
	int		wallt;
	int		wallb;
	int		distance_top;
}	t_render;

typedef struct s_casting
{
	double	xstep;
	double	ystep;
	double	xintercept;
	double	xnext;
	double	ynext;
	double	yintercept;
	double	angle;
	double	verdistance;
	double	horizdestance;
}	t_casting;

typedef struct s_img
{
	void	*img;
	int		endian;
	int		bpp;
	int		size_len;
	char	*addr;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	angle;
	int		turndirection;
	int		walkdirection;
	double	movespeed;
	double	rotationspeed;
	double	verticalx;
	double	verticaly;
	double	horizx;
	double	horizy;
	int		flag;
}	t_player;

typedef struct const_t
{
	int		num_of_rays;
	double	fov;
	int		height;
	int		width;
}	t_const;

typedef struct s_cube
{
	double		p_position_x;
	double		p_position_y;
	char		*no;
	char		*we;
	char		*ea;
	char		*so;
	t_img		*so_texture;
	t_img		*no_texture;
	t_img		*we_texture;
	t_img		*ea_texture;
	t_img		*texture;	
	int			c;
	int			f;
	int			*files_f;
	int			psp;
	int			mapheight;
	int			mapwidth;
	int			max_width;
	char		**map;
	void		*mlx_init;
	void		*mlx_window;
	int			render;
	int			texture_offs_x;
	int			texture_offs_y;
	int			texture_color;
	t_img		*img;
	t_player	*player;
	t_const		*stable;
}	t_cube;

typedef struct s_ray
{
	double	raydistance;
	double	xray;
	double	yray;
	double	ray_angle;
	int		is_vertical_hit;
	double	wall_hit_point_x;
	double	wall_hit_point_y;
}	t_ray;

/********************** Parsing Functions **********************/
int		hasawall(int x, int y, t_cube *cube);
void	ft_get_no(t_cube *cube, char *line);
void	ft_get_so(t_cube *cube, char *line);
void	ft_get_we(t_cube *cube, char *line);
void	ft_get_ea(t_cube *cube, char *line);
void	ft_get_xpms(t_cube *cube, char **argv);
int		*ft_files_f_init(void);
char	*ft_strjoin_1(char *str, char c);
int		ft_check_rgb_2(char *line);
int		ft_get_rgb(char *line);
int		ft_count_elements(char *str, char c);
int		ft_rgb_check(char *line);
void	ft_get_c(t_cube *cube, char *line);
void	ft_get_f(t_cube *cube, char *line);
void	ft_get_cf(t_cube *cube, char **argv);
int		ft_strcmp(char *s1, char *s2);
int		ft_is_an_xpm(char *line);
int		ft_get_width(char **str);
int		ft_get_hight(char **str);
void	ft_print_2d(char **str);
void	ft_free_2d(char **str);
void	ft_parse_map_2(t_cube *cube, char *map);
void	ft_parse_map(t_cube *cube, char **argv, char *arg, int i);
char	is_a_direction(char c);
int		is_valid(char c);
int		c_is_safe(t_cube *cube, size_t i, size_t j);
int		ft_check_map(t_cube *cube);
void	ft_get_player_position(t_cube *cube);
void	ft_get_map(t_cube *cube, char **argv);
void	ft_cube_values_init(t_cube *cube);
void	ft_struct_init(char **argv, t_cube *cube);
void	ft_free_parsing(t_cube *cube);
void	ft_print(char *str, char *s);
void	ft_print_cube(t_cube *cube);
void	ft_exit(char *str);
void	ft_init_player(t_cube *cube);
void	ft_img_init(t_img *img);
void	ft_mlx_init(t_cube *cube);
void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color);
void	render_map(t_cube *cube);
int		cub_draw(t_cube *cube);
void	update_player(t_cube *cube);
void	init_const_vr(t_cube *cube);
int		is_a_wall(int x, int y, t_cube *cube);
void	ft_new_image(t_cube *cube);
int		release_key_hook(int key, t_cube *cube);
int		press_key_hook(int key, t_cube *cube);
int		ft_count_2d(char **str);
char	*ft_get_mid_string(char *str, char c);
char	*ft_strdup_texture(char *str);
int		ft_check_header_and_footer(char **Map, t_cube *cube);
int		ft_map_final_check(t_cube *cube);
int		ft_texture_final_check(char *xpm);
int		ft_theres_player(t_cube *cube);
int		ft_open_file_ea(t_cube *cube);
int		ft_open_file_no(t_cube *cube);
int		ft_open_file_we(t_cube *cube);
int		ft_open_file_so(t_cube *cube);
int		ft_check_file_extensions(t_cube *cube);
char	*ft_strdup_texture(char *str);
int		ft_texture_final_check(char *xpm);
char	*ft_get_texture(char *xpm);
void	ft_get_textures(t_cube *cube);
void	ft_textures_init(t_cube *cube);
int		is_down(double angle);
int		is_right(double angle);
void	resize_angle(double *angle);
void	floor_ceeling_render(t_cube *cube);
void	cast_all_ray(t_cube *cube);
double	cast_horizntal(t_cube *cube, double angle);
double	cast_vertical(t_cube *cube, double angle);
#endif