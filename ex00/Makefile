Name = BitcoinExchange

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
RM = rm -rf

SRCS = main.cpp ./srcs/BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)

all : $(Name)

$(Name) : $(OBJS)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJS)

%.o:%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(Name)

re : fclean all

.PHONY : all clean fclean re