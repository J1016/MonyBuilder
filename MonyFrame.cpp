#include "borderlayout.h"
#include "MonyFrame.h"
#include "MonyTabPageCreate.h"
#include "MonyTabScriptEditor.h"
#include <qDebug>
#include <QHBoxLayout>

#include <QFileDialog>
#include <qDebug>
#include "MonyTool.h"
#include "flowlayout.h"

//定义当前框架窗口
CMonyFrame * CMonyFrame::sm_pMainFrame;

//
//构造函数 : 构造一个 CMonyFrame
//
CMonyFrame::CMonyFrame(QWidget * pParent) :
    QMainWindow(pParent)
{
    sm_pMainFrame = this;

    //基本面板结构设置

    // //菜单信息

    // //主面板信息
    m_pMainPanel = new QWidget(this);
    InitTabs();
    BorderLayout * pBorderLayout = new BorderLayout;
    m_pMainPanel->setLayout(pBorderLayout);
    m_pTabbedPanel = new QTabWidget(m_pMainPanel);
    pBorderLayout->addWidget(m_pTabbedPanel, BorderLayout::Center);

    for(int i = 0; i < m_tabList.size(); i++)
    {
        CMonyTab * pTab = m_tabList.at(i);
        m_pTabbedPanel->addTab(pTab, pTab->GainTitle());
    }

    // //提示信息
    QWidget * pTipWidget = new QWidget(m_pMainPanel);
    m_pTipLabel = new QLabel();
    m_pTipLabel->setText(QString::fromLocal8Bit("就绪。"));
    FlowLayout * pFlowLayout = new FlowLayout;
    pTipWidget->setLayout(pFlowLayout);
    pFlowLayout->addWidget(m_pTipLabel);
    pBorderLayout->addWidget(pTipWidget, BorderLayout::South);

    // 基本面板参数设置
    int nWidth = 800;
    int nHeight = 600;

    setCentralWidget(m_pMainPanel);
    resize(nWidth, nHeight);
    showMaximized();
}

//
//析构函数 : 释放一个 CMonyFrame
//
CMonyFrame::~CMonyFrame()
{

}

//初始化标签信息
//
void CMonyFrame::InitTabs()
{
    m_tabList.append(new CMonyTabScriptEditor());
}

//设置状态信息文本
//参数1:	文本信息
//
void CMonyFrame::SetStatusText(QString text)
{
    if (NULL == sm_pMainFrame)
    {
        return;
    }

    sm_pMainFrame->m_pTipLabel->setText(text);
}

