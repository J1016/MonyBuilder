#ifndef MONYTOOL_H
#define MONYTOOL_H

#include "MonyDatabase.h"
#include <QPoint>
#include <QScriptValueList>
#include <QString>

//
//���幤����
//
class CMonyTool
{
public:
    static QString sm_fileRoot;                                     //�ļ���·��
    static QString sm_fileScriptPath;                               //�ű��ļ�·��
    static QString sm_fileResPath;                                  //��Դ�ļ�·��
    static QString sm_fileRunPath;                                  //�����ļ�·��
    static QString sm_fileDataPath;                                 //�����ļ�·��
    static QString sm_fileImagePath;                                //ͼƬ�ļ�·��
    static QString sm_fileJsPath;                                   //js �ļ�·��
    static QString sm_dirsNeedCreates[10];                          //����Ҫ�������ļ���

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
