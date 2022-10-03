/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:00 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 11:45:13 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_flag(char *arg, char *flag)
{
	bool	is_flag;
	int		flaglen;

	flaglen = ft_strlen(flag);
	is_flag = false;
	if (ft_strncmp(arg, flag, flaglen) == 0)
	{
		is_flag = true;
		while (arg[flaglen])
		{
			if (arg[flaglen] != flag[1])
				is_flag = false;
			flaglen++;
		}
	}
	return (is_flag);
}

void	echo_print(bool n_flag, char **argv)
{
	while (*argv)
	{
		printf("%s", *argv);
		argv++;
		if (*argv)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}

int	ft_echo(int argc, char **argv)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	while (argv[i] && check_flag(argv[i], "-n"))
		i++;
	if (i > 1)
		n_flag = true;
	echo_print(n_flag, &(argv[i]));
	return (0);
}
