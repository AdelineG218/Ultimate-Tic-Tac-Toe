ifeq ($(OS),Windows_NT)
	TARGET_MAKEFILE = Makefile.win
	CCFLAGS += -D WIN32
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		CCFLAGS += -D AMD64
		ARCH = x86
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			CCFLAGS += -D AMD64
			ARCH = x64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			CCFLAGS += -D IA32
			ARCH = x86
		endif
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CCFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CCFLAGS += -D OSX
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		CCFLAGS += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CCFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CCFLAGS += -D ARM
	endif
endif

all:
	@$(MAKE) -f $(TARGET_MAKEFILE) -w ARCH=$(ARCH) all

clean:
	@$(MAKE) -f $(TARGET_MAKEFILE) -w clean

info:
	@echo "CCFLAGS = $(CCFLAGS)"
	@echo "ARCH = $(ARCH)"

.PHONY: all clean unquarantine info
