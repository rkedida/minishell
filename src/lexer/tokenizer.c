/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:08:10 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 22:50:20 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_state(char line)
{
	int	*state;

	state = &data()->state;
	if (line == DQUOTE && *state == DQUOTE)
			*state = 0;
	else if (line == DQUOTE && *state == 0)
			*state = DQUOTE;
	if (line == SQUOTE && *state == SQUOTE)
			*state = 0;
	else if (line == SQUOTE && *state == 0)
		*state = SQUOTE;
	return (*state);
}

bool	check_spaces(char c)
{
	if (c == SPACE || c == TAB || c == NEWLINE)
		return (true);
	return (false);
}

bool check_operators(char c)
{
	if (c == LESS || c == GREATER || c == PIPE)
		return (true);
	return (false);
}

bool shall_split(char *line, char *token_value, int state)
{
	char	char_next;

	char_next = *(line + 1);
	if (char_next == '\0')
		return (true);
	if (check_spaces(char_next) && state == 0)
		return (true);
	if (!check_operators(*line) && check_operators(char_next) && state == 0)
		return (true);
	if (*line == PIPE && *(line + 1) == PIPE)
		return (true);
	if (check_operators(*line) && !check_operators(char_next) && state == 0)
		return (true);
	if ((check_operators(*line) && (char_next != *token_value
			|| ft_strlen(token_value) > 1)) && state == 0)
		return (true);
	return (false);
}

void	tokenize(char *line, t_token *token)
{
	int state;
	char *token_value;

	state = 0;
	token_value = NULL;
	while (*line)
	{
		state = set_state(*line);
		printf("char is: %c\n", *line);
		if (*line == '$' && state == SQUOTE)
			*line = PLACEHOLDER;
		if (!check_spaces(*line) || state != 0)
		{
			token_value = append_char_to_token(token_value, *line);
			if (shall_split(line, token_value, state))
			{
				token = save_token(line, token_value, state);
				token_value = NULL;
			}
		}
		// print_token(token);
		line++;
	}
	// return (check_syntax());
}
