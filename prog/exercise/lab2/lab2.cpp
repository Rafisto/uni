#include <iostream>
#include <vector>

using namespace std;

class PascalTriangleRow {
private:
    vector<int> pascalRow;
public:
    PascalTriangleRow(int n) {
        pascalRow.push_back(1);
        for (int k = 1; k < n; k++) {
            pascalRow.push_back(pascalRow.back() * (n-k)/(k+1));
        }
    }

    int getRowItemValue(int index) {
        if (0 > index) return -1;
        if (pascalRow.size() - 1 < index) return -1;
        return this->pascalRow[index];
    }
};

int main(int argc, char *argv[]) {
    PascalTriangleRow *p;
    p = new PascalTriangleRow(strtol(argv[1], nullptr, 10));
    for (int i = 2; i < argc; i++) {
        int arg = strtol(argv[i], nullptr, 10);
        printf("pascal_at_index(%d) = %d\n", arg, p->getRowItemValue(arg));
    }
    return 0;
}