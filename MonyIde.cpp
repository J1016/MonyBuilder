#include "MonyFrame.h"
#include "MonyTool.h"
#include <QApplication>

#include <opencv2/opencv.hpp>
#include <qDebug>

//初始化系统级字体的方法
//参数1:	字体名称
//参数2:	字体风格
//参数3:	字体尺寸
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

//    //模板匹配
//    cv::matchTemplate(image_source, image_template, image_matched,
//            cv::TM_CCOEFF_NORMED);

//    double minVal, maxVal;
//    cv::Point minLoc, maxLoc;
//    //寻找最佳匹配位置
//    cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);
//    cv::imshow("TestOpencv", image_source);

//    qDebug() << "before" << endl;
//    CMonyTool::Sleep(5000);
//    qDebug() << "end" << endl;
    return application.exec();
}
