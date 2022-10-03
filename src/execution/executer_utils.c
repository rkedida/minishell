/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:36:32 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 12:51:20 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_args(t_simple_cmd *simple_cmd, char ***p_arg_array)
{
	int		i;
	int		len;
	t_args	*args;
	char	**arg_array;

	i = 0;
	len = 0;
	args = simple_cmd->args;
	while (args && ++len)
		args = args->next;
	*p_arg_array = malloc(sizeof(char *) * (len + 1));
	if (*p_arg_array == NULL)
		return (4);
	arg_array = *p_arg_array;
	arg_array[len] = NULL;
	args = simple_cmd->args;
	while (i < len)
	{
		arg_array[i] = args->value;
		args = args->next;
		i++;
	}
	return (len);
}

char	**ft_getpath(char *cmd)
{
	int		i;
	char	*keypair;
	char	**path;

	i = 0;
	keypair = NULL;
	path = ft_split(ft_getenv("PATH"), ':');
	i = 0;
	if (path == NULL || access(cmd, F_OK | X_OK) == 0)
	{
		path = malloc(sizeof(char *) * 2);
		path[0] = cmd;
		path[1] = NULL;
	}
	else
	{
		while (path && path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], cmd);
			i++;
		}
	}
	return (path);
}

bool	is_builtin(char	*cmd)
{
	if (!strcmp(cmd, "cd") || !strcmp(cmd, "echo")
		|| !strcmp(cmd, "cd") || !strcmp(cmd, "env")
		|| !strcmp(cmd, "export") || !strcmp(cmd, "unset")
		|| !strcmp(cmd, "pwd") || !strcmp(cmd, "export")
		|| !strcmp(cmd, "exit"))
		return (true);
	return (false);
}

bool	check_cmds(char	*cmd)
{
	int		i;
	bool	res;
	char	**path;

	i = 0;
	res = false;
	path = ft_getpath(cmd);
	while (path && path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
			res = true;
		i++;
	}
	if (is_builtin(cmd))
		res = false;
	if (path != NULL)
		free_dp(path);
	return (res);
}
