# @Author: danielb
# @Date:   2017-07-22T23:36:04+02:00
# @Last modified by:   daniel_b
# @Last modified time: 2017-08-03T18:28:36+02:00

NAME 	=	MyEngine

SRCS	=	Window.cpp \
				Shader.cpp \
				Triangle.cpp \
				Object.cpp \
				Renderer.cpp \
				Material.cpp \
				Scene/Object/Wavefront.cpp \
				Scene/SceneManager.cpp \
				Scene/INode.cpp

OBJS	=	$(SRCS:.cpp=.o)

SRCS_SAMPLE = main.cpp \
							$(SRCS)

OBJS_SAMPLE	=	$(SRCS_SAMPLE:.cpp=.o)


CPPFLAGS	=	-std=c++11 -I./ -g

LDFLAGS		=	-lSDL2 -lGL -lGLU -lGLEW

all: $(NAME)

lib: $(OBJS) $(eval CPPFLAGS += -fPIC)
	g++ -shared -fPIC -o libmxe.so $(OBJS) $(LDFLAGS)

install:
	cp libmxe.so /usr/lib

$(NAME): $(OBJS_SAMPLE)
	g++ -o $(NAME) $(OBJS_SAMPLE) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_SAMPLE)

fclean: clean
	rm -rf $(NAME)

re: fclean all
