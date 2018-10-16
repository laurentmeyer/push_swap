CC = 		gcc
CFLAGS =	-Wall -Wextra -Werror
NAME =		libft_lds.a
BUILDDIR =	builds
SOURCEDIR =	srcs
HEADERDIR = includes

CCHEADERS = -I./$(HEADERDIR)		\
			-I../libft/includes		\
			-I../int_array/includes

SRCFILES =	algo.c					\
			init.c

SOURCES =	$(SRCFILES:%.c=$(SOURCEDIR)/%.c)
OBJECTS =	$(SOURCES:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all