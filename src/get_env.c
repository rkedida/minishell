/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:10:09 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/01 18:10:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_getenv_list(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = data()->env_list;
	while (tmp_env != NULL)
	{
		if ((strcmp(name, tmp_env->name)) == 0)
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*ft_getenv(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = ft_getenv_list(name);
	if (tmp_env)
		return (tmp_env->value);
	return (NULL);
}
