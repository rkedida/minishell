/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:36:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/09/24 23:30:07 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_qoutes(char *str, char opening_quote, int i)
// {	
// 	while (str[i])
// 	{
// 		if (str[i] == opening_quote)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


// void	qoutes_check(char *line)
// {
// 	int	i;
// 	int	quote_opened;

// 	i = 0;
// 	quote_opened = 0;
// 	while (line[i])
// 	{
// 		if (line[i] && line[i] == '\'')
// 		{
// 			i++;
// 			if (check_qoutes(line, '\'', i) == 0 && quote_opened)
// 			{
// 				printf("minishell : : command not found\n");
// 				break ;
// 			}
// 			quote_opened = 1;
// 		}
// 		if (line[i] && line[i] == '\"')
// 		{
// 			i++;
// 			if (check_qoutes(line, '\"', i) == 0 && quote_opened)
// 			{
// 				printf("minishell : : command not found\n");
// 				break ;
// 			}
// 			quote_opened = 1;
// 		}
// 		i++;
// 	}
// }

// // write a function for creating nodes

// // write a function for splitting a line into nodes

// // void	split_line(char *line)
// // {
// // 	t_cmd	*node;
// // 	char	*tmp;
// // 	int		i;

// // 	i = 0;
// // 	while (line[i])
// // 	{
// // 		tmp = ft_strcpyt(line, ' ');
// // 		node = create_node(tmp);
// // 		i++;
// // 	}
// // }

// char *parsing(char *line)
// {
// 	char	**tmp;
// 	char	*str;
// 	int		i;
// 	int		counter;

// 	i = 0;
// 	while (line && line[i] != '\0')
// 	{
// 		tmp = ft_split(line, ' ');
// 		str = ft_strdup(tmp[0]);
// 		i++;
// 	}
// 	printf("%s\n", str);
// 	return (str);
// }

// //  write a function for creating nodes

// t_cmd	*create_nodes(char *line)
// {
// 	t_cmd	*node;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	node = malloc(sizeof(t_cmd));
// 	if (!node)
// 		return (NULL);
// 	// while (node->next != NULL)
// 	// 	node = node->next;
// 	if (!node->cmd)
// 	{
// 		node->cmd = line;
// 		node->next = NULL;
// 	}
// 	while (node->cmd->next != NULL)
// 		node = node->next;
// 	return (node);
// }

// void	prompt(int ac, char **av, char **envp)
// {
// 	// int		i;
// 	char	*line;
// 	char	*string;
// 	t_cmd	*cmd_node;

// 	line = NULL;
// 	// i = 1;
// 	while (true)
// 	{
// 		line = readline("BALU > ");
// 		if (ft_strlen(line) > 0)
// 			add_history(line);
// 		qoutes_check(line);
// 		// printf("%s\n", line);
// 		string = parsing(line);
// 		cmd_node = create_nodes(string);
// 		// printf("cmd_node = %s\n", cmd_node->cmd);
// 		printf("cmd_node->cmd = %s\n", cmd_node->cmd);
// 		cmd_node = cmd_node->next;
		

// 		if (strcmp(line, ";") == 0)
// 		{
// 			printf("fuck you\n");
// 			break ;
// 		}
// 		// parsing(ac, av, envp);
// 		if (strcmp(line, "exit") == 0)
// 			break ;
// 	}
// }

// // int main(void)
// int main(int ac, char **av, char **envp)
// {
// 	char *tab;

// 	prompt(ac, av, envp);
// 	clear_history();
// 	// rl_on_new_line()
// 	return (0);
// }

#include <string.h>
#include <stdlib.h>
#include "minishell.h"

void	print_token(t_token *token)
{
	t_token *tmp = token;
	int		i;

	i = 0;
	while (tmp != NULL)
	{
		printf("[%d] : [%s] -> ", i++, tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

t_token	*init(t_token *token)
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
	before_mid = ft_strjoin(before, var);
	var = ft_strjoin(before_mid, var);
	return (var);
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
		if (var && (paramlen(var + 1) != 0 || *(var + 1) == QMARK))
		{
			exp = expand_single(token->value, var_pos, var, token->split);
			token->value = exp;
		}
		if (!ft_strchr(token->value, DOLLAR) || paramlen(ft_strchr(token->value, DOLLAR) + 1) == 0)
			token = token->next;
	}
	replace_placeholders();
}

void	lexer(char *user_input)
{
	t_token	*token;
	char	*line;
	char	*quoted;

	token = init(token);
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
		return ;
	tokenize(line, token);
}

int main(int ac, char **argv)
{
	char	*line;
	t_token	*token;

	line = NULL;
	token = init(token);
	while (1)
	{
		line = readline("BALU > ");
		if (ft_strlen(line) > 0)
			add_history(line);
		// tokenize(line, token);
		lexer(line);
		if (data()->tokens)
			print_token(data()->tokens);
		if (strcmp(line, ";") == 0)
		{
			printf("fuck you\n");
			break ;
		}
	}
	return 0;
}