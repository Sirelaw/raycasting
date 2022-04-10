#include "../../includes/cub3d.h"

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
	vars->player[0] * vars->tile_size, vars->player[1] * vars->tile_size);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->im[BLACK].l,
	vars->player[0] * vars->tile_size, vars->player[1] * vars->tile_size);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->im[FIG1].l,
	vars->player[0] * vars->tile_size, vars->player[1] * vars->tile_size);
}
