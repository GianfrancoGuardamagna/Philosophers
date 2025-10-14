# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 12:30:00 by gguardam          #+#    #+#              #
#    Updated: 2025/10/14 13:21:50 by gguardam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
# CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I.

SRCS = main.c \
		loader.c \
		monitor.c \
		routine.c \
		parsing/parser.c \
		utils/dead_comprobation.c \
		utils/time.c \
		utils/isint.c \
		utils/atoi.c \
		states/eat.c \
		states/think.c \
		states/sleep.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philosophers.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re