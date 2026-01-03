# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mustafa <mustafa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#              #
#    Updated: 2026/01/03 23:57:21 by mustafa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

NAME        = pipex
BONUS_NAME  = pipex_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I. -I./libft

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = main.c \
              pipex_utils/process.c \
              pipex_utils/file_operations.c \
              pipex_utils/command_parsing.c \
              pipex_utils/error_handling.c \
              pipex_utils/utils.c

BONUS_SRCS  = bonus/main_bonus.c \
              pipex_utils/process.c \
              pipex_utils/file_operations.c \
              pipex_utils/command_parsing.c \
              pipex_utils/error_handling.c \
              pipex_utils/utils.c \
              bonus/process_bonus.c \
              bonus/file_operations_bonus.c \
              get_next_line/get_next_line.c \
              get_next_line/get_next_line_utils.c

OBJS        = $(SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re