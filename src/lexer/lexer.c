/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:07:05 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/03 15:16:18 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_t_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	token->value = NULL;
	token->type = 0;
	token->next = NULL;
	token->split = false;
	token->error = false;
	token->expansion = false;
	return (token);
}

bool	quotes_matched(char *line)
{
	char *pipe;

	pipe = ft_strchr(line, PIPE);
	data()->state = 0;
	while (*line)
	{
		set_state(*line);
		line++;
	}
	if (set_state(*line) != 0 || (pipe && *(pipe + 1) == '\0' && ft_strlen(line) > 1))
		return (false);
	else
		return (true);
}

int	strip_quotes(void)
{
	char	*stripped;
	int		state;
	t_token	*token;
	char	*quoted;

	token = data()->tokens;
	data()->state = 0;
	while (token)
	{
		stripped = NULL;
		quoted = token->value;
		if (strcmp(quoted, "\"\"") == 0)
			quoted = " ";
		while (quoted && *quoted)
		{
			state = set_state(*quoted);
			if ((*quoted != SQUOTE && *quoted != DQUOTE)
				|| (state != *quoted && state != 0))
				stripped = append_char_to_token(stripped, *quoted);
			quoted++;
		}
		token->value = stripped;
		token = token->next;
	}
	return (true);
}

void	del_empty_tokens(void)
{
	t_token	*token;
	t_token	*next_token;

	token = data()->tokens;
	while (token)
	{
		next_token = token->next;
		if (next_token && next_token->value == NULL)
			token->next = next_token->next;
		else
			token = token->next;
	}
}

void	print_token(t_token *token);

int	lexer(char *user_input)
{
	t_token	*token;
	char	*line;
	char	*quoted;

	token = NULL;
	token = init_t_token(token);
	line = ft_strdup(user_input);
	data()->state = 0;
	line = ft_strtrim(line, "\n\t ");
	while (!quotes_matched(line))
	{
		quoted = readline("> ");
		if (quoted)
			line = ft_strjoin(line, quoted);
		else
			break ;
		free(quoted);
	}
	if (!*line)
		return (-1);
	tokenize(line, token);
	// print_token(data()->tokens);
	param_expand();
	strip_quotes();
	tokenize_operators();
	del_empty_tokens();
	return (check_syntax());
}
