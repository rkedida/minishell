/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:49:03 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 20:04:25 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include <stdbool.h>

int		xecute(void);
void	init_fds(int fd[4]);
void	reset_fds(int fd[4]);
char	**ft_getpath(char *cmd);
bool	check_cmds(char	*cmd);
bool	is_builtin(char	*cmd);
int		add_env(char *name, char *value);
int		init_args(t_simple_cmd *simple_cmd, char ***arg_array);

/* ----- Inbuilts Commands */
int		ft_export(int argc, char *argv[], char **envp);
int		ft_env(int argc, char **argv, char **envp);
int		ft_unset(int argc, char *argv[], char **envp);
int		ft_cd(int argc, char **argv, char **envp);
int		ft_pwd(void);
// int		ft_unset(int argc, char *argv[], char *envp[]);
int		ft_echo(int argc, char **argv);
int		ft_exit(int argc, char **argv);
int		exec_builtin(t_simple_cmd *simple_cmd);
int		child_process(t_simple_cmd *simple_cmd);

int	is_valid_name(char *argv);
char	**env_to_arr(void);
int	init_env(int argc, char **argv, char **envp);
void	free_dp(char **i);


enum e_exec_STATE
{
	IDLE = 0,
	EXEC = 1,
	HEREDOC = 2,
};

enum e_FILE_DESCRIPTORS
{
	STDIN_INIT = 0,
	STDOUT_INIT = 1,
	IN = 2,
	OUT = 3,
};

#endif