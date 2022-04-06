/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_game_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:54:13 by ttokesi           #+#    #+#             */
/*   Updated: 2022/04/06 23:14:33 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	close1(int keycode, t_vars *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static int	close12(t_vars *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	set_startvalues(t_vars *game, int lines, int rows)
{
	game->enemy = 0;
	game->count = 0;
	game->sizer = 6; // size of small map
	game->wi_x = rows;
	game->he_y = lines;
	game->collect = 0;
	game->check = 0;
	game->bh_x = -1;
	game->bh_y = -1;
	game->b2_x = -1;
	game->b2_y = -1;
}

void	game_starter(t_vars *game, int lines, int rows)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 20 * 65, 15 * 65,
			"42 cube3D");

// pixel part
 	game->img = mlx_new_image(game->mlx, 20 * 65, 15 * 65);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	my_mlx_pixel_put(game, game->fi_x + 500, game->fi_y + 500, 0x00CCFF66);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 000, 000);


	mlx_hook(game->win, 2, 1L << 2, close1, game);
	mlx_hook(game->win, 17, 1L << 17, close12, game);
	img_handler(game);
	set_startvalues(game, lines, rows);
	mlx_key_hook(game->win, key_hook, game);
	load_fields(game);
	mlx_loop_hook(game->mlx, my_timer, game);
	mlx_loop(game->mlx);
}
