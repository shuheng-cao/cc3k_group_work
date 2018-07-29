#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>
#include <memory>

class Subject;

class Observer {
 public:
    // pass the Subject that called the notify method
    virtual void notify(std::shared_ptr<Subject> whoFrom) = 0;
    
    virtual ~Observer();
};
#endif
