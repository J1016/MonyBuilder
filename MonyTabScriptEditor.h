#ifndef MONYTABSCRIPTEDITOR_H
#define MONYTABSCRIPTEDITOR_H

#include "codeeditor.h"
#include "IMonyAgent.h"
#include "IMonyButtonListener.h"
#include "MonyButtonPane.h"
#include "MonyTab.h"
#include <QMap>
#include <QPlainTextEdit>
#include <QRunnable>
#include <QTextEdit>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class CMonyTabScriptEditor : public CMonyTab,
                             public IMonyButtonListener,
                             public QRunnable,
                             public IMonyAgent
{
private:
    CMonyButtonPane * m_pButtonPane;                               //主面板
    CodeEditor * m_pScriptEdit;                                    //脚本文本区域
    QTextEdit * m_pTipEdit;                                        //提示文本区域
    QMap<QString, QString> * m_pParamMap;                          //参数哈希表信息
    QMap<QString, QString> * m_pResponseMap;                       //结果哈希表信息
    QMap<QString, QString> * m_pGlobalMap;                         //全局参数哈希表信息
    lua_State * m_pLuaState;                                       //全局 lua state 信息

public:
    CMonyTabScriptEditor();
    virtual ~CMonyTabScriptEditor();

    virtual QString GainTitle();
    virtual void AgTrace(QString content);
    virtual bool AgTesting();
    virtual void AgClearHttpParamMap();
    virtual QString AgGainSericode();
    virtual QMap<QString, QString> * AgGainHttpParamMap();
    virtual QMap<QString, QString> * AgGainHttpResponseMap();
    virtual lua_State * AgGainLuaState();
    virtual QMap<QString, QString> * AgGainGlobalParamMap();
    virtual void run();
    void OpenScriptFile(QString path);
    virtual void ButtonActioned(QString tag);
};

#endif // MONYTABSCRIPTEDITOR_H
