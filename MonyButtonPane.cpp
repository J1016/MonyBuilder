#include "borderlayout.h"
#include <flowlayout.h>
#include "MonyButtonPane.h"
#include <qDebug>
#include <QPushButton>
#include <QGridLayout>

#include <QSignalMapper>

//
//构造函数 : 构造一个 CMonyButtonPane
//
CMonyButtonPane::CMonyButtonPane(QString & buttonsInfo,
        IMonyButtonListener * pActionListener)
{
    QStringList infomations = buttonsInfo.split("#");
//    m_pButtons = new QPushButton[infomations.size()];
//    m_tags = new QString[infomations.size()];

    int nGridNumX = 0;
    int nGridNumY = 0;

    nGridNumY = 1;
    nGridNumX = infomations.size();

    QWidget * pWidget = new QWidget;
    QGridLayout * pLayout = new QGridLayout;
    pWidget->setLayout(pLayout);

    QSignalMapper * pSignalMapper = new QSignalMapper(this);
    for (int i = 0; i < infomations.size(); i++)
    {
        qDebug() << infomations.at(i) << endl;
        QStringList infomation = infomations.at(i).split(",");
        qDebug() << infomation.at(0) << endl;
        m_pButtons[i] = new QPushButton(infomation[0]);
        m_tags[i] = infomation[1];
        pSignalMapper->setMapping(m_pButtons[i], m_tags[i]);
        //connect(m_pButtons[i], SIGNAL(clicked(bool)), this, SLOT(slot_buttonClicked(bool)));
        connect(m_pButtons[i], SIGNAL(clicked()), pSignalMapper, SLOT(map()));

        pLayout->addWidget(m_pButtons[i]);
    }

    connect(pSignalMapper, SIGNAL(mapped(QString)), this, SLOT(slot_buttonClicked(QString)));

    m_pListener = pActionListener;
    FlowLayout * pLayout2 = new FlowLayout;
    setLayout(pLayout2);
    pLayout2->addWidget(pWidget);
}

//
//析构函数 : 释放一个 CMonyButtonPane
//
CMonyButtonPane::~CMonyButtonPane()
{

}

//针对一个标签进行允禁的方法
//参数1:	标签信息
//参数2:	是否启用
//
void CMonyButtonPane::EnableButton(QString tag, bool bEnable)
{
    if (NULL == tag)
    {
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        if (tag == m_tags[i])
        {
            m_pButtons[i]->setEnabled(bEnable);
            return;
        }
    }
}

void CMonyButtonPane::slot_buttonClicked(bool bChecked)
{
    qDebug() << "void CMonyButtonPane::slot_buttonClicked" << endl;
    if (NULL == m_pListener || NULL == m_pButtons)
    {
        return;
    }

    //m_pListener->ButtonActioned(m_tags[4]);

    for (int i = 0; i < 8; i++)
    {
        if (m_pButtons[i]->isChecked())
        {
            qDebug() << i << " is checked" << endl;
            //m_pListener->ButtonActioned(m_tags[i]);
        }
        else
        {
            qDebug() << i << " is not checked" << endl;
        }
    }
}

void CMonyButtonPane::slot_buttonClicked(QString tag)
{
    qDebug() << "cliked button is " << tag << endl;
    if (NULL == m_pListener || NULL == m_pButtons)
    {
        return;
    }

    m_pListener->ButtonActioned(tag);
}
