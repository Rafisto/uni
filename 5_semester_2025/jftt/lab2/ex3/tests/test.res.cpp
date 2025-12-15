#include <string>

using namespace std;

int s1 = 1;
int s2 = 2;
string s3 = "test//not a comment";

string s4 = "test/*not a comment*/";

string s5 = "//escape\\//\\//not a comment\\\\";
string s6 = "string \
    //this is not a comment";
string s7 = "string \
    /* comment test/* comment";
string s8 = "string //not a comment\\\
    //not a comment escaped \
    with \
    a dozen \
    strings";
string s9 = "";
char s10 = '\\';
char s11 = '\\';
string s12 = "\\\"//not a comment";
string s13 = "/*not a comment*/";
string s14 = "this is not a comment";
int d1 = 1;
int d2 = 1;
int d3 = 1;
int d4 = 1;
int d5 = 1;
int d6 = 0;
