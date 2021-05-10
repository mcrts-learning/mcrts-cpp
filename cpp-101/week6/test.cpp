#include <string>
#include <iostream>
#include <vector>
#include <array>
using namespace std;


int main() {
array<array<string, 1>, 3> s = { "a", "a", "c"};
s[2][0] = "d";


    return 0;
}

