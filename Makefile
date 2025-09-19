# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 16:26:27 by pfreire-          #+#    #+#              #
#    Updated: 2025/09/17 10:30:50 by pfreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -Wall -Werror -Wextra -g
SRC_FILES =
OBJS = $(SRC_FILES:.c=.o)
LIBFT = libft/libft.a


all: $(NAME) 

$(NAME):$(OBJS) $(LIBFT) 
	@$(CC) -g $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	
$(LIBFT):
	@$(MAKE) -C libft

clean:
	@rm -f $(OBJS)
	@make clean -C libft
fclean:clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

ra: re clean
	@rm -f $(OBJS)
	@make clean -C libft

e: all clean

.PHONY: all fclean clean re
