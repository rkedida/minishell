/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:05:41 by rkedida           #+#    #+#             */
/*   Updated: 2022/09/24 22:22:08 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALZYER_H
# define LEXICAL_ANALZYER_H

# define RESET			y
# define NO_RESET		n
# define PLACEHOLDER	0x1D

#include "readline/readline.h"
#include "readline/history.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../libft/includes/libft.h"

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

// functions in tokenizer.c

int		set_state(char line);
bool	check_spaces(char c);
bool	check_operators(char c);
bool	shall_split(char *line, char *token_value, int state);
void	tokenize(char *line, t_token *token);

// functions in tokenizer_utils.c

char	*ft_append_char(char *line, char c);
t_token	*save_token(char *line, char *value, int state);


#endif