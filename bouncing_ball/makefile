SRCS=Graphics.cpp Shapes.cpp Sources.cpp Physics_ball.cpp
SRC_DIR= $(addprefix src/,$(SRCS))
LFLAGS=-lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl

GLEW_LIB=-Wl,-rpath,/usr/lib64
all:
	g++ -Wall $(GLEW_LIB) $(SRC_DIR) $(LFLAGS) -o bouncing_ball.bin -std=c++11 -L /usr/lib/ -L . -I ~/home/aidan/git/games_programming/glm-0.9.8.4 -I include -g
