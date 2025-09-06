#
# Makefile for VL library
#

CXXFLAGS ?= --std=c++11 
OPTS=-O3
DBG_OPTS=-DVL_DEBUG -g

PREFIX ?= /usr/local
LIB_DIR = $(PREFIX)/lib
INCLUDE_DIR = $(PREFIX)/include

VL_HEADERS = ../include/VL/* VLConfig.h
VL_SOURCES = ../src/VL/* 

libvl.a: LibVLf.o LibVLd.o LibVLfd.o LibVLi.o
	$(AR) rcs $@ $^

libvld.a: LibVLfD.o LibVLdD.o LibVLfdD.o LibVLiD.o
	$(AR) rcs $@ $^

VLConfig.h: ../include/VL/VLConfigBase.h
	cp $^ VLConfig.h

%.o: ../src/%.cpp $(VL_HEADERS) $(VL_SOURCES)
	$(CXX) $(CXXFLAGS) $(OPTS) -I../include -I. -c $< -o $@

%D.o: ../src/%.cpp $(VL_HEADERS) $(VL_SOURCES)
	$(CXX) $(CXXFLAGS) $(DBG_OPTS) -I../include -I. -c $< -o $@

install: libvl.a libvld.a VLConfig.h
	mkdir -p $(LIB_DIR)
	cp libvl.a libvld.a $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR)
	cp ../include/VL234f.h  $(INCLUDE_DIR)	
	cp ../include/VL234d.h  $(INCLUDE_DIR)	
	cp ../include/VL234i.h  $(INCLUDE_DIR)	
	cp ../include/VLf.h     $(INCLUDE_DIR)	
	cp ../include/VLd.h     $(INCLUDE_DIR)	
	cp ../include/VLfd.h    $(INCLUDE_DIR)	
	cp ../include/VLi.h     $(INCLUDE_DIR)	
	cp -r ../include/VL     $(INCLUDE_DIR)
	cp VLConfig.h           $(INCLUDE_DIR)

clean:
	rm -f *.o
	rm -f *.a
