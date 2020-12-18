#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <rtw/dp/observer.h>
#include <rtw/dp/observable.h>

class test_observable : public rtw::observable {
};

class test_observer : public rtw::observer {
private:
    int id_;
public:
    test_observer (int id) : id_{ id } {}
    void update (rtw::observable& o) {
        std::cout << "notified" << id_ << std::endl;
    }
};

int main()
{
    std::shared_ptr<test_observable> sub = std::make_shared<test_observable>();
    std::shared_ptr<test_observer> obj1 = std::make_shared<test_observer>(1);
    std::shared_ptr<test_observer> obj2 = std::make_shared<test_observer>(2);

    sub->attach(obj1);
    sub->attach(obj2);

    int counter = 0;
    while (counter < 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        sub->notify();
        counter++;
        if (obj1 && counter == 5) {
            obj1.reset();
        }
        if (obj2 && counter == 7) {
            sub->detach(obj2);
        }
    }

    sub->detach(obj1);

    return 0;
}