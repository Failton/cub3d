# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruthann <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/04 21:28:43 by pruthann          #+#    #+#              #
#    Updated: 2021/03/24 12:34:46 by pruthann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= src/cast_rays.c src/check_circuit.c src/check_cub.c src/check_map.c src/color_utils_1.c src/color_utils_2.c src/hooks.c src/inter_points.c src/main.c src/parcer_numbers.c src/parcer_textures.c src/parcer_utils.c src/put_sprite_utils.c src/put_sprite.c src/put_textures.c src/screenshot.c src/utils.c

GNL = get_next_line/get_next_line_utils.c get_next_line/get_next_line.c

LIBFT = libft/ft_atoi.c libft/ft_calloc.c libft/ft_lstadd_back.c libft/ft_lstnew.c libft/ft_lstsize.c libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strrchr.c

OBJS_SRC	= ${SRC:.c=.o}

OBJS_GNL	= ${GNL:.c=.o}

OBJS_LIBFT	= ${LIBFT:.c=.o}

NAME	= cub3D

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS_SRC} ${OBJS_GNL} ${OBJS_LIBFT}
	${CC} ${CFLAGS} ${OBJS_SRC} ${OBJS_GNL} ${OBJS_LIBFT} libmlx.dylib -o ${NAME}

all:		${NAME}

clean:
	${RM} ${OBJS_SRC} ${OBJS_GNL} ${OBJS_LIBFT}

fclean:		clean
	${RM} ${OBJS_SRC} ${OBJS_GNL} ${OBJS_LIBFT} ${NAME} 

re:			fclean all

.PHONY:	all clean fclean re
