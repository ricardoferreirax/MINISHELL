# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 16:26:27 by pfreire-          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/09/16 17:08:19 by pfreire-         ###   ########.fr        #
=======
#    Updated: 2025/09/16 11:32:03 by pfreire-         ###   ########.fr        #
>>>>>>> ricardo
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
<<<<<<< HEAD
NFLAGS = -Wall -Werror -Wextra -g 
=======
NFLAGS = -Wall -Werror -Wextra -g
>>>>>>> ricardo
SRC_FILES =	test_main.c \
			parsing/aux_funcs.c
OBJS = $(SRC_FILES:.c=.o)
LIBFT = libft/libft.a


all: $(NAME) 

<<<<<<< HEAD
$(NAME):$(OBJS) $(LIBFT) 
	@$(CC) -g $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)
=======
$(NAME):$(OBJS) $(LIBFT) $(MLX)
	@$(CC) -g $(OBJS) $(LIBFT) -o $(NAME)
>>>>>>> ricardo

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
