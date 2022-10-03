/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:21 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 12:14:10 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_exit(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 2)
		err_handle(5, "exit", " too many arguments");
	if (argc >= 2)
	{
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
			{
				err_handle(5, "exit", "numeric argument required");
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(argv[1]));
	}
	else
	{
		exit(data()->exit_state);
	}
	return (data()->exit_state);
}
