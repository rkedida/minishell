/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:42 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 20:01:10 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char *argv)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(argv[0]) || argv[0] == '_'))
		return (false);
	while (argv[i] != '\0')
	{
		if (!(ft_isalnum(argv[i]) || argv[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_unset(int argc, char *argv[], char **envp)
{
	t_env_list	*next;
	t_env_list	*tmp_env;
	int			i;

	i = 1;
	tmp_env = data()->env_list;
	while (argv[i])
	{
		if (!is_valid_name(argv[i]))
		{
			err_handle(2, "unset", argv[i]);
			data()->exit_state = 1;
		}
		if ((strcmp(argv[i], tmp_env->value) == 0))
			data()->env_list = tmp_env->next;
		while (tmp_env != NULL)
		{
			next = tmp_env->next;
			if (next != NULL && ((strcmp(argv[i], next->name)) == 0))
				tmp_env->next = next->next;
			tmp_env = tmp_env->next;
		}
		i++;
	}
	return (data()->exit_state);
}
