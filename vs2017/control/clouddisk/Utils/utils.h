#pragma once
#include <qstring.h>
namespace utils
{
	QString webUnicodeToString(QString&src);
	QString StringToWebUnicode(QString&src);
	QString GetNameByUrl(const QString&url);
}
