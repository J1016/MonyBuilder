#ifndef MONYEXECUTORREGFUNCS_H
#define MONYEXECUTORREGFUNCS_H

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

//------定义相关的全局函数------
//创建对象
int LuaGetExecutor(lua_State * L);

//打印函数
int LuaTrace(lua_State * L);

int LuaClearHttpParamMap(lua_State * L);

int LuaDateMilli(lua_State * L);

int LuaInvoke(lua_State * L);

int LuaSericode(lua_State * L);

int LuaArrayGet(lua_State * L);

int LuaArrayLength(lua_State * L);

int LuaInputVercode(lua_State * L);

int LuaFixedGainMousePwd(lua_State * L);

int LuaLoadDurableParam(lua_State * L);

int LuaSaveDurableParam(lua_State * L);

int LuaGetGlobalParam(lua_State * L);

int LuaSetGlobalParam(lua_State * L);

int LuaSetHttpParam(lua_State * L);

int LuaGetHttpResponse(lua_State * L);

int LuaGetHttpResponseMerge(lua_State * L);

int LuaGetHttpResponseTotal(lua_State * L);

int LuaHttpGetGainFile(lua_State * L);

int LuaHttpPostGainFile(lua_State * L);

int LuaHttpGet(lua_State * L);

int LuaHttpOptions(lua_State * L);

int LuaHttpPost(lua_State * L);

int LuaHttpPostExt(lua_State * L);

int LuaMathRandomDouble(lua_State * L);

int LuaMathRandomDoubleValue(lua_State * L);

int LuaMathRandomInt(lua_State * L);

int LuaMathRandomIntValue(lua_State * L);

int LuaMathRandomString(lua_State * L);

int LuaStringEquals(lua_State * L);

int LuaStringCut(lua_State * L);

int LuaStringFindLine(lua_State * L);

int LuaStringReplace(lua_State * L);

int LuaStringUrlEncode(lua_State * L);

int LuaStringUrlDecode(lua_State * L);

int LuaStringGainFileName(lua_State * L);

int LuaRectLimit(lua_State * L);

int LuaHomepageCallback(lua_State * L);

int LuaRunJs(lua_State * L);

int LuaMatchTemplate(lua_State * L);

int LuaSleep(lua_State * L);

//------注册全局函数供Lua使用------
//构造函数
static const luaL_Reg luaRegExecutorConstructorFuncs[] =
{
    { "get", LuaGetExecutor },
    { NULL, NULL }
};

//成员操作函数
static const luaL_Reg luaRegExecutorMemberFuncs[] =
{
    { "trace", LuaTrace },
    { "clearHttpParamMap", LuaClearHttpParamMap },
    { "dateMilli", LuaDateMilli },
    { "invoke", LuaInvoke },
    { "sericode", LuaSericode },
    { "arrayGet", LuaArrayGet },
    { "arrayLength", LuaArrayLength },
    { "inputVercode", LuaInputVercode },
    { "fixedGainMousePwd", LuaFixedGainMousePwd },
    { "loadDurableParam", LuaLoadDurableParam },
    { "saveDurableParam", LuaSaveDurableParam },
    { "getGlobalParam", LuaGetGlobalParam },
    { "setGlobalParam", LuaSetGlobalParam },
    { "setHttpParam", LuaSetHttpParam },
    { "getHttpResponse", LuaGetHttpResponse },
    { "getHttpResponseMerge", LuaGetHttpResponseMerge },
    { "getHttpResponseTotal", LuaGetHttpResponseTotal },
    { "httpGetGainFile", LuaHttpGetGainFile },
    { "httpPostGainFile", LuaHttpPostGainFile },
    { "httpGet", LuaHttpGet },
    { "httpOptions", LuaHttpOptions },
    { "httpPost", LuaHttpPost },
    { "httpPostExt", LuaHttpPostExt },
    { "mathRandomDouble", LuaMathRandomDouble },
    { "mathRandomDoubleValue", LuaMathRandomDoubleValue },
    { "mathRandomInt", LuaMathRandomInt },
    { "mathRandomIntValue", LuaMathRandomIntValue },
    { "mathRandomString", LuaMathRandomString },
    { "stringEquals", LuaStringEquals },
    { "stringCut", LuaStringCut },
    { "stringFindLine", LuaStringFindLine },
    { "stringReplace", LuaStringReplace },
    { "stringUrlEncode", LuaStringUrlEncode },
    { "stringUrlDecode", LuaStringUrlDecode },
    { "stringGainFileName", LuaStringGainFileName },
    { "rectLimit", LuaRectLimit },
    { "homepageCallback", LuaHomepageCallback },
    { "runJs", LuaRunJs },
    { "matchTemplate", LuaMatchTemplate },
    { "sleep", LuaSleep },
    //{ "__gc", lua_auto_gc }, //注册Lua内部函数__gc
    //{ "__tostring", lua_student2string },
    { NULL, NULL },
};


int LuaOpenExecutorLibs(lua_State * L);

#endif // MONYEXECUTORREGFUNCS_H
