/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:27:43 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 03:51:04 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	paramlen(char *param)
{
	int	len;

	len = 0;
	if (param[len] == QMARK)
		return (1);
	if (param[len] != '_' && !ft_isalpha(param[len]))
		return (0);
	while (param[len] == '_' || ft_isalnum(param[len]))
		len++;
	return (len);
}

char	*expand_single(char *value, int var_pos, char *var)
{
	char	*before;
	char	*before_mid;
	char	*after;
	char	*tmp;
	int		len;

	len = paramlen(var + 1);
	var = ft_substr(var, 1, len, 0);
	if (*var == QMARK)
		tmp = ft_itoa(data()->exit_state);
	else
		tmp = ft_strdup(ft_getenv(var));
	free(var);
	var = tmp;
	before = ft_substr(value, 0, var_pos, 0);
	after = ft_substr(value, var_pos + len + 1,
			ft_strlen(value) - var_pos - len - 1, 0);
	before_mid = ft_strjoin_withnull(before, var, 1);
	var = ft_strjoin_withnull(before_mid, after, 1);
	free(after);
	return (var);
}

void	replace_placeholders(void)
{
	t_token	*token;

	token = data()->tokens;
	while (token)
	{
		if (token->type == TOKEN && ft_strchr(token->value, PLACEHOLDER))
			*(ft_strchr(token->value, PLACEHOLDER)) = DOLLAR;
		if (!ft_strchr(token->value, PLACEHOLDER))
			token = token->next;
	}
}

void	param_expand(void)
{
	t_token	*token;
	char	*exp;
	char	*var;
	int		var_pos;

	token = data()->tokens;
	while (token)
	{
		var = ft_strchr(token->value, DOLLAR);
		var_pos = ft_strchr_pos(token->value, DOLLAR);
		if (var && paramlen(var + 1) != 0 && token->expansion)
		{
			exp = expand_single(token->value, var_pos, var);
			free(token->value);
			token->value = exp;
		}
		if (!token->expansion || !ft_strchr(token->value, DOLLAR)
			|| paramlen(ft_strchr(token->value, DOLLAR) + 1) == 0)
			token = token->next;
	}
	tokenize_operators();
	del_empty_tokens();
	fusion();
}
