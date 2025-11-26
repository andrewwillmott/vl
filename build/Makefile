#
# Makefile for VL library
#

ifeq ($(origin CXX), default) # gmake defaults this to g++ instead of c++
	CXX = c++
endif
CXXFLAGS ?= --std=c++11
OPTS=-O3 -Wall
DBG_OPTS=-DVL_DEBUG -g

PREFIX ?= /usr/local
LIB_DIR = $(PREFIX)/lib
INCLUDE_DIR = $(PREFIX)/include

VL_HEADERS = ../include/VL/* VLConfig.hpp
VL_SOURCES = ../src/VL/*

all: libvl.a libvld.a

libvl.a: LibVLf.o LibVLd.o LibVLfd.o LibVLi.o
	$(AR) rcs $@ $^

libvld.a: LibVLfD.o LibVLdD.o LibVLfdD.o LibVLiD.o
	$(AR) rcs $@ $^

# Create a copy that can be modified with site-local options before install
VLConfig.hpp: ../include/VLConfig.hpp
	cp $^ VLConfig.hpp

%.o: ../src/%.cpp $(VL_HEADERS) $(VL_SOURCES)
	$(CXX) $(CXXFLAGS) $(OPTS) -I../include -I. -c $< -o $@

%D.o: ../src/%.cpp $(VL_HEADERS) $(VL_SOURCES)
	$(CXX) $(CXXFLAGS) $(DBG_OPTS) -I../include -I. -c $< -o $@

install: libvl.a libvld.a VLConfig.hpp
	mkdir -p $(LIB_DIR)
	cp libvl.a libvld.a $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)
	cp ../include/VL234f.hpp  $(INCLUDE_DIR)
	cp ../include/VL234d.hpp  $(INCLUDE_DIR)
	cp ../include/VL234i.hpp  $(INCLUDE_DIR)
	cp ../include/VLf.hpp     $(INCLUDE_DIR)
	cp ../include/VLd.hpp     $(INCLUDE_DIR)
	cp ../include/VLfd.hpp    $(INCLUDE_DIR)
	cp ../include/VLi.hpp     $(INCLUDE_DIR)
	cp -r ../include/VL       $(INCLUDE_DIR)
	cp VLConfig.hpp           $(INCLUDE_DIR)

clean:
	rm -f *.o
	rm -f *.a
