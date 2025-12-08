# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2025/10/18 23:12:26 by rmedeiro         ###   ########.fr        #
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
	execution/prepare_child.c \
	execution/child_process.c \
	execution/external_cmds.c \
	execution/execute_single.c \
	utils/errors.c \
	utils/pipe_utils.c \
	utils/close_utils.c \
	utils/split_quotes.c \
	utils/clean_utils.c \
	builtin/ft_echo.c \
	builtin/ft_pwd.c \
	builtin/ft_env.c \
	builtin/ft_cd.c \
	builtin/ft_unset.c \
	builtin/ft_exit.c \
	builtin/export/ft_export.c \
	builtin/export/export_array.c \
	builtin/export/export_utils.c \
	builtin/export/sort_export.c \
	parsing/aux_funcs.c \
	signals/signals.c \
	parsing/parse.c \
	parsing/init_fill_mini.c \
	parsing/redir.c \
	parsing/split_ignore_quotes.c \
	parsing/validate_input.c \
	parsing/utils.c \
	parsing/fill_subcmd.c \
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
