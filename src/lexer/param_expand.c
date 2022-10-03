/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:27:43 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 22:47:05 by rkedida          ###   ########.fr       */
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

char	*field_split(char *str)
{
	char	*split;

	split = NULL;
	while (*str)
	{
		if (!check_spaces(*str))
		{
			split = append_char_to_token(split, *str);
			if (check_spaces(*(str + 1)))
				split = append_char_to_token(split, SPACE);
		}
		str++;
	}
	return (split);
}

char	*expand_single(char *value, int var_pos, char *var, bool split)
{
	char	*before;
	char	*before_mid;
	char	*after;
	char	*tmp;
	int		len;

	len = paramlen(var + 1);
	var = ft_substr(var, 1, len);
	if (*var == QMARK)
		tmp = ft_itoa(data()->exit_state);
	else
		tmp = ft_strdup(ft_getenv(var));
	if (tmp && split)
		tmp = field_split(tmp);
	var = tmp;
	before = ft_substr(value, 0, var_pos);
	after = ft_substr(value, var_pos + len + 1, ft_strlen(value) - var_pos - len - 1);
	before_mid = ft_strjoin_withnull(before, var);
	var = ft_strjoin_withnull(before_mid, var);
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
		// if (!var)
		// 	return (err_handle(1, "", token->value));
		// printf("var: %s	var %s\n", token->value, var);
		var_pos = ft_strchr_pos(token->value, DOLLAR);
		// if (!var_pos)
		// 	return (err_handle(1, "", token->value));
		if (var && (paramlen(var + 1) != 0 || *(var + 1) == QMARK))
		{
			exp = expand_single(token->value, var_pos, var, token->split);
			token->value = exp;
		}
		if (!ft_strchr(token->value, DOLLAR) || paramlen(ft_strchr(token->value, DOLLAR) + 1) == 0)
			token = token->next;
	}
	replace_placeholders();
	// return (check_syntax());
}
