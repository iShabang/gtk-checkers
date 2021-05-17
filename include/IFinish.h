#ifndef _CHECKERS_IFINISH_H_
#define _CHECKERS_IFINISH_H_

class IFinish {
public:
    virtual ~IFinish() {}

    virtual void finished() = 0;
};

#endif //_CHECKERS_IFINISH_H_
