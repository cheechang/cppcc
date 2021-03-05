#include <QtWidgets/QApplication>
#include <QtGui>
#include <QtGlobal>
#if defined(__linux__) || defined(_WIN32)
#include "ScreenShotClient.h"
#else
#include "FullScreenWidget.h"
#endif
int main(int argc, char *argv[])
{
	qputenv("QT_SCALE_FACTOR", "1");
	QApplication a(argc, argv);
	QStringList arguments = QApplication::arguments();
#ifndef _DEBUG
	Q_INIT_RESOURCE(res);
#endif
	QString applicationPath = QCoreApplication::applicationDirPath();
	qDebug() << "applicationPath" << applicationPath;
	//设置字体
	QDir fontDir;
	QString fontDirPath = applicationPath + "/Font";
	fontDir.setPath(fontDirPath);
	int fontId = 0;
	QFileInfoList fontlist = fontDir.entryInfoList(QDir::Files, QDir::Name);
	for (int i = 0; i < fontlist.size(); i++)
	{
		QString fontPath = fontlist.at(i).absoluteFilePath();
		fontId = QFontDatabase::addApplicationFont(fontPath);
		if (!fontId)
		{
			QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
			QFont font(fontName);
			font.setPixelSize(10*90/72);
			a.setFont(font);
		}
	}
	//加载qt默认语言包
	QTranslator qQtTranslator;
#ifndef _DEBUG
	qQtTranslator.load(":language/qt_zh_CN.qm");
#else
	qQtTranslator.load("language/qt_zh_CN.qm");
#endif
	a.installTranslator(&qQtTranslator);

	/*
#ifndef WINDOWS_PATCH_UPDATE
	QStringList libPath;
	libPath << applicationPath + "/qml" << applicationPath + "/plugins"\
		<< applicationPath + "/Material" << applicationPath + "/Qt"\
		<< applicationPath + "/platforms" << applicationPath + "/QtGraphicalEffects"\
		<< applicationPath + "/QtQml" << applicationPath + "/QtQuick"\
		<< applicationPath + "/QtQuick.2" << applicationPath + "/Font";
	///设置库目录
	a.setLibraryPaths(libPath);
#endif
	*/
#if defined (__linux__) || defined (_WIN32)
	if (arguments.size() < 2)
	{
		qDebug() << QString("参数错误");
		return 1;
	}
	ScreenShotClient client;
	QObject::connect(&client, SIGNAL(signalexit()), &a, SLOT(quit()));
	client.Init();
#else
	fullScreenWidget* screen = fullScreenWidget::GetInstance();
	QObject::connect(screen, SIGNAL(exitPixmap()), &a, SLOT(quit()));
	QPixmap pixmap = screen->getFullScreenPixmap();
	screen->loadBackgroundPixmap(pixmap);
	screen->hide();
	screen->setWindowFlags(Qt::FramelessWindowHint);
	screen->move(0,0);
	screen->showFullScreen();
	screen->raise();
	screen->activateWindow();
#endif
	return a.exec();
}
