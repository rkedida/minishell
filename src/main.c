/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:36:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/01 20:22:39 by rkedida          ###   ########.fr       */
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
	token = NULL;
}



//////////////////////////parsing////////////////////////////////////













//////////////////// printer //////////////////////////

// // printer for infiles

void	print_infiles(t_infiles *infile)
{
	while (infile != NULL)
	{
		printf("infile: %d ", infile->value);
		infile = infile->next;
	}
}

// printer for outfiles

void	print_outfiles(t_outfiles *outfile)
{
	while (outfile != NULL)
	{
		printf("outfile: %d\n", outfile->value);
		outfile = outfile->next;
	}
}

// printer for simple_cmd

void	print_simple_cmd(t_simple_cmd *simple_cmd)
{
	int	i;

	while (simple_cmd != NULL)
	{
		printf("cmd: %s ", simple_cmd->cmd);
		i = 0;
		while (simple_cmd->args != NULL)
		{
			printf("args[%d]: %s\n", i, simple_cmd->args->value);
			i++;
			simple_cmd->args = simple_cmd->args->next;
		}
		print_infiles(simple_cmd->infile);
		print_outfiles(simple_cmd->outfile);
		simple_cmd = simple_cmd->next;
	}
}

// printer for cmds

void	print_cmds(void)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = data()->cmds;
	print_simple_cmd(simple_cmd);
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
		parse();
		// if (data()->tokens)
			// print_token(data()->tokens);
		if (strcmp(line, ";") == 0)
		{
			printf("fuck you\n");
			break ;
		}
	}
	return 0;
}