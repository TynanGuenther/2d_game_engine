CXX = g++
CXXFLAGS = -Wall -Wextra -I./include
LIBS = -lglfw -lGL -ldl

SRC = src/main.cpp src/GameObject.cpp glad.c 
OUT = game

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

