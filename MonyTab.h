#ifndef MONYTAB_H
#define MONYTAB_H

#include <QString>
#include <QWidget>

class CMonyTab : public QWidget
{
public:
    CMonyTab();
    virtual ~CMonyTab();

    virtual QString GainTitle() = 0;
};

#endif // MONYTAB_H
