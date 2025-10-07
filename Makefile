# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2025/10/07 19:30:32 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a

SRC_FILES = \
	main.c execution/execution.c execution/redirection.c \
	execution/multiple_cmds.c execution/heredoc.c execution/builtin.c execution/cmd_path.c \
	execution/child_process.c execution/execute_cmds.c utils/errors.c utils/pipe_utils.c \
	utils/split_quotes.c builtin/ft_echo.c builtin/ft_pwd.c builtin/ft_env.c execution/execute_single.c \
	parsing/parse.c parsing/pipeline_build.c parsing/redir.c parsing/split_ignore_quotes.c \
	parsing/cmd_build.c parsing/validate_input.c parsing/utils.c \
	envyan/envyan_init.c envyan/envyan_to_array.c envyan/envyan_utils.c envyan/set_envyan.c \
	envyan/handle_shlvl.c builtin/cd/cd_cases.c builtin/cd/cd_utils.c builtin/cd/ft_cd.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -lreadline -lhistory -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re