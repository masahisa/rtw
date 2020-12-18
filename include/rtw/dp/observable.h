#ifndef RTW_OBSERVABLE_H
#define RTW_OBSERVABLE_H

#include <memory>
#include <vector>

namespace rtw {

class observer;

class observable {
private:
    std::vector<std::weak_ptr<rtw::observer>> observers_;
public:
    virtual ~observable() = default;
public:
    void attach(const std::shared_ptr<rtw::observer>& observer);
    void detach(const std::shared_ptr<rtw::observer>& observer);
    void notify();
};

} // namespace rtw

#endif // RTW_OBSERVABLE_H