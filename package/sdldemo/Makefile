# Compiler


# Compiler Flags
# CFLAGS_CUSTOM = -Wall -g -I./include -I. $(shell sdl2-config --cflags)
CFLAGS_CUSTOM = -I. $(shell sdl2-config --cflags)

# Linker Flags
LDLIBS = $(shell sdl2-config --libs) -lSDL2_image -lglfw -lGLESv2 -lm -ldl
# -lSDL2

# Source Files
SRCS = main.c ogl.c shaders.c glad.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Executable Name
EXEC = sdldemo

# Default Target
all: $(EXEC)

# Link Object Files to Create Executable
$(EXEC): $(OBJS)
	$(CC) $(LDLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)

# Compile Source Files to Object Files
%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_CUSTOM) -c $< -o $@

# Clean Target
clean:
	rm -f $(OBJS) $(EXEC)

# Phony Targets
.PHONY: all clean
