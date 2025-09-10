CXXFLAGS := $(CXXFLAGS) --std=c++11

VL234F_SUBS = -f vl234f.sed
VL234I_SUBS = -f vl234i.sed

all: vl234f vlvec234f vl234i

vlvec234f:
	@echo "Generating VLVec234f.*"
	@echo "//\n// VLVec234f.hpp\n//\n// Copyright Andrew Willmott\n//\n" > VLVec234f.hpp
	@echo "#ifndef VL234f_H\n#define VL234f_H\n"    >> VLVec234f.hpp
	@echo "#include <cmath>"                        >> VLVec234f.hpp
	@cat ../include/VL/Defs.hpp                     >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Constants.hpp >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Math.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec2.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec3.hpp      >> VLVec234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Vec4.hpp      >> VLVec234f.hpp
	@echo "\n#endif"                                >> VLVec234f.hpp

	@echo '#include "VLVec234f.hpp"'                >  VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec2.cpp        >> VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec3.cpp        >> VLVec234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec4.cpp        >> VLVec234f.cpp

vl234f:
	@echo "Generating VL234f.*"
	@echo "//\n// VL234f.hpp\n//\n// Copyright Andrew Willmott\n//\n" > VL234f.hpp
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
	@sed $(VL234F_SUBS) ../include/VL/Quat.hpp      >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Transform.hpp >> VL234f.hpp
	@echo "\n#include <iostream>"                   >> VL234f.hpp
	@sed $(VL234F_SUBS) ../include/VL/Stream234.hpp >> VL234f.hpp
	@echo "\n#endif"                                >> VL234f.hpp

	@echo "//\n// VL234f.cpp\n//\n// Copyright Andrew Willmott\n//\n" > VL234f.cpp
	@echo '\n#include "VL234f.hpp"\n'               >> VL234f.cpp
	@echo "#include <ctype.h>"                      >> VL234f.cpp
	@echo "#include <iomanip>"                      >> VL234f.cpp
	@echo "#include <vector>"                       >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec2.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec3.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Vec4.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat2.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat3.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Mat4.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Quat.cpp          >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Transform.cpp     >> VL234f.cpp
	@sed $(VL234F_SUBS) ../src/VL/Stream234.cpp     >> VL234f.cpp

vl234i:
	@echo "Generating Vec234i.*"
	@echo "//\n// VL234i.hpp\n//\n// Copyright Andrew Willmott\n//\n" > VL234i.hpp
	@echo "#ifndef VL234i_H\n#define VL234i_H\n"    >> VL234i.hpp
	@echo "#include <cmath>"                        >> VL234i.hpp
	@cat                ../include/VL/Defs.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Constants.hpp >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Math.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec2.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec3.hpp      >> VL234i.hpp
	@sed $(VL234I_SUBS) ../include/VL/Vec4.hpp      >> VL234i.hpp
#	@echo "\n#include <iostream>"                   >> VL234i.hpp
#	@sed $(VL234I_SUBS) ../include/VL/Stream234.hpp >> VL234i.hpp
	@echo "\n#endif"                                >> VL234i.hpp

	@echo "//\n// VL234i.cpp\n//\n// Copyright Andrew Willmott\n//\n" > VL234i.cpp
	@echo '\n#include "VL234i.hpp"'                 >> VL234i.cpp
	@echo "#include <ctype.h>"                      >> VL234i.cpp
	@echo "#include <iomanip>"                      >> VL234i.cpp
	@echo "#include <vector>"                       >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec2.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec3.cpp          >> VL234i.cpp
	@sed $(VL234I_SUBS) ../src/VL/Vec4.cpp          >> VL234i.cpp
#	@sed $(VL234I_SUBS) ../src/VL/Stream234.cpp     >> VL234i.cpp

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