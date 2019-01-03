#include "borderlayout.h"
#include "MonyButtonPane.h"
#include "MonyExecutor.h"
#include "MonyFrame.h"
#include "MonySyntaxHighLighter.h"
#include "MonyTabScriptEditor.h"
#include "MonyTool.h"
#include <qDebug>
#include <QFileDialog>
#include <QLayout>
#include <QMessageBox>
#include <QThread>

//
//构造函数 : 构造一个 CMonyTabScriptEditor
//
CMonyTabScriptEditor::CMonyTabScriptEditor()
{
    //按钮面板设置
    QString buttonInfomation;
    buttonInfomation.append(QString::fromLocal8Bit("新建脚本,new"));
    buttonInfomation.append(QString::fromLocal8Bit("#打开脚本,open"));
    buttonInfomation.append(QString::fromLocal8Bit("#打开测试头脚本,opentest"));
    buttonInfomation.append(QString::fromLocal8Bit("#保存脚本,save"));
    buttonInfomation.append(QString::fromLocal8Bit("#运行当前测试流程,test"));
    buttonInfomation.append(QString::fromLocal8Bit("#查看全局参数,seeglobal"));
    buttonInfomation.append(QString::fromLocal8Bit("#查看联网参数,seehttp"));
    buttonInfomation.append(QString::fromLocal8Bit("#清空控制台,clear"));

    m_pButtonPane = new CMonyButtonPane(buttonInfomation, this);
//    m_pButtonPane->EnableButton("save", false);
//    m_pButtonPane->EnableButton("test", false);

    //脚本文本区域
    m_pScriptEdit = new CodeEditor;
    CMonySyntaxHighlighter * pHighLighter = new CMonySyntaxHighlighter(
            m_pScriptEdit->document());

    //提示文本区域
    m_pTipEdit = new QTextEdit;
    m_pTipEdit->setText(QString::fromLocal8Bit("-- 禁用状态，等待新的脚本建立。"));
    m_pTipEdit->setReadOnly(true);

    //基本设置
    BorderLayout * pLayout = new BorderLayout;
    pLayout->addWidget(m_pButtonPane, BorderLayout::West);
    pLayout->addWidget(m_pScriptEdit, BorderLayout::Center);
    pLayout->addWidget(m_pTipEdit, BorderLayout::East);
    setLayout(pLayout);

    m_pParamMap = NULL;
    m_pResponseMap = NULL;
    m_pGlobalMap = NULL;
    m_pLuaState = NULL;
}

//
//析构函数 : 释放一个 CMonyTabScriptEditor
//
CMonyTabScriptEditor::~CMonyTabScriptEditor()
{

}

QString CMonyTabScriptEditor::GainTitle()
{
    return QString::fromLocal8Bit("流程测试");
}

void CMonyTabScriptEditor::AgTrace(QString content)
{
    QString tipText = m_pTipEdit->toPlainText();

//    tipText += "\n---------------- " + CMonyTool::GainDateDatailString()
//            + " ----------------\n";
    tipText += "\n------------ " + CMonyTool::GainDateDatailString()
            + " ------------\n";
    tipText += content;

    m_pTipEdit->setText(tipText);
}

bool CMonyTabScriptEditor::AgTesting()
{
    return true;
}

void CMonyTabScriptEditor::AgClearHttpParamMap()
{
    m_pParamMap = NULL;
}

QString CMonyTabScriptEditor::AgGainSericode()
{
    return "#testcase";
}

QMap<QString, QString> * CMonyTabScriptEditor::AgGainHttpParamMap()
{
    if (NULL == m_pParamMap)
    {
        m_pParamMap = new QMap<QString, QString>();
        m_pParamMap->insert("Connection", "keep-alive");
        m_pParamMap
                ->insert(
                        "User-Agent",
                        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.89 Safari/537.1");
        m_pParamMap
                ->insert("Accept",
                        "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
        m_pParamMap->insert("Accept-Language", "zh-CN,zh;q=0.8");
        m_pParamMap->insert("Accept-Charset", "GBK,utf-8;q=0.7,*;q=0.3");
    }

    return m_pParamMap;
}

QMap<QString, QString> * CMonyTabScriptEditor::AgGainHttpResponseMap()
{
    if (NULL == m_pResponseMap)
    {
        m_pResponseMap = new QMap<QString, QString>();
    }

    return m_pResponseMap;
}

lua_State * CMonyTabScriptEditor::AgGainLuaState()
{
    if (NULL == m_pLuaState)
    {
        m_pLuaState = luaL_newstate();
    }

    return m_pLuaState;
}

QMap<QString, QString> * CMonyTabScriptEditor::AgGainGlobalParamMap()
{
    if (NULL == m_pGlobalMap)
    {
        m_pGlobalMap = new QMap<QString, QString>();
    }

    return m_pGlobalMap;
}

void CMonyTabScriptEditor::run()
{
    qDebug() << "void CMonyTabScriptEditor::run" << endl;
}

//打开一个脚本文件的方法
//
void CMonyTabScriptEditor::OpenScriptFile(QString path)
{
    QFile * pFile = new QFile(path);
    pFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream ts(pFile);

    QString content = ts.readAll();
    pFile->close();

    m_pScriptEdit->setPlainText(content);
}

void CMonyTabScriptEditor::ButtonActioned(QString tag)
{
    //新建操作
    if (tag == "new")
    {
        m_pScriptEdit->setEnabled(true);
        m_pTipEdit->setEnabled(true);
        m_pScriptEdit->setPlainText(QString::fromLocal8Bit("--\n-- Mony 脚本引擎 v1.0\n-- 日期: ")
                + CMonyTool::GainDateString() + "\n--\n\n");
        m_pTipEdit->setText(QString::fromLocal8Bit("-- 就绪状态，等待脚本测试执行。\n"));
        m_pButtonPane->EnableButton("save", true);
        m_pButtonPane->EnableButton("test", true);

        return;
    }

    //打开操作
    if (tag == "open")
    {
        QString rootPath = CMonyTool::GainOncePath(CMonyTool::sm_fileScriptPath);
        QFileDialog dialog(this, NULL, rootPath, NULL);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setNameFilter(QString::fromLocal8Bit("脚本文件 (*.txt)"));
        QStringList fileNames;
        if (dialog.exec())
        {
            fileNames = dialog.selectedFiles();
            OpenScriptFile(fileNames.at(0));
        }

        return;
    }

    //打开测试预处理文件操作
    if (tag == "opentest")
    {
        QString fileName = CMonyTool::sm_fileScriptPath + "testor.txt";
        OpenScriptFile(fileName);

        return;
    }

    //保存操作
    if (tag == "save")
    {
        QString realSavePath = NULL;

        QString rootPath = CMonyTool::GainOncePath(CMonyTool::sm_fileScriptPath);
        QFileDialog dialog(this, NULL, rootPath, NULL);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setNameFilter(QString::fromLocal8Bit("脚本文件 (*.txt)"));
        realSavePath = dialog.getSaveFileName();

//        CMonyTool::ReplaceForWord(realSavePath, "/", "\\");
//        if (realSavePath == rootPath + "api.txt")
        if (realSavePath == "api.txt")
        {
            QMessageBox msgBox;
            msgBox.setText("不允许修改接口文件 api.txt ！");
            msgBox.setDefaultButton(QMessageBox::Save);
            int nRet = msgBox.exec();
            return;
        }

        if (NULL != realSavePath)
        {
            QString content = m_pScriptEdit->toPlainText();
            if (!realSavePath.endsWith(".txt"))
            {
                realSavePath += ".txt";
            }

            QString tip = "文件 \"" + realSavePath + "\" 保存成功。";
            CMonyFrame::SetStatusText(QString::fromLocal8Bit(tip.toLatin1()));

            QFile * pFile = new QFile(realSavePath);
            pFile->open(QIODevice::ReadWrite | QIODevice::Text);
            pFile->write(content.toUtf8());
            pFile->close();
        }

        return;
    }

    //运行测试操作
    if (tag == "test")
    {
        m_pButtonPane->EnableButton("test", false);

        QString testorContent = CMonyTool::ReadFileString(
                CMonyTool::sm_fileScriptPath + "testor.txt");
        QString scriptContent = m_pScriptEdit->toPlainText();

        CMonyExecutor executor(this);
        executor.RunScript(testorContent, scriptContent);

        m_pLuaState = NULL;
        m_pButtonPane->EnableButton("test", true);

        return;
    }

    //查看全局参数
    if (tag == "seeglobal")
    {
        if (NULL == m_pGlobalMap)
        {
            return;
        }

        QString content = "当前联网参数内容如下：\n\n";

        QMapIterator<QString, QString> i(*m_pGlobalMap);
        while (i.hasNext())
        {
            QString key = i.next().value();
            QString value = m_pGlobalMap->value(key);

            content += key + " : " + value;
            content += "\n---------\n";
            qDebug() << i.key() << ": " << i.value() << endl;
        }

        m_pTipEdit->setText(content);

        return;
    }

    //查看联网参数
    if (tag == "seehttp")
    {
        if (NULL == m_pParamMap)
        {
            return;
        }

        QString content = "当前联网参数内容如下：\n\n";

        QMapIterator<QString, QString> i(*m_pParamMap);
        while (i.hasNext())
        {
            QString key = i.next().value();
            QString value = m_pParamMap->value(key);

            content += key + " : " + value;
            content += "\n---------\n";
            qDebug() << i.key() << ": " << i.value() << endl;
        }

        m_pTipEdit->setText(content);

        return;
    }

    //清空控制台
    if (tag == "clear")
    {
        m_pTipEdit->setText("");
        CMonyFrame::SetStatusText(QString::fromLocal8Bit("控制台信息已经被清空！"));

        return;
    }
}





