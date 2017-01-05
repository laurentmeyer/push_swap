CC = 		gcc
CFLAGS =	-Wall -Wextra -Werror
NAME =		libftprintf.a
TEMP =		temp.a
BUILDDIR =	srcs
SOURCEDIR =	srcs
HEADERDIR = includes

LFTPATH =	./libft
LIBFT = 	$(LFTPATH)/libft.a

CCHEADERS = -I./$(HEADERDIR)	\
			-I$(LFTPATH)/includes

SRCFILES =	ft_printf.c				\
			ft_asprintf.c			\
			get_conversion.c		\
			get_handler.c			\
			get_modifier.c			\
			get_flags.c				\
			get_precision.c			\
			get_width.c				\
			handler_integers.c		\
			handler_percent.c		\
			handler_string.c		\
			handler_char.c			\
			handler_pointer.c		\
			ft_itoa_base_max.c

SOURCES =	$(SRCFILES:%.c=$(SOURCEDIR)/%.c)
OBJECTS =	$(SOURCES:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(MAKE) -C $(LFTPATH)
	ar rcs $(TEMP) $(OBJECTS)
	libtool -static -o $(NAME) $(LIBFT) $(TEMP)
	rm $(TEMP)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	$(MAKE) -C $(LFTPATH) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LFTPATH) fclean
	rm -f $(NAME)

re: fclean all
