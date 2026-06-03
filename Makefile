TARGET = vfs_program
SRCS = $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(SRCS); g++ -std=c++17 $(SRCS) -o $(TARGET)

clean:; rm -f $(TARGET)
