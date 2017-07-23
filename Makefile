# @Author: danielb
# @Date:   2017-07-22T23:36:04+02:00
# @Last modified by:   danielb
# @Last modified time: 2017-07-23T05:13:18+02:00

NAME 	=	MyEngine

SRCS	=	main.cpp \
				Window.cpp \
				Shader.cpp \
				Triangle.cpp

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -g

LDFLAGS		=	-lGL -lGLEW -lglfw

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
