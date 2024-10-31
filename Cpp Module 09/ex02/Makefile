NAME = PmergeMe
FLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++


all: $(NAME)

$(NAME): *.cpp
	$(CC) $(FLAGS) *.cpp -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all