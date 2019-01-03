#ifndef MONYDATABASE_H
#define MONYDATABASE_H

#include <QDataStream>
#include <QObject>
#include <QString>

class CMonyDatabase : public QObject
{
    Q_OBJECT

private:
    QString m_loginCookies;                      //´æ´¢µÄµÇÂ¼ cookies

public:
    CMonyDatabase();
    virtual ~CMonyDatabase();

    void SetLoginCookies(QString loginCookies);

    QString GetLoginCookies();

    friend QDataStream & operator>>(QDataStream & in, CMonyDatabase & data);
    friend QDataStream & operator<<(QDataStream & out, const CMonyDatabase & data);
};

#endif // MONYDATABASE_H
