//
//  main.cpp
//  SizeOf
//
//  Created by Lin Luo on 6/8/18.
//  Copyright © 2018 Linfinity. All rights reserved.
//

#include <iostream>
#include "SizeOf.h"

struct Test {
    size_t SizeOf() const { return 42; }
};

int main()
{
    int* p = nullptr;
    std::cout << SizeOf(p) << std::endl;

    Test t;
    std::cout << SizeOf(t) << std::endl;

    std::string s = "123";
    std::cout << SizeOf(s) << std::endl;

    std::vector<int> vi = {1, 2};
    std::cout << SizeOf(vi) << std::endl;

    std::vector<std::vector<std::string>> vvi = {{"023"}};
    std::cout << SizeOf(vvi) << std::endl;

    std::map<int, std::string> mis = {{0, "1"}};
    std::cout << sizeof(mis) << ", " << SizeOf(mis) << std::endl;

    std::map<int, std::vector<int>> mivi  {{0, {0, 1}}};
    std::cout << sizeof(mivi) << ", " << SizeOf(mivi) << std::endl;

    std::vector<std::map<int, std::vector<std::string>>> vmii{{{0, {"1", "22"}}}};
    std::cout << sizeof(vmii) << ", " << SizeOf(vmii) << std::endl;
    return 0;
}

