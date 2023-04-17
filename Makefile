NAME	= pipex

SRCS	= src/pipex.c

OBJS	= $(SRCS:.c=.o)

INCS	= -I./includes -I./Libft

HEADER	= ./includes/pipex.h

LIBFT	= -L./Libft -lft

all:	lib $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) $(INCS) $(LIBFT) $(OBJS) -o $(NAME)

lib:
	make -C Libft

clean:
	$(MAKE) clean -C Libft
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C Libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib