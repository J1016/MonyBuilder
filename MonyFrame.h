#ifndef MONYFRAME_H
#define MONYFRAME_H

#include "MonyTab.h"
#include <QLabel>
#include <QMainWindow>

class CMonyFrame : public QMainWindow
{
    Q_OBJECT

private:
    static CMonyFrame * sm_pMainFrame;                      //��ǰ��ܴ���
    QWidget * m_pMainPanel;                                 //�������
    QTabWidget * m_pTabbedPanel;							//��ҳ����ǩ
    QLabel * m_pTipLabel;                                   //��ʾ��Ϣ���
    QVector<CMonyTab *> m_tabList;                          //��弯

public:
    explicit CMonyFrame(QWidget * pParent = 0);
    virtual ~CMonyFrame();

    void InitTabs();

    static void SetStatusText(QString text);
};

#endif // MONYFRAME_H
