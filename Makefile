# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 12:38:50 by rkedida           #+#    #+#              #
#    Updated: 2022/08/12 21:42:26 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CFLAGS				=
HEADERS				= -I ./includes
OBJ_DIR				= ./obj/
LIBFT				= ./libft/libft.a

SRC_DIR				= ./src/
SRCS_FILES			= main.c
SRC					= $(addprefix $(SRC_DIR), $(SRCS_FILES))

OBJS_FILES			= $(addprefix $(OBJ_DIR), $(SRCS_FILES))
OBJS	 			= $(OBJS_FILES:.c=.o)

BOLD	= \033[1m
BLACK	= \033[30;1m
RED	= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# //= Recipes =//

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(OBJ_DIR)%.o : $(BONUS_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJS)
	@make -C ./libft --silent
	@$(CC) -lreadline $(HEADERS) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

norm: 
	@norminette

git:
	git add .
	git commit -m "Update"
	git push

clean:
	@make clean -C ./libft --silent
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C ./libft --silent
	@rm -f $(NAME)
	@rm -f $(BONUS)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft