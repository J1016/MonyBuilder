#include "IMonyAgent.h"
#include "MonyDatabase.h"
#include "MonyExecutor.h"
#include "MonyExecutorRegFuncs.h"
#include "MonyTool.h"
#include <qDebug>
#include <QDateTime>
#include <QScriptEngine>

static const luaL_Reg luaRegLibs[] =
{
    { "base", luaopen_base }, //ϵͳģ��
    { "os", luaopen_os }, //os ģ��
    { "math", luaopen_math }, //math ģ��
    { "Executor", LuaOpenExecutorLibs }, //ģ������ Executor��ע�ắ�� LuaOpenExecutorLibs
    { NULL, NULL }
};

CMonyExecutor * CMonyExecutor::sm_pExecutor;

//
//���캯�� : ����һ�� CMonyExecutor
//����1:	������Ϣ
//
CMonyExecutor::CMonyExecutor(IMonyAgent * pAgent)
{
    sm_pExecutor = this;

    m_pCurrentEnv = pAgent;
    m_bBusyNow = false;
}

//
//�������� : �ͷ�һ�� CMonyExecutor
//
CMonyExecutor::~CMonyExecutor()
{

}

//��ӡ����̨ log �ķ���
//����1:	��ӡ������
//
void CMonyExecutor::Trace(QString content)
{
    IMonyAgent * pAgent = GetAgent();

    pAgent->AgTrace(content);
}

//��� http ������Ϣ
//
void CMonyExecutor::ClearHttpParamMap()
{
    qDebug() << "void CMonyExecutor::ClearHttpParamMap" << endl;
    IMonyAgent * pAgent = GetAgent();

    pAgent->AgClearHttpParamMap();
}

//��ȡ��ǰ�����ں�����
//����:	�õ��ĺ�����
//
long CMonyExecutor::DateMilli()
{
    qDebug() << "long CMonyExecutor::DateMilli" << endl;
    return QDateTime::currentDateTime().toTime_t();
}

//����һ���ű�
//����1:	�ű�����
//
void CMonyExecutor::Invoke(QString name)
{
    QString content = CMonyTool::ReadFileString(CMonyTool::sm_fileScriptPath
            + name);
    if (NULL == content)
    {
        return;
    }
    if (m_bBusyNow)
    {
        qDebug() << QString::fromLocal8Bit("���󣺽ű�����æµ���޷� invoke �µĽű���") << endl;

        return;
    }

    lua_State * L = m_pCurrentEnv->AgGainLuaState();
    luaL_dostring(L, content.toLatin1());
}

//��ȡΨһ���к���Ϣ
//����:	�õ������к�
//
QString CMonyExecutor::Sericode()
{
    IMonyAgent * pAgent = GetAgent();

    return pAgent->AgGainSericode();
}

//��ȡ�־û��ִ�
//����1:	����Ϣ
//����:	�õ����ִ�ֵ
//
QString CMonyExecutor::LoadDurableParam(QString key)
{
    if (NULL == key)
    {
        return NULL;
    }

    IMonyAgent * pAgent = GetAgent();
    CMonyDatabase * pDatabase = CMonyTool::LoadDatabase(pAgent->AgGainSericode());

    if (NULL == pDatabase)
    {
        return NULL;
    }

    // ��¼�� cookies
    if (key == "cookies")
    {
        return pDatabase->GetLoginCookies();
    }

    return NULL;
}

//����һ�� database �ķ���
//����1:	����������
//����1:	���ݶ���
//����:	�õ��Ĵ�����
//
void CMonyExecutor::SaveDurableParam(QString key, QString param)
{
    if (NULL == key)
    {
        return;
    }

    IMonyAgent * pAgent = GetAgent();
    CMonyDatabase * pDatabase = CMonyTool::LoadDatabase(pAgent->AgGainSericode());

    if (NULL == pDatabase)
    {
        pDatabase = new CMonyDatabase();
    }

    // ��¼�� cookies

    if (key == "cookies")
    {
        pDatabase->SetLoginCookies(param);
    }

    CMonyTool::SaveDatabase(pAgent->AgGainSericode(), pDatabase);
}

//��ȡȫ�ֲ����ķ���
//����1:	����Ϣ
//����:	�õ���ȫ�ֲ���
//
QString CMonyExecutor::GetGlobalParam(QString key)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pGlobalMap = pAgent->AgGainGlobalParamMap();

    return (*pGlobalMap)[key];
}

//����ȫ�ֲ����ķ���
//����1:	����Ϣ
//����1:	ֵ��Ϣ
//
void CMonyExecutor::SetGlobalParam(QString key, QString value)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pGlobalMap = pAgent->AgGainGlobalParamMap();

    pGlobalMap->insert(key, value);
}

//�������������ķ���
//����1:	����Ϣ
//����2:	ֵ��Ϣ
//
void CMonyExecutor::SetHttpParam(QString key, QString value)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pParamMap = pAgent->AgGainHttpParamMap();

    pParamMap->insert(key, value);
}

//��ȡ�������صĲ�����Ϣ
//����1:	��
//����:	�õ��ķ��ز���
//
QString CMonyExecutor::GetHttpResponse(QString key)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pResponseMap = pAgent->AgGainHttpResponseMap();

    return (*pResponseMap)[key];
}

//��ȡһ�� key �µ����� response �ķ���
//����1:	����Ϣ
//����:	�õ��ķ��ز���
//
QString CMonyExecutor::GetHttpResponseMerge(QString key)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pResponseMap = pAgent->AgGainHttpResponseMap();

    return (*pResponseMap)[key];
}

//http ����һ�Σ���ʹ�� log
//����1:	��ַ��Ϣ
//����2:	file
//����3:	bOriginFile
//����4:	prePostData
//����5:	Ҫ post ������
//����6:	endPostData
//����7:	��ʽ��Ϣ
//����:	�õ��Ľ��
//
QString CMonyExecutor::HttpConnectWaysWithLog(QString url, QString file,
        bool bOriginFile, QString prePostData, QString postData,
        QString endPostData, QString way)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pParamMap = pAgent->AgGainHttpParamMap();
    QMap<QString, QString> * pResponseMap = pAgent->AgGainHttpResponseMap();

    if (NULL != file)
    {
        file = CMonyTool::sm_fileRunPath + file;
    }

    if (!url.startsWith("http") && !url.startsWith("https"))
    {
        url = "http://" + url;
    }

    return CMonyTool::HttpConnect(url, file, bOriginFile, pParamMap,
            pResponseMap, prePostData, postData, endPostData, way);
}

//������ַ����ȡΪ�ļ�
//����1:	url
//����4:	file
//����:	�õ��Ľ����Ϣ
//
void CMonyExecutor::HttpGetGainFile(QString url, QString file)
{
    HttpConnectWaysWithLog(url, file, true, NULL, NULL, NULL, "GET");
}

//������ַ����ȡΪ�ļ�
//����1:	url
//����2:	prePostData
//����3:	postData
//����4:	file
//����:	�õ��Ľ����Ϣ
//
void CMonyExecutor::HttpPostGainFile(QString url, QString prePostData,
        QString postData, QString file)
{
    HttpConnectWaysWithLog(url, file, true, prePostData, postData, NULL,
            "POST");
}

//������ַ
//����1:	url
//����2:	logFile
//����:	�õ��Ľ����Ϣ
//
QString CMonyExecutor::HttpGet(QString url, QString logFile)
{
    return HttpConnectWaysWithLog(url, logFile, false, NULL, NULL, NULL,
            "GET");
}

//������ַ
//����1:	url
//����2:	logFile
//����:	�õ��Ľ����Ϣ
//
QString CMonyExecutor::HttpOptions(QString url, QString logFile)
{
    return HttpConnectWaysWithLog(url, logFile, false, NULL, NULL, NULL,
            "OPTIONS");
}

//������ַ
//����1:	url
//����2:	file
//����:	�õ��Ľ����Ϣ
//
QString CMonyExecutor::HttpPost(QString url, QString prePostData,
        QString postData, QString logFile)
{
    return HttpConnectWaysWithLog(url, logFile, false, prePostData, postData, NULL,
            "POST");
}

//�Ƚ� 2 ���ַ����Ƿ����
//����1:	source
//����2:	dest
//
bool CMonyExecutor::StringEquals(QString source, QString dest)
{
    if (NULL == source || NULL == dest)
    {
        return false;
    }
    return source == dest;
}

//��ȡһ���ַ����ķ���
//����1:	Դ�ִ�
//����2:	����ִ�
//����3:	�Ҳ��ִ�
//����:	�õ��Ľ�ȡ�ִ�
//
QString CMonyExecutor::StringCut(QString source, QString left, QString right)
{
    return CMonyTool::CutString(source, left, right);
}

//����һ�� url �ַ�������ķ���
//����1:	�ַ�����Ϣ
//����2:	��������
//����3:	�Ƿ�������� % ������Ϣ
//
QString CMonyExecutor::StringUrlEncode(QString value, QString encode,
        bool bExactly)
{
    return CMonyTool::StringUrlEncode(value, encode, bExactly);
}

//����һ�� url �ַ�������ķ���
//����1:	�ַ�����Ϣ
//����2:	��������
//����:	�õ��Ľ����Ϣ
//
QString CMonyExecutor::StringUrlDecode(QString value, QString encode)
{
    return CMonyTool::StringUrlDecode(value, encode);
}

//ִ��һ�� js �����ķ���
//����1:	js �ļ���
//����2:	������
//����:	�õ��Ľ����Ϣ
//
QString CMonyExecutor::RunJs(QString file, QString func, QScriptValueList args)
{
    return CMonyTool::RunJs(file, func, args);
}

//Ѱ�����ƥ��λ�õķ���
//����1:	Դͼ��
//����2:	ģ��ͼ��
//����:	�õ������ƥ���
//
QPoint CMonyExecutor::MatchTemplate(QString soucreFile, QString templateFile)
{
    return CMonyTool::MatchTemplate(soucreFile, templateFile);
}

//ǿ�Ƶ�ǰ�߳����� msecs ����
//����1:	����
//
void CMonyExecutor::Sleep(unsigned long msecs)
{
    CMonyTool::Sleep(msecs);
}

//ִ��һ�νű����Եķ���
//����1:	Ԥ����ű���Ϣ
//����2:	�ű���Ϣ
//
void CMonyExecutor::RunScript(QString preScript, QString mainScript)
{
    QString api = CMonyTool::ReadFileString(CMonyTool::sm_fileScriptPath
            + "api.lua");
    lua_State * L = m_pCurrentEnv->AgGainLuaState();

    //ע���� Lua ʹ�õĿ�
    const luaL_Reg * pLuaReg = luaRegLibs;
    for (; pLuaReg->func; ++pLuaReg)
    {
        luaL_requiref(L, pLuaReg->name, pLuaReg->func, 1);
        lua_pop(L, 1);
    }

    //���ؽű�������������ӡ����
    if (luaL_dostring(L, api.toLatin1()) ||
            luaL_dostring(L, preScript.toLatin1()) ||
            luaL_dostring(L, mainScript.toLatin1()))
    {
        qDebug() << lua_tostring(L, -1) << endl;
    }

    lua_close(L);
}

//��ȡ�������ķ���
//����:	�õ��Ĵ������
//
IMonyAgent * CMonyExecutor::GetAgent()
{
    return m_pCurrentEnv;
}






