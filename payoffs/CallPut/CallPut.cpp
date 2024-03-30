#pragma once

#include <iostream>

extern "C" {
  
  __declspec(dllexport) int test(void(*callback)()) {
    std::cout << "I'm a vanilla call/put" << std::endl;
    callback();
    return 0;
  }

}
