# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/10/15 14:55:09 by pfreire-         ###   ########.fr        #
=======
#    Updated: 2025/10/16 15:43:10 by rmedeiro         ###   ########.fr        #
>>>>>>> ricardo
#                                                                              #
# **************************************************************************** #

NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a

SRC_FILES = \
	main.c \
	execution/execution.c \
	execution/redirection.c \
	execution/multiple_cmds.c \
	execution/heredoc.c \
	execution/builtin.c \
	execution/cmd_path.c \
	execution/child_process.c \
	execution/execute_cmds.c \
	execution/execute_single.c \
	utils/errors.c \
	utils/pipe_utils.c \
	utils/split_quotes.c \
	utils/clean_utils.c \
	builtin/ft_echo.c \
	builtin/ft_pwd.c \
	builtin/ft_env.c \
	builtin/ft_cd.c \
	builtin/ft_unset.c \
	builtin/export/ft_export.c \
	builtin/export/export_array.c \
	builtin/export/export_utils.c \
	builtin/export/sort_export.c \
<<<<<<< HEAD
	parsing/aux_funcs.c \
=======
	signals/signals.c \
>>>>>>> ricardo
	parsing/parse.c \
	parsing/pipeline_build.c \
	parsing/redir.c \
	parsing/split_ignore_quotes.c \
	parsing/cmd_build.c \
	parsing/validate_input.c \
	parsing/utils.c \
	envyan/envyan_init.c \
	envyan/envyan_array.c \
	envyan/envyan_utils.c \
	envyan/envyan_clean.c \
	envyan/set_envyan.c \
	shlvl/handle_shlvl.c \

OBJ_DIR   = objs
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -lreadline -lhistory -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
e: all clean
	clear
.PHONY: all clean fclean re