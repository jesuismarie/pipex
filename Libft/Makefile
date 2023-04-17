NAME			= libft.a

SRCS			= $(shell find . -name '*.c')

OBJS			= $(SRCS:.c=.o)

HEADER			= libft.h
RM				= rm -f
AR				= ar rcs
CC				= cc
FLAGS 			= -Wall -Wextra -Werror

%.o: %.c 	$(HEADER) Makefile
				$(CC) $(FLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS) 
					$(AR) $(NAME) $(OBJS)

clean:	
				$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re: 			fclean all

.PHONY:			all clean fclean re