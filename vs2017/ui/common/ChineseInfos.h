#pragma once
#include <QString>
//判断是否是中文系统
bool LocalLanguageCH_Z();
QString GetFileMD5(QString filePath);
bool CompareMD5(QString md5_1, QString md5_2);
bool CheckMarComplete(const QString FileName, const QString md5);
QStringList GetMd5FromRecordFile(QString filePath);
QString GetAppDataLocalPath();
QString GetDesktopLocalPath();
void LoadHighDpiInfo();