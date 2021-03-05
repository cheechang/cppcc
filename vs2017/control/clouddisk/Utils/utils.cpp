#include "utils.h"
#include <QStringList>
namespace utils
{
	QString webUnicodeToString(QString& src){
		QString str("");
		QStringList templist;

		if (!src.contains("&#")){
			return src;
		}
		templist = src.split(";");
		for (int index = 0;index<templist.size(); ++index){
			int lenth = templist.at(index).length();
			if (lenth > 2) {
				QString temp = templist.at(index).mid(2, lenth);
				str += QChar(atoi(temp.toLocal8Bit().data()));
			}
		}
		return str;
	}
	QString StringToWebUnicode(QString&src){
		QString str("");
		for (int index = 0; index < src.size();++index){
			str += QString("&#")+ src.at(index).unicode()+ QString(";");
		}
		return str;
	}
	QString GetNameByUrl(const QString&url){
		QStringList list;
		list = url.split("/");
		return list.size()>0 ? list.last() : "";
	}
}