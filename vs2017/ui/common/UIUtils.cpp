#include "UIUtils.h"
#include "common/Controlptr.h"
#include "common/UIUtils.h"
#include "ChineseInfos.h"
#include <QDir>
#include <QFileInfo>
#include <QStringList>
qint64 UIUtils::m_localid = 0;
QString UIUtils::GetDataFullPath(int type){
	QString Path("");
	QString Name("");

	IUserControl_Ptr userCtrl = USERCONTROL;
	std::vector<std::string> keys;
	keys.push_back("savefilepath");

	std::vector<data::UserLocalSetting> retData;
	bool isGet = userCtrl->getLocalSettingSync(keys,retData);
	if (!retData.empty())
	{
		for (qint16 index = 0; index < retData.size(); ++index)
		{
			if (retData[index].key == std::string("savefilepath"))
			{
				QString sdMsg = QString::fromUtf8(retData[index].val.data());
				sdMsg = sdMsg.replace(" ", "");
				sdMsg = sdMsg.toLower();
				Path = sdMsg;
				break;
			}
		}
	}

	switch(type){
	case DATAPATH_USERIMG:
		{
			Path = QString::fromUtf8(USERIMGPATH);
			break;
		}
	case DATACACHEPATH_USERIMG:
		{
			Path = QString::fromUtf8(USERIMGPATH)+QString("cache/");
			break;
		}
	case DATAPATH_USERFILE:
		{
			Path = Path.isEmpty() ? QString::fromUtf8(USERFILEPATH) :Path;
			break;
		}
	case DATACACHEPATH_USERFILE:
		{
			Path = Path.isEmpty() ? QString::fromUtf8(USERFILEPATH)+QString("cache/"):Path+QString("cache/");
			break;
		}
	case DATAPATH_USERAUDIO:
		{
			Path = QString::fromUtf8(USERAUDIOPATH);
			break;
		}
	case DATACACHEPATH_USERAUDIO:
		{
			Path = QString::fromUtf8(USERAUDIOPATH) +QString("cache/");
			break;
		}
	case DATAPATH_USERVIDEO:
		{
			Path = Path.isEmpty() ? QString::fromUtf8(USERVIDEOPATH): Path;
			break;
		}
	case DATACACHEPATH_USERVIDEO:
		{
			Path = Path.isEmpty() ? QString::fromUtf8(USERVIDEOPATH)+QString("cache/"): Path+QString("cache/");
			break;
		}
	}
	QDir tempDir;
	if (!tempDir.exists(Path))
	{
		tempDir.mkdir(Path);
	}
	return Path;
}
QString UIUtils::GetNameByUrl(const QString&url){
	QStringList list;
	list = url.split("/");
	return list.size()>0?list.last():"";
}
QString UIUtils::GetPicNameByUrl(const QString&url){
	QString result("");
	result = url;
	return 	result.replace("/","_");
}
QString UIUtils::GetPicNameDirPrefix(const QString url){
	QString result("");
	QString name("");
	result = url;
	name = GetNameByUrl(result);
	result = result.replace(name,"");
	return result;
}
bool UIUtils::IsFileExist(const QString&path){
	QFileInfo fileInfo(path);
	if (fileInfo.isFile() && fileInfo.exists())
	{
		return true;
	}
	return false;
}
void UIUtils::removeSpaceBeforeCharacter(QString& str){
	while (str.count() > 0 && str.at(0) == ' ')
	{
		str.remove(0, 1);
	}
}

QString UIUtils::RepairLocalFilePath(QString path)
{
	//数据迁移，可能导致数据目录不对，更新数据目录
	QString retPath = path;
	QString tmpPath = GetAppDataLocalPath();
	tmpPath.replace("\\", "/");

	if (!path.contains(tmpPath))
	{
		int index = path.indexOf(QString::number(CURENTUSERID));
		tmpPath.append("/");
		tmpPath.append(path.mid(index, -1));
		retPath = tmpPath;
	}
	return retPath;
}

qint64 UIUtils::getLocalId(){
	++m_localid;
	return m_localid;
}