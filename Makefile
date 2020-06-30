# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 16:15:52 by jpizarro          #+#    #+#              #
#    Updated: 2020/06/30 20:02:20 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
# Cambiarlo por los nombres de los archivos!!!
# SRC = $(shell find . -name "ft*.c" ! -name "ft_lst*.c")
SRC = ft_printf.c ft_printf_utils.c

OBJ	= $(SRC:.c=.o)

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			cd libft && $(MAKE)
			cp libft/libft.a $(NAME)
			ar rc  $(NAME) $(OBJ)
			ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJ) $(OBJ_B)
			$(MAKE) clean -C ./libft

fclean:		clean
			$(RM) $(NAME)
			$(RM) libft.a
			$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY: all clean fclean re

# MAKEFILE para test según Toni
#
#SRCS    = ft_printf.c ft_printf_utils.c
#OBJS    = ${SRCS:.c=.o}
#NAME    = libftprintf.a
#CC      = cc
#RM      = rm -f
#CFLAGS    = -Wall -Werror -Wextra
#.c.o:
#	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
#$(NAME):	${OBJS}
#		    cd libft && ${MAKE}
#		    cp libft/libft.a ${NAME}
#		    ar rc ${NAME} ${OBJS}
#		    ranlib ${NAME}
#all:	${NAME}
#clean:
#	${RM} ${OBJS} ${OBJ_BONUS}
#	${MAKE} clean -C ./libft
#fclean :	clean
#	${RM} ${NAME}
#	${RM} libft.a
#	${MAKE} fclean -C ./libft
#re:      fclean all
#.PHONY:    re all clean fclean