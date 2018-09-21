#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include "thread.h"

using namespace std;

mutex box_lock;
int active_big10 = active_pac12 = 0;
int wait_big10, wait_pac12;
cv big10, pac12;

bool TURN = 0; // turn variable, 0 for big 10, 1 for pac 12

void big10_fan_enters(){
    box_lock.lock();

    while(active_pac12 > 0 || (wait_pac12 > 0 && TURN = 1)){
        big10.wait(box_lock)
    }
    active_big10++;
    wait_big10--;

    box_lock.unlock();
}

void big10_fan_leaves(){
    box_lock.lock();

    active_big10--;
    TURN = 1;
    if(active_big10 == 0)
        pac12.signal()

    box_lock.unlock();
}

void pac12_fan_enters(){
    box_lock.lock();

    while(active_big10 > 0 || (wait_big10 > 0 && TURN = 0)){
        pac12.wait(box_lock)
    }
    active_pac12++;
    wait_pac12--;

    box_lock.unlock();

}

void pac12_fan_leaves(){
    box_lock.lock();
    
    active_pac12--;
    TURN = 0;
    if(active_pac12 == 0)
        big10.signal()

    box_lock.unlock();

}



