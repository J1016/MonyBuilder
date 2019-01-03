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

//�����ļ���·��
QString CMonyTool::sm_fileRoot = "D:\\TestQt\\MonyBuilder";

//����ű��ļ�·��
QString CMonyTool::sm_fileScriptPath = CMonyTool::sm_fileRoot + "\\scripts\\";

//������Դ�ļ�·��
QString CMonyTool::sm_fileResPath = CMonyTool::sm_fileRoot + "\\res\\";

//���������ļ�·��
QString CMonyTool::sm_fileRunPath = CMonyTool::sm_fileRoot + "\\run\\";

//���������ļ�·��
QString CMonyTool::sm_fileDataPath = CMonyTool::sm_fileRoot + "\\data\\";

//����ͼƬ�ļ�·��
QString CMonyTool::sm_fileImagePath = CMonyTool::sm_fileRoot + "\\images\\";

//���� js �ļ�·��
QString CMonyTool::sm_fileJsPath = CMonyTool::sm_fileRoot + "\\js\\";

QString CMonyTool::sm_dirsNeedCreates[10] = { CMonyTool::sm_fileScriptPath,
        CMonyTool::sm_fileResPath, CMonyTool::sm_fileRunPath, CMonyTool::sm_fileDataPath,
        CMonyTool::sm_fileImagePath};

//
//���캯�� : ����һ�� CMonyTool
//
CMonyTool::CMonyTool()
{
}

//
//�������� : �ͷ�һ�� CMonyTool
//
CMonyTool::~CMonyTool()
{

}

//��ʼ�������ļ���
//
void CMonyTool::InitDirs()
{
    for (int i = 0; i < 10; i++)
    {
        QDir dir;
        dir.mkpath(CMonyTool::sm_dirsNeedCreates[i]);
    }
}

//�� content ��Ϣ���йؼ����滻
//����1:	�ִ���Ϣ
//����2:	�ؼ�����Ϣ
//����3:	Ҫ�滻������
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

//��ȡһ�� database �ķ���
//����1:	����������
//����:	�õ��Ĵ�����
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

//����һ�� database �ķ���
//����1:	����������
//����2:	���ݶ���
//����:	�õ��Ĵ�����
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

//����һ���ı��ķ���
//����1:	·����Ϣ
//����:	�õ����ı���Ϣ
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

//��ȡһ��·���ķ���
//����1:	·���ִ�
//����:	�õ�����Ч·���ִ�
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

//��ȡ��ǰʱ���ַ���
//����:	�õ���ʱ���ַ���
//
QString CMonyTool::GainDateDatailString()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

//��ȡ��ǰʱ���ַ���
//����:	�õ���ʱ���ַ���
//
QString CMonyTool::GainDateString()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyy-MM-dd");
}

//���������ַ�����Ϣ���и�һ���ַ����ķ���
//����1:	Դ�ִ���Ϣ
//����2: ����ʾ�ַ���
//����3: �Ҳ��ʾ�ַ���
//����:	�õ����и�����
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

//����һ�� http connect �����ķ���
//����1:	�������ַ��Ϣ
//����2:	�����Ҫ�洢���ļ������ļ�����Ϣ������Ϊ NULL
//����3:	�Ƿ�Ҫ����ԭ���ļ�
//����4:	�����б���Ϣ
//����5:	����б���Ϣ
//����6:	ǰ����Ҫ post ������
//����7:	��Ҫ post �����ݣ����Ϊ NULL ��ʾ get
//����8:	�ύ��ʽ
//����:	�õ��ķ��ؽ����Ϣ�����Ϊ�㳤�ȱ�ʾʧ��
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

//����һ�� url �ַ�������ķ���
//����1:	�ַ�����Ϣ
//����2:	��������
//����:	�õ��Ľ����Ϣ
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

//����һ�� url �ַ�������ķ���
//����1:	�ַ�����Ϣ
//����2:	��������
//����:	�õ��Ľ����Ϣ
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

//ִ��һ�� js �����ķ���
//����1:	js �ļ���
//����2:	������
//����:	�õ��Ľ����Ϣ
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

//Ѱ�����ƥ��λ�õķ���
//����1:	Դͼ��
//����2:	ģ��ͼ��
//����:	�õ������ƥ���
//
QPoint CMonyTool::MatchTemplate(QString soucreFile, QString templateFile)
{
    cv::Mat imageSource = cv::imread(soucreFile.toStdString(),
            cv::IMREAD_GRAYSCALE);
    cv::Mat imageTemplate = cv::imread(templateFile.toStdString(),
            cv::IMREAD_GRAYSCALE);
    cv::Mat imageMatched;

    //ģ��ƥ��
    cv::matchTemplate(imageSource, imageTemplate, imageMatched,
            cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    //Ѱ�����ƥ��λ��
    cv::minMaxLoc(imageMatched, &minVal, &maxVal, &minLoc, &maxLoc);

    cv::Mat imageColor;
    cv::cvtColor(imageSource, imageColor, CV_GRAY2BGR);
    cv::rectangle(imageColor, cv::Point(maxLoc.x, maxLoc.y),
            cv::Point(maxLoc.x + imageTemplate.cols, maxLoc.y + imageTemplate.rows),
            (7, 249, 151), 2);

    //����һ���´���
    std::string windowName = "TestOpencv";
    //��ͼ����ʾ���´����Ĵ�����
    cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
    cv::imshow(windowName, imageSource);
    cv::imshow(windowName, imageMatched);
    cv::imshow(windowName, imageColor);
    qDebug() << "maxLoc.x = " << maxLoc.x << ",maxLoc.y = " << maxLoc.y << endl;
    return QPoint(maxLoc.x, maxLoc.y);
}

//ǿ�Ƶ�ǰ�߳����� msecs ����
//����1:	����
//
void CMonyTool::Sleep(unsigned long msecs)
{
    QThread::msleep(msecs);
}






