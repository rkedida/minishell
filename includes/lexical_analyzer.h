/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:05:41 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/03 16:20:03 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALZYER_H
# define LEXICAL_ANALZYER_H

# define RESET			y
# define NO_RESET		n
# define PLACEHOLDER	0x1D

// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #include <unistd.h>

# include "minishell.h"

typedef struct s_token
{
	char			*value;
	int				type;
	bool			split;
	bool			error;
	bool			expansion;
	struct s_token	*next;
}					t_token;

enum e_STN
{
	SPACE=' ',
	NEWLINE='\n',
	TAB='\t'
};

enum e_OPERATORS 
{
	PIPE='|',
	EQUAL='=',
	LESS='<',
	GREATER='>',
	LESS_LESS=20000,
	GREATER_GREATER=40000
};

enum e_grammer
{
	WORD=-1,
	REDIR=20200,
	QMARK='?'
};

enum e_TOKENS
{
	TOKEN=-2,
	OPERATOR=-3,
	REDIR_IO=-2,
	DQUOTE='\"',
	SQUOTE='\'',
	FLAG='-',
	ERROR=-9,
	DOLLAR='$'
};

enum e_state
{
	INSQUOTE,
	OUTSQUOTE,
	INDQUOTE,
	OUTDQUOTE
};

// functions in syntax_checker.c

int	print_err(char *format, char *s1, char *s2, char *s3);
int	err_handle(int error_code, char *prog, char *error_input);
int	check_syntax(void);

// functions in tokenize_operators.c

int	is_redir(t_token *token);
int	tokenize_operators(void);

// functions in param_expand.c

int		paramlen(char *param);
char	*field_split(char *str);
char	*expand_single(char *value, int var_pos, char *var, bool split);
void	replace_placeholders(void);
void	param_expand(void);

// functions in lexer.c

t_token	*init_t_token(t_token *token);
bool	quotes_matched(char *line);
int		strip_quotes(void);
void	del_empty_tokens(void);
int		lexer(char *user_input);

// functions in tokenizer.c

int		set_state(char line);
bool	check_spaces(char c);
bool	check_operators(char c);
bool	shall_split(char *line, char *token_value, int state);
void	tokenize(char *line, t_token *token);

// functions in tokenizer_utils.c

char	*append_char_to_token(char *line, char c);
t_token	*save_token(char *line, char *value, int state);


#endif