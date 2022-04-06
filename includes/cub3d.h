/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:02:23 by oipadeol          #+#    #+#             */
/*   Updated: 2022/04/06 23:05:09 by oipadeol         ###   ########.fr       */
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

enum e_images
{
	FIG1 = 0,
	NONE = 1,
	FLOOR = 4,
	BH1 = 5,
	WALL = 9,
	GOVER = 17,
	WIN = 18
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

// -----game-------
typedef struct s_img
{
	void			*l;
	char			*p;
	enum e_images	name;
}	t_img;

typedef struct s_vars
{
	t_img	im[19];
	void	*mlx;
	void	*win;
	int		count;
	char	**map;
	void	*img;
	char	start_orientation;
	double	orient;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	char	**input;
	int		enemy;
	int		map_size[2];
	int		collect;
	int		check;
	int		fi_x;
	int		fi_y;
	int		player_x;
	int		player_y;
	int		player_dx;
	int		player_dy;
	int		bh_x;
	int		bh_y;
	int		b2_x;
	int		b2_y;
	int		wi_x;
	int		he_y;
	int 	sizer;
}				t_vars;

//utils

void	game_starter(t_vars *game, int lines, int rows);

//mapmaker
void	proc_file(int fd);

// mlx game related

void	img_handler(t_vars *game);
int		key_hook(int keycode, t_vars *game);
int		my_timer(t_vars *game);
// void	put_num_screen(t_vars *game);
void	load_fields(t_vars *game);
void	my_killer(t_vars *game);


// ------- input ---------

void	input_rows(int argc, char **argv, t_vars *vars);
int		check_valid(char **input, t_vars *vars);
void	ft_error(void);

#endif