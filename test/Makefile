INC_PATH=src
SRC_PATH=src
OUT_EXE=libutils-test
OUT_EXE_SUFFIX=
OUT_EXE_PATH=bin
OUT_OBJ_PATH=obj

TOOLCHAIN_PREFIX=
CXX=$(TOOLCHAIN_PREFIX)g++

# libutils
LIBUTILS_INC_PATH=../inc
LIBUTILS_LIB_PATH=../lib
LIBUTILS_LIB=utils

# Additional stuff
USER_INC_PATHS?=
USER_LIB_PATHS?=
USER_LIBS?=gtest pthread tinyxml2 turbojpeg png
USER_SYMBOLS?=

# Basically you are not going to mess up with things below

ifeq ($(OS),Windows_NT)
WIN32=1
$(info Host = Win32)

else
UNIX=1
$(info Host = *nix)

endif

ifneq ($(firstword $(sort $(MAKE_VERSION) 3.81)),3.81)
$(error Require GNU Make 3.81 or newer)

else
$(info Make version = $(MAKE_VERSION))

endif

ifdef WIN32
# TODO Also print CC version on win32

else ifdef UNIX
$(info CXX = $(shell $(CXX) --version | (read -r line; echo $$line)))

endif

$(info User include paths = $(USER_INC_PATHS))
$(info User lib paths = $(USER_LIB_PATHS))
$(info User libs = $(USER_LIBS))
$(info User symbols = $(USER_SYMBOLS))


.DEFAULT_GOAL:=all

CXXFLAGS=
CPPFLAGS=
LDFLAGS=
LDLIBS=
BIN_SUFFIX=

CPPFLAGS+=$(addprefix -I,$(INC_PATHS)) $(addprefix -I,$(USER_INC_PATHS)) -I$(LIBUTILS_INC_PATH)
CPPFLAGS+=$(addprefix -D,$(USER_SYMBOLS))
CPPFLAGS+=-MMD

CXXFLAGS+=-fmessage-length=0
CXXFLAGS+=-fno-strict-aliasing -ffunction-sections -fdata-sections
CXXFLAGS+=-std=gnu++1y
CXXFLAGS+=-Wall -Wextra -pedantic

LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=$(addprefix -L,$(USER_LIB_PATHS)) -L$(LIBUTILS_LIB_PATH)
LDLIBS+=-l$(LIBUTILS_LIB)$(BIN_SUFFIX) $(addprefix -l,$(USER_LIBS))


ifeq ($(LU_BUILD),DEBUG)
BIN_SUFFIX:=$(BIN_SUFFIX)-d
CPPFLAGS+=-DDEBUG=1
CXXFLAGS+=-O0 -g3
$(info Build = DEBUG)

else ifeq ($(LU_BUILD),RELEASE)
BIN_SUFFIX:=$(BIN_SUFFIX)-r
CPPFLAGS+=-DRELEASE=1 -DNDEBUG
CXXFLAGS+=-O3 -g0
$(info Build = RELEASE)

else
$(warning Unknown build type, defaulting to DEBUG (set LU_BUILD))
BIN_SUFFIX:=$(BIN_SUFFIX)-d
CPPFLAGS+=-DDEBUG=1
CXXFLAGS+=-O0 -g3
$(info Build = DEBUG)

endif


ifeq ($(MAKECMDGOALS),dry)
CXXFLAGS+=-fsyntax-only
$(info Performing dry run (no binary))
endif

# End setting flags


$(info Building $(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX))

ifdef WIN32
rwildcard=$(wildcard $1/$2) $(foreach d,$(wildcard $1/*),$(call rwildcard,$(d),$2))
SRC_FILES:=$(SRC_FILES) $(call rwildcard,$(SRC_PATH),*.cpp)

else ifdef UNIX
SRC_FILES:=$(shell find $(SRC_PATH) -type f -name *.cpp)

endif


OBJ_FILES:=$(SRC_FILES:$(SRC_PATH)/%.cpp=$(OUT_OBJ_PATH)/%.o)
OBJ_FILES:=$(OBJ_FILES:%.o=%$(BIN_SUFFIX).o)

DEPENDS:=$(OBJ_FILES:.o=.d)
-include $(DEPENDS)

# Create all the DIRs
OUT_DIRS:=$(sort $(dir $(OBJ_FILES)))
ifdef WIN32
$(shell mkdir $(subst /,\,$(OUT_DIRS)) bin > nul)

else ifdef UNIX
$(shell mkdir -p $(OUT_DIRS) bin)

endif


.PHONY: all clean dry

all: $(OUT_EXE_PATH)/$(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX)

dry: $(OBJ_FILES)

.SECONDEXPANSION:

$(OUT_EXE_PATH)/$(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX): $(OBJ_FILES) $(LIBUTILS_LIB_PATH)/lib$(LIBUTILS_LIB)$(BIN_SUFFIX).a
	$(info Linking objects)
	@$(CXX) $(LDFLAGS) -o $@ $(OBJ_FILES) $(LDLIBS)

$(OUT_OBJ_PATH)/%.o: $$(subst $(BIN_SUFFIX),,$(SRC_PATH)/%.cpp)
	$(info Compiling $(<))
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(info Cleaning $(<))
ifdef WIN32
	@rmdir /s /q $(OUT_OBJ_PATH) $(OUT_EXE_PATH)

else ifdef UNIX
	@rm -f $(OUT_EXE_PATH)/*
	@find $(OUT_OBJ_PATH) -type f \( -name *.o -o -name *.d \) -exec rm -f {} \;

endif
