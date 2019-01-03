#ifndef MONYAGENT_H
#define MONYAGENT_H

#include <QString>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class IMonyAgent
{
public:
    virtual void AgTrace(QString content) = 0;
    virtual bool AgTesting() = 0;
    virtual void AgClearHttpParamMap() = 0;
    virtual QString AgGainSericode() = 0;
    virtual QMap<QString, QString> * AgGainHttpParamMap() = 0;
    virtual QMap<QString, QString> * AgGainHttpResponseMap() = 0;
    virtual lua_State * AgGainLuaState() = 0;
    virtual QMap<QString, QString> * AgGainGlobalParamMap() = 0;
};

#endif // MONYAGENT_H
