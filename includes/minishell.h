/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:36:04 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 19:55:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include "../libft/includes/libft.h"
#include "env.h"
#include "lexical_analyzer.h"
#include "parser.h"
#include "execution.h"

struct s_args;
struct s_token;
struct s_infiles;
struct s_outfiles;
struct s_heredocs;
struct s_simple_cmd;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	bool				is_env;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_data
{
	t_simple_cmd	*cmds;
	t_token		*tokens;
	t_env_list	*env_list;
	char		**envp;
	int			state;
	int			exit_state;
	int			n_heredocs;
	
}				t_data;

char		*ft_getenv(char *name);
t_data		*data(void);
t_env_list	*ft_getenv_list(char *name);

#endif