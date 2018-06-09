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
    std::cout << sizeof(std::vector<int>::value_type) << std::endl;

    int* p = nullptr;
    std::cout << SizeOf(p) << std::endl;

    Test t;
    std::cout << SizeOf(t) << std::endl;
    std::cout << SizeOf(&t) << std::endl;

    std::unordered_map<int, int> umii{{0, 0}};
    std::cout << "umii: " << sizeof(umii) << ", " << SizeOf(umii) << std::endl;

    std::string s = "123";
    std::cout << "s: " << SizeOf(s) << std::endl;

    std::vector<int> vi = {1, 2};
    std::cout << "vi: " << SizeOf(vi) << std::endl;

    std::deque<std::unordered_set<std::string>> duss{{"1"}};
    std::cout << "duss: " << sizeof(duss) << ", " << SizeOf(duss) << std::endl;

    std::vector<std::vector<std::string>> vvi = {{"023"}};
    std::cout << SizeOf(vvi) << std::endl;

    std::map<int, std::string> mis = {{0, "1"}};
    std::cout << sizeof(mis) << ", " << SizeOf(mis) << std::endl;

    std::map<int, std::vector<int>> mivi  {{0, {0, 1}}};
    std::cout << sizeof(mivi) << ", " << SizeOf(mivi) << std::endl;

    std::vector<std::map<int, std::vector<std::string>>> vmii{{{0, {"11", "223"}}}};
    std::cout << "vmii: " << sizeof(vmii) << ", " << SizeOf(vmii) << std::endl;
    return 0;
}


