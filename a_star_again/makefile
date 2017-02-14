SRCS= Search.cpp Path_planning.cpp
SRC_DIR= $(addprefix src/,$(SRCS))
LFLAGS=-lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl

GLEW_LIB=-Wl,-rpath,/usr/lib64
all:
	g++ -g -Wall $(GLEW_LIB) $(SRC_DIR) $(LFLAGS) -o bin/a_star.bin -std=c++11 -L /usr/lib/ -L . -I include -I ../vector_library/include -g
