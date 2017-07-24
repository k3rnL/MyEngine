# @Author: danielb
# @Date:   2017-07-22T23:36:04+02:00
# @Last modified by:   danielb
# @Last modified time: 2017-07-24T01:54:02+02:00

NAME 	=	MyEngine

SRCS	=	main.cpp \
				Window.cpp \
				Shader.cpp \
				Triangle.cpp \
				Object.cpp

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -g

LDFLAGS		=	-lSDL2 -lGL -lGLU -lGLEW

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
