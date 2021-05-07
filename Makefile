TARGET = japanese_helloworld
OBJS = src/main.o src/screen_setting.o src/net_setting.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -fcheck-new
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

LIBS =
LIBS += dxlibp_UTF8.a -lpspgu -lz -lm -lpsprtc -lpspaudio -lpspaudiocodec -lstdc++ -lpsputility -lpspvalloc -lpsppower -lpspgum -lpsphttp -lpspssl

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Japanese Hello World
PSP_EBOOT_ICON = assets/icon.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
