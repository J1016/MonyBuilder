#ifndef MONYBUTTONLISTENER_H
#define MONYBUTTONLISTENER_H

#include <QString>

class IMonyButtonListener
{
public:
    virtual void ButtonActioned(QString tag) = 0;
};

#endif // MONYBUTTONLISTENER_H
