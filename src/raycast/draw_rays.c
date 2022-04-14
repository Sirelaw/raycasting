#include "../../includes/cub3d.h"

float	get_dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
}

void	draw_rays(t_vars *vars, float theta)
{
	int 	mx, my, mp, dof;
	float	rx, ry, xo, yo, aTan, nTan;
	int		point_h[2];
	int		point_v[2];
	float	dist[2];

	dof = 0;
	dist[0] = 1000000;
	dist[1] = 1000000;
	aTan = -1 / tan(theta);
	if (theta > M_PI) // looking up
	{
		ry = (((int)(vars->player[1]) >> 5) << 5) - 0.0001;
		rx = (vars->player[1] - ry) * aTan + vars->player[0];
		yo = -32;
		xo = -yo * aTan;
	}
	else if (theta < M_PI) // looking down
	{
		ry = (((int)(vars->player[1]) >> 5) << 5) + 32;
		rx = (vars->player[1] - ry) * aTan + vars->player[0];
		yo = 32;
		xo = -yo * aTan;
	}
	if (theta == 0 || theta == M_PI) // looking straight left or right
	{
		rx = vars->player[0];
		ry = vars->player[1];
		dof = vars->win_h / vars->tile_size;
	}
	while (dof < vars->win_h / vars->tile_size)
	{
		mx = (int)(rx) >> 5;
		my = (int)(ry) >> 5;
		if (mx >= 0 && my >= 0 && mx < vars->map_width && my < vars->map_height && (vars->input)[my][mx] == '1')
		{
			point_h[0] = rx;
			point_h[1] = ry;
			dist[0] = get_dist(vars->player[0], vars->player[1], rx, ry);
			dof = vars->win_h / vars->tile_size;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	point_h[0] = rx;
	point_h[1] = ry;
	

	// --- Check Vertical lines ---
	dof = 0;
	nTan = -tan(theta);
	if (theta > M_PI_2 && theta < 3 * M_PI_2) // looking left
	{
		rx = (((int)(vars->player[0]) >> 5) << 5) - 0.0001;
		ry = (vars->player[0] - rx) * nTan + vars->player[1];
		xo = -32;
		yo = -xo * nTan;
	}
	if (theta < M_PI_2 || theta > 3 * M_PI_2) // looking right
	{
		rx = (((int)(vars->player[0]) >> 5) << 5) + 32;
		ry = (vars->player[0] - rx) * nTan + vars->player[1];
		xo = 32;
		yo = -xo * nTan;
	}
	if (theta == M_PI_2 || theta == 3 * M_PI_2) // looking straight up or down
	{
		rx = vars->player[0];
		ry = vars->player[1];
		dof = vars->win_w / vars->tile_size;
	}
	while (dof < vars->win_w / vars->tile_size)
	{
		mx = (int)(rx) >> 5;
		my = (int)(ry) >> 5;
		if (mx >= 0 && my >= 0 && mx < vars->map_width && my < vars->map_height && (vars->input)[my][mx] == '1')
		{
			point_v[0] = rx;
			point_v[1] = ry;
			dist[1] = get_dist(vars->player[0], vars->player[1], rx, ry);
			dof = vars->win_w / vars->tile_size;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	if (dist[0] < dist[1])
		plotline(vars->player, point_h, vars, WHITE);
	else
		plotline(vars->player, point_v, vars, RED);
}
