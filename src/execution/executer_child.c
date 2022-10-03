/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:37:53 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 12:45:35 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exit(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(130);
}

int	exec_builtin(t_simple_cmd *simple_cmd)
{
	int		res;
	int		argc;
	char	**argv;
	char	**env;

	res = 0;
	argv = NULL;
	env = env_to_arr();
	argc = init_args(simple_cmd, &argv);
	if (strcmp(argv[0], "cd") == 0)
		res = ft_cd(argc, argv, env);
	else if (strcmp(argv[0], "echo") == 0)
		res = ft_echo(argc, argv);
	else if (strcmp(argv[0], "env") == 0 && (ft_getenv("PATH")
			|| !err_handle(1, "", argv[0])))
		res = ft_env(argc, argv, env);
	else if (strcmp(argv[0], "export") == 0)
		res = ft_export(argc, argv, env);
	else if (strcmp(argv[0], "unset") == 0)
		res = ft_unset(argc, argv, env);
	else if (strcmp(argv[0], "pwd") == 0)
		res = ft_pwd();
	else if (strcmp(argv[0], "exit") == 0)
		res = ft_exit(argc, argv);
	return (res);
}

void	free_dp(char **i)
{
	while (*i)
	{
		free(*i);
		*i = NULL;
		i++;
	}
}

int	child_process(t_simple_cmd *simple_cmd)
{
	char	**path;
	char	**args;
	int		argc;
	int		res;
	char	**env;

	res = 0;
	args = NULL;
	env = env_to_arr();
	signal(SIGINT, child_exit);
	if (!check_cmds(simple_cmd->cmd))
	{
		err_handle(1, "", simple_cmd->cmd);
		exit (127);
	}
	path = ft_getpath(simple_cmd->cmd);
	argc = init_args(simple_cmd, &args);
	while (execve(*path, args, env) && *path)
		path++;
	free_dp(path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (res);
}
