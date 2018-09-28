#include <iostream>
#include "HelloWorld.h"
#include "HelloWorldImpl.h"

void HelloWorld::HelloWorldImpl::hello() {
    count ++;
    std::cout << "Hello world!!! " << "Called " << count << " times." << std::endl;
}
