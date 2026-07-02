CC = clang
CFLAGS = -Wall -Wextra -std=c23 -O2 -I../3_libjpp_rust/include -ldl -lm
AFLAGS = -lgnat

LIB_C = ../1_libjpp_c/libjpp.c
LIB_RS_STATIC = ../3_libjpp_rust/target/release/libjpp.a
LIB_RS_DYNAMIC = ../3_libjpp_rust/target/release/libjpp.so
LIB_ADA_STATIC = ../2_libjpp_ada/libjpp.a
LIB_ADA_DYNAMIC = ../2_libjpp_ada/libjpp.so
MAIN = test.c

all: c_library rust_static rust_dynamic ada_static ada_dynamic test

c_library: $(LIB_C) $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) $(LIB_C) -o c_library

rust_static: $(MAIN) $(LIB_RS_STATIC)
	$(CC) $(CFLAGS) $(MAIN) $(LIB_RS_STATIC) -o rust_static

rust_dynamic: $(MAIN) $(LIB_RS_DYNAMIC)
	$(CC) $(CFLAGS) $(MAIN) $(LIB_RS_DYNAMIC) -o rust_dynamic

ada_static: $(MAIN) $(LIB_ADA_STATIC)
	$(CC) $(CFLAGS) $(AFLAGS) $(MAIN) $(LIB_ADA_STATIC) -o ada_static

ada_dynamic: $(MAIN) $(LIB_ADA_STATIC)
	$(CC) $(CFLAGS) $(AFLAGS) $(MAIN) $(LIB_ADA_DYNAMIC) -o ada_dynamic

test:
	./c_library
	./rust_static
	./rust_dynamic
	./ada_static
	./ada_dynamic

clean:
	rm -f rust_static rust_dynamic ada_static ada_dynamic c_library