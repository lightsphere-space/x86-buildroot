################################################################################
#
# SDLDEMO2
#
################################################################################

SDLDEMO2_VERSION = 1.0
SDLDEMO2_SITE = $(BR2_EXTERNAL)/package/sdldemo2
SDLDEMO2_SITE_METHOD = local

SDLDEMO2_DEPENDENCIES = sdl2

define SDLDEMO2_BUILD_CMDS
    # TODO: remove comments
    # (cd $(@D) && $(SHELL) $(SDLDEMO2_DL_DIR)/$($(PKG)_SOURCE))
    # cp -f package/sdldemo2/Makefile $(@D)
    $(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" -C $(@D)
endef

define SDLDEMO2_INSTALL_TARGET_CMDS
    $(INSTALL) -m 0755 -D $(@D)/sdldemo2 $(TARGET_DIR)/usr/bin/sdldemo2
endef

$(eval $(generic-package))
