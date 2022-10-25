/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:21 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 07:45:43 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit(void)
{
	if (isatty(fileno(stdin)))
		printf("exit\n");
}

void	ft_exit_helper(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
	{
		if (i == 0 && (ft_isdigit(argv[1][i])
			|| argv[1][0] == '+' || argv[1][0] == '-'))
			i++;
		else if (!ft_isdigit(argv[1][i]))
		{
			print_exit();
			err_handle(5, "exit: ", "numeric argument required: ");
			exit(255);
		}
		else
			i++;
	}
	if (i == 0)
	{
		print_exit();
		err_handle(5, "exit: ", "numeric argument required: ");
		exit(255);
	}
}

int	ft_exit(int argc, char **argv)
{
	if (argc > 2)
	{
		print_exit();
		err_handle(5, "exit: ", "too many arguments: ");
	}
	if (argc >= 2)
	{
		ft_exit_helper(argv);
		print_exit();
		exit(ft_atoi(argv[1]));
	}
	else
	{
		print_exit();
		exit(data()->exit_state);
	}
	return (data()->exit_state);
}
