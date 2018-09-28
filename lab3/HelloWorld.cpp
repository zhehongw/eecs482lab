#include "HelloWorld.h"
#include "HelloWorldImpl.h"

HelloWorld::HelloWorld() {
    // allocate an instance of HelloWorldImpl and remember its address in pImpl
    pImpl = new HelloWorldImpl;
}
    
HelloWorld::~HelloWorld() {
    // delete the instance of HelloWorldImpl that you allocated above
    delete pImpl;
}

void HelloWorld::speak() {
    // call your impl's hello() function 
    pImpl -> hello();
}
