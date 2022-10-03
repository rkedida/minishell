/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:36:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/03 19:34:36 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

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

// #include <string.h>
// #include <stdlib.h>

// #include "minishell.h"

//////////////////////////parsing////////////////////////////////////

//////////////////// printer //////////////////////////


// // function to free nodes

// void	free_nodes(t_token *token)
// {
// 	t_token *tmp;

// 	while (token != NULL)
// 	{
// 		tmp = token;
// 		token = token->next;
// 		free(tmp);
// 	}
// }

// int main(int ac, char **argv)
// {
// 	char	*line;
// 	t_token	*token;

// 	line = NULL;
// 	token = init_t_token(token);
// 	while (1)
// 	{
// 		line = readline("BALU > ");
// 		if (ft_strlen(line) > 0)
// 			add_history(line);
// 		// tokenize(line, token);
// 		lexer(line);
// 		parse();
// 		print_token(data()->tokens);
		
// 		if (strcmp(line, ";") == 0)
// 		{
// 			printf("fuck you\n");
// 			break ;
// 		}
// 	}
// 	return 0;
// }

#include "../includes/minishell.h"

char	*prompt(void)
{
	char	*line;
	char	*prompt;
	char	*cwd;
	char	*last;

	line = NULL;
	prompt = "$ ";
	cwd = getcwd(NULL, 0);
	last = ft_strrchr(cwd, '/');
	last++;
	prompt = ft_strjoin(last, prompt);
	free(cwd);
	line = readline(prompt);
	return (line);
}

int	end_session(void)
{
	// change_ctrlc_sym(true);
	// mem_free_all();
	// rl_clear_history();
	printf("exit\n");
	return (data()->exit_state);
}

int	refresh_session(int argc, char **argv, char *envp[])
{
	data()->envp = envp;
	data()->state = 0;
	data()->tokens = NULL;
	data()->cmds = NULL;
	data()->n_heredocs = 0;
	return (0);
}

int	init_session(int argc, char **argv, char *envp[])
{
	data()->exit_state = 0;
	// data()->malloc_count = 0;
	// data()->mem_alloced = NULL;
	// signal(SIGINT, sig_ctrlc);
	// signal(SIGQUIT, SIG_IGN);
	// change_ctrlc_sym(false);
	init_env(argc, argv, envp);
	return (0);
}

void print_ascii_art()
{
	printf("\033[32m");
	FILE *stream = fopen("src/ascii_header.txt", "r");
	if (stream)
	{
		char line[256];
		while (fgets(line, sizeof(line), stream))
			printf("%s", line);
		fclose(stream);
	}
	else
		printf("\033[31mError: ascii_art.txt not found\n");
	printf("\033[0m\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	line = NULL;
	// print_ascii_art();
	init_session(argc, argv, envp);
	while (true)
	{
		refresh_session(argc, argv, envp);
		line = prompt();
		if (line)
		{
			if (*line)
				add_history(line);
			if (lexer(line) != 6 && !parse())
				xecute();
			// print_cmds();
			// print_token(data()->tokens);
			data()->state = 0;
		}
		else
			break ;
		free(line);
	}
	return (end_session());
}