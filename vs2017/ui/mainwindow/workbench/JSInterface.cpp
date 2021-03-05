#include "jsinterface.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>
#include "Json.h"
#include "log.h"
#include "../../common/Common.h"

JSInterface::JSInterface(QObject *parent)
	: QObject(parent)
{
	m_pAppMgr = APPMGRCONTROL;

	CONNECT_SERVICE(GetOrganization(std::string, QString, QString));
	CONNECT_SERVICE(GetLocalPhotos(std::string, QString, QString));
	CONNECT_SERVICE(GetLocalFiles(std::string, QString, QString));
	CONNECT_SERVICE(GetGroupMembers(std::string, QString, QString));
	CONNECT_SERVICE(FileUploadFailure(std::string));
}

JSInterface::~JSInterface()
{

}

void JSInterface::takePhoto(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	emit callback(fname, uuid, "{}");
END;
}

void JSInterface::getAccountInfo(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	std::string args = m_pAppMgr->getAccountInfoJson();
	emit callback(fname, uuid, QString::fromStdString(args));
END;
}

void JSInterface::getPosition(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	emit callback(fname, uuid, "{}");
END;
}

void JSInterface::getContactList(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	std::string args = m_pAppMgr->getContactListJson();
	emit callback(fname, uuid, QString::fromStdString(args));
END;
}

void JSInterface::getOrganization(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	m_pAppMgr->getOrganizationJson(uuid.toStdString(),
		CBind(&JSInterface::signalSerGetOrganization, this,
			CPlaceholders  _1, fname, uuid));
END;
}

void JSInterface::onSerGetOrganization(std::string str, QString fname,
	QString uuid)
{
BEGIN;
	emit callback(fname, uuid, QString::fromStdString(str));
END;
}

void JSInterface::getGroupList(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	std::string args = m_pAppMgr->getGroupListJson();
	emit callback(fname, uuid, QString::fromStdString(args));
END;
}

void JSInterface::getLocalPhotos(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	Json::Reader reader;
	Json::Value obj;
	if (reader.parse(uuid.toStdString(), obj))
	{
		if (obj["size"].isInt())
		{
			QStringList images = QFileDialog::getOpenFileNames(NULL,
				QString::fromLocal8Bit(("请选择图片")), QDir::homePath(),
					"Images (*.png *.xpm *.jpg *.bmp)");
			if (images.size() > obj["size"].asInt())
			{
				QString tip = QString("一次上传的图片不能超过%1个")
					.arg(obj["size"].asInt());
				QMessageBox msgbox(QMessageBox::Warning, transfer("提示"), tip,
					QMessageBox::Ok, NULL);
				msgbox.exec();
				return;
			}
			else if (images.size() == 0)
			{
				emit callback(fname, uuid, "{\"mPhotoPath\":[]}");
				return;
			}
			
			std::vector<std::string> vec;
			for(int i = 0; i < images.size(); i++)
			{
				vec.push_back(images[i].toStdString());
			}

			m_pAppMgr->getLocalPhotosJson(vec, 
				CBind(&JSInterface::signalSerGetOrganization, this,
					CPlaceholders  _1, fname, uuid),
				CBind(&JSInterface::signalSerFileUploadFailure, this,
					CPlaceholders  _1));
		}
	}
END;
}

void JSInterface::onSerGetLocalPhotos(std::string str, QString fname,
	QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "Json: %s", str.data());
	emit callback(fname, uuid, QString::fromStdString(str));
END;
}

void JSInterface::getLocalFiles(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	Json::Reader reader;
	Json::Value obj;
	if (reader.parse(uuid.toStdString(), obj))
	{
		if (obj["size"].isInt())
		{
			QStringList files = QFileDialog::getOpenFileNames(NULL,
				QString::fromLocal8Bit(("请选择文件")), QDir::homePath());
			if (files.size() > obj["size"].asInt())
			{
				QString tip = QString("一次上传的文件不能超过%1个")
					.arg(obj["size"].asInt());
				QMessageBox msgbox(QMessageBox::Warning, transfer("提示"), tip,
					QMessageBox::Ok, NULL);
				msgbox.exec();
				return;
			}
			else if (files.size() == 0)
			{
				emit callback(fname, uuid, "{\"mFilePath\":[]}");
				return;
			}
			
			std::vector<std::string> vec;
			for(int i = 0; i < files.size(); i++)
			{
				vec.push_back(files[i].toStdString());
			}

			m_pAppMgr->getLocalFilesJson(vec, 
				CBind(&JSInterface::signalSerGetLocalFiles, this,
					CPlaceholders  _1, fname, uuid),
				CBind(&JSInterface::signalSerFileUploadFailure, this,
					CPlaceholders  _1));
		}
	}
END;
}

void JSInterface::onSerGetLocalFiles(std::string str, QString fname,
	QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "Json: %s", str.data());
	emit callback(fname, uuid, QString::fromStdString(str));
END;
}

void JSInterface::getInfoWithSweep(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	emit callback(fname, uuid, "{}");
END;
}

void JSInterface::showNavigationBar(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
END;
}

void JSInterface::closeView(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
END;
}

void JSInterface::getLanguage(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	Json::FastWriter writer;
	Json::Value obj;
	obj["language"] = "zh";
	QString str = QString::fromStdString(writer.write(obj));
	emit callback(fname, uuid, str);
END;
}

void JSInterface::getVersionMark(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	emit callback(fname, uuid, "{}");
END;
}

void JSInterface::copyTextToPaste(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	Json::Reader reader;
	Json::Value obj;
	if (reader.parse(uuid.toStdString(), obj))
	{
		if (obj["url"].isString())
		{
			QClipboard *clipboard = QApplication::clipboard();
			clipboard->setText(QString::fromStdString(obj["url"].asString()));
			clipboard = NULL;
		}
	}
END;
}

void JSInterface::getGroupMembers(QString fname, QString uuid)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "uuid: %s", uuid.toStdString().data());
	m_pAppMgr->getGroupMembersJson(uuid.toStdString(), 
		CBind(&JSInterface::signalSerGetGroupMembers, this,
			CPlaceholders  _1, fname, uuid));
END;
}

void JSInterface::onSerGetGroupMembers(std::string str, QString fname,
	QString uuid)
{
BEGIN;
	emit callback(fname, uuid, QString::fromStdString(str));
END;
}

void JSInterface::onSerFileUploadFailure(std::string str)
{
BEGIN;
	AddLog(LOG_LEV_INFO, "file name: %s", str.data());
	QString tip = QString("%1上传失败").arg(QString::fromStdString(str));
	QMessageBox msgbox(QMessageBox::Warning, transfer("提示"), tip,
		QMessageBox::Ok, NULL);
	msgbox.exec();
END;
}

Q_INVOKABLE void JSInterface::test()
{

}

Q_INVOKABLE void JSInterface::openChat(QString fname,QString params, QString uuid)
{
	LOG_METHOD("WebBrowserController::openChat", LOG_FILE);
	Json::Reader reader;
	Json::Value obj;
	if (reader.parse(params.toStdString(), obj))
	{
		if (obj["chatId"].isInt())
		{
			int64 ChatId = obj["chatId"].asInt64();
			emit signalSerOpenChatWidget(ChatId);
			Log(LOG_LEV_INFO, LOG_FILE, "ChatId: %lld", ChatId);
		}
		int64 chatidt = 21265121362;
		emit signalSerOpenChatWidget(chatidt);
	}
}

