#
# Makefile for a VL test program
#

ifeq ($(origin CXX), default) # gmake defaults this to g++ instead of c++
	CXX = c++
endif
CXXFLAGS := $(CXXFLAGS) --std=c++11

check: clean vltest
	@-./vltest | \
	  sed -e 's/[0-9].[0-9]*e-1[6-9]/0/g; s/-0\([^\.0-9]\)/0\1/g' > out.txt
	@-echo \
	  "--- Differences from reference run ------------------------------"
	@-diff out.txt out-ref.txt
# the sed command above clips numbers like 6.12345e-16 to zero, and converts
# -0 to 0.

vltest: VLTest.cpp ../include/* ../include/VL/* ../src/* ../src/VL/*
	$(CXX) $(CXXFLAGS) -I ../include -I . ../src/LibVLfd.cpp ../src/LibVLd.cpp ../src/LibVLf.cpp VLTest.cpp -o vltest

clean:
	rm -f out.txt
