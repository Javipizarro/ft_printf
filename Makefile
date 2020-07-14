# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 16:15:52 by jpizarro          #+#    #+#              #
#    Updated: 2020/07/14 16:43:18 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_printer.c ft_utils_cs.c ft_utils_diopux.c ft_utils_efg.c ft_utils_t_convspecs.c ft_utils_t_n.c

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

bonus	:	all

clean:
			$(RM) $(OBJ) $(OBJ_B)
			$(MAKE) clean -C ./libft

fclean:		clean
			$(RM) $(NAME)
			$(RM) libft.a
			$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY: bonus all clean fclean re
