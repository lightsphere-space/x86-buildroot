################################################################################
#
# SDLDEMO Buildroot Package
#
################################################################################

# Version and source location (in this case, using the local directory)
SDLDEMO_VERSION = 1.0
SDLDEMO_SITE = $(BR2_EXTERNAL)/package/SDLDEMO
SDLDEMO_SITE_METHOD = local

# Dependencies
SDLDEMO_DEPENDENCIES = sdl2

# Source files
SDLDEMO_SRC_FILES = main.c ogl.c shaders.c glad.c

# Object files
SDLDEMO_OBJS = $(SDLDEMO_SRC_FILES:.c=.o)

# Executable name
SDLDEMO_EXEC = demo_app
SQLDEMO_ASSET = tex.png

# Build the package
define SDLDEMO_BUILD_CMDS
    $(TARGET_CC) $(TARGET_CFLAGS) -I$(SRCDIR)/include -I$(SRCDIR) $(shell sdl2-config --cflags) -c $(SDLDEMO_SRC_FILES) -o $(SDLDEMO_OBJS)
    $(TARGET_CC) $(SDLDEMO_OBJS) $(shell sdl2-config --libs) -lSDL2_image -lglfw -lGLESv2 -lm -ldl -o $(SDLDEMO_EXEC)
endef

# Install the executable
define SDLDEMO_INSTALL_TARGET_CMDS
    $(INSTALL) -m 0755 -D $(SDLDEMO_EXEC) $(TARGET_DIR)/usr/bin/$(SDLDEMO_EXEC)
    $(INSTALL) -m 0644 -D $(SQLDEMO_ASSET) $(TARGET_DIR)/usr/share/sqldemo/$(SQLDEMO_ASSET)
endef

# Clean the build
define SDLDEMO_CLEAN_CMDS
    rm -f $(SDLDEMO_OBJS) $(SDLDEMO_EXEC)
endef

# Register the package
$(eval $(generic-package))
