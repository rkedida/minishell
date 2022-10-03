/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:13:07 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/03 16:35:41 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #include <unistd.h>

# include "minishell.h"

struct s_env_list;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}				t_args;

typedef struct s_infiles
{
	int					value;
	char				*dlmtr;
	struct s_infiles	*next;
}				t_infiles;

typedef struct s_outfiles
{
	int					value;
	struct s_outfiles	*next;
}				t_outfiles;

typedef struct s_heredocs
{
	int					value;
	struct s_heredocs	*next;
}				t_heredocs;

typedef struct s_simple_cmd
{
	char				*cmd;
	t_args				*args;
	t_infiles			*infile;
	t_outfiles			*outfile;
	t_heredocs			*heredocs;
	bool				error;
	struct s_simple_cmd	*next;
}				t_simple_cmd;

struct s_token;
// functions in heredoc.c

char	*heredoc_expand(char *line);
int	read_heredocs(char	*dlmtr);
int	add_infiles(t_infiles **infile, char *file, int mode);
int	add_outfiles(t_outfiles **outfile, char *file, int mode);

// functions in parser.c

bool	is_io_modifier(int type);
int	init_cmd_struct(t_simple_cmd **simple_cmd);
int	add_args(t_args **args, char *value);
int	parse_redir(t_simple_cmd *cmd, t_token *token);
int	parse(void);

#endif