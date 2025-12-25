# Makefile for Lunar Lander Simulator

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = -pthread
TARGET = lunar_lander
SRC = lunar_lander.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) flight_data.csv

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
