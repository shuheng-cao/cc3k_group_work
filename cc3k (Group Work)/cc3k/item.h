#ifndef __ITEM_H__
#define __ITEM_H__
#include "subject.h"
class PC;

class Item: public Subject {
    std::shared_ptr<PC> user;
public:
    Item(int x, int y);
    virtual std::shared_ptr<PC> getUser();
    virtual void setUser(std::shared_ptr<PC> whouUsed);
};

#endif
