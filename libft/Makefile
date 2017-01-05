CC = 		gcc
CFLAGS =	-Wall -Wextra -Werror
NAME =		libft.a

LFTPATH =		./libft
LIBFT = 		$(LFTPATH)/libft_original.a
PRINTFPATH =	./ft_printf
PRINTF =		$(PRINTFPATH)/libftprintf.a

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) :
	$(MAKE) -C $(LFTPATH)
	$(MAKE) -C $(PRINTFPATH)
	libtool -static -o $(NAME) $(LIBFT) $(PRINTF)

clean:
	$(MAKE) -C $(LFTPATH) clean
	$(MAKE) -C $(PRINTFPATH) clean

fclean: clean
	$(MAKE) -C $(LFTPATH) fclean
	$(MAKE) -C $(PRINTFPATH) fclean
	rm -f $(NAME)

re: fclean all
