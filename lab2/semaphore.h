#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

class semaphore {
public:
    semaphore(unsigned int);
    ~semaphore();

    void down();
    void up();

    class impl;                                 // defined by the thread library
    impl *impl_ptr;                             // used by the thread library

    /*
     * Disable the copy constructor and copy assignment operator.
     */
    semaphore(const semaphore&) = delete;
    semaphore& operator=(const semaphore&) = delete;

    /*
     * Move constructor and move assignment operator.
     */
    semaphore(semaphore&&);
    semaphore& operator=(semaphore&&);
};

#endif /* _SEMAPHORE_H */
