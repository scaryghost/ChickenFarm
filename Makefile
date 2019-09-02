.PHONY: build clean

include config.mk

define mkdir =
mkdir -p $@
endef

MODULES_SRC_DIR=$(addsuffix /cpp, $(addprefix src/, $(MODULES)))
GEN:=
SRCS:=$(foreach src_dir, $(MODULES_SRC_DIR), $(shell find $(src_dir) -name \*.cpp))
RES_SRCS:=$(shell find $(RES_DIR) -name \*.\*)
EXPORT_HEADERS:=$(foreach module, $(addprefix src/, $(MODULES)), $(shell find $(module) -maxdepth 1 -name \*.h))

CXXFLAGS+=-Isrc -Ideps/include
ifeq ($(CONFIG),debug)
    CXXFLAGS+=-g
    LD_FLAGS:=-g
else ifeq ($(CONFIG),release)
    CXXFLAGS+=-O3
    LD_FLAGS:=-s
else
    $(error Invalid value for "CONFIG", must be 'release' or 'debug')
endif

LD_FLAGS+=-shared -Wl,

ifeq ($(MACHINE),x86)
    ARCH=-m32
else ifeq ($(MACHINE),x64)
    ARCH=-m64
else ifeq ($(MACHINE),arm)
    ARCH=-marm
else
    $(error Unrecognized "MACHINE" value, use 'x86', 'x64', or 'arm')
endif

ifndef NO_MULTILIB
    CXXFLAGS+=$(ARCH)
else
    ARCH=
endif

LD_FLAGS:=$(addprefix -L,$(LIB_DIRS)) -Wl,-Bstatic $(addprefix -l,$(STATIC_LIBS)) -Wl,-Bdynamic $(addprefix -l,$(DYNAMIC_LIBS))

REAL_DIST_DIR:=$(DIST_DIR)/$(CONFIG)/app/$(MACHINE)
REAL_BUILD_DIR:=$(BUILD_DIR)/$(MACHINE)/$(CONFIG)
MODULES_BUILD_DIR:=$(addprefix $(REAL_BUILD_DIR)/, $(MODULES_SRC_DIR))
RES_DIST_DIR:=$(addprefix $(REAL_DIST_DIR)/, $(RES_DIR))

RES_OBJS:=$(foreach src, $(RES_SRCS), $(addprefix $(REAL_DIST_DIR)/, $(src)))
OBJS:=$(addprefix $(REAL_BUILD_DIR)/, $(SRCS:%.cpp=%.o))
DEPS:=$(OBJS:%.o=%.d)

APP_OUTPUT:=$(REAL_DIST_DIR)/$(APP_NAME)

build: $(APP_OUTPUT) $(RES_OBJS)

$(REAL_BUILD_DIR)/%.o: %.cpp
	$(CXX) -MMD -MP -MF "$(@:%.o=%.d)" -c -o $@ $(CXXFLAGS) $<

-include $(addsuffix /config.mk, $(MODULES_SRC_DIR))
-include $(DEPS)

$(MODULES_BUILD_DIR):
	$(mkdir)

$(REAL_DIST_DIR):
	$(mkdir)

$(RES_DIST_DIR):
	$(mkdir)

$(RES_DIST_DIR)%:: $(RES_DIR)% | $(RES_DIST_DIR)
	cp $< $@
$(OBJS): | $(MODULES_BUILD_DIR)
$(APP_OUTPUT): $(OBJS) | $(REAL_DIST_DIR) 
	$(CXX) -o $@ $^ $(LD_FLAGS)

clean:
	rm -Rf $(BUILD_DIR) $(DIST_DIR) $(GEN)