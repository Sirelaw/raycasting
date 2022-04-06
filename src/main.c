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

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars);
	input_rows(argc, argv, &vars);
	printf("%d %d\n", vars.player_x, vars.player_y);
	game_starter(&vars, 24, 48);
	print_str_arr(vars.input);
	return (0);
}