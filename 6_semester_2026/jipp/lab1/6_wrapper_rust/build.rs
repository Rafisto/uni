use std::env;

fn main() {
    let lib_type = env::var("JPP_LINK_MODE").unwrap_or_else(|_| "c_static".to_string());

    match lib_type.as_str() {
        "c_static" => {
            println!("cargo:rustc-link-search=native=../1_libjpp_c");
            println!("cargo:rustc-link-lib=static=jpp");
        }
        "c_dynamic" => {
            println!("cargo:rustc-link-search=native=../1_libjpp_c");
            println!("cargo:rustc-link-lib=dylib=jpp");
            println!("cargo:rustc-link-arg=-Wl,-rpath,../1_libjpp_c");
        }
        "ada_static" => {
            println!("cargo:rustc-link-search=native=../2_libjpp_ada");
            println!("cargo:rustc-link-lib=static=jpp");
            println!("cargo:rustc-link-lib=gnat");
        }
        "ada_dynamic" => {
            println!("cargo:rustc-link-search=native=../2_libjpp_ada");
            println!("cargo:rustc-link-lib=dylib=jpp");
            println!("cargo:rustc-link-arg=-Wl,-rpath,../2_libjpp_ada");
            println!("cargo:rustc-link-lib=gnat");
        }
        "rust_library" => {
            println!("cargo:rustc-link-search=native=../3_libjpp_rust/target/release");
            println!("cargo:rustc-link-lib=static=jpp");
        }
        _ => panic!("Unknown JPP_LINK_MODE: {}", lib_type),
    }

    println!("cargo:rustc-link-lib=m");
    println!("cargo:rerun-if-env-changed=JPP_LINK_MODE");
}