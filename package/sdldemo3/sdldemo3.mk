################################################################################
#
# SDLDEMO3
#
################################################################################

SDLDEMO3_VERSION = 1.0
SDLDEMO3_SITE = package/sdldemo3
SDLDEMO3_SITE_METHOD = local

SDLDEMO3_DEPENDENCIES = sdl2

define SDLDEMO3_BUILD_CMDS
    # TODO: remove comments
    # (cd $(@D) && $(SHELL) $(SDLDEMO3_DL_DIR)/$($(PKG)_SOURCE))
    cp -f package/sdldemo3/Makefile $(@D)
    $(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" -C $(@D)
endef

define SDLDEMO3_INSTALL_TARGET_CMDS
    $(INSTALL) -m 0755 -D $(@D)/sdldemo3 $(TARGET_DIR)/usr/bin/sdldemo3
endef

$(eval $(generic-package))
