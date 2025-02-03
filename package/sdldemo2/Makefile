################################################################################
#
# SDLDEMO2 Buildroot Package
#
################################################################################

# Version and source location (in this case, using the local directory)
SDLDEMO2_VERSION = 1.0
SDLDEMO2_SITE = $(BR2_EXTERNAL)/package/SDLDEMO2
SDLDEMO2_SITE_METHOD = local

# Dependencies
SDLDEMO2_DEPENDENCIES = sdl2

# Source files
SDLDEMO2_SRC_FILES = main.c

# Object files
SDLDEMO2_OBJS = $(SDLDEMO2_SRC_FILES:.c=.o)

# Executable name
SDLDEMO2_EXEC = demo_app

# Build the package
define SDLDEMO2_BUILD_CMDS
    $(TARGET_CC) $(TARGET_CFLAGS) -I$(SRCDIR)/include -I$(SRCDIR) $(shell sdl2-config --cflags) -c $(SDLDEMO2_SRC_FILES) -o $(SDLDEMO2_OBJS)
    $(TARGET_CC) $(SDLDEMO2_OBJS) $(shell sdl2-config --libs) -lSDL2_image -lglfw -lGLESv2 -lm -ldl -o $(SDLDEMO2_EXEC)
endef

# Install the executable
define SDLDEMO2_INSTALL_TARGET_CMDS
    $(INSTALL) -D $(SDLDEMO2_EXEC) $(TARGET_DIR)/usr/bin/$(SDLDEMO2_EXEC)
endef

# Clean the build
define SDLDEMO2_CLEAN_CMDS
    rm -f $(SDLDEMO2_OBJS) $(SDLDEMO2_EXEC)
endef

# Register the package
$(eval $(generic-package))
