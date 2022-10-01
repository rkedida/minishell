/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:16:02 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/01 17:25:23 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_io_modifier(int type)
{
	if (type == LESS || type == LESS_LESS
		|| type == GREATER || type == GREATER_GREATER)
		return (true);
	return (false);
}

int	init_cmd_struct(t_simple_cmd **simple_cmd)
{
	*simple_cmd = malloc(sizeof(t_simple_cmd));
	if (*simple_cmd == NULL)
		return (2);
	(*simple_cmd)->cmd = NULL;
	(*simple_cmd)->args = NULL;
	(*simple_cmd)->next = NULL;
	(*simple_cmd)->infile = NULL;
	(*simple_cmd)->outfile = NULL;
	(*simple_cmd)->heredocs = NULL;
	(*simple_cmd)->error = false;
	return (0);
}

int	add_args(t_args **args, char *value)
{
	while (*args != NULL)
		args = &(*args)->next;
	*args = malloc(sizeof(t_args));
	if (*args == NULL)
		return (2);
	(*args)->value = value;
	(*args)->next = NULL;
	return (0);
}

int	parse_redir(t_simple_cmd *cmd, t_token *token)
{
	int	last_op;
	int	res;

	res = 0;
	last_op = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (is_io_modifier(token->type))
			last_op = token->type;
		if (token->type == REDIR)
		{
			if (last_op == LESS || last_op == LESS_LESS)
			{
				if (add_infiles(&(cmd->infile), token->value, last_op) != 0)
					token->error = true;
			}
			else if (last_op == GREATER || last_op == GREATER_GREATER)
				res = add_outfiles(&(cmd->outfile), token->value, last_op);
			last_op = 0;
		}
		token = token->next;
	}
	return (0);
}

int	parse(void)
{
	t_token			*token;
	t_simple_cmd	*simple_cmd;

	token = data()->tokens;
	init_cmd_struct(&(data()->cmds));
	simple_cmd = data()->cmds;
	while (token && !parse_redir(simple_cmd, token))
	{
		while (token && token->type != PIPE)
		{
			if (token->error)
				simple_cmd->error = true;
			if (token->type == WORD && simple_cmd->cmd == NULL)
				simple_cmd->cmd = token->value;
			if (token->type == WORD)
				add_args(&(simple_cmd->args), token->value);
			token = token->next;
		}
		if (!token)
			break ;
		init_cmd_struct(&(simple_cmd->next));
		simple_cmd = simple_cmd->next;
		token = token->next;
	}
	return (0);
}
