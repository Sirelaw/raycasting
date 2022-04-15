#include "../../includes/cub3d.h"

void plot_line_angle(int start[2], float theta, float dist, t_vars *vars)
{
	int	new_point[2];
	
	new_point[0] = start[0] + (dist * cosf(theta));
	new_point[1] = start[1] + (dist * sinf(theta));
	plotline(start, new_point, vars, BLUE);
}

static void	cast_ray(t_vars *vars, float theta)
{
	float	temp[2];
	int		point[2];
	float	dy;
	float	dx;

	dx = cosf(theta) * vars->tile_size;
	dy = sinf(theta) * vars->tile_size;
	temp[0] = vars->player_f[0];
	temp[1] = vars->player_f[1];
	while((vars->input)[(int)temp[1] >> 5][(int)temp[0] >> 5] != '1')
	{
		temp[0] += dx;
		temp[1] += dy;
	}
	point[0] = temp[0];
	point[1] = temp[1];
	plotline(vars->player, point, vars, BLUE + GREEN);
}

void	cast_rays(t_vars *vars)
{
	int		i;
	float	dtheta;
	float	theta;

	i = 0;
	theta = vars->orient - M_PI / 6;
	dtheta = (M_PI / 3.0) / 1200;
	vars->img = mlx_new_image(vars->mlx, vars->win_w, vars->win_h);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_lenght, &vars->endian);
	while (i++ < 1200)
	{
		theta += dtheta;
		if (theta > 2 * M_PI)
			theta -= 2 * M_PI;
		else if (theta < 0)
			theta += 2 * M_PI;
		draw_rays(vars, theta);
	}
	plot_line_angle(vars->player, vars->orient, 20, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	draw_field(vars);
}

void	draw_field(t_vars *vars)
{
	int	i;
	int	j;
	char	**input;

	i = 0;
	input = vars->input;
	while (input[i])
	{
		j = 0;
		while(input[i][j])
		{
			if (input[i][j] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win,
				vars->im[WHITE_32].l,
				j * vars->tile_size, i * vars->tile_size);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->im[PLAYER].l,
	vars->player[0], vars->player[1]);
}
