#include "../../includes/cub3d.h"

float	get_dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
}

void	look_left_right(t_vars *vars, t_ray* ray)
{
	while (ray->dof < vars->win_w / vars->tile_size)
	{
		ray->mx = (int)(ray->rx) >> 5;
		ray->my = (int)(ray->ry) >> 5;
		if (ray->mx >= 0 && ray->my >= 0 && ray->mx < vars->map_width
			&& ray->my < vars->map_height
			&& (vars->input)[ray->my][ray->mx] == '1')
		{
			ray->point_v[0] = ray->rx;
			ray->point_v[1] = ray->ry;
			ray->dist[1] = get_dist(vars->player[0], vars->player[1], ray->rx, ray->ry);
			ray->dof = vars->win_w / vars->tile_size;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

void	init_look_left_right(t_vars *vars, t_ray* ray, float theta)
{
	if (theta > M_PI_2 && theta < 3 * M_PI_2)
	{
		ray->rx = (((int)(vars->player[0]) >> 5) << 5) - 0.0001;
		ray->ry = (vars->player[0] - ray->rx) * ray->nTan + vars->player[1];
		ray->xo = -32;
		ray->yo = -ray->xo * ray->nTan;
	}
	if (theta < M_PI_2 || theta > 3 * M_PI_2)
	{
		ray->rx = (((int)(vars->player[0]) >> 5) << 5) + 32;
		ray->ry = (vars->player[0] - ray->rx) * ray->nTan + vars->player[1];
		ray->xo = 32;
		ray->yo = -ray->xo * ray->nTan;
	}
	if (theta == M_PI_2 || theta == 3 * M_PI_2)
	{
		ray->rx = vars->player[0];
		ray->ry = vars->player[1];
		ray->dof = vars->win_w / vars->tile_size;
	}
	look_left_right(vars, ray);
}

void	look_up_down(t_vars *vars, t_ray* ray)
{
	ray->dof = 0;
	while (ray->dof < vars->win_h / vars->tile_size)
	{
		ray->mx = (int)(ray->rx) >> 5;
		ray->my = (int)(ray->ry) >> 5;
		if (ray->mx >= 0 && ray->my >= 0 && ray->mx < vars->map_width
			&& ray->my < vars->map_height
			&& (vars->input)[ray->my][ray->mx] == '1')
		{
			ray->point_h[0] = ray->rx;
			ray->point_h[1] = ray->ry;
			ray->dist[0] = get_dist(vars->player[0], vars->player[1], ray->rx, ray->ry);
			ray->dof = vars->win_h / vars->tile_size;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

void	init_look_up_down(t_vars *vars, t_ray* ray, float theta)
{
	if (theta > M_PI)
	{
		ray->ry = (((int)(vars->player[1]) >> 5) << 5) - 0.0001;
		ray->rx = (vars->player[1] - ray->ry) * ray->aTan + vars->player[0];
		ray->yo = -32;
		ray->xo = -ray->yo * ray->aTan;
	}
	else if (theta < M_PI)
	{
		ray->ry = (((int)(vars->player[1]) >> 5) << 5) + 32;
		ray->rx = (vars->player[1] - ray->ry) * ray->aTan + vars->player[0];
		ray->yo = 32;
		ray->xo = -ray->yo * ray->aTan;
	}
	if (theta == 0 || theta == M_PI)
	{
		ray->rx = vars->player[0];
		ray->ry = vars->player[1];
		ray->dof = vars->win_h / vars->tile_size;
	}
	look_up_down(vars, ray);
}

void	draw_rays(t_vars *vars, float theta)
{
	t_ray	ray;

	ray.dist[0] = 1000000;
	ray.dist[1] = 1000000;
	ray.aTan = -1 / tan(theta);
	ray.nTan = -tan(theta);
	init_look_up_down(vars, &ray, theta);
	init_look_left_right(vars, &ray, theta);
	if (ray.dist[0] < ray.dist[1])
		plotline(vars->player, ray.point_h, vars, WHITE);
	else
		plotline(vars->player, ray.point_v, vars, RED);
}
