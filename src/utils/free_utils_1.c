/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:20:08 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 18:20:52 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env_list *env_list)
{
	t_env_list	*prev;

	if (!env_list)
		return ;
	prev = env_list;
	env_list = env_list->next;
	while (env_list)
	{
		free(prev->value);
		free(prev->name);
		free(prev);
		prev = env_list;
		env_list = env_list->next;
	}
	free(prev->value);
	free(prev->name);
	free(prev);
}