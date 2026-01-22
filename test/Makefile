#
# Makefile for a VL test program
#

ifeq ($(origin CXX), default) # gmake defaults this to g++ instead of c++
	CXX = c++
endif
CXXFLAGS := $(CXXFLAGS) --std=c++11

check: test testint

vltest: VLTest.cpp ../include/* ../include/VL/* ../src/* ../src/VL/*
	$(CXX) $(CXXFLAGS) -I ../include ../src/LibVLfd.cpp ../src/LibVLd.cpp ../src/LibVLf.cpp VLTest.cpp -o vltest

vltestint: VLTestInt.cpp ../include/* ../include/VL/* ../src/* ../src/VL/*
	$(CXX) $(CXXFLAGS) -I ../include ../src/LibVLi.cpp ../src/LibVLf.cpp VLTestInt.cpp -o vltestint

test: vltest
	@./vltest | \
	  sed -e 's/[0-9].[0-9]*e-1[6-9]/0/g; s/-0\([^\.0-9]\)/0\1/g' > out.txt
	@echo "--- Differences from reference run (Vecfd) ----------------------"
	@-diff --strip-trailing-cr out.txt out-ref.txt
# the sed command above clips numbers like 6.12345e-16 to zero, and converts
# -0 to 0.

testint: vltestint
	@./vltestint | \
	  sed -e 's/[0-9].[0-9]*e-[01][0-9]/0/g; s/-0\([^\.0-9]\)/0\1/g' > outi.txt
	@echo "--- Differences from reference run (Veci) -----------------------"
	@-diff --strip-trailing-cr outi.txt outi-ref.txt

clean:
	@$(RM) -f out.txt outi.txt vltest vltestint *.gch
