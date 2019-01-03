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
    QPushButton * m_pButtons[8];                               //��ť����Ϣ
    QString m_tags[8];                                         //��ť���ʾ��Ϣ
    IMonyButtonListener * m_pListener;                         //������Ϣ

public:
    CMonyButtonPane(QString & buttonsInfo, IMonyButtonListener * pActionListener);
    virtual ~CMonyButtonPane();

    void EnableButton(QString tag, bool bEnable);

public slots:
    void slot_buttonClicked(bool bChecked);
    void slot_buttonClicked(QString tag);
};

#endif // MONYBUTTONPANE_H
