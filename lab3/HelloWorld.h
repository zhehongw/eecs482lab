#ifndef _HELLOWORLD_H
#define _HELLOWORLD_H

/*
 *  *  This code is all the user of the library has to include.
 *   */
class HelloWorld {
public:
    HelloWorld();

    ~HelloWorld();

    void speak();

    class HelloWorldImpl;
    HelloWorldImpl *pImpl;
};
#endif // _HELLOWORLD_H
