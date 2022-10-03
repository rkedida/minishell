/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:28 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 20:04:53 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing(char *name, char *value)
{
	t_env_list	*existing;

	existing = ft_getenv_list(name);
	if (existing && value)
	{
		existing->value = value;
		existing->is_env = true;
	}
}

int	add_env(char *name, char *value)
{
	t_env_list	*new;

	if (ft_getenv_list(name))
		update_existing(name, value);
	else
	{
		new = data()->env_list;
		while (new && new->next)
			new = new->next;
		new->next = malloc(sizeof(t_env_list));
		if (new->next == NULL)
			return (4);
		new = new->next;
		new->name = name;
		new->value = value;
		if (value)
			new->is_env = true;
		else
			new->is_env = false;
		new->next = NULL;
	}
	return (0);
}

static int	update_env(char *argv[])
{
	char		*assign;
	char		*name;
	char		*value;

	value = NULL;
	while (++argv && *argv)
	{
		if (**argv)
		{
			assign = ft_strchr(*argv, '=');
			if (assign)
			{
				name = ft_substr(*argv, 0, assign - *argv);
				value = ft_substr(*argv, ft_strlen(*argv)
						- ft_strlen(assign) + 1, ft_strlen(assign + 1));
			}
			else
				name = *argv;
			if (!is_valid_name(name))
				err_handle(2, "export", name);
			else
				add_env(name, value);
		}
	}
	return (0);
}

int	ft_export(int argc, char *argv[], char **envp)
{
	char	**env_arr;

	if (argc > 1)
	{
		update_env(argv);
		argv++;
		while (*argv)
		{
			if (!is_valid_name(*argv))
				return (1);
			argv++;
		}
	}		
	else
	{
		env_arr = env_to_arr();
		print_env_or_export("export", env_arr);
	}
	return (0);
}
