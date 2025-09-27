CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -I/usr/include/SFML

LDFLAGS = -L./SFML-3.0.0-linux-gcc-64-bit/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_FILES = src/main.cpp src/Game.cpp src/Plane.cpp src/Bullet.cpp src/Bomb.cpp src/Bomber.cpp

OBJS= $(SRC_FILES:.cpp=.o)

TARGET = SpaceGame
all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)
