#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if ((x >= vars->map_w) || (y >= vars->map_l) || (x < 0) || (y < 0))
		return ;
	dst = vars->addr + (y * vars->line_lenght + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_str_arr(char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		printf("%s\n", input[i]);
		i++;
	}
}

int	render_next_frame(t_vars *vars)
{
	// mlx_destroy_image(vars->mlx, vars->img);
	// vars->img = mlx_new_image(vars->mlx, vars->map_w, vars->map_l);
	// vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
	// 		&vars->line_lenght, &vars->endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->im[BLACK].l,
	vars->player[0] * vars->tile_size, vars->player[1] * vars->tile_size);
	return (0);
}

int	clean_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	// free_all(vars);
	exit(EXIT_SUCCESS);
}


void	rotate_player(int keycode, t_vars *vars)
{
	if (keycode == LEFT_KEY)
		vars->orient += M_PI_2 / 10;
	else if (keycode == RIGHT_KEY)
		vars->orient -= M_PI_2 / 10;
	if (vars->orient >= 2 * M_PI)
		vars->orient = 0;
	else if (vars->orient < 0)
		vars->orient = 2 * M_PI;
	vars->player_d[0] = cos(vars->orient) * 5;
	vars->player_d[1] = sin(vars->orient) * 5;
	printf("Angle:	%f, player_d[0]:	%f, player_d[1]	%f\n", vars->orient, vars->player_d[0], vars->player_d[1]);
}

void	move_image(int keycode, t_vars *vars)
{
	if (keycode == A_KEY)
		vars->player_f[0] -= vars->player_d[0];
	else if (keycode == D_KEY)
		vars->player_f[0] += vars->player_d[0];
	else if (keycode == S_KEY)
	{
		vars->player_f[0] -= vars->player_d[0];
		vars->player_f[1] -= vars->player_d[1];
	}
	else if (keycode == W_KEY)
	{
		vars->player_f[0] += vars->player_d[0];
		vars->player_f[1] += vars->player_d[1];
	}
	vars->player[0] = vars->player_f[0];
	vars->player[1] = vars->player_f[1];
	printf("Angle:	%f, player_d[0]:	%f, player_d[1]	%f\n", vars->orient, vars->player_d[0], vars->player_d[1]);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		clean_destroy(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->im[BLACK].l,
	vars->player[0] * vars->tile_size, vars->player[1] * vars->tile_size);
	if ((keycode >= 123) && (keycode <= 126))
		rotate_player(keycode, vars);
	else if (((keycode >= A_KEY) && (keycode <= D_KEY)) || ((keycode >= S_KEY)
			&& (keycode <= W_KEY)))
		move_image(keycode, vars);
	render_next_frame(vars);
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	if ((mousecode == 4) || (mousecode == 5))
	{
		// zoom_image(mousecode, x, y, vars);
		// render_next_frame(vars);
	}
	return (0);
}

void	init_vars(t_vars *vars)
{
	vars->input	= NULL;
	vars->map_w = 1500;
	vars->map_l = 320;
	vars->start_orientation = 0;
	vars->player[0] = 0;
	vars->player[1] = 0;
	vars->player_d[0] = 0;
	vars->player_d[1] = 0;
	vars->player_f[0] = 0;
	vars->player_f[1] = 0;
	vars->sizer = 6;
	vars->tile_size = 32;
	vars->origin[0] = 0;
	vars->origin[1] = 0;
}

int	draw_line(t_vars *vars)
{
	// int	point1[2];
	// int	point2[2];

	// point1[0] = (20.0 * cosf(vars->orient)) * vars->sizer;
	// point1[1] = (20.0 * sinf(vars->orient)) * vars->sizer;
	// point2[0] = 2;
	// point2[1] = 2;
	// vars->img = mlx_new_image(vars->mlx, vars->map_w, vars->map_l);
	// vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
	// 		&vars->line_lenght, &vars->endian);
	// plotline(vars->player, point1, vars, GREEN + BLUE);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars);
	input_rows_init_player(argc, argv, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map_w,
			vars.map_l, "42+2 cube3D");
	vars.img = mlx_new_image(vars.mlx, vars.map_w, vars.map_l);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_lenght, &vars.endian);
	draw_line(&vars);
	img_handler(&vars);
	draw_field(&vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 17, 0, clean_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}