#include <string>

using namespace std;

/** doxygen comment 1* */

int s1 = 1; // simple comment
int s2 = 2; /* simple comment */
/* 
    multiline comments
    should be deleted
*/
string s3 = "test//not a comment";

// test comment

string s4 = "test/*not a comment*/";

/* test comment */

string s5 = "//escape\\//\\//not a comment\\\\";
string s6 = "string \
    //this is not a comment"; // but this is a comment
string s7 = "string \
    /* comment test/* comment"; // but this is a comment
string s8 = "string //not a comment\\\
    //not a comment escaped \
    with \
    a dozen \
    strings"; // this is a comment
string s9 = "";
char s10 = '\\';
char s11 = '\\'; //comment
string s12 = "\\\"//not a comment"; //comment
string s13 = "/*not a comment*/";
string s14 = "this is not a comment"; // \
    but this is a comment
int d1 = 1;
/**
    doxygen comment 2*
*/
int d2 = 1;
/*! doxygen comment 3 */
int d3 = 1;
/*!
    doxygen comment 4
*/
int d4 = 1;
//! doxygen comment 5
int d5 = 1;
/// doxygen comment 6 \
    and the end of the comment
int d6 = 0;
