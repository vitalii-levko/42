# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 13:33:38 by vlevko            #+#    #+#              #
#    Updated: 2018/01/28 13:55:37 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_arrfree.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_factorial.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_lstadd.c \
	ft_lstdel.c \
	ft_lstdelone.c \
	ft_lstfree.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_memalloc.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c \
	ft_sqrt.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strclr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strequ.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strncat.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnequ.c \
	ft_strnew.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strsplit.c \
	ft_strstr.c \
	ft_strsub.c \
	ft_strtrim.c \
	ft_swap.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_printf.c

SRCS = srcs/parse_ctrl.c \
	srcs/ft_itoa_base_slu_oxx.c \
	srcs/ft_strdup_w.c \
	srcs/cast_mdi.c \
	srcs/cast_ssdi.c \
	srcs/cast_hldi.c \
	srcs/cast_mu.c \
	srcs/cast_ws.c \
	srcs/cast_pc_w.c \
	srcs/route_di.c \
	srcs/route_uu.c \
	srcs/route_pxx.c \
	srcs/route_oo.c \
	srcs/route_ss.c \
	srcs/route_ecc.c

OBJ = $(SRC:.c=.o) $(SRCS:.c=.o)

INC = -I includes/

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror -c

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
