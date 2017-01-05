CC = 		gcc
CFLAGS =	-Wall -Wextra -Werror
CHECKER =	checker
PUSHSWAP =	push_swap
BUILDDIR =	srcs
SOURCEDIR =	srcs
HEADERDIR = includes

SRCFILES =	init.c			\
			push.c			\
			print.c

CCHEADERS = -I./$(HEADERDIR)				\
			-I$(LIBFT)/libft/includes		\
			-I$(LIBFT)/ft_printf/includes

LIBFT = 	./libft
CCLIBS = 	-L$(LIBFT) -lft

SOURCES = 		$(SRCFILES:%.c=$(SOURCEDIR)/%.c)
CHECKERMAIN =	$(SOURCEDIR)/$(CHECKER).c
PUSHSWAPMAIN =	$(SOURCEDIR)/$(PUSHSWAP).c
CHECKERSRCS =	$(SOURCES)		\
				$(CHECKERMAIN)
PUSHSWAPSRCS =	$(SOURCES)		\
				$(PUSHSWAPMAIN)
CHECKEROBJS =	$(CHECKERSRCS:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all clean fclean re

all : $(CHECKER) $(PUSHSWAP)

$(CHECKER) : $(CHECKEROBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CCHEADERS) $(CCLIBS) $(CHECKEROBJS) -o $(CHECKER)

$(PUSHSWAP) : $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CCHEADERS) $(CCLIBS) $(OBJECTS) $(PUSHSWAPMAIN) -o $(PUSHSWAP)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(CHECKER)
	rm -f $(PUSHSWAP)

re: fclean all
