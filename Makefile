NAME	= pipex

SRC		= src

SRCS	= $(shell find $(SRC) -name '*.c')

OBJS	= $(SRCS:src/%.c=obj/%.o)

INCS	= -I./includes -I./Libft

FLAGS	= -Wall -Wextra -Werror# -fsanitize=address -g

HEADER	= ./includes/pipex.h

LIBFT	= -L./Libft -lft

all:	mkdir lib $(NAME)

mkdir:
	@mkdir -p obj

obj/%.o: src/%.c $(HEADER) Makefile
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) $(INCS) $(OBJS) $(LIBFT) -o $(NAME)

lib:
	@make -C Libft

clean:
	$(MAKE) clean -C Libft
	rm -rf obj

fclean: clean
	$(MAKE) fclean -C Libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib