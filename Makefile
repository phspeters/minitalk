# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 09:58:30 by pehenri2          #+#    #+#              #
#    Updated: 2023/12/04 18:48:20 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT				= client
SERVER				= server
CLIENT_BONUS		= clientbonus
SERVER_BONUS		= serverbonus
CFLAGS				= -Wextra -Wall -Werror -Wunreachable-code -g3 -fsanitize=address #-Ofast
LIBFT				= ./lib/libft
CC					= cc
HEADERS				= -I ./include -I $(LIBFT)
LIBS				= $(LIBFT)/libft.a
SRCS_PATH			= ./src/mandatory/
CLIENT_SRCS			= client.c
SERVER_SRCS			= server.c
CLIENT_OBJS			= $(addprefix $(SRCS_PATH),$(CLIENT_SRCS:%.c=%.o))
SERVER_OBJS			= $(addprefix $(SRCS_PATH),$(SERVER_SRCS:%.c=%.o))
BONUS_PATH			= ./src/bonus/
CLIENT_BONUS_SRCS	= client_bonus.c
SERVER_BONUS_SRCS	= server_bonus.c
CLIENT_BONUS_OBJS	= $(addprefix $(BONUS_PATH),$(CLIENT_BONUS_SRCS:%.c=%.o))
SERVER_BONUS_OBJS	= $(addprefix $(BONUS_PATH),$(SERVER_BONUS_SRCS:%.c=%.o))
EXE					?= 	client

all: libft $(CLIENT) $(SERVER)

bonus: libft $(CLIENT_BONUS) $(SERVER_BONUS)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"

$(CLIENT): $(CLIENT_OBJS)
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBS) $(HEADERS) -o $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBS) $(HEADERS) -o $(SERVER)

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS)
	@$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) $(LIBS) $(HEADERS) -o $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_OBJS)
	@$(CC) $(CFLAGS) $(SERVER_BONUS_OBJS) $(LIBS) $(HEADERS) -o $(SERVER_BONUS)

clean:
	@rm -rf $(CLIENT_OBJS)
	@rm -rf $(SERVER_OBJS)
	@rm -rf $(CLIENT_BONUS_OBJS)
	@rm -rf $(SERVER_BONUS_OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(CLIENT)
	@rm -rf $(SERVER)
	@rm -rf $(CLIENT_BONUS)
	@rm -rf $(SERVER_BONUS)
	@make -C $(LIBFT) fclean

re: fclean all

norm:
	@norminette $(SRCS_PATH) $(BONUS_PATH) $(LIBFT) $(HEADERS)

val: all
	valgrind --leak-check=full --suppressions=MLX42_suppressions ./$(EXE) $(ARGS)

.PHONY: all, clean, fclean, re, rebonus, norm, val