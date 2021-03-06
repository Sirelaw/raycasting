#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if ((x >= vars->win_w) || (y >= vars->win_h) || (x < 0) || (y < 0))
		return ;
	dst = vars->addr + (y * vars->line_lenght + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render_next_rays(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	cast_rays(vars);
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, vars->win_w, vars->win_h);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_lenght, &vars->endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->im[PLAYER].l,
	vars->player[0] * vars->tile_size, vars->player[1] * vars->tile_size);
	return (0);
}

void	rotate_player(int keycode, t_vars *vars)
{
	if (keycode == RIGHT_KEY)
		vars->orient += 0.1;
	else if (keycode ==  LEFT_KEY)
		vars->orient -= 0.1;
	if (vars->orient > 2 * M_PI)
		vars->orient -= 2 * M_PI;
	else if (vars->orient < 0)
		vars->orient += 2 * M_PI;
	vars->player_d[0] = cosf(vars->orient);
	vars->player_d[1] = sinf(vars->orient);
	render_next_rays(vars);
}

static void	check_valid_position(float temp[2], t_vars *vars)
{
	if ((vars->input)[(int)temp[1] >> 5][(int)temp[0] >> 5] != '1')
	{
		vars->player_f[0] = temp[0];
		vars->player_f[1] = temp[1];
		vars->player[0] = temp[0];
		vars->player[1] = temp[1];
	}
	render_next_rays(vars);
}

void	move_image(int keycode, t_vars *vars)
{
	float temp[2];

	temp[0] = vars->player_f[0];
	temp[1] = vars->player_f[1];
	if (keycode == A_KEY)
	{
		temp[0] += STEP * vars->player_d[1];
		temp[1] -= STEP * vars->player_d[0];
	}
	else if (keycode == D_KEY)
	{
		temp[0] -= STEP * vars->player_d[1];
		temp[1] += STEP * vars->player_d[0];
	}
	else if (keycode == S_KEY)
	{
		temp[0] -= STEP * vars->player_d[0];
		temp[1] -= STEP * vars->player_d[1];
	}
	else if (keycode == W_KEY)
	{
		temp[0] += STEP * vars->player_d[0];
		temp[1] += STEP * vars->player_d[1];
	}
	check_valid_position(temp, vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		clean_destroy(vars);
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

int	clean_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	// free_all(vars);
	exit(EXIT_SUCCESS);
}