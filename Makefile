# ===== Compiler =====
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# ===== Project name =====
TARGET = rpg

# ===== Directories =====
SRC_DIRS = Board Dice Enemy Entity Game Inventory Item Player Main Input Attack Merchant
OBJ_DIR = obj

# ===== Sources =====
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# ===== Objects =====
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# ===== Include paths =====
INCLUDES = $(foreach dir,$(SRC_DIRS),-I$(dir))

# ===== Default rule =====
all: $(TARGET)

# ===== Link =====
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# ===== Compile =====
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ===== Run =====
run: $(TARGET)
	./$(TARGET)

# ===== Clean =====
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# ===== Rebuild =====
re: clean all
