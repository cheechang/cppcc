#pragma  once;
#include <QString>
#include "common/Common.h"
class UIUtils
{
public:
	static QString GetDataFullPath(int type);
	static QString GetNameByUrl(const QString&url);
	static QString GetPicNameByUrl(const QString&url);
	static bool    IsFileExist(const QString&path);
	static QString GetPicNameDirPrefix(const QString url);
	static void removeSpaceBeforeCharacter(QString& str);
	static QString RepairLocalFilePath(QString path);
	static qint64 getLocalId();
private:
	static qint64 m_localid;
};

