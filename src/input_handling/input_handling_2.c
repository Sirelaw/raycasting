/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:51:48 by oipadeol          #+#    #+#             */
/*   Updated: 2022/04/05 15:35:47 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_error(void)
{
	write(STDERR_FILENO, "Error\n", 6);
	exit(1);
}

int	check_valid(char** input)
{
	int	i;
	int	j;
	int	arr_len;

	arr_len = 0;
	while (input && input[arr_len])
		arr_len++;
	
	
}