GXX := g++ --std=c++17

ifeq ($(OS), Windows_NT)
	COMPILER_FLAGS := -IC:/Program\ Files/SFML-2.5.1/include -DSFML_STATIC
	LINKER_FLAGS := -LC:/Program\ Files/SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
else
	COMPILER_FLAGS :=
	LINKER_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system
endif

HEADERS := 
SOURCES := 

OBJECTS := $(SOURCES:%.cpp=%.o)

main: main.o $(OBJECTS) $(HEADERS)
	$(GXX) main.o $(OBJECTS) $(LINKER_FLAGS) -o main.exe

main.o: main.cpp
	$(GXX) $(COMPILER_FLAGS) -c main.cpp -o main.o

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(GXX) $(COMPILER_FLAGS) -c $(@:.o=.cpp) -o $@

.PHONY: clean build run rerun rebuild

clean:
	rm $(OBJECTS) main.o main.exe

build: main
rerun: clean run
rebuild: clean build

run: main
	@./main.exe
