

SHELL  = bash
TARGET = PuzzlePic
CC     = g++
SDL2 = sdl2
SDL2_IMAGE = SDL2_image
SDL2_TTF = SDL2_ttf

# Flags that are used regardless of compiliation options go here
CCFL := -c -g -Wall `pkg-config --cflags $(SDL2) $(SDL2_IMAGE) $(SDL2_TTF)`
LDFL := -Wall `pkg-config --libs $(SDL2) $(SDL2_IMAGE) $(SDL2_TTF)`

# List of source files. 
SRCS := main.cpp

#SRCS := Tiles.cpp Player.cpp Display.cpp Test.cpp 

# Construct file lists
OBJS := $(addprefix build/obj/,$(patsubst %.cpp,%.o,$(SRCS)))
DEPS := $(addprefix build/dep/,$(patsubst %.cpp,%.d,$(SRCS)))
SRCS := $(addprefix src/,$(SRCS))

# All the make rules
.PHONY: all clean 

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFL) -o $(TARGET)

build/obj/%.o: src/%.cpp
	@ mkdir -p $(@D)
	@ mkdir -p $(subst obj,dep,$(@D))
	@ $(CC) -MM -MP -MT $@ -MF $(patsubst %.o,%.d,$(subst obj,dep,$@)) $<
	$(CC) $(CCFL) $< -o $@

clean:
	rm -rf build
	rm -f $(TARGET)

# Include automagically generated dependencies
-include $(DEPS) 
