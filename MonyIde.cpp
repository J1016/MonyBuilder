#include "MonyFrame.h"
#include "MonyTool.h"
#include <QApplication>

#include <opencv2/opencv.hpp>
#include <qDebug>

//��ʼ��ϵͳ������ķ���
//����1:	��������
//����2:	������
//����3:	����ߴ�
//
void InitGlobalFontSetting(QString fontName, int nStyle,
            int nSize)
{

}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    InitGlobalFontSetting(NULL, 0, 0);
    CMonyTool::InitDirs();
    CMonyFrame frame;
    frame.show();

//    QString soucreFile = "D:\\TestQt\\MonyBuilder\\run\\9ad7fbf830c348a68286a3bddcf09b79.jpg";
//    QString templateFile = "D:\\TestQt\\MonyBuilder\\run\\b99fcd01815842c28408f94fe9d76f96.png";
//    cv::Mat image_source = cv::imread(soucreFile.toStdString(),
//            cv::IMREAD_GRAYSCALE);
//    cv::Mat image_template = cv::imread(templateFile.toStdString(),
//            cv::IMREAD_GRAYSCALE);
//    cv::Mat image_matched;

//    //ģ��ƥ��
//    cv::matchTemplate(image_source, image_template, image_matched,
//            cv::TM_CCOEFF_NORMED);

//    double minVal, maxVal;
//    cv::Point minLoc, maxLoc;
//    //Ѱ�����ƥ��λ��
//    cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);
//    cv::imshow("TestOpencv", image_source);

//    qDebug() << "before" << endl;
//    CMonyTool::Sleep(5000);
//    qDebug() << "end" << endl;
    return application.exec();
}
