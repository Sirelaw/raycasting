/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:02:23 by oipadeol          #+#    #+#             */
/*   Updated: 2022/04/15 02:12:20 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "get_line.h"
# include "ray_cast.h"

# define STEP 10

enum e_images
{
	FIG1 ,
	NONE ,
	WHITE_32 ,
	NONE_32,
	PLAYER,
	FLOOR ,
	WALL ,
	BLACK,
	IMAGE_COUNT
};

enum	e_keys
{
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	W_KEY = 13,
	LEFT_KEY = 123,
	RIGHT_KEY = 124	
};

typedef struct s_img
{
	void			*l;
	char			*path;
	enum e_images	name;
}	t_img;

typedef struct s_ray
{
	int 	mx;
	int		my;
	int		dof;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	aTan;
	float	nTan;
	int		point_h[2];
	int		point_v[2];
	float	dist[2];
}	t_ray;


typedef struct s_vars
{
	t_img	im[IMAGE_COUNT];
	void	*mlx;
	void	*win;
	int		count;
	int		win_w;
	int		win_h;
	char	**map;
	void	*img;
	char	start_orientation;
	double	orient;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int		player[2];
	float	player_f[2];
	float	player_d[2];
	int		origin[2];
	char	**input;
	int		map_width;
	int		map_height;
	int		images[8];
	int 	sizer;
	int		tile_size;
}				t_vars;

void	img_handler(t_vars *vars);

// ------- mlx  ----------
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int mousecode, int x, int y, t_vars *vars);
int		clean_destroy(t_vars *vars);

// ------- input ---------
void	input_rows_init_player(int argc, char **argv, t_vars *vars);
int		check_valid(char **input, t_vars *vars);
void	standardize_input(char **str_ptr, int *max_len);
void	ft_error(void);

// ------ ray --------

void	plotline(int x0_y0[2], int x1_y1[2], t_vars *vars, int color);
void	plot_line_angle(int start[2], float theta, float dist, t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	draw_field(t_vars *vars);
void	draw_rays(t_vars *vars, float theta);
void	cast_rays(t_vars *vars);


// -------- dev -------

void	print_str_arr(char **input);

#endif