APP_NAME?=chicken-farm
MODULES?=main

KERNEL?=$(shell uname -s)

ifndef MACHINE
    MACHINE_RAW:=$(shell uname -m)
    ifeq ($(MACHINE_RAW),x86_64)
        MACHINE:=x64
    else ifeq ($(MACHINE_RAW),amd64)
        MACHINE:=x64
    else ifneq (,$(findstring arm, $(MACHINE_RAW)))
        MACHINE:=arm
    else ifeq ($(MACHINE_RAW),aarch64)
        MACHINE:=arm
    else
        MACHINE:=x86
    endif
endif

RES_DIR?=res
BUILD_DIR?=build
DIST_DIR?=dist
LIB_DIRS?=deps/lib
CONFIG?=release
CXXFLAGS?=-std=c++14 -Wall
DYNAMIC_LIBS?=allegro allegro_main allegro_image