#ifndef MONYTABPAGECREATE_H
#define MONYTABPAGECREATE_H

#include "MonyTab.h"
#include <QString>

class CMonyTabPageCreate : public CMonyTab
{
public:
    CMonyTabPageCreate();
    virtual ~CMonyTabPageCreate();

    virtual QString GainTitle();
};

#endif // MONYTABPAGECREATE_H
