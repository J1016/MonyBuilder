#include "MonyDatabase.h"

//
//构造函数 : 构造一个 CMonyDatabase
//
CMonyDatabase::CMonyDatabase()
{

}

//
//析构函数 : 释放一个 CMonyDatabase
//
CMonyDatabase::~CMonyDatabase()
{

}

//设置存储的登录 cookies的方法
//参数1:	存储的登录 cookies
//
void CMonyDatabase::SetLoginCookies(QString loginCookies)
{
    this->m_loginCookies = loginCookies;
}

//获取存储的登录 cookies的方法
//返回:	得到的存储的登录 cookies
//
QString CMonyDatabase::GetLoginCookies()
{
    return this->m_loginCookies;
}

QDataStream & operator>>(QDataStream & in, CMonyDatabase & data)
{
    in >> data.m_loginCookies;
    return in;
}

QDataStream & operator<<(QDataStream & out, const CMonyDatabase & data)
{
    out << data.m_loginCookies;
    return out;
}

