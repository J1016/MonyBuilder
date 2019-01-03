#include "MonyExecutor.h"
#include "MonyExecutorRegFuncs.h"
#include <qDebug>
#include <QPoint>

#include <QScriptValueList>

int LuaGetExecutor(lua_State * L)
{
    //����һ������ָ��ŵ�stack����ظ�Lua��ʹ�ã�userdata��λ��-1
    CMonyExecutor ** pExecutor = (CMonyExecutor **)lua_newuserdata(
            L, sizeof(CMonyExecutor *));
    *pExecutor = CMonyExecutor::sm_pExecutor;

    //Lua->stack���õ�ȫ��Ԫ��λ��-1,userdataλ��-2
    luaL_getmetatable(L, "ExecutorClass");

    //��Ԫ��ֵ��λ��-2��userdata��������-1��Ԫ��
    lua_setmetatable(L, -2);

    return 1;
}

int LuaTrace(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);

    std::string content = lua_tostring(L, -1);
    (*pExecutor)->Trace(QString::fromStdString(content));

    return 0;
}

int LuaClearHttpParamMap(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    (*pExecutor)->ClearHttpParamMap();

    return 0;
}

int LuaDateMilli(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    lua_pushinteger(L, (*pExecutor)->DateMilli());

    return 1;
}

int LuaInvoke(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);

    std::string name = lua_tostring(L, -1);
    (*pExecutor)->Invoke(QString::fromStdString(name));

    return 0;
}

int LuaSericode(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    lua_pushstring(L, (*pExecutor)->Sericode().toLatin1());

    return 1;
}

int LuaArrayGet(lua_State * L)
{
    return 0;
}

int LuaArrayLength(lua_State * L)
{
    return 0;
}

int LuaInputVercode(lua_State * L)
{
    return 0;
}

int LuaFixedGainMousePwd(lua_State * L)
{
    return 0;
}

int LuaLoadDurableParam(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);

    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->LoadDurableParam(
            QString::fromStdString(key)).toLatin1());

    return 1;
}

int LuaSaveDurableParam(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string value = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);

    (*pExecutor)->SaveDurableParam(
            QString::fromStdString(key), QString::fromStdString(value));

    return 0;
}

int LuaGetGlobalParam(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);

    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->GetGlobalParam(
            QString::fromStdString(key)).toLatin1());

    return 1;
}

int LuaSetGlobalParam(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string value = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);
    (*pExecutor)->SetGlobalParam(
            QString::fromStdString(key), QString::fromStdString(value));

    return 0;
}

int LuaSetHttpParam(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string value = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);
    (*pExecutor)->SetHttpParam(
            QString::fromStdString(key), QString::fromStdString(value));

    return 0;
}

int LuaGetHttpResponse(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);

    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->GetHttpResponse(
            QString::fromStdString(key)).toLatin1());

    return 1;
}

int LuaGetHttpResponseMerge(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);

    std::string key = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->GetHttpResponseMerge(
            QString::fromStdString(key)).toLatin1());

    return 1;
}

int LuaGetHttpResponseTotal(lua_State * L)
{
    return 0;
}

int LuaHttpGetGainFile(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string file = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string url = lua_tostring(L, -1);
    lua_pop(L, 1);

    (*pExecutor)->HttpGetGainFile(
            QString::fromStdString(url), QString::fromStdString(file));

    return 0;
}

int LuaHttpPostGainFile(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);
    luaL_checktype(L, -3, LUA_TSTRING);
    luaL_checktype(L, -4, LUA_TSTRING);

    std::string file = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string postData = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string prePostData = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string url = lua_tostring(L, -1);
    lua_pop(L, 1);

    (*pExecutor)->HttpPostGainFile(
            QString::fromStdString(url), QString::fromStdString(prePostData),
            QString::fromStdString(postData), QString::fromStdString(file));

    return 0;
}

int LuaHttpGet(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string logFile = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string url = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->HttpGet(
            QString::fromStdString(url), QString::fromStdString(logFile))
            .toLatin1());

    return 1;
}

int LuaHttpOptions(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string logFile = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string url = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->HttpOptions(
            QString::fromStdString(url), QString::fromStdString(logFile))
            .toLatin1());

    return 0;
}

int LuaHttpPost(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);
    luaL_checktype(L, -3, LUA_TSTRING);
    luaL_checktype(L, -4, LUA_TSTRING);

    std::string logFile = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string postData = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string prePostData = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string url = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->HttpPost(
            QString::fromStdString(url), QString::fromStdString(prePostData),
            QString::fromStdString(postData), QString::fromStdString(logFile))
            .toLatin1());

    return 1;
}

int LuaHttpPostExt(lua_State * L)
{
    return 0;
}

int LuaMathRandomDouble(lua_State * L)
{
    return 0;
}

int LuaMathRandomDoubleValue(lua_State * L)
{
    return 0;
}

int LuaMathRandomInt(lua_State * L)
{
    return 0;
}

int LuaMathRandomIntValue(lua_State * L)
{
    return 0;
}

int LuaMathRandomString(lua_State * L)
{
    return 0;
}

int LuaStringEquals(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string dest = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string source = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushboolean(L, (*pExecutor)->StringEquals(
            QString::fromStdString(source), QString::fromStdString(dest)));

    return 1;
}

int LuaStringCut(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);
    luaL_checktype(L, -3, LUA_TSTRING);

    std::string right = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string left = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string source = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->StringCut(
            QString::fromStdString(source), QString::fromStdString(left),
            QString::fromStdString(right)).toLatin1());

    return 1;
}

int LuaStringFindLine(lua_State * L)
{
    return 0;
}

int LuaStringReplace(lua_State * L)
{
    return 0;
}

int LuaStringUrlEncode(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TBOOLEAN);
    luaL_checktype(L, -2, LUA_TSTRING);
    luaL_checktype(L, -3, LUA_TSTRING);

    bool bExactly = lua_toboolean(L, -1);
    lua_pop(L, 1);
    std::string encode = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string value = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->StringUrlEncode(
            QString::fromStdString(value), QString::fromStdString(encode),
            bExactly).toLatin1());

    return 1;
}

int LuaStringUrlDecode(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string encode = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string value = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->StringUrlDecode(
            QString::fromStdString(value), QString::fromStdString(encode))
            .toLatin1());

    return 1;
}

int LuaStringGainFileName(lua_State * L)
{
    return 0;
}

int LuaRectLimit(lua_State * L)
{
    return 0;
}

int LuaHomepageCallback(lua_State * L)
{
    return 0;
}

int LuaRunJs(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TNUMBER);

    int nIsNum;
    int nParamCount = lua_tonumberx(L, -1, &nIsNum);
    lua_pop(L, 1);
    QScriptValueList tmpArgs;
    for (int i = 0; i < nParamCount; i++)
    {
        tmpArgs << lua_tostring(L, -1);
        lua_pop(L, 1);
    }
    QScriptValueList args;
    for (int i = tmpArgs.size() - 1; i >= 0 ; i--)
    {
        args << tmpArgs.at(i);
    }

    std::string func = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string file = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, (*pExecutor)->RunJs(
            QString::fromStdString(file), QString::fromStdString(func), args)
            .toLatin1());

    return 1;
}

int LuaMatchTemplate(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TSTRING);
    luaL_checktype(L, -2, LUA_TSTRING);

    std::string templateFile = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::string soucreFile = lua_tostring(L, -1);
    lua_pop(L, 1);

    QPoint maxLoc = (*pExecutor)->MatchTemplate(
            QString::fromStdString(soucreFile), QString::fromStdString(templateFile));
    qDebug() << "maxLoc.x = " << maxLoc.x() << ",maxLoc.y = " << maxLoc.y() << endl;
    lua_pushinteger(L, maxLoc.x());
    lua_pushinteger(L, maxLoc.y());

    return 2;
}

int LuaSleep(lua_State * L)
{
    CMonyExecutor ** pExecutor = (CMonyExecutor **)luaL_checkudata(
            L, 1, "ExecutorClass");
    luaL_argcheck(L, pExecutor != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TNUMBER);

    int nIsNum;
    unsigned long msecs = lua_tointegerx(L, -1, &nIsNum);
    lua_pop(L, 1);

    (*pExecutor)->Sleep(msecs);

    return 0;
}

int LuaOpenExecutorLibs(lua_State * L)
{
    //����ȫ��Ԫ����������˶�LUA_REGISTRYINDEX�Ĳ�������Ԫ���λ��Ϊ-1
    luaL_newmetatable(L, "ExecutorClass");

    //��Ԫ����Ϊһ������ѹջ��λ��-1��ԭԪ��λ��-2
    lua_pushvalue(L, -1);

    //����-2λ��Ԫ���__index������ֵΪλ��-1��Ԫ��������λ��-1��Ԫ��ԭԪ���λ��Ϊ-1
    lua_setfield(L, -2, "__index");

    //����Ա����ע�ᵽԪ���У������ȫ��Ԫ������þ�ȫ������ˣ�
    luaL_setfuncs(L, luaRegExecutorMemberFuncs, 0);

    //ע�ṹ�캯�����±��У������ظ�Lua
    luaL_newlib(L, luaRegExecutorConstructorFuncs);

    return 1;
}
