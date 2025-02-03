################################################################################
#
# SDLDEMO
#
################################################################################

SDLDEMO_VERSION = 1.0
SDLDEMO_SITE = $(BR2_EXTERNAL)/package/SDLDEMO
SDLDEMO_SITE_METHOD = local

SDLDEMO_DEPENDENCIES = sdl2

define SDLDEMO_BUILD_CMDS
    # TODO: remove comments
    # (cd $(@D) && $(SHELL) $(DHRYSTONE_DL_DIR)/$($(PKG)_SOURCE))
    # cp -f package/ramsmp/Makefile $(@D)
    $(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" -C $(@D)
endef

define SDLDEMO_INSTALL_TARGET_CMDS
    $(INSTALL) -m 0755 -D $(@D)/sdldemo $(TARGET_DIR)/usr/bin/sdldemo
    $(INSTALL) -m 0644 -D $(@D)/tex.png $(TARGET_DIR)/usr/share/sdldemo/tex.png
endef

$(eval $(generic-package))
