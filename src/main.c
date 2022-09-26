/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:36:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/09/26 18:21:33 by rkedida          ###   ########.fr       */
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

t_env_list	*ft_getenv_list(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = data()->env_list;
	while (tmp_env != NULL)
	{
		if ((strcmp(name, tmp_env->name)) == 0)
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*ft_getenv(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = ft_getenv_list(name);
	if (tmp_env)
		return (tmp_env->value);
	return (NULL);
}

char	*field_split(char *str)
{
	char	*split;

	split = NULL;
	while (*str)
	{
		if (!check_spaces(*str))
		{
			split = ft_append_char(split, *str);
			if (check_spaces(*(str + 1)))
				split = ft_append_char(split, SPACE);
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
				stripped = ft_append_char(stripped, *quoted);
			quoted++;
		}
		token->value = stripped;
		token = token->next;
	}
	return (true);
}

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

int	print_err(char *format, char *s1, char *s2, char *s3)
{
	int	init_stdout;
	int	res;

	init_stdout = dup(STDOUT_FILENO);
	res = dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(format, s1, s2, s3);
	dup2(STDOUT_FILENO, init_stdout);
	return (0);
}

int	err_handle(int error_code, char *prog, char *error_input)
{
	char	*err[7];

	err[0] = "missing ]";
	err[1] = "command not found";
	err[2] = "not an valid identifier";
	err[3] = "no such file or directory";
	err[4] = "syntax error near unexpected token";
	err[5] = "syntax error near unexpected token 'newline'";
	err[6] = "syntax error near unexpected token";
	if (error_code == 0)
		print_err("minishell: %s: %s: %s\n", prog, error_input, err[0]);
	if (error_code == 1)
		print_err("minishell: %s: %s: %s\n", prog, error_input, err[1]);
	if (error_code == 2)
		print_err("minishell: %s: %s: %s\n", prog, error_input, err[2]);
	if (error_code == 3)
		print_err("minishell: %s: %s: %s\n", prog, error_input, err[3]);
	if (error_code == 4 || error_code == 6)
		print_err("minishell: %s: %s: `%s'\n", prog, err[4], error_input);
	if (error_code == 5)
		print_err("minishell:%s %s: %s\n", prog, "", error_input);
	return (error_code);
}

static int	check_syntax_helper(void)
{
	int		args;
	t_token	*token;

	args = 0;
	token = data()->tokens;
	while (token && ++args)
	{
		if ((args == 1 && token->type != WORD && !is_redir(token))
			|| (args == 1 && !token->next && token->type != WORD))
		{
			token->error = true;
			return (err_handle(6, "", token->value));
		}
		else if (token->type == PIPE && token->next
			&& token->next->type == PIPE)
			return (err_handle(6, "", token->value));
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
		if (is_redir(token) && token->next && token->next->type != REDIR)
		{
			token->error = true;
			return (err_handle(6, "", token->value));
		}
		else if ((is_redir(token) && token->next && is_redir(token->next)))
		{
			token->error = true;
			return (err_handle(4, "", token->value));
		}
		token = token->next;
	}
	return (0);
}


int	lexer(char *user_input)
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
		return (-1);
	tokenize(line, token);
	param_expand();
	strip_quotes();
	tokenize_operators();
	del_empty_tokens();
	return (check_syntax());
}

//////////////////////////parsing////////////////////////////////////

bool	is_io_modifier(int type)
{
	if (type == LESS || type == DLESS
		|| type == GREAT || type == DGREAT)
		return (true);
	return (false);
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

char	*heredoc_expand(char *line)
{
	char	*var;
	int		var_pos;

	var = ft_strchr(line, DOLLAR);
	if (!var)
		return (line);
	var_pos = var - line;
	free(line);
	line = expand_single(line, var_pos, var, false);
	line = ft_strndup(line, ft_strlen(line));
	return (line);
}

int	read_heredocs(char	*dlmtr)
{
	int			fd;
	char		*line;
	char		*heredoc;

	line = NULL;
	g_data.n_heredocs++;
	heredoc = ft_strjoin("heredoc", ft_itoa(g_data.n_heredocs));
	fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	g_data.state = 2;
	line = readline("> ");
	if (g_data.state == 0 && close(fd) != 99)
		return (-1);
	while (line && strcmp(line, dlmtr))
	{
		line = heredoc_expand(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	fd = open(heredoc, O_RDONLY);
	return (fd);
}

int	add_infiles(t_infiles **infile, char *file, int mode)
{
	while (*infile != NULL)
		infile = &(*infile)->next;
	*infile = malloc(sizeof(t_infiles));
	if (*infile == NULL)
		return (2);
	if (mode == LESS)
	{
		(*infile)->value = open(file, O_RDONLY);
		if ((*infile)->value == -1)
		{
			err_handle(3, "", file);
			return (3);
		}
		(*infile)->dlmtr = NULL;
	}
	else if (mode == DLESS)
		(*infile)->value = read_heredocs(file);
	(*infile)->next = NULL;
	return (0);
}

int	add_outfiles(t_outfiles **outfile, char *file, int mode)
{
	while (*outfile != NULL)
		outfile = &(*outfile)->next;
	*outfile = malloc(sizeof(t_outfiles));
	if (*outfile == NULL)
		return (2);
	if (mode == GREATER)
		(*outfile)->value = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (mode == DGREAT)
		(*outfile)->value = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	(*outfile)->next = NULL;
	return (0);
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