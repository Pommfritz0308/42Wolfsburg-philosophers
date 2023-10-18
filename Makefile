# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 10:36:38 by fbohling          #+#    #+#              #
#    Updated: 2023/10/12 14:50:09 by fbohling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_split.c philo.c utils.c utils2.c std_func.c std_func2.c \
		std_func3.c actions.c
OBJS = $(SRCS:.c=.o)

BONUS =
BONUS_OBJS = $(BONUS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean bonus re
