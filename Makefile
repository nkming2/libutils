INC_PATH=inc
SRC_PATH=src
OUT_LIB=utils
OUT_LIB_PATH=lib
OUT_OBJ_PATH=obj

CC=gcc
CXX=g++
AR=ar

# Additional include dirs
ALL_INC_PATHS=$(INC_PATH) $(SRC_PATH)

# Additional symbols
ALL_SYMBOLS=

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

$(info User include paths = $(ALL_INC_PATHS))
$(info User symbols = $(ALL_SYMBOLS))

.DEFAULT_GOAL:=all

CXXFLAGS=
CPPFLAGS=
ARFLAGS=
BIN_SUFFIX=

CPPFLAGS+=$(addprefix -I,$(ALL_INC_PATHS))
CPPFLAGS+=$(addprefix -D,$(ALL_SYMBOLS))
CPPFLAGS+=-MMD

CXXFLAGS+=-std=gnu++11
CXXFLAGS+=-fmessage-length=0
CXXFLAGS+=-fno-strict-aliasing
CXXFLAGS+=-pedantic -Wall -Wextra

ifeq ($(LU_BUILD),DEBUG)
BIN_SUFFIX:=$(BIN_SUFFIX)-d
CPPFLAGS+=-DDEBUG
CXXFLAGS+=-O0 -g3
$(info Build = DEBUG)

else ifeq ($(LU_BUILD),RELEASE)
BIN_SUFFIX:=$(BIN_SUFFIX)-r
CPPFLAGS+=-DRELEASE -DNDEBUG
CXXFLAGS+=-O3 -g0
$(info Build = RELEASE)

else
$(warning Unknown build type, defaulting to DEBUG (set LU_BUILD))
BIN_SUFFIX:=$(BIN_SUFFIX)-d
CPPFLAGS+=-DDEBUG
CXXFLAGS+=-O0 -g3
$(info Build = DEBUG)

endif

ifeq ($(MAKECMDGOALS),dry)
CXXFLAGS+=-fsyntax-only
$(info Performing dry run (no binary))
endif

ARFLAGS+=-r

# End setting flags

$(info Building lib$(OUT_LIB)$(BIN_SUFFIX).a)

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

OUT_DIRS:=$(sort $(dir $(OBJ_FILES)))
ifdef WIN32
$(shell mkdir $(subst /,\,$(OUT_DIRS)) lib > nul)

else ifdef UNIX
$(shell mkdir -p $(OUT_DIRS) lib)

endif

.PHONY: all clean dry

all: $(OUT_LIB_PATH)/lib$(OUT_LIB)$(BIN_SUFFIX).a

dry: $(OBJ_FILES)

.SECONDEXPANSION:

$(OUT_LIB_PATH)/lib$(OUT_LIB)$(BIN_SUFFIX).a: $(OBJ_FILES)
	$(info Packing library)
	@$(AR) $(ARFLAGS) $@ $^

$(OUT_OBJ_PATH)/%.o: $$(subst $(BIN_SUFFIX),,$(SRC_PATH)/%.cpp)
	$(info Compiling $(<))
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(info Cleaning $(<))
ifdef WIN32
	@rmdir /s /q $(OUT_OBJ_PATH) $(OUT_LIB_PATH)

else ifdef UNIX
	@rm -f $(OUT_LIB_PATH)/*.a
	@find $(OUT_OBJ_PATH) -type f \( -name *.o -o -name *.d \) -exec rm -f {} \;

endif