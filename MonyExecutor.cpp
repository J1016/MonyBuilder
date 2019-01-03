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
    { "base", luaopen_base }, //系统模块
    { "os", luaopen_os }, //os 模块
    { "math", luaopen_math }, //math 模块
    { "Executor", LuaOpenExecutorLibs }, //模块名字 Executor，注册函数 LuaOpenExecutorLibs
    { NULL, NULL }
};

CMonyExecutor * CMonyExecutor::sm_pExecutor;

//
//构造函数 : 构造一个 CMonyExecutor
//参数1:	代理信息
//
CMonyExecutor::CMonyExecutor(IMonyAgent * pAgent)
{
    sm_pExecutor = this;

    m_pCurrentEnv = pAgent;
    m_bBusyNow = false;
}

//
//析构函数 : 释放一个 CMonyExecutor
//
CMonyExecutor::~CMonyExecutor()
{

}

//打印控制台 log 的方法
//参数1:	打印的内容
//
void CMonyExecutor::Trace(QString content)
{
    IMonyAgent * pAgent = GetAgent();

    pAgent->AgTrace(content);
}

//清空 http 参数信息
//
void CMonyExecutor::ClearHttpParamMap()
{
    qDebug() << "void CMonyExecutor::ClearHttpParamMap" << endl;
    IMonyAgent * pAgent = GetAgent();

    pAgent->AgClearHttpParamMap();
}

//获取当前的日期毫秒数
//返回:	得到的毫秒数
//
long CMonyExecutor::DateMilli()
{
    qDebug() << "long CMonyExecutor::DateMilli" << endl;
    return QDateTime::currentDateTime().toTime_t();
}

//调用一个脚本
//参数1:	脚本名称
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
        qDebug() << QString::fromLocal8Bit("错误：脚本环境忙碌！无法 invoke 新的脚本！") << endl;

        return;
    }

    lua_State * L = m_pCurrentEnv->AgGainLuaState();
    luaL_dostring(L, content.toLatin1());
}

//获取唯一序列号信息
//返回:	得到的序列号
//
QString CMonyExecutor::Sericode()
{
    IMonyAgent * pAgent = GetAgent();

    return pAgent->AgGainSericode();
}

//获取持久化字串
//参数1:	键信息
//返回:	得到的字串值
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

    // 登录用 cookies
    if (key == "cookies")
    {
        return pDatabase->GetLoginCookies();
    }

    return NULL;
}

//保存一个 database 的方法
//参数1:	代理者名称
//参数1:	数据对象
//返回:	得到的代理者
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

    // 登录用 cookies

    if (key == "cookies")
    {
        pDatabase->SetLoginCookies(param);
    }

    CMonyTool::SaveDatabase(pAgent->AgGainSericode(), pDatabase);
}

//获取全局参数的方法
//参数1:	键信息
//返回:	得到的全局参数
//
QString CMonyExecutor::GetGlobalParam(QString key)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pGlobalMap = pAgent->AgGainGlobalParamMap();

    return (*pGlobalMap)[key];
}

//设置全局参数的方法
//参数1:	键信息
//参数1:	值信息
//
void CMonyExecutor::SetGlobalParam(QString key, QString value)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pGlobalMap = pAgent->AgGainGlobalParamMap();

    pGlobalMap->insert(key, value);
}

//设置联网参数的方法
//参数1:	键信息
//参数2:	值信息
//
void CMonyExecutor::SetHttpParam(QString key, QString value)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pParamMap = pAgent->AgGainHttpParamMap();

    pParamMap->insert(key, value);
}

//获取联网返回的参数信息
//参数1:	键
//返回:	得到的返回参数
//
QString CMonyExecutor::GetHttpResponse(QString key)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pResponseMap = pAgent->AgGainHttpResponseMap();

    return (*pResponseMap)[key];
}

//获取一个 key 下的所有 response 的方法
//参数1:	键信息
//返回:	得到的返回参数
//
QString CMonyExecutor::GetHttpResponseMerge(QString key)
{
    IMonyAgent * pAgent = GetAgent();
    QMap<QString, QString> * pResponseMap = pAgent->AgGainHttpResponseMap();

    return (*pResponseMap)[key];
}

//http 连接一次，并使用 log
//参数1:	网址信息
//参数2:	file
//参数3:	bOriginFile
//参数4:	prePostData
//参数5:	要 post 的数据
//参数6:	endPostData
//参数7:	方式信息
//返回:	得到的结果
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

//连接网址，获取为文件
//参数1:	url
//参数4:	file
//返回:	得到的结果信息
//
void CMonyExecutor::HttpGetGainFile(QString url, QString file)
{
    HttpConnectWaysWithLog(url, file, true, NULL, NULL, NULL, "GET");
}

//连接网址，获取为文件
//参数1:	url
//参数2:	prePostData
//参数3:	postData
//参数4:	file
//返回:	得到的结果信息
//
void CMonyExecutor::HttpPostGainFile(QString url, QString prePostData,
        QString postData, QString file)
{
    HttpConnectWaysWithLog(url, file, true, prePostData, postData, NULL,
            "POST");
}

//连接网址
//参数1:	url
//参数2:	logFile
//返回:	得到的结果信息
//
QString CMonyExecutor::HttpGet(QString url, QString logFile)
{
    return HttpConnectWaysWithLog(url, logFile, false, NULL, NULL, NULL,
            "GET");
}

//连接网址
//参数1:	url
//参数2:	logFile
//返回:	得到的结果信息
//
QString CMonyExecutor::HttpOptions(QString url, QString logFile)
{
    return HttpConnectWaysWithLog(url, logFile, false, NULL, NULL, NULL,
            "OPTIONS");
}

//连接网址
//参数1:	url
//参数2:	file
//返回:	得到的结果信息
//
QString CMonyExecutor::HttpPost(QString url, QString prePostData,
        QString postData, QString logFile)
{
    return HttpConnectWaysWithLog(url, logFile, false, prePostData, postData, NULL,
            "POST");
}

//比较 2 个字符串是否相等
//参数1:	source
//参数2:	dest
//
bool CMonyExecutor::StringEquals(QString source, QString dest)
{
    if (NULL == source || NULL == dest)
    {
        return false;
    }
    return source == dest;
}

//截取一个字符串的方法
//参数1:	源字串
//参数2:	左侧字串
//参数3:	右侧字串
//返回:	得到的截取字串
//
QString CMonyExecutor::StringCut(QString source, QString left, QString right)
{
    return CMonyTool::CutString(source, left, right);
}

//进行一次 url 字符串编码的方法
//参数1:	字符串信息
//参数2:	编码类型
//参数3:	是否编码类似 % 这种信息
//
QString CMonyExecutor::StringUrlEncode(QString value, QString encode,
        bool bExactly)
{
    return CMonyTool::StringUrlEncode(value, encode, bExactly);
}

//进行一次 url 字符串解码的方法
//参数1:	字符串信息
//参数2:	编码类型
//返回:	得到的结果信息
//
QString CMonyExecutor::StringUrlDecode(QString value, QString encode)
{
    return CMonyTool::StringUrlDecode(value, encode);
}

//执行一次 js 函数的方法
//参数1:	js 文件名
//参数2:	函数名
//返回:	得到的结果信息
//
QString CMonyExecutor::RunJs(QString file, QString func, QScriptValueList args)
{
    return CMonyTool::RunJs(file, func, args);
}

//寻找最佳匹配位置的方法
//参数1:	源图像
//参数2:	模板图像
//返回:	得到的最佳匹配点
//
QPoint CMonyExecutor::MatchTemplate(QString soucreFile, QString templateFile)
{
    return CMonyTool::MatchTemplate(soucreFile, templateFile);
}

//强制当前线程休眠 msecs 毫秒
//参数1:	毫秒
//
void CMonyExecutor::Sleep(unsigned long msecs)
{
    CMonyTool::Sleep(msecs);
}

//执行一次脚本测试的方法
//参数1:	预处理脚本信息
//参数2:	脚本信息
//
void CMonyExecutor::RunScript(QString preScript, QString mainScript)
{
    QString api = CMonyTool::ReadFileString(CMonyTool::sm_fileScriptPath
            + "api.lua");
    lua_State * L = m_pCurrentEnv->AgGainLuaState();

    //注册让 Lua 使用的库
    const luaL_Reg * pLuaReg = luaRegLibs;
    for (; pLuaReg->func; ++pLuaReg)
    {
        luaL_requiref(L, pLuaReg->name, pLuaReg->func, 1);
        lua_pop(L, 1);
    }

    //加载脚本，如果出错，则打印错误
    if (luaL_dostring(L, api.toLatin1()) ||
            luaL_dostring(L, preScript.toLatin1()) ||
            luaL_dostring(L, mainScript.toLatin1()))
    {
        qDebug() << lua_tostring(L, -1) << endl;
    }

    lua_close(L);
}

//获取代理对象的方法
//返回:	得到的代理对象
//
IMonyAgent * CMonyExecutor::GetAgent()
{
    return m_pCurrentEnv;
}






