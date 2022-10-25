/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:37:53 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 05:43:16 by kfergani         ###   ########.fr       */
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
	env = env_to_arr();
	argc = init_args(simple_cmd, &argv, 0);
	if (ft_strcmp(argv[0], "cd") == 0)
		res = ft_cd(argc, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		res = ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		res = ft_env(argc);
	else if (ft_strcmp(argv[0], "export") == 0)
		res = ft_export(argc, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		res = ft_unset(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		res = ft_pwd();
	else if (ft_strcmp(argv[0], "exit") == 0)
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

void	handel_child_error(t_simple_cmd *cmd, char **path, char **env, int res)
{
	if (res)
	{
		if (res == 1)
			err_handle(8, *path, "");
		else
			err_handle(1, "", ft_strjoin2(cmd->cmd, ": ", 0));
		free_dp(path);
		free_dp(env);
		exit (127);
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
	res = check_cmds(simple_cmd->cmd);
	path = ft_getpath(simple_cmd->cmd);
	handel_child_error(simple_cmd, path, env, res);
	argc = init_args(simple_cmd, &args, 1);
	while (execve(*path, args, env) && *path)
		path++;
	free_dp(path);
	free_dp(env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit (res);
}
