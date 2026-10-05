CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = filemanager

SRC = src/main.cpp \
      src/FileManager.cpp \
      src/PermissionManager.cpp \
      src/FileLockManager.cpp \
      src/AuditLogger.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
