#ifndef MONYBUTTONPANE_H
#define MONYBUTTONPANE_H

#include "IMonyButtonListener.h"
#include <QPushButton>
#include <QString>
#include <QWidget>

class CMonyButtonPane : public QWidget
{
    Q_OBJECT

private:
    QPushButton * m_pButtons[8];                               //按钮组信息
    QString m_tags[8];                                         //按钮组标示信息
    IMonyButtonListener * m_pListener;                         //监听信息

public:
    CMonyButtonPane(QString & buttonsInfo, IMonyButtonListener * pActionListener);
    virtual ~CMonyButtonPane();

    void EnableButton(QString tag, bool bEnable);

public slots:
    void slot_buttonClicked(bool bChecked);
    void slot_buttonClicked(QString tag);
};

#endif // MONYBUTTONPANE_H
