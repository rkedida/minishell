/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:31:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/01 14:31:43 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *token)
{
	int	type;

	if (token)
	{
		type = token->type;
		if (type == LESS || type == LESS_LESS || type == GREATER || type == GREATER_GREATER)
			return (true);
	}
	return (false);
}

int	tokenize_operators(void)
{
	t_token	*token;

	token = data()->tokens;
	while (token)
	{
		if (token && token->value && token->type == OPERATOR)
		{
			if (strcmp(token->value, "<") == 0)
				token->type = LESS;
			else if (strcmp(token->value, "<<") == 0)
				token->type = LESS_LESS;
			else if (strcmp(token->value, ">") == 0)
				token->type = GREATER;
			else if (strcmp(token->value, ">>") == 0)
				token->type = GREATER_GREATER;
			else if (strcmp(token->value, "|") == 0)
				token->type = PIPE;
			if (is_redir(token) && token->next && token->next->type == TOKEN)
				token->next->type = REDIR;
		}
		else if (token->type != REDIR)
			token->type = WORD;
		token = token->next;
	}
	return (0);
}
