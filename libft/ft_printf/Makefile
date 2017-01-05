CC = 		gcc
CFLAGS =	-Wall -Wextra -Werror
NAME =		libftprintf.a
BUILDDIR =	srcs
SOURCEDIR =	srcs
HEADERDIR = includes

CCHEADERS = -I./$(HEADERDIR)		\
			-I../libft/includes

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
	ar rcs $(NAME) $(OBJECTS)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
