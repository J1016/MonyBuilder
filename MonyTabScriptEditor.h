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
    CMonyButtonPane * m_pButtonPane;                               //�����
    CodeEditor * m_pScriptEdit;                                    //�ű��ı�����
    QTextEdit * m_pTipEdit;                                        //��ʾ�ı�����
    QMap<QString, QString> * m_pParamMap;                          //������ϣ����Ϣ
    QMap<QString, QString> * m_pResponseMap;                       //�����ϣ����Ϣ
    QMap<QString, QString> * m_pGlobalMap;                         //ȫ�ֲ�����ϣ����Ϣ
    lua_State * m_pLuaState;                                       //ȫ�� lua state ��Ϣ

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
