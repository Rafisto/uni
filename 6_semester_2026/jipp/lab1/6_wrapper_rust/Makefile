all: c_static c_dynamic ada_static ada_dynamic rust_library test

c_static:
	JPP_LINK_MODE=c_static cargo build --release
	cp target/release/rust_bin ./c_static

c_dynamic:
	JPP_LINK_MODE=c_dynamic cargo build --release
	cp target/release/rust_bin ./c_dynamic

ada_static:
	JPP_LINK_MODE=ada_static cargo build --release
	cp target/release/rust_bin ./ada_static

ada_dynamic:
	JPP_LINK_MODE=ada_dynamic cargo build --release
	cp target/release/rust_bin ./ada_dynamic

rust_library:
	JPP_LINK_MODE=rust_library cargo build --release
	cp target/release/rust_bin ./rust_library

test: all
	./c_static
	./c_dynamic
	./ada_static
	./ada_dynamic
	./rust_library

clean:
	rm -f c_static c_dynamic ada_static ada_dynamic rust_library
	cargo clean