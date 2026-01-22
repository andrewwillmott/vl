#
# Makefile for generating cut-down single header/source variants
#

ifeq ($(origin CXX), default) # gmake defaults this to g++ instead of c++
	CXX = c++
endif
CXXFLAGS := $(CXXFLAGS) --std=c++11

VL234F_SUBS = -f vl234f.sed
VL234I_SUBS = -f vl234i.sed

all: vl234f vlvec234f vl234i vlvec234i
no_io: vl234f_no_io vlvec234f vl234i_no_io vlvec234i

vlvec234f:
	@echo "Generating VLVec234f.*"
	@echo "//\n// VLVec234f.hpp\n//\n// Andrew Willmott\n//\n" > VLVec234f.hpp
	@echo "#ifndef VL234f_H\n#define VL234f_H\n"    >> VLVec234f.hpp
	@echo "#include <cmath>"                        >> VLVec234f.hpp
	@cat                ../include/VL/Defs.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Constants.hpp >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Math.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec2.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec3.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec4.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Swizzle.hpp   >> VLVec234f.hpp
	@echo "\n#endif"                                >> VLVec234f.hpp

	@echo "//\n// VLVec234f.cpp\n//\n// Andrew Willmott\n//\n" > VLVec234f.cpp
	@echo '\n#include "VLVec234f.hpp"'              >> VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec2.cpp          >> VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec3.cpp          >> VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec4.cpp          >> VLVec234f.cpp

vl234f_base:
	@echo "Generating VL234f.*"
	@echo "//\n// VL234f.hpp\n//\n// Andrew Willmott\n//\n" > VL234f.hpp
	@echo "#ifndef VL234f_H\n#define VL234f_H\n"    >> VL234f.hpp
	@echo "#include <cmath>"                        >> VL234f.hpp
	@cat                ../include/VL/Defs.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Constants.hpp >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Math.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec2.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec3.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec4.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Mat2.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Mat3.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Mat4.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Swizzle.hpp   >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Quat.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Transform.hpp >> VL234f.hpp

	@echo "//\n// VL234f.cpp\n//\n// Andrew Willmott\n//\n" > VL234f.cpp
	@echo '\n#include "VL234f.hpp"\n'               >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec2.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec3.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec4.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat2.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat3.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat4.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Quat.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Transform.cpp     >> VL234f.cpp

vl234f_no_io: vl234f_base
	@echo "\n#endif"                                >> VL234f.hpp

vl234f: vl234f_base
	@echo "\n#include <stdio.h>"                    >> VL234f.hpp
	@echo "\n#include <string.h>"                   >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/PrintBase.hpp >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Print234.hpp  >> VL234f.hpp
	@echo "\n#include <iostream>"                   >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Stream234.hpp >> VL234f.hpp
	@echo "\n#endif"                                >> VL234f.hpp

	@sed $(VL234F_SUBS) ../include/VL/PrintBase.hpp >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Print234.cpp      >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/PrintBase.cpp     >> VL234f.cpp
	@echo "#include <ctype.h>"                      >> VL234f.cpp
	@echo "#include <iomanip>"                      >> VL234f.cpp
	@echo "#include <vector>"                       >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Stream234.cpp     >> VL234f.cpp

vlvec234i:
	@echo "Generating VLVec234i.*"
	@echo "//\n// VLVec234i.hpp\n//\n// Andrew Willmott\n//\n" > VLVec234i.hpp
	@echo "#ifndef VL234i_H\n#define VL234i_H\n"    >> VLVec234i.hpp
	@echo "#include <cmath>"                        >> VLVec234i.hpp
	@cat                ../include/VL/Defs.hpp      >> VLVec234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Constants.hpp >> VLVec234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Math.hpp      >> VLVec234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec2.hpp      >> VLVec234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec3.hpp      >> VLVec234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec4.hpp      >> VLVec234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Swizzle.hpp   >> VLVec234i.hpp
	@echo "\n#endif"                                >> VLVec234i.hpp

	@echo "//\n// VLVec234i.cpp\n//\n// Andrew Willmott\n//\n" > VLVec234i.cpp
	@echo '\n#include "VLVec234i.hpp"'              >> VLVec234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec2.cpp          >> VLVec234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec3.cpp          >> VLVec234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec4.cpp          >> VLVec234i.cpp

vl234i_base:
	@echo "Generating VL234i.*"
	@echo "//\n// VL234i.hpp\n//\n// Andrew Willmott\n//\n" > VL234i.hpp
	@echo "#ifndef VL234i_H\n#define VL234i_H\n"    >> VL234i.hpp
	@echo "#include <cmath>"                        >> VL234i.hpp
	@cat                ../include/VL/Defs.hpp      >> VL234i.hpp
	@echo "#define VL_NO_REAL"                      >> VL234i.hpp
	@echo "#define VL_PRINT_INT"                    >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Constants.hpp >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Math.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec2.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec3.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec4.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Mat2.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Mat3.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Mat4.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Swizzle.hpp   >> VL234i.hpp

	@echo "//\n// VL234i.cpp\n//\n// Andrew Willmott\n//\n" > VL234i.cpp
	@echo '\n#include "VL234i.hpp"\n'               >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec2.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec3.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec4.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Mat2.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Mat3.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Mat4.cpp          >> VL234i.cpp

vl234i_no_io: vl234i_base
	@echo "#undef VL_NO_REAL\n#undef VL_PRINT_INT"  >> VL234i.hpp
	@echo "\n#endif"                                >> VL234i.hpp

vl234i: vl234i_base
	@echo "\n#include <stdio.h>"                    >> VL234i.hpp
	@echo "\n#include <string.h>"                   >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/PrintBase.hpp >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Print234.hpp  >> VL234i.hpp
	@echo "\n#include <iostream>"                   >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Stream234.hpp >> VL234i.hpp
	@echo "\n#undef VL_NO_REAL\n#undef VL_PRINT_INT"  >> VL234i.hpp
	@echo "\n#endif"                                >> VL234i.hpp

	@sed $(VL234I_SUBS) ../include/VL/PrintBase.hpp >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Print234.cpp      >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/PrintBase.cpp     >> VL234i.cpp
	@echo "#include <ctype.h>"                      >> VL234i.cpp
	@echo "#include <iomanip>"                      >> VL234i.cpp
	@echo "#include <vector>"                       >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Stream234.cpp     >> VL234i.cpp

testf: vl234f
	$(CXX) $(CXXFLAGS) -I. VL234fTest.cpp VL234f.cpp -o vl234f_test
	@-./vl234f_test | \
	  sed -e 's/[0-9].[0-9]*e-[01][0-9]/0/g; s/-0\([^\.0-9]\)/0\1/g' > outf.txt
	@-echo \
	  "--- Differences from reference run ------------------------------"
	@-diff outf-ref.txt outf.txt

testi: vl234i vl234f
	$(CXX) $(CXXFLAGS) -I. VL234iTest.cpp VL234i.cpp VL234f.cpp -o vl234i_test
	@-./vl234i_test | \
	  sed -e 's/[0-9].[0-9]*e-[01][0-9]/0/g; s/-0\([^\.0-9]\)/0\1/g' > outi.txt
	@-echo \
	  "--- Differences from reference run ------------------------------"
	@-diff outi-ref.txt outi.txt

test: testf testi

check: all
	@echo "Checking that all files compile..."
	$(CXX) $(CXXFLAGS) -c VL234f.cpp VLVec234f.cpp VL234i.cpp VLVec234i.cpp

clean:
	@$(RM) -f *.gch
	@$(RM) -f VL234f.* VLVec234f.* VL234i.* VLVec234i.*
	@$(RM) -f vl234f_test vl234i_test outf.txt outi.txt
