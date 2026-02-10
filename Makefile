CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude
LIBS = -lglfw -lGL -ldl

SRC = src/main.cpp glad.c
OUT = game

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

