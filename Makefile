# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbakker <jbakker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/26 13:10:28 by jbakker       #+#    #+#                  #
#    Updated: 2024/05/02 15:53:54 by jbakker       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC := cc
DIR := objs/
EXTRAFLAGS := -Wall -Wextra -Werror

SRCS := pipex.c utils.c
BONUS_SRCS := pipex_bonus.c utils_bonus.c

BINS := $(addprefix ${DIR}, ${SRCS:.c=.o})
BONUS_BINS := $(addprefix ${DIR}, ${BONUS_SRCS:.c=.o})

all: ${NAME}

${NAME}: ${BINS}
	@make -C libft
	@${CC} ${EXTRAFLAGS} ${BINS} ./libft/libft.a -o ${NAME}

${DIR}%.o: %.c pipex.h
	@mkdir -p ${DIR}
	@${CC} ${EXTRAFLAGS} -c $< -o $@

bonus: ${BONUS_BINS}
	@make -C libft
	@${CC} ${EXTRAFLAGS} ${BONUS_BINS} ./libft/libft.a -o ${NAME}

clean:
	@make -C libft clean
	@rm -rf ${DIR}

fclean: clean
	@make -C libft fclean
	@rm -f ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re