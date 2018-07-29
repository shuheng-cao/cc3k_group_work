#include "subject.h"
#include "observer.h"
using namespace std;

Subject::Subject(int x, int y) {
    position = make_pair(x, y);
}


void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}


void Subject::notifyObservers() {
    for (auto &ob: observers) {
        ob->notify(shared_ptr<Subject>(this, [](Subject*){}));
    }
}


void Subject::detach(std::shared_ptr<Observer> o) {
    for (auto it = observers.begin(); it == observers.end(); it++) {
        if (*it == o) {
            observers.erase(it);
        }
    }
}


void Subject::clearAllObservers() {
    observers.clear();
}


int Subject::getX() {
    return position.first;
}


int Subject::getY(){
    return position.second;
}


pair<int, int> Subject::getPosn() {
    return position;
}


void Subject::setX(int n) {
    position.first = n;
}


void Subject::setY(int n) {
    position.second = n;
}


Subject::~Subject() {
    
}
