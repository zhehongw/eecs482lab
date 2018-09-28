#include "HelloWorld.h"

int main() {
    HelloWorld greeter;
    for (int i = 0; i < 3; ++i) {
      greeter.speak();
    }
    return 0;
}
