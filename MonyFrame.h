#ifndef MONYFRAME_H
#define MONYFRAME_H

#include "MonyTab.h"
#include <QLabel>
#include <QMainWindow>

class CMonyFrame : public QMainWindow
{
    Q_OBJECT

private:
    static CMonyFrame * sm_pMainFrame;                      //当前框架窗口
    QWidget * m_pMainPanel;                                 //基本面板
    QTabWidget * m_pTabbedPanel;							//分页面板标签
    QLabel * m_pTipLabel;                                   //提示信息面板
    QVector<CMonyTab *> m_tabList;                          //面板集

public:
    explicit CMonyFrame(QWidget * pParent = 0);
    virtual ~CMonyFrame();

    void InitTabs();

    static void SetStatusText(QString text);
};

#endif // MONYFRAME_H
