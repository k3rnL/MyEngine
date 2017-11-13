# @Author: danielb
# @Date:   2017-07-22T23:36:04+02:00
# @Last modified by:   daniel_b
# @Last modified time: 2017-11-13T01:08:35+01:00

NAME 	=	MyEngine

LIB 	= libfse.so

SRC_PATH	=	./source/
OBJ_PATH	=	./obj/
INC_PATH 	= ./include/

SRCS	=	source/Window.cpp \
				source/ShaderManager.cpp \
				source/Material.cpp \
				source/Scene/Object/Object.cpp \
				source/Scene/Object/Wavefront.cpp \
				source/Scene/SceneManager.cpp \
				source/Scene/INode.cpp \
				source/Scene/CameraFPS.cpp \
				source/GLItem/Shader.cpp \
				source/GLItem/Mesh.cpp \
				source/Renderer/Renderer.cpp \
				source/Renderer/ObjectRenderer.cpp \
				source/Renderer/ObjectsToDrawCallback.cpp


OBJS	=	$(SRCS:.cpp=.o)

SRCS_SAMPLE = main.cpp \
							$(SRCS)

OBJS_SAMPLE	=	$(SRCS_SAMPLE:.cpp=.o)


CPPFLAGS	=	-std=c++11 -I$(INC_PATH) -O3 -g

LDFLAGS		=	-lassimp -lSDL2 -lGL -lGLU -lGLEW

all: $(NAME)

lib: $(OBJS) $(eval CPPFLAGS += -fPIC)
	g++ -shared -fPIC -o $(LIB) $(OBJS) $(LDFLAGS)

install:
	cp libmxe.so /usr/lib
	mkdir -p /usr/include/fse
	cp -r include/ /usr/

$(NAME): $(OBJS_SAMPLE)
	g++ -o $(NAME) $(OBJS_SAMPLE) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_SAMPLE)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB)

re: fclean all
