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
//���캯�� : ����һ�� CMonyTabScriptEditor
//
CMonyTabScriptEditor::CMonyTabScriptEditor()
{
    //��ť�������
    QString buttonInfomation;
    buttonInfomation.append(QString::fromLocal8Bit("�½��ű�,new"));
    buttonInfomation.append(QString::fromLocal8Bit("#�򿪽ű�,open"));
    buttonInfomation.append(QString::fromLocal8Bit("#�򿪲���ͷ�ű�,opentest"));
    buttonInfomation.append(QString::fromLocal8Bit("#����ű�,save"));
    buttonInfomation.append(QString::fromLocal8Bit("#���е�ǰ��������,test"));
    buttonInfomation.append(QString::fromLocal8Bit("#�鿴ȫ�ֲ���,seeglobal"));
    buttonInfomation.append(QString::fromLocal8Bit("#�鿴��������,seehttp"));
    buttonInfomation.append(QString::fromLocal8Bit("#��տ���̨,clear"));

    m_pButtonPane = new CMonyButtonPane(buttonInfomation, this);
//    m_pButtonPane->EnableButton("save", false);
//    m_pButtonPane->EnableButton("test", false);

    //�ű��ı�����
    m_pScriptEdit = new CodeEditor;
    CMonySyntaxHighlighter * pHighLighter = new CMonySyntaxHighlighter(
            m_pScriptEdit->document());

    //��ʾ�ı�����
    m_pTipEdit = new QTextEdit;
    m_pTipEdit->setText(QString::fromLocal8Bit("-- ����״̬���ȴ��µĽű�������"));
    m_pTipEdit->setReadOnly(true);

    //��������
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
//�������� : �ͷ�һ�� CMonyTabScriptEditor
//
CMonyTabScriptEditor::~CMonyTabScriptEditor()
{

}

QString CMonyTabScriptEditor::GainTitle()
{
    return QString::fromLocal8Bit("���̲���");
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

//��һ���ű��ļ��ķ���
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
    //�½�����
    if (tag == "new")
    {
        m_pScriptEdit->setEnabled(true);
        m_pTipEdit->setEnabled(true);
        m_pScriptEdit->setPlainText(QString::fromLocal8Bit("--\n-- Mony �ű����� v1.0\n-- ����: ")
                + CMonyTool::GainDateString() + "\n--\n\n");
        m_pTipEdit->setText(QString::fromLocal8Bit("-- ����״̬���ȴ��ű�����ִ�С�\n"));
        m_pButtonPane->EnableButton("save", true);
        m_pButtonPane->EnableButton("test", true);

        return;
    }

    //�򿪲���
    if (tag == "open")
    {
        QString rootPath = CMonyTool::GainOncePath(CMonyTool::sm_fileScriptPath);
        QFileDialog dialog(this, NULL, rootPath, NULL);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setNameFilter(QString::fromLocal8Bit("�ű��ļ� (*.txt)"));
        QStringList fileNames;
        if (dialog.exec())
        {
            fileNames = dialog.selectedFiles();
            OpenScriptFile(fileNames.at(0));
        }

        return;
    }

    //�򿪲���Ԥ�����ļ�����
    if (tag == "opentest")
    {
        QString fileName = CMonyTool::sm_fileScriptPath + "testor.txt";
        OpenScriptFile(fileName);

        return;
    }

    //�������
    if (tag == "save")
    {
        QString realSavePath = NULL;

        QString rootPath = CMonyTool::GainOncePath(CMonyTool::sm_fileScriptPath);
        QFileDialog dialog(this, NULL, rootPath, NULL);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setNameFilter(QString::fromLocal8Bit("�ű��ļ� (*.txt)"));
        realSavePath = dialog.getSaveFileName();

//        CMonyTool::ReplaceForWord(realSavePath, "/", "\\");
//        if (realSavePath == rootPath + "api.txt")
        if (realSavePath == "api.txt")
        {
            QMessageBox msgBox;
            msgBox.setText("�������޸Ľӿ��ļ� api.txt ��");
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

            QString tip = "�ļ� \"" + realSavePath + "\" ����ɹ���";
            CMonyFrame::SetStatusText(QString::fromLocal8Bit(tip.toLatin1()));

            QFile * pFile = new QFile(realSavePath);
            pFile->open(QIODevice::ReadWrite | QIODevice::Text);
            pFile->write(content.toUtf8());
            pFile->close();
        }

        return;
    }

    //���в��Բ���
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

    //�鿴ȫ�ֲ���
    if (tag == "seeglobal")
    {
        if (NULL == m_pGlobalMap)
        {
            return;
        }

        QString content = "��ǰ���������������£�\n\n";

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

    //�鿴��������
    if (tag == "seehttp")
    {
        if (NULL == m_pParamMap)
        {
            return;
        }

        QString content = "��ǰ���������������£�\n\n";

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

    //��տ���̨
    if (tag == "clear")
    {
        m_pTipEdit->setText("");
        CMonyFrame::SetStatusText(QString::fromLocal8Bit("����̨��Ϣ�Ѿ�����գ�"));

        return;
    }
}





