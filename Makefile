GXX := g++ --std=c++17

ifeq ($(OS), Windows_NT)
	SFML_DIR := C:/Program\ Files/SFML-2.5.1
	COMPILER_FLAGS := -I$(SFML_DIR)/include -DSFML_STATIC
	LINKER_FLAGS := -L$(SFML_DIR)/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
else
	COMPILER_FLAGS :=
	LINKER_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system
endif

HEADERS := 
SOURCES := 

OBJECTS := $(SOURCES:%.cpp=%.o)

PROJECT_NAME := Doom

main: main.o $(OBJECTS) $(HEADERS)
	$(GXX) main.o $(OBJECTS) $(LINKER_FLAGS) -o $(PROJECT_NAME).exe

main.o: main.cpp
	$(GXX) $(COMPILER_FLAGS) -c main.cpp -o main.o

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(GXX) $(COMPILER_FLAGS) -c $(@:.o=.cpp) -o $@

.PHONY: clean build run rerun rebuild

clean:
	rm $(OBJECTS) main.o $(PROJECT_NAME).exe

build: main
rerun: clean run
rebuild: clean build

run: $(PROJECT_NAME)
	ifneq ($(OS), Windows_NT)
		chmod u+x ./$(PROJECT_NAME).exe
	endif
	@./$(PROJECT_NAME).exe
