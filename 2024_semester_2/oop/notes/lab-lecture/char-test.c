// char* in rodata <- trying to change it will result in segmentation fault

int main(void) {
    char* s = "Ala";
    s[0] = 'a';
}
