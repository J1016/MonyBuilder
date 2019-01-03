#include "MonyDatabase.h"
#include "MonyTool.h"
#include <opencv2/opencv.hpp>
#include <QDataStream>
#include <QDateTime>
#include <QDir>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QScriptEngine>
#include <QTextStream>
#include <QThread>

//定义文件根路径
QString CMonyTool::sm_fileRoot = "D:\\TestQt\\MonyBuilder";

//定义脚本文件路径
QString CMonyTool::sm_fileScriptPath = CMonyTool::sm_fileRoot + "\\scripts\\";

//定义资源文件路径
QString CMonyTool::sm_fileResPath = CMonyTool::sm_fileRoot + "\\res\\";

//定义运行文件路径
QString CMonyTool::sm_fileRunPath = CMonyTool::sm_fileRoot + "\\run\\";

//定义数据文件路径
QString CMonyTool::sm_fileDataPath = CMonyTool::sm_fileRoot + "\\data\\";

//定义图片文件路径
QString CMonyTool::sm_fileImagePath = CMonyTool::sm_fileRoot + "\\images\\";

//定义 js 文件路径
QString CMonyTool::sm_fileJsPath = CMonyTool::sm_fileRoot + "\\js\\";

QString CMonyTool::sm_dirsNeedCreates[10] = { CMonyTool::sm_fileScriptPath,
        CMonyTool::sm_fileResPath, CMonyTool::sm_fileRunPath, CMonyTool::sm_fileDataPath,
        CMonyTool::sm_fileImagePath};

//
//构造函数 : 构造一个 CMonyTool
//
CMonyTool::CMonyTool()
{
}

//
//析构函数 : 释放一个 CMonyTool
//
CMonyTool::~CMonyTool()
{

}

//初始化所有文件夹
//
void CMonyTool::InitDirs()
{
    for (int i = 0; i < 10; i++)
    {
        QDir dir;
        dir.mkpath(CMonyTool::sm_dirsNeedCreates[i]);
    }
}

//对 content 信息进行关键字替换
//参数1:	字串信息
//参数2:	关键字信息
//参数3:	要替换的内容
//
void CMonyTool::ReplaceForWord(QString & content, QString key,
        QString value)
{
    if (NULL == value)
    {
        return;
    }
    int start = 0;
    int end, length;

    length = key.length();
    start = content.indexOf(key);
    while (start >= 0)
    {
        end = start + length;

        content.replace(start, end, value);
        start = content.indexOf(key, start);
    }
}

//获取一个 database 的方法
//参数1:	代理者名称
//返回:	得到的代理者
//
CMonyDatabase * CMonyTool::LoadDatabase(QString agentName)
{
    if (NULL == agentName)
    {
        return NULL;
    }
    if (!agentName.endsWith(".db"))
    {
        agentName += ".db";
    }
    QFile file(CMonyTool::sm_fileDataPath + agentName);
    if (!file.exists())
    {
        return NULL;
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        return NULL;
    }
    CMonyDatabase * pDataBase = new CMonyDatabase;

    QDataStream ds(&file);

    ds >> *pDataBase;

    file.close();
    return pDataBase;
}

//保存一个 database 的方法
//参数1:	代理者名称
//参数2:	数据对象
//返回:	得到的代理者
//
void CMonyTool::SaveDatabase(QString agentName, CMonyDatabase * pDatabase)
{
    if (NULL == agentName || NULL == pDatabase)
    {
        return;
    }
    if (!agentName.endsWith(".db"))
    {
        agentName += ".db";
    }
    QFile file(CMonyTool::sm_fileDataPath + agentName);
    if (!file.exists())
    {
        return;
    }
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QDataStream ds(&file);

    ds << *pDatabase;

    file.close();
}

//读入一个文本的方法
//参数1:	路径信息
//返回:	得到的文本信息
//
QString CMonyTool::ReadFileString(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return NULL;
    }

    QTextStream ts(&file);

    QString content = ts.readAll();
    file.close();
    return content;
}

//获取一次路径的方法
//参数1:	路径字串
//返回:	得到的有效路径字串
//
QString CMonyTool::GainOncePath(QString path)
{
    QFileInfo fi(path);

    if(fi.isDir())
    {
        QDir dir;
        dir.mkpath(path);
    }

    return path;
}

//获取当前时间字符串
//返回:	得到的时间字符串
//
QString CMonyTool::GainDateDatailString()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

//获取当前时间字符串
//返回:	得到的时间字符串
//
QString CMonyTool::GainDateString()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyy-MM-dd");
}

//根据左右字符串信息，切割一个字符串的方法
//参数1:	源字串信息
//参数2: 左侧标示字符串
//参数3: 右侧标示字符串
//返回:	得到的切割内容
//
QString CMonyTool::CutString(QString source, QString left, QString right)
{
    if (NULL == source || NULL == left || NULL == right)
    {
        return NULL;
    }

    int startIndex = source.indexOf(left);
    if (startIndex < 0)
    {
        return NULL;
    }
    startIndex += left.length();
    int endIndex = source.indexOf(right, startIndex);
    if (endIndex < 0)
    {
        return NULL;
    }

    return source.mid(startIndex, endIndex - startIndex);
}

//进行一次 http connect 操作的方法
//参数1:	请求的网址信息
//参数2:	如果需要存储成文件，则文件名信息，否则为 NULL
//参数3:	是否要保留原有文件
//参数4:	参数列表信息
//参数5:	结果列表信息
//参数6:	前置需要 post 的数据
//参数7:	需要 post 的数据，如果为 NULL 表示 get
//参数8:	提交方式
//返回:	得到的返回结果信息，如果为零长度表示失败
//
QString CMonyTool::HttpConnect(QString url, QString file,
        bool bOriginFile, QMap<QString, QString> * pPropMap,
        QMap<QString, QString> * pResponseMap, QString postPreData,
        QString postData, QString postEndData, QString way)
{
    QString resultString;
    QByteArray dataArray;

    QUrl httpUrl = QUrl(url);

    QNetworkRequest request;
    request.setUrl(httpUrl);

    QMapIterator<QString, QString> i(*pPropMap);
    while (i.hasNext())
    {
        QString key = i.next().key();
        QString value = pPropMap->value(key);
        QByteArray headerName;
        QByteArray headerValue;
        headerName.append(key);
        headerValue.append(value);
        request.setRawHeader(headerName, headerValue);
    }

    if (NULL != postData)
    {
        if (postData.startsWith("#file#"))
        {

        }
        else
        {
            dataArray.append(postData);
        }
    }

    QNetworkAccessManager * pManager = new QNetworkAccessManager();
#if 0
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("127.0.0.1");
    proxy.setPort(8888);
    pManager->setProxy(proxy);
#endif
    QNetworkReply * pReplay = NULL;
    if (way == "GET")
    {
        pReplay = pManager->get(request);
    }
    else if (way == "POST")
    {
        pReplay = pManager->post(request, dataArray);
    }

    QEventLoop eventLoop;
    QObject::connect(pManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray bytes = pReplay->readAll();
    pReplay->close();

    QVariant variant = pReplay->header(QNetworkRequest::ContentTypeHeader);
    QString contentType = variant.toString();
    contentType = CutString(contentType + "#", "charset=", "#");
    if (NULL != contentType)
    {
        if (contentType == "utf-8")
        {
            resultString = QString::fromLocal8Bit(bytes);
        }
    }
    else
    {
        resultString = QString(bytes);
    }

    pResponseMap->clear();
    for (int i = 0; i < pReplay->rawHeaderList().size(); i++)
    {
        QString key = QString(pReplay->rawHeaderList().at(i));
        QString value = QString(
                pReplay->rawHeader(pReplay->rawHeaderList().at(i)));
        pResponseMap->insert(key, value);
    }

    if (NULL != file)
    {
        QFile temp(file);

        if (bOriginFile)
        {
            temp.open(QIODevice::WriteOnly);
            temp.write(bytes);
            temp.close();
            resultString = "";
        }
        else
        {
            temp.open(QIODevice::WriteOnly);
            temp.write(bytes);
            temp.close();
        }
    }

    return resultString;
}

//进行一次 url 字符串编码的方法
//参数1:	字符串信息
//参数2:	编码类型
//返回:	得到的结果信息
//
QString CMonyTool::StringUrlEncode(QString value, QString encode,
        bool bExactly)
{
    if (NULL == value)
    {
        return value;
    }
    if ((!bExactly) && value.startsWith("%"))
    {
        return value;
    }
    if (NULL == encode)
    {
        return QString(value.toLatin1().toPercentEncoding());
    }

    return QString(value.toUtf8().toPercentEncoding());
}

//进行一次 url 字符串解码的方法
//参数1:	字符串信息
//参数2:	编码类型
//返回:	得到的结果信息
//
QString CMonyTool::StringUrlDecode(QString value, QString encode)
{
    if (NULL == value)
    {
        return value;
    }
    QByteArray text;
    if (NULL == encode)
    {
        text = QByteArray::fromPercentEncoding(value.toLatin1());
    }

    text = QByteArray::fromPercentEncoding(value.toUtf8());
    return text.data();
}

//执行一次 js 函数的方法
//参数1:	js 文件名
//参数2:	函数名
//返回:	得到的结果信息
//
QString CMonyTool::RunJs(QString file, QString func, QScriptValueList args)
{
    QString result;
    QString content = CMonyTool::ReadFileString(
            CMonyTool::sm_fileJsPath + file);

    QScriptEngine engine;
    QScriptValue js = engine.evaluate(content);
    QScriptValue function;
    function = engine.globalObject().property(func);
    result = function.call(QScriptValue(), args).toString();
    return result;
}

//寻找最佳匹配位置的方法
//参数1:	源图像
//参数2:	模板图像
//返回:	得到的最佳匹配点
//
QPoint CMonyTool::MatchTemplate(QString soucreFile, QString templateFile)
{
    cv::Mat imageSource = cv::imread(soucreFile.toStdString(),
            cv::IMREAD_GRAYSCALE);
    cv::Mat imageTemplate = cv::imread(templateFile.toStdString(),
            cv::IMREAD_GRAYSCALE);
    cv::Mat imageMatched;

    //模板匹配
    cv::matchTemplate(imageSource, imageTemplate, imageMatched,
            cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    //寻找最佳匹配位置
    cv::minMaxLoc(imageMatched, &minVal, &maxVal, &minLoc, &maxLoc);

    cv::Mat imageColor;
    cv::cvtColor(imageSource, imageColor, CV_GRAY2BGR);
    cv::rectangle(imageColor, cv::Point(maxLoc.x, maxLoc.y),
            cv::Point(maxLoc.x + imageTemplate.cols, maxLoc.y + imageTemplate.rows),
            (7, 249, 151), 2);

    //创建一个新窗口
    std::string windowName = "TestOpencv";
    //将图像显示都新创建的窗口中
    cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
    cv::imshow(windowName, imageSource);
    cv::imshow(windowName, imageMatched);
    cv::imshow(windowName, imageColor);
    qDebug() << "maxLoc.x = " << maxLoc.x << ",maxLoc.y = " << maxLoc.y << endl;
    return QPoint(maxLoc.x, maxLoc.y);
}

//强制当前线程休眠 msecs 毫秒
//参数1:	毫秒
//
void CMonyTool::Sleep(unsigned long msecs)
{
    QThread::msleep(msecs);
}






