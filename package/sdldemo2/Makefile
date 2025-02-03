# Compiler


# Compiler Flags
# CFLAGS_CUSTOM = -Wall -g -I./include -I. $(shell sdl2-config --cflags)

# Linker Flags
# LDLIBS = -lglfw -lGLESv2
LDLIBS = -lSDL2 -lSDL2_image -lm -ldl
# -lSDL2

# Source Files
SRCS = main.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Executable Name
EXEC = sdldemo2

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
