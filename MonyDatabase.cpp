#include "MonyDatabase.h"

//
//���캯�� : ����һ�� CMonyDatabase
//
CMonyDatabase::CMonyDatabase()
{

}

//
//�������� : �ͷ�һ�� CMonyDatabase
//
CMonyDatabase::~CMonyDatabase()
{

}

//���ô洢�ĵ�¼ cookies�ķ���
//����1:	�洢�ĵ�¼ cookies
//
void CMonyDatabase::SetLoginCookies(QString loginCookies)
{
    this->m_loginCookies = loginCookies;
}

//��ȡ�洢�ĵ�¼ cookies�ķ���
//����:	�õ��Ĵ洢�ĵ�¼ cookies
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

