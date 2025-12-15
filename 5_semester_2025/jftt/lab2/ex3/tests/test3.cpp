//#include <iostream>

/**
 * header-name
 */
//! Handling of `//`, `/*`, `*/` is implementation and platform dependent
//! #include <never/*comment*/>
//! #include "never/*comment*/"
#include <not//comment>
#include "not//comment"


//! Comments within `<>` get removed outside #include, but paths with a space are handled
//! platform specific (Windows includes properly, MacOS doesn't)
// #ifndef INCFILE
// #   define INCFILE <iostream/*redacted*/>
// #endif
// #include INCFILE
#include <iostream>

//*
//*/

 // 
int q;

// Comment\
void nuke(void);

/// TEST MACRO
#define TEST 1//2137

/*! Important function */
int/**/f(){return 42;}

/**
 * Documentation
 */
int main(void) {
    // > 1
    std::cout << TEST << "\n";

    printf("/* foo bar");
    //*/" bar();

    // > /* is great */ and so is //
    std::cout << "/* is great */"
        << " and so is //"\
    "\n";

    // > :oa
    std::cout << ":o"
    // o:
    "a\n";

    // >42
    std::cout << f()/**/ << "\n";
}

