#include "ChineseInfos.h"
#include<qlocale.h>
#include <log.h>
#include <QCryptographicHash>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>
#include <QSysInfo>
#include <QDataStream>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include "Common.h"
#if QT_VERSION < 0x050000 
#include <QApplication>
#include<QDesktopServices>
#else
#include <QtWidgets/QApplication> 
#include<QStandardPaths>
#include<QDesktopServices>
#endif
//判断是否是中文系统
bool LocalLanguageCH_Z()
{
	if (QLocale::Chinese == QLocale::system().language() || QLocale::C == QLocale::system().language())
	{
		return true;
	}
	return false;
}
QString GetFileMD5(QString filePath){
	BEGIN;
	QFile localFile(filePath);
	QCryptographicHash ch(QCryptographicHash::Md5);
	quint64 totalBytes = 0;
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = 0;
	quint64 loadSize = 1024 * 4;
	QByteArray buf;
	QString md5;

	if (!localFile.open(QFile::ReadOnly))
	{
		qDebug() << "file open error.";
		return 0;
	}
	totalBytes = localFile.size();
	bytesToWrite = totalBytes;
	while (true)
	{
		if (bytesToWrite > 0)
		{
			buf = localFile.read(qMin(bytesToWrite, loadSize));
			ch.addData(buf);
			bytesWritten += buf.length();
			bytesToWrite -= buf.length();
			buf.resize(0);
		}
		else
		{
			break;
		}

		if (bytesWritten == totalBytes)
		{
			break;
		}
	}
	localFile.close();
	md5 = QString::fromLocal8Bit(ch.result().toHex()).toUpper();
   END;
	return md5;
}
bool CompareMD5(QString md5_1, QString md5_2){
	BEGIN;
	if (md5_1.isEmpty()) return false;
	if (md5_2.isEmpty()) return false;
	END;
	return md5_1.toUpper() == md5_2.toUpper();
}
bool CheckMarComplete(const QString FileName, const QString md5){
	BEGIN;
	if (FileName.isEmpty()) return false;
	if (md5.isEmpty()) return false;
	QString FileHash = GetFileMD5(FileName);
	END;
	return CompareMD5(md5, FileHash);
}
QStringList GetMd5FromRecordFile(QString filePath){
	BEGIN;
	QFileInfo file;
	QStringList Md5List;
	file.setFile(filePath);
	if (file.isFile() && file.exists()){
		QFile dataFile(filePath);
		if (dataFile.open(QFile::ReadOnly))
		{
			QDataStream in(&dataFile);
			quint32 logicnumber = 0;
			QString md5,dependmd5;
			in.setVersion(QDataStream::Qt_4_8);

			in >>logicnumber>>md5>>dependmd5;
			Md5List<<md5<<dependmd5;
			dataFile.close();
		}
		else{
			qDebug() << "Cannot open file for reading: ";
			return Md5List;
		}
	}
	BEGIN;
	return Md5List;
}

QString GetDesktopLocalPath()
{
#if(QT_VERSION < QT_VERSION_CHECK(5,6,0))
	return  QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);
#else
	return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
#endif
}

QString GetAppDataLocalPath()
{
	QString appDataPath;
#if(QT_VERSION < QT_VERSION_CHECK(5,6,0))
	appDataPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
	appDataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
	QDir dir(appDataPath);
	bool bret = dir.exists();
	if (!bret){
		dir.mkdir(appDataPath);
	}
	return appDataPath;
}

void LoadHighDpiInfo(){
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
	{
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		Log(LOG_LEV_DEBUG, LOG_FILE, "Qt::AA_EnableHighDpiScaling on");
	}
#endif
	gDdpi = 1.0;
	QApplication::desktop()->logicalDpiX() / 96.0;
	QString dpistr = QString::number(gDdpi);
	Log(LOG_LEV_DEBUG, LOG_FILE, "[dpistr=%s]", dpistr.toLocal8Bit().data());
	Log(LOG_LEV_DEBUG, LOG_FILE, "[dpi=%0.2f]", gDdpi);
}