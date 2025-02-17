#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

export TARGET		:=	ereader-manager
export TOPDIR		:=	$(CURDIR)
export GAME_TITLE	:=	e-Reader Manager
export GAME_ICON	:=	$(CURDIR)/icon.bmp


.PHONY: arm7/$(TARGET).elf arm9/$(TARGET).elf

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all: $(TARGET).nds

debug: $(TARGET)-debug.nds

#---------------------------------------------------------------------------------
$(TARGET).nds	:	arm7/$(TARGET).elf arm9/$(TARGET).elf
	ndstool -7 arm7/$(TARGET).elf -9 arm9/$(TARGET).elf -b $(GAME_ICON) "$(GAME_TITLE);$(GAME_SUBTITLE1);$(GAME_SUBTITLE2)" -c $(TARGET).nds 

#---------------------------------------------------------------------------------
arm7/$(TARGET).elf:
	$(MAKE) -C arm7
	
#---------------------------------------------------------------------------------
arm9/$(TARGET).elf:
	$(MAKE) -C arm9

#---------------------------------------------------------------------------------
$(TARGET)-debug.nds	:	arm7/$(TARGET)-debug.elf arm9/$(TARGET)-debug.elf
	ndstool	-c $(TARGET)-debug.nds -7 arm7/$(TARGET)-debug.elf -9 arm9/$(TARGET)-debug.elf

#---------------------------------------------------------------------------------
arm7/$(TARGET)-debug.elf:
	$(MAKE) -C arm7 -f Makefile.debug
	
#---------------------------------------------------------------------------------
arm9/$(TARGET)-debug.elf:
	$(MAKE) -C arm9 -f Makefile.debug

#---------------------------------------------------------------------------------
clean:
	$(MAKE) -C arm9 clean
	$(MAKE) -C arm7 clean
	rm -f $(TARGET).nds $(TARGET).arm7 $(TARGET).arm9
	rm -f $(TARGET)-debug.nds $(TARGET)-debug.arm7 $(TARGET)-debug.arm9
