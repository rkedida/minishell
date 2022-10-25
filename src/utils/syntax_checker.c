/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:36:48 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 18:53:03 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(t_token *token)
{
	if (!token)
		return (NULL);
	token = token->next;
	while (token && token->type == SPACE)
		token = token->next;
	return (token);
}

int	check_syntax_helper2(t_token *token, int mod)
{
	token->error = true;
	token->err_code = 5;
	dprintf(STDERR_FILENO, "minishell: syntax error near token `newline'\n");
	data()->exit_state = 258;
	if (mod == 1)
		return (data()->exit_state);
	else if (mod == 2)
		return (err_handle(4, "", token->value));
	else
	{
		token->err_code = 4;
		return (err_handle(4, "", ft_strjoin2(token->value, ": ", 0)));
	}
}

static int	check_syntax_helper(void)
{
	int		args;
	t_token	*token;

	args = 0;
	token = data()->tokens;
	while (token && ++args)
	{
		if (args == 1 && (token->type == LESS || token->type == GREATER
				|| token->type == GREATER_GREATER || token->type == LESS_LESS))
			return (check_syntax_helper2(token, 1));
		if ((args == 1 && token->type != WORD && token->type != SPACE
				&& !is_redir(token)) || (args == 1 && !token->next
				&& token->type != WORD))
			return (check_syntax_helper2(token, 2));
		else if (token->type == PIPE && get_next_token(token)
			&& get_next_token(token)->type == PIPE)
			return (check_syntax_helper2(token, 3));
		token = token->next;
	}
	return (0);
}

int	check_syntax(void)
{
	t_token	*token;

	token = data()->tokens;
	check_syntax_helper();
	while (token)
	{
		if (is_redir(token) && get_next_token(token)
			&& get_next_token(token)->type != REDIR)
		{
			token->error = true;
			token->err_code = 6;
			return (err_handle(6, "", ft_strjoin2(token->value, "", 0)));
		}
		else if ((is_redir(token) && get_next_token(token)
				&& is_redir(get_next_token(token))))
		{
			token->error = true;
			token->err_code = 4;
			return (err_handle(4, "", ft_strjoin2(token->value, ": ", 0)));
		}
		token = token->next;
	}
	return (0);
}
