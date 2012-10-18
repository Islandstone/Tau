#ifndef _ITIMER_INCLUDE
#define _ITIMER_INCLUDE

class ITimer {
public:
    virtual float CurrentTime() = 0;

    virtual void Start() = 0;
    virtual void Reset() = 0;
    virtual void Restart() = 0;
};

#endif
