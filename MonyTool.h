#ifndef MONYTOOL_H
#define MONYTOOL_H

#include "MonyDatabase.h"
#include <QPoint>
#include <QScriptValueList>
#include <QString>

//
//定义工具类
//
class CMonyTool
{
public:
    static QString sm_fileRoot;                                     //文件根路径
    static QString sm_fileScriptPath;                               //脚本文件路径
    static QString sm_fileResPath;                                  //资源文件路径
    static QString sm_fileRunPath;                                  //运行文件路径
    static QString sm_fileDataPath;                                 //数据文件路径
    static QString sm_fileImagePath;                                //图片文件路径
    static QString sm_fileJsPath;                                   //js 文件路径
    static QString sm_dirsNeedCreates[10];                          //所有要创建的文件夹

public:
    CMonyTool();
    virtual ~CMonyTool();

    static void InitDirs();
    static void ReplaceForWord(QString & content, QString key,
            QString value);
    static CMonyDatabase * LoadDatabase(QString agentName);
    static void SaveDatabase(QString agentName, CMonyDatabase * pDatabase);
    static QString ReadFileString(QString path);
    static QString GainOncePath(QString path);
    static QString GainDateDatailString();
    static QString GainDateString();
    static QString CutString(QString source, QString left, QString right);
    static QString HttpConnect(QString url, QString file,
            bool bOriginFile, QMap<QString, QString> * pPropMap,
            QMap<QString, QString> * pResponseMap, QString postPreData,
            QString postData, QString postEndData, QString way);
    static QString StringUrlEncode(QString value, QString encode,
            bool bExactly);
    static QString StringUrlDecode(QString value, QString encode);
    static QString RunJs(QString file, QString func, QScriptValueList args);
    static QPoint MatchTemplate(QString soucreFile, QString templateFile);
    static void Sleep(unsigned long msecs);
};

#endif // MONYTOOL_H
