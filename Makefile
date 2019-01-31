CC = g++
CFLAGS = -std=c++11
DIR_INC = /data/home/pengl/App/Lib/C/htslib/Install/include
LIBRARY_DIRS = /data/home/pengl/App/Lib/C/htslib/Install/lib
TARGET = two
two: main.cpp
	$(CC) $(CFLAGS) $< -I $(DIR_INC) -L $(LIBRARY_DIRS) -lhts -o $(TARGET) segment.cpp
