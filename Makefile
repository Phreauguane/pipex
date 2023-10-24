NAME = pipex

RM = rm -rf

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = pipex.c pipex_utils.c

$(NAME) :
	make all -C libft
	$(CC) $(CFLAGS) $(SRC) -I libft -L libft -l ft -o $(NAME)

all	: $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all