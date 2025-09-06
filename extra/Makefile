CXXFLAGS := $(CXXFLAGS) --std=c++11

VL234F_SUBS = -f vl234f.sed
VL234I_SUBS = -f vl234i.sed

all: vl234f vlvec234f vl234i

vlvec234f:
	@echo "generating vlvec234f"
	@echo "//\n// VLVec234f.h\n//\n// Copyright Andrew Willmott\n//\n\n" > VLVec234f.h
	@echo "#include <cmath>"                      >> VLVec234f.h
	@cat ../include/VL/Defs.h                     >> VLVec234f.h
	@sed $(VL234F_SUBS) ../include/VL/Constants.h >> VLVec234f.h
	@sed $(VL234F_SUBS) ../include/VL/Math.h      >> VLVec234f.h
	@sed $(VL234F_SUBS) ../include/VL/Vec2.h      >> VLVec234f.h
	@sed $(VL234F_SUBS) ../include/VL/Vec3.h      >> VLVec234f.h
	@sed $(VL234F_SUBS) ../include/VL/Vec4.h      >> VLVec234f.h

	@echo '#include "VLVec234f.h"'         >  VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec4.cpp >> VLVec234f.cpp

vl234f:
	@echo "generating vl234f"
	@echo "//\n// VL234f.h\n//\n// Copyright Andrew Willmott\n//\n\n" > VL234f.h
	@echo "#include <cmath>"                      >> VL234f.h
	@cat                ../include/VL/Defs.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Constants.h >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Math.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Vec2.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Vec3.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Vec4.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Mat2.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Mat3.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Mat4.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Quat.h      >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Transform.h >> VL234f.h
	@echo "\n#include <iostream>"                 >> VL234f.h
	@sed $(VL234F_SUBS) ../include/VL/Stream234.h >> VL234f.h

	@echo "//\n// VL234f.cpp\n//\n// Copyright Andrew Willmott\n//\n\n" > VL234f.cpp
	@echo '\n#include "VL234f.h"\n'             >> VL234f.cpp
	@echo "#include <ctype.h>"                  >> VL234f.cpp
	@echo "#include <iomanip>"                  >> VL234f.cpp
	@echo "#include <vector>"                   >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec4.cpp      >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat2.cpp      >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat3.cpp      >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat4.cpp      >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Quat.cpp      >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Transform.cpp >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Stream234.cpp >> VL234f.cpp

vl234i:
	@echo "generating vl234i"
	@echo "//\n// VL234i.h\n//\n// Copyright Andrew Willmott\n//\n\n" > VL234i.h
	@echo "#include <cmath>"                        >> VL234i.h
	@cat                ../include/VL/Defs.h        >> VL234i.h
	@sed $(VL234I_SUBS) ../include/VL/Constants.h   >> VL234i.h
	@sed $(VL234I_SUBS) ../include/VL/Math.h        >> VL234i.h
	@sed $(VL234I_SUBS) ../include/VL/Vec2.h        >> VL234i.h
	@sed $(VL234I_SUBS) ../include/VL/Vec3.h        >> VL234i.h
	@sed $(VL234I_SUBS) ../include/VL/Vec4.h        >> VL234i.h

	@echo "//\n// VL234i.cpp\n//\n// Copyright Andrew Willmott\n//\n" > VL234i.cpp
	@echo '\n#include "VL234i.h"'          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec4.cpp >> VL234i.cpp

test:
	$(CXX) $(CXXFLAGS) -I. -I../h VL234Test.cpp VL234f.cpp -o vl234test
	@-./vl234test | \
	  sed -e 's/[0-9].[0-9]*e-[01][78]/0/g; s/-0\([^\.0-9]\)/0\1/g' > out.txt
	@-echo \
	  "--- Differences from reference run ------------------------------"
	@-diff out-ref.txt out.txt

clean:
	rm -f *.gch
	rm -f VL234f.* VLVec234f.* VL234i.* out.txt