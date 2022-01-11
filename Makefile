GXX := g++ --std=c++17

ifeq ($(OS), Windows_NT)
	SFML_DIR := C:/Program\ Files/SFML-2.5.1
	CFLAGS := -I$(SFML_DIR)/include -DSFML_STATIC
	LFLAGS := -L$(SFML_DIR)/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
else
# 	When on linux, static linking is not a requirement unlike some other OS's (*cough* windows *cough*), the Path actually works like you'd expect.
	CFLAGS :=
	LFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
endif

PROJECT_NAME  := pacenstein

SOURCE_DIR := src
BUILD_DIR  := obj

#------------------------------------
# No touchie below here
#------------------------------------

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS := $(wildcard $(SOURCE_DIR)/*.hpp)

OBJECTS := $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:%.cpp=%.o))

# include existing .o files as dependencies
-include $(OBJECTS:.o=.d)

# Link
build: dirs $(BUILD_DIR)/main.o $(OBJECTS) $(HEADERS)
	$(GXX) $(OBJECTS) $(LFLAGS) -o $(PROJECT_NAME).exe

dirs:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -r $(BUILD_DIR) $(PROJECT_NAME).exe

rerun: clean run
rebuild: clean build

run: build
	@./$(PROJECT_NAME).exe

$(BUILD_DIR)/main.o: $(SOURCE_DIR)/main.cpp
	$(GXX) $(CFLAGS) -c $(SOURCE_DIR)/main.cpp -o $(BUILD_DIR)/main.o

# Compile
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	$(GXX) $(CFLAGS) -c -o $@ $<

.PHONY: build clean run rerun rebuild
