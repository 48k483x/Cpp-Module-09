# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 15:46:40 by tfriedri          #+#    #+#              #
#    Updated: 2023/09/18 11:55:58 by tfriedri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	PmergeMe

CPPFLAGS		=	-Wall -Werror -Wextra -std=c++98

SRCS			=	main.cpp \
					PmergeMe.cpp \

OBJS			=	$(SRCS:.cpp=.o)

$(NAME):			$(OBJS)
					$(CXX) $(CPPFLAGS) $(OBJS) -o $(NAME)

all:				$(NAME)

clean:
					rm -rf $(OBJS)

fclean:				clean
					rm -f $(NAME)

re:					fclean all
