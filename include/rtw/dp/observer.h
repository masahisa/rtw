#ifndef RTW_OBSERVER_H
#define RTW_OBSERVER_H

namespace rtw {

class observable;

class observer {
private:
public:
    virtual ~observer() = default;
public:
    virtual void update(observable&) = 0;
};

} // namespace rtw

#endif // RTW_OBSERVER_H