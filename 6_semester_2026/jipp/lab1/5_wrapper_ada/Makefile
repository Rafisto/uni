ADA      = gnatmake
AFLAGS   = -gnat2022 -gnata
LDFLAGS  = -ldl -lm

LIB_C_STATIC   = ../1_libjpp_c/libjpp.a
LIB_C_DYNAMIC  = ../1_libjpp_c/libjpp.so
LIB_RS_STATIC  = ../3_libjpp_rust/target/release/libjpp.a
LIB_RS_DYNAMIC = ../3_libjpp_rust/target/release/libjpp.so
LIB_ADA_STATIC = ../2_libjpp_ada/libjpp.a
LIB_ADA_DYNAMIC = ../2_libjpp_ada/libjpp.so

MAIN_ADA = test.adb
SPEC_ADA = wrapper.ads

all: c_static c_dynamic ada_library rust_static rust_dynamic test

c_static: $(MAIN_ADA) $(SPEC_ADA)
	$(ADA) $(AFLAGS) $(MAIN_ADA) -o c_static -largs $(LIB_C_STATIC) $(LDFLAGS)

c_dynamic: $(MAIN_ADA) $(SPEC_ADA)
	$(ADA) $(AFLAGS) $(MAIN_ADA) -o c_dynamic \
	  -largs $(LIB_C_DYNAMIC) $(LDFLAGS)

ada_library: $(MAIN_ADA) $(SPEC_ADA) $(LIB_ADA_STATIC)
	$(ADA) $(AFLAGS) $(MAIN_ADA) -o ada_library \
	  -largs $(LIB_ADA_STATIC) $(LDFLAGS)

rust_static: $(MAIN_ADA) $(SPEC_ADA) $(LIB_RS_STATIC)
	$(ADA) $(AFLAGS) $(MAIN_ADA) -o rust_static \
	  -largs $(LIB_RS_STATIC) $(LDFLAGS)

rust_dynamic: $(MAIN_ADA) $(SPEC_ADA) $(LIB_RS_DYNAMIC)
	$(ADA) $(AFLAGS) $(MAIN_ADA) -o rust_dynamic \
	  -largs $(LIB_RS_DYNAMIC) $(LDFLAGS)

test:
	./c_static
	./c_dynamic
	./ada_library
	./rust_static
	./rust_dynamic

clean:
	rm -f *.o *.ali c_static c_dynamic ada_library rust_static rust_dynamic