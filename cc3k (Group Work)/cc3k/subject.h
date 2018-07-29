#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>
#include <memory>

class Observer;

class Subject {
    std::pair<int, int> position;
    std::vector<std::shared_ptr<Observer>> observers;
 public:
    Subject(int x, int y);
    void attach(std::shared_ptr<Observer> o);
    void detach(std::shared_ptr<Observer> o);
    void clearAllObservers();
    void notifyObservers();
    int getX();
    int getY();
    std::pair<int, int> getPosn();
    void setX(int n);
    void setY(int n);
    virtual ~Subject() = 0;
};


#endif
