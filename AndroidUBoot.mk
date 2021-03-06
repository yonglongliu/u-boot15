ifeq ($(TARGET_KERNEL_ARCH) , arm64)
UBOOT_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linaro-x86/aarch64/gcc-linaro-4.8/gcc-linaro-4.8-2015.06-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
SRCARCH := arm
else ifeq ($(TARGET_KERNEL_ARCH), arm)
UBOOT_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
SRCARCH := arm
else ifeq ($(TARGET_KERNEL_ARCH), x86)
UBOOT_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linux-x86/x86/x86_64-linux-android-4.9/bin/x86_64-linux-android-
SRCARCH := x86
endif

UBOOT_OUT := $(TARGET_OUT_INTERMEDIATES)/u-boot15
UBOOT_CONFIG := $(UBOOT_OUT)/include/config.h
UBOOT_DTB_BUILT_BIN := $(UBOOT_OUT)/u-boot-dtb.bin
UBOOT_BUILT_BIN := $(UBOOT_OUT)/u-boot.bin
FDL2_BUILT_BIN := $(UBOOT_OUT)/fdl2.bin

ifeq ($(TARGET_BUILD_VARIANT),userdebug)
UBOOT_DEBUG_FLAG := -DDEBUG
endif

export UBOOT_CONFIG_PRODUCT UBOOT_DEBUG_FLAG

ifeq ($(strip $(CONFIG_SANSA_SECBOOT)),true)
UBOOT_SECURE_BOOT_FLAG := -DCONFIG_SECBOOT
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_SANSA_SECBOOT
endif

ifeq ($(strip $(PRODUCT_SECURE_BOOT)),SPRD)
UBOOT_SECURE_BOOT_FLAG := -DCONFIG_SECBOOT
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_SPRD_SECBOOT
endif

ifeq ($(strip $(PRODUCT_VBOOT)),V2)
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_VBOOT_V2

endif

export UBOOT_SECURE_BOOT_FLAG

ifeq ($(strip $(BOARD_TEE_CONFIG)),trusty)
UBOOT_TOS_TRUSTY_FLAG := -DTOS_TRUSTY
endif

export UBOOT_TOS_TRUSTY_FLAG

ifeq ($(strip $(CONFIG_CHIP_UID)),true)
UBOOT_CHIP_UID_FLAG += -DCONFIG_CHIP_UID
endif

export UBOOT_CHIP_UID_FLAG

ifeq ($(strip $(CONFIG_TEE_FIREWALL)),true)
UBOOT_FIREWALL_FLAG := -DCONFIG_TEE_FIREWALL
endif

export UBOOT_FIREWALL_FLAG

ifeq ($(TARGET_ARCH), arm)
ifeq ($(strip $(BOARD_ATF_CONFIG)),true)
UBOOT_ARMV7_LPAE_FLAG := -DCONFIG_ARMV7_LPAE
endif
endif
export UBOOT_ARMV7_LPAE_FLAG

ifeq ($(strip $(CONFIG_BOARD_KERNEL_CMDLINE)),true)
UBOOT_KERNEL_CMDLINE_FLAG := -DCONFIG_BOARD_KERNEL_CMDLINE
endif
export UBOOT_KERNEL_CMDLINE_FLAG

.PHONY: $(UBOOT_OUT)
$(UBOOT_OUT):
	@echo "Start U-Boot build board $(UBOOT_DEFCONFIG)"

$(UBOOT_CONFIG): u-boot15/configs/$(addsuffix _defconfig,$(UBOOT_DEFCONFIG)) $(UBOOT_OUT)
	@mkdir -p $(UBOOT_OUT)
	$(MAKE) -C u-boot15 ARCH=$(SRCARCH) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=../$(UBOOT_OUT) distclean
	$(MAKE) -C u-boot15 ARCH=$(SRCARCH) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=../$(UBOOT_OUT) $(UBOOT_DEFCONFIG)_defconfig

ifeq ($(strip $(NORMAL_UART_MODE)),true)
	@echo "#define NORMAL_UART_MODE" >> $(UBOOT_CONFIG)
endif

$(INSTALLED_UBOOT_TARGET) : $(UBOOT_CONFIG)
	$(MAKE) -C u-boot15 ARCH=$(SRCARCH) DEVICE_TREE=$(UBOOT_TARGET_DTB) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) AUTOBOOT_FLAG=true O=../$(UBOOT_OUT)
	-cp $(UBOOT_DTB_BUILT_BIN) $(UBOOT_BUILT_BIN)
	@cp $(UBOOT_BUILT_BIN) $(PRODUCT_OUT)/u-boot_autopoweron.bin
	$(MAKE) -C u-boot15 ARCH=$(SRCARCH) DEVICE_TREE=$(UBOOT_TARGET_DTB) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=../$(UBOOT_OUT) clean
	$(MAKE) -C u-boot15 ARCH=$(SRCARCH) DEVICE_TREE=$(UBOOT_TARGET_DTB) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=../$(UBOOT_OUT)
	-cp $(UBOOT_DTB_BUILT_BIN) $(UBOOT_BUILT_BIN)
	@cp $(UBOOT_BUILT_BIN) $(PRODUCT_OUT)
	@cp $(UBOOT_BUILT_BIN) $(FDL2_BUILT_BIN)
	@cp $(FDL2_BUILT_BIN) $(PRODUCT_OUT)
	@echo "Install U-Boot target done"
