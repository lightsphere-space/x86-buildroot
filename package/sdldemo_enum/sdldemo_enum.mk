################################################################################
#
# SDLDEMO_ENUM
#
################################################################################

SDLDEMO_ENUM_VERSION = 1.0
SDLDEMO_ENUM_SITE = package/sdldemo_enum
SDLDEMO_ENUM_SITE_METHOD = local

SDLDEMO_ENUM_DEPENDENCIES = sdl2

define SDLDEMO_ENUM_BUILD_CMDS
    # TODO: remove comments
    # (cd $(@D) && $(SHELL) $(SDLDEMO_ENUM_DL_DIR)/$($(PKG)_SOURCE))
    cp -f package/sdldemo_enum/Makefile $(@D)
    $(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" -C $(@D)
endef

define SDLDEMO_ENUM_INSTALL_TARGET_CMDS
    $(INSTALL) -m 0755 -D $(@D)/sdldemo_enum $(TARGET_DIR)/usr/bin/sdldemo_enum
endef

$(eval $(generic-package))
