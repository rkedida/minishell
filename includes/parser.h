/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:13:07 by rkedida           #+#    #+#             */
/*   Updated: 2022/09/26 18:14:55 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}			t_args;

typedef struct s_infiles
{
	int					value;
	char				*dlmtr;
	struct s_infiles	*next;
}			t_infiles;

typedef struct s_outfiles
{
	int					value;
	struct s_outfiles	*next;
}			t_outfiles;

typedef struct s_heredocs
{
	int					value;
	struct s_heredocs	*next;
}			t_heredocs;

typedef struct s_simple_cmd
{
	char				*cmd;
	t_args				*args;
	t_infiles			*infile;
	t_outfiles			*outfile;
	t_heredocs			*heredocs;
	bool				error;
	struct s_simple_cmd	*next;
}				t_simple_cmd;

#endif