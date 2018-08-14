CC = 		gcc
CFLAGS =	-g -Wall -Wextra -Werror
CHECKER =	checker
PUSHSWAP =	push_swap
BUILDDIR =	builds
SOURCEDIR =	srcs
HEADERDIR = includes

SRCFILES =	init_stacks.c		\
			init_display.c		\
			error.c				\
			free.c				\
			do_op.c				\
			verifs.c			\
			verifs_increasing.c	\
			verifs_decreasing.c	\
			insertions.c		\
			rotations_swaps.c	\
			algo_lds.c			\
			algo_small.c		\
			display.c

CCHEADERS = -I./$(HEADERDIR)				\
			-I$(LIBFT)/libft/includes		\
			-I$(LIBFT)/ft_printf/includes	\
			-I$(MINILIB)

LIBFT = 	./libft
MINILIB = 	./mlx/
CCLIBS =	-L$(LIBFT) -lft			\
			-L$(MINILIB) -lmlx

CCFRAMEWORKS = -framework AppKit -framework OpenGL

SOURCES = 		$(SRCFILES:%.c=$(SOURCEDIR)/%.c)
CHECKERMAIN =	$(SOURCEDIR)/$(CHECKER).c
PUSHSWAPMAIN =	$(SOURCEDIR)/$(PUSHSWAP).c
CHECKERSRCS =	$(SOURCES)		\
				$(CHECKERMAIN)
CHECKEROBJS =	$(CHECKERSRCS:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)
PUSHSWAPSRCS =	$(SOURCES)		\
				$(PUSHSWAPMAIN)
PUSHSWAPOBJS =	$(PUSHSWAPSRCS:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all clean fclean re

all : $(CHECKER) $(PUSHSWAP)

$(CHECKER) : $(CHECKEROBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MINILIB)
	$(CC) $(CCHEADERS) $(CCLIBS) $(CHECKEROBJS) $(CCFRAMEWORKS) -o $(CHECKER)

$(PUSHSWAP) : $(PUSHSWAPOBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MINILIB)
	$(CC) $(CCHEADERS) $(CCLIBS) $(PUSHSWAPOBJS) $(CCFRAMEWORKS) -o $(PUSHSWAP)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MINILIB) clean
	rm -rf $(BUILDDIR)
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(CHECKER)
	rm -f $(PUSHSWAP)

re: fclean all