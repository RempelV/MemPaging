# Compilador
CXX = gcc

# Flag do compilador
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++14 -lpthreads

# Diretórios
MAIN_DIR = .
BUILD_DIR = build

# Arquivos fonte e objeto
SOURCES = $(wildcard $(MAIN_DIR)/*.c)
OBJECTS_NAME = $(notdir $(SOURCES))

# Out name
EXEC = myprogram

# Regra padrão
all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(BUILD_DIR)
	$(CXX) ./$(OBJECTS_NAME) -o ./$(BUILD_DIR)/$(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(BUILD_DIR)/$(EXEC)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
