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

//���嵱ǰ��ܴ���
CMonyFrame * CMonyFrame::sm_pMainFrame;

//
//���캯�� : ����һ�� CMonyFrame
//
CMonyFrame::CMonyFrame(QWidget * pParent) :
    QMainWindow(pParent)
{
    sm_pMainFrame = this;

    //�������ṹ����

    // //�˵���Ϣ

    // //�������Ϣ
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

    // //��ʾ��Ϣ
    QWidget * pTipWidget = new QWidget(m_pMainPanel);
    m_pTipLabel = new QLabel();
    m_pTipLabel->setText(QString::fromLocal8Bit("������"));
    FlowLayout * pFlowLayout = new FlowLayout;
    pTipWidget->setLayout(pFlowLayout);
    pFlowLayout->addWidget(m_pTipLabel);
    pBorderLayout->addWidget(pTipWidget, BorderLayout::South);

    // ��������������
    int nWidth = 800;
    int nHeight = 600;

    setCentralWidget(m_pMainPanel);
    resize(nWidth, nHeight);
    showMaximized();
}

//
//�������� : �ͷ�һ�� CMonyFrame
//
CMonyFrame::~CMonyFrame()
{

}

//��ʼ����ǩ��Ϣ
//
void CMonyFrame::InitTabs()
{
    m_tabList.append(new CMonyTabScriptEditor());
}

//����״̬��Ϣ�ı�
//����1:	�ı���Ϣ
//
void CMonyFrame::SetStatusText(QString text)
{
    if (NULL == sm_pMainFrame)
    {
        return;
    }

    sm_pMainFrame->m_pTipLabel->setText(text);
}

