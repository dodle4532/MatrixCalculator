#include <iostream>
#include "matrix.h"

using namespace std;



int main(int argc, char *argv[])
{
    // std::cout << "Enter matrix\n";
    // std::vector<std::string> vec;
    // std::string str = "\n";
    // while (str != "") {
    //     std::getline(std::cin, str);
    //     if (str == "") {
    //         break;
    //     }
    //     vec.push_back(str);
    // }
    // Matrix m(vec);
    // std::cout << m;

    std::vector<std::vector<float>> v = {{1, 1},
                                        {1, 4}};
    Matrix m(v);
    std::cout << m.pow(-1);
    return 0;
}
