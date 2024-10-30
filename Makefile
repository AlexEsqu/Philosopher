# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2024/10/30 17:34:47 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC_DIR		= ./src

OBJ_DIR		= ./obj

SRCS		= main.c \

OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(SRC_DIR)/, $(SRCS)))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror


all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(addprefix $(SRC_DIR)/, $(SRCS))

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

debug:		$(OBJS)
			$(CC) $(CFLAGS) -g -o $(NAME) $(addprefix $(SRC_DIR)/, $(SRCS))

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re debug
