# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 12:38:50 by rkedida           #+#    #+#              #
#    Updated: 2022/10/02 19:55:02 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SOURCES 	= $(shell find ./src -name "*.c")
HEADERS 	= $(shell find ./includes -name "*.h")

LIBFT		= ./libft/libft.a

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
# DEPENDS 	= $(patsubst %.c, %.d, $(SOURCES))

CFLAGS 		= -g
RLFLAGS 	= -lreadline

all: $(NAME)

%.o: %.c
# @$(CC) -Iincludes $(CFLAGS) -MMD -MP -c $< -o $@
	@$(CC) -Iincludes $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJECTS)
	@make -C ./libft --silent
	@echo "Dependencies Compiled !"
	@$(CC) $(CFLAGS) $(RLFLAGS) $(LIBFT) -Iincludes $(OBJECTS) -o $(NAME)
	@echo "Compiled !"

clean:
	@make fclean -C ./libft --silent
	-@$(RM) $(OBJECTS) $(DEPENDS)
	-@$(RM) $(OBJECTS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@$(RM) $(NAME)

test:
	@$(shell ./esh_tester.sh)

git:
	@git add .
	-@git commit -m "Update!"
	@git push
	@echo "Commited!"

run: all
	./$(NAME)

re: clean all

.PHONY: re run fclean clean all

# -include $(DEPENDS)