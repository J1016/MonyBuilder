#ifndef MONYEXECUTOR_H
#define MONYEXECUTOR_H

#include "IMonyAgent.h"
#include <QPoint>
#include <QScriptValueList>
#include <QString>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class CMonyExecutor
{
public:
    static CMonyExecutor * sm_pExecutor;

private:
    IMonyAgent * m_pCurrentEnv;
    bool m_bBusyNow;

public:
    CMonyExecutor(IMonyAgent * pAgent);
    virtual ~CMonyExecutor();

    void Trace(QString content);
    void ClearHttpParamMap();
    long DateMilli();
    void Invoke(QString name);
    QString Sericode();
    QString LoadDurableParam(QString key);
    void SaveDurableParam(QString key, QString param);
    QString GetGlobalParam(QString key);
    void SetGlobalParam(QString key, QString value);
    void SetHttpParam(QString key, QString value);
    QString GetHttpResponse(QString key);
    QString GetHttpResponseMerge(QString key);
    QString HttpConnectWaysWithLog(QString url, QString file,
            bool bOriginFile, QString prePostData, QString postData,
            QString endPostData, QString way);
    void HttpGetGainFile(QString url, QString file);
    void HttpPostGainFile(QString url, QString prePostData,
            QString postData, QString file);
    QString HttpGet(QString url, QString logFile);
    QString HttpOptions(QString url, QString logFile);
    QString HttpPost(QString url, QString prePostData,
            QString postData, QString logFile);
    bool StringEquals(QString source, QString dest);
    QString StringCut(QString source, QString left, QString right);
    QString StringUrlEncode(QString value, QString encode,
            bool bExactly);
    QString StringUrlDecode(QString value, QString encode);
    QString RunJs(QString file, QString function, QScriptValueList args);
    QPoint MatchTemplate(QString soucreFile, QString templateFile);
    void Sleep(unsigned long msecs);
    void RunScript(QString preScript, QString mainScript);
    IMonyAgent * GetAgent();
};

#endif // MONYEXECUTOR_H
