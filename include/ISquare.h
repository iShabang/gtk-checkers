#ifndef _CHECKERS_ISQUARE_H_
#define _CHECKERS_ISQUARE_H_

#include "IPiece.h"
#include "Position.h"

#include <memory>

class ISquare {
public:
    virtual ~ISquare() {}
    virtual bool hasPiece() = 0;
    virtual void setPiece(std::shared_ptr<IPiece> p) = 0;
    virtual std::shared_ptr<IPiece> removePiece() = 0;
    virtual const std::shared_ptr<IPiece> piece() const = 0;
    virtual const Position pos() const = 0;
    virtual void setMovable(bool value) = 0;
    virtual void setPrepped(bool value) = 0;
    virtual void setValid(bool value) = 0;
    virtual bool movable() = 0;
    virtual bool valid() = 0;
    virtual bool prepped() = 0;
};


#endif //_CHECKERS_ISQUARE_H_
