#include <rtw/dp/observable.h>
#include <algorithm>
#include <rtw/dp/observer.h>

namespace rtw {

void observable::attach(const std::shared_ptr<rtw::observer>& observer)
{
    observers_.push_back(observer);
}

void observable::detach(const std::shared_ptr<rtw::observer>& observer)
{
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(), [&](const std::weak_ptr<rtw::observer>& weak_observer) -> bool {
        return weak_observer.expired() || weak_observer.lock() == observer;
    }), observers_.end());
}

void observable::notify()
{
    for (std::weak_ptr<rtw::observer> weak_observer : observers_) {
        if (!weak_observer.expired()) {
            std::shared_ptr<rtw::observer> observer = weak_observer.lock();
            observer->update(*this);
        }
    }
}

} // namespace rtw