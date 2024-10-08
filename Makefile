CC := g++ -std=c++17
CFLAGS := -Wall -Werror -Wextra -Wreorder-ctor
OBJ_DIR := obj
SRC_DIRS := parsing prediction training pipeline
SRC_FILES := parsing/split.cpp pipeline/pipeline.cpp training/training.cpp training/network.cpp training/globals.cpp
OBJ_FILES := $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)
EXE := exec
$(EXE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXE)

re: fclean $(EXE)

.PHONY: clean fclean re