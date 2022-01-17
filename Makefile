CC := g++ --std=c++17

ifeq ($(OS), Windows_NT)
	SFML_DIR := C:/Program Files/SFML-2.5.1
	CFLAGS := -I"$(SFML_DIR)/include" -DSFML_STATIC
	LFLAGS := -L"$(SFML_DIR)/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfreetype -lopengl32 -lwinmm -lgdi32
	MKDIR := mkdir
else
	CFLAGS :=
	LFLAGS := -lsfml-system -lsfml-window -lsfml-graphics
	MKDIR := mkdir -p
endif

PROJECT_NAME  := pacenstein
TARGET        := $(PROJECT_NAME).exe

BUILD_DIR  := obj
SOURCE_DIR := src

DIRS        = . entities entities/items entities/items/ghosts states
SOURCE_DIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCE_DIR)/, $(dir)))
TARGET_DIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILD_DIR)/, $(dir)))
INCLUDES    = $(foreach dir, $(SOURCE_DIRS), $(addprefix -I, $(dir)))

VPATH = $(SOURCE_DIRS)

SOURCES = $(foreach dir, $(SOURCE_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS = $(subst $(SOURCE_DIR), $(BUILD_DIR), $(SOURCES:.c=.o))
DEPS    = $(OBJECTS:.o=.d)

OBJECTS := $(patsubst $(SOURCE_DIR)/%, $(BUILD_DIR)/%, $(SOURCES:%.cpp=%.o))

define generateRules
$(1)/%.o: %.cpp
	$(CC) -c $$(INCLUDES) $$(CFLAGS) -o $$@ $$<
endef

.PHONY: build dirs clean run rerun rebuild

-include $(DEPS)

$(foreach targetdir, $(TARGET_DIRS), $(eval $(call generateRules, $(targetdir))))

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LFLAGS)

build: dirs $(TARGET)

dirs:
	-$(MKDIR) $(TARGET_DIRS)

clean:
	-@rm -r $(BUILD_DIR)/* $(PROJECT_NAME).exe

rerun: clean run
rebuild: clean build

run: build
	@./$(PROJECT_NAME).exe
