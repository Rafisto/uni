#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "generator.hpp"

using namespace std;

int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <number_of_keys>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int kpos = generate_random_key(n);

    vector<int> result = generate_random_keys(n);

    cout << n << endl;
    cout << kpos << endl;

    for (const auto &key : result)
    {
        cout << key << " ";
    }
    cout << endl;

    return 0;
}