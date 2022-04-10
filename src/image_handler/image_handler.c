/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:53:35 by ttokesi           #+#    #+#             */
/*   Updated: 2022/04/10 16:43:16 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	p_img(t_vars *g)
{
	g->im[FLOOR].path = "./img/floor.xpm";
	g->im[NONE].path = "./img/none.xpm";
	g->im[WALL].path = "./img/wall.xpm";
	g->im[FIG1].path = "./img/fig1.xpm";
	g->im[BLACK].path = "./img/black.xpm";
	g->im[WHITE_32].path = "./img/white_32.xpm";
	g->im[NONE_32].path = "./img/none_32.xpm";
	g->im[PLAYER].path = "./img/player_6.xpm";
}

static void	load_img(t_vars *vars)
{
	int	w;
	int	h;
	int	i;

	i = 0;
	while (i < IMAGE_COUNT - 1)
	{
		vars->im[i].l = mlx_xpm_file_to_image(vars->mlx,
					vars->im[i].path, &w, &h);
		i++;
	}
}

void	img_handler(t_vars *game)
{
	p_img(game);
	load_img(game);
}
