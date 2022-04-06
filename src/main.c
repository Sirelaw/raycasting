#include "../includes/cub3d.h"

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

void	init_vars(t_vars *vars)
{
	vars->input	= NULL;
	vars->start_orientation = 0;
	vars->player_x = 0;
	vars->player_y = 0;
	vars->map_size[0] = 1024;
	vars->map_size[1] = 550;
}

void	init_orient(double	*orient, char start_orientation)
{
	if (start_orientation == 'E')
		*orient = 0;
	else if (start_orientation == 'N')
		*orient = M_PI_2;
	else if (start_orientation == 'W')
		*orient = M_PI;
	else if (start_orientation == 'S')
		*orient = 3 * M_PI_2;
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
	vars->player_dx = cos(vars->orient) * 5;
	vars->player_dy = sin(vars->orient) * 5;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars);
	input_rows(argc, argv, &vars);
	init_orient(&vars.orient, vars.start_orientation);
	printf("%d %d	%f\n", vars.player_x, vars.player_y, vars.orient);
	game_starter(&vars, 24, 48);
	print_str_arr(vars.input);
	return (0);
}