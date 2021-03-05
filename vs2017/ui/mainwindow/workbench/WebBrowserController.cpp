#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QStandardPaths>
#include <QGuiApplication>
#include <QClipboard>
#include <QMetaType>
#include <QFileInfo>
#include <common/ChineseInfos.hpp>
#include <utils/PinYinConvert.h>
#include <utils/Error.h>
#include "WebBrowserController.h"
#include <QPainter>
#include <interface/jsonToolExport.h>
#include <interface/jsonTransTool.h>
extern std::string g_serverName;
std::string g_version;
WebBrowserController::WebBrowserController(QObject *parent)
{
	//qRegisterMetaType<MemberList>("MemberList&");

	/*m_userService = USERSERVICE;
	m_contactService = CONTACTSERVICE;
	m_lddService = LDDSERVICE;
	m_groupService = GROUPSERVICE;
	m_fileService = FILESERVICE;
	m_configService = CONFIGSERVICE;
	m_authService = AUTHSERVICE;
	CONNECT_SERVICE(GetVisibleOrgUsers(service::ErrorInfo, int8, int8,
	std::vector<model::OrganizationInfo>&,
	std::vector<model::EntpriseUserInfo>&,
	QString, QString));
	CONNECT_SERVICE(SendImage(service::ErrorInfo, int64, const std::string&,
	const std::string&, QStringList, QJsonArray, QJsonArray,uint, QString, QString));
	CONNECT_SERVICE(SendFile(service::ErrorInfo, int64, const std::string&,
	QStringList, QJsonArray, QJsonArray, uint, QString, QString));
	CONNECT_SERVICE(GetGroupMembers(service::ErrorInfo, MemberList&, QString,
	QString));
	CONNECT_SERVICE(CreateGroup(service::ErrorInfo, int64, QString, QString));
	CONNECT_SERVICE(DeleteGroup(service::ErrorInfo,QString, QString));
	CONNECT_SERVICE(AuthAccessToken(service::ErrorInfo, const std::string, QString, QString));
	CONNECT_SERVICE(CircleOfFriend(service::ErrorInfo, std::string&, QString, QString));*/
}

WebBrowserController::~WebBrowserController()
{

}

//void WebBrowserController::InitUI(QQuickView* view, QQuickItem* item)
//{
//	QVariant v;
//	v.setValue(this);
//	item->setProperty("ctrl", v);
//}

//void WebBrowserController::UnInitUI()
//{
//
//}

void WebBrowserController::setJssdkVersion(QString param)
{
	//LOG_METHOD("WebBrowserController::setJssdkVersion", LOG_FILE);
	QJsonDocument doc = QJsonDocument::fromJson(param.toUtf8());
	QJsonValue jsVersion = doc.object().value("version");
	if (jsVersion.isUndefined())
	{
		g_version = "1.8.0";
	}
	else
	{
		g_version = jsVersion.toVariant().toString().toStdString();
	}
}

void WebBrowserController::openChat(QString fname, QString paramjson, QString uuid){
	//LOG_METHOD("WebBrowserController::openChat", LOG_FILE);
	QJsonParseError json_error;
	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8(), &json_error);
	if (json_error.error != QJsonParseError::NoError)
	{
		return;
	}
	QJsonValue chatId = doc.object().value("chatid");
	if (chatId.isUndefined())
	{
		//Log(LOG_LEV_INFO, LOG_FILE, "chatId error");
		return;
	}
	int64 ChatId = chatId.toVariant().toLongLong();
	emit signalCtrlStartChat(ChatId);
	//Log(LOG_LEV_INFO, LOG_FILE, "ChatId: %lld", ChatId);
}






//void WebBrowserController::takePhoto(QString fname, QString uuid)
//{
//	//LOG_METHOD("WebBrowserController::takePhoto()", LOG_FILE);
//	//Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//	emit callback(fname, uuid, "{}");
//}

//void WebBrowserController::getAccountInfo(QString param, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getAccountInfo()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//	model::Account accountInfo;
//	m_userService->getAccountInfo(accountInfo);
//	QJsonDocument doc = QJsonDocument::fromJson(param.toUtf8());
//	QJsonValue isEntUser = doc.object().value("isEntUser");
//	Log(LOG_LEV_INFO, LOG_FILE, "UserName: %s, UserID: %lld",
//		QString::fromStdString(accountInfo.name.value()).toLocal8Bit().data(),
//		accountInfo.id.value());
//	QString serverName = getAreaName();
//	QJsonObject object;
//	QString mPortraitUrl;
//
//	mPortraitUrl = QString::fromStdString(accountInfo.thumbAvatarUrl.value());
//	if (isEntUser.isUndefined() )
//	{	
//		object.insert("mUserName", QString::fromStdString(accountInfo.name.value()));
//		object.insert("mUserId", QString::number(accountInfo.id.value()));
//		object.insert("mPortraitUrl", mPortraitUrl);
//		object.insert("serverName", QString::fromStdString(g_serverName));
//		object.insert("extend", QString::fromStdString(accountInfo.extends.value()));
//		object.insert("nickID", QString::fromStdString(accountInfo.nickId.value()));
//		object.insert("phoneNumber", QString::fromStdString(accountInfo.phone.value()));
//		object.insert("email", QString::fromStdString(accountInfo.email.value()));
//		object.insert("serverHost", QString::fromStdString(getOutterIP()));
//		qDebug() << QString::fromStdString(accountInfo.extends.value());
//		QJsonDocument document;
//		document.setObject(object);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//		emit callback(param, uuid, strJSON);
//		Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toLocal8Bit().data());
//		
//	}
//	else
//	{	
//		bool IsEntUser = isEntUser.toVariant().toBool();
//		if (IsEntUser)
//		{
//			m_lddService->queryEntUserOneById(0,accountInfo.id.value(), std::bind(&WebBrowserController::signalSerEntUserInfo, this, std::placeholders::_1, std::placeholders::_2, param, uuid));
//		}
//		else
//		{
//			QJsonObject object;
//			object.insert("mUserName", QString::fromStdString(accountInfo.name.value()));
//			object.insert("mUserId", QString::number(accountInfo.id.value()));
//			object.insert("mPortraitUrl", mPortraitUrl);
//			object.insert("serverName", QString::fromStdString(g_serverName));
//			object.insert("extend", QString::fromStdString(accountInfo.extends.value()));
//			object.insert("nickID", QString::fromStdString(accountInfo.nickId.value()));
//			object.insert("phoneNumber", QString::fromStdString(accountInfo.phone.value()));
//			object.insert("email", QString::fromStdString(accountInfo.email.value()));
//			object.insert("serverHost", QString::fromStdString(getOutterIP()));
//			qDebug() << QString::fromStdString(accountInfo.extends.value());
//			QJsonDocument document;
//			document.setObject(object);
//			QString strJSON(document.toJson(QJsonDocument::Compact));
//
//			emit callback(param, uuid, strJSON);
//			Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toLocal8Bit().data());
//		}
//	}
//}
//void WebBrowserController::onSerEntUserInfo(service::ErrorInfo err, std::vector<EntpriseUserInfo> entinfo, QString param, QString uuid)
//{
//	QJsonObject object;
//	QString serverName = getAreaName();
//	for (auto i : entinfo)
//	{
//		object.insert("mUserName", QString::fromStdString(i.enName));
//		object.insert("mUserId", QString::number(i.userID));
//		QString mPortraitUrl;
//		mPortraitUrl =  QString::fromStdString(i.userHeadUrl);
//		object.insert("mPortraitUrl", mPortraitUrl);
//		object.insert("serverName", QString::fromStdString(g_serverName));
//		object.insert("extend", QString::fromStdString(i.extend));
//		object.insert("nickID", QString::number(i.roleID));
//		object.insert("phoneNumber", QString::fromStdString(i.enMobile));
//		object.insert("email", QString::fromStdString(i.enMail));
//		object.insert("serverHost", QString::fromStdString(getOutterIP()));
//	}
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	emit callback(param, uuid, strJSON);
//	Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toLocal8Bit().data());
//}
//void WebBrowserController::getPosition(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getPosition()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//	emit callback(fname, uuid, "{}");
//}
//
//void WebBrowserController::getContactList(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getContactList()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonObject object;
//	QJsonArray arr;
//	std::vector< std::shared_ptr<model::Contact> > vecContacts;
//	m_contactService->getContactList(vecContacts);
//	for (auto contact : vecContacts)
//	{
//		if (contact->isApp.value() == 2)
//		{
//			Log(LOG_LEV_INFO, LOG_FILE, "buddyName: %s, serverName: %s, "
//				"pinyin: %s, buddyID: %lld, isApp: %d",
//				QString::fromStdString(contact->name.value()).toLocal8Bit().data(),
//				QString::fromStdString(contact->server.value()).toLocal8Bit().data(),
//				QString::fromStdString(contact->pinyin.value()).toLocal8Bit().data(),
//				contact->id.value(),
//				contact->isApp.value());
//
//			QJsonObject obj;
//			QString mPortraitUrl;
//			if (contact->name.value().length() == 0)
//			{
//				obj.insert("buddyName", QString::number(contact->id.value()));
//			}
//			else
//			{
//				obj.insert("buddyName", QString::fromStdString(contact->name.value()));
//			}
//			obj.insert("serverName", QString::fromStdString(contact->server.value()));
//			mPortraitUrl = QString::fromStdString(contact->thumbAvatarUrl.value());
//			obj.insert("portraitURL", mPortraitUrl);
//			char c;
//			if (contact->pinyin.value().length() != 0)
//			{
//				c = contact->pinyin.value().at(0);
//			}
//			else if (contact->name.value().length() != 0)
//			{
//				c = utils::PinYinConvert::GetTeam(contact->name.value());
//			}
//			else
//			{
//				c = '#';
//			}
//			obj.insert("buddyNameInitial", QString(c));
//			obj.insert("buddyID", QString::number(contact->id.value()));
//			arr.push_back(obj);
//		}
//	}
//
//	object.insert("contacts", arr);
//
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//
//	emit callback(fname, uuid, strJSON);
//	splitLog(strJSON);
//}
//
//void WebBrowserController::getOrganization(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getOrganization()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonDocument doc = QJsonDocument::fromJson(uuid.toUtf8());
//	QJsonValue valOrgId = doc.object().value("orgId");
//	if (valOrgId.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "orgid error");
//		return;
//	}
//
//	qint64 orgId = valOrgId.toVariant().toLongLong();
//	Log(LOG_LEV_INFO, LOG_FILE, "orgid: %lld", orgId);
//
//	m_lddService->getVisibleOrgUsers(0, 0, orgId,
//		std::bind(&WebBrowserController::signalSerGetVisibleOrgUsers,
//			this, std::placeholders::_1, std::placeholders::_2,
//			std::placeholders::_3, std::placeholders::_4,
//			std::placeholders::_5, fname, uuid));
//}
//
//void WebBrowserController::getGroupList(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getGroupList()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonObject object;
//	QJsonArray arr;
//	std::vector<std::shared_ptr<TinyGroup>> groups;
//	m_groupService->getGroupList(groups);
//	for (auto group : groups)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "groupName: %s, pinyin: %s, serverName: %s, "
//			"groupID: %lld",
//			QString::fromStdString(group->groupName.value()).toLocal8Bit().data(),
//			QString::fromStdString(group->pinyin.value()).toLocal8Bit().data(),
//			QString::fromStdString(group->server.value()).toLocal8Bit().data(),
//			group->groupId.value());
//
//		QJsonObject obj;
//		obj.insert("groupName", QString::fromStdString(group->groupName.value()));
//		char c;
//		if (group->pinyin.value().length() != 0)
//		{
//			c = group->pinyin.value().at(0);
//		}
//		else if (group->groupName.value().length() != 0)
//		{
//			c = utils::PinYinConvert::GetTeam(group->groupName.value());
//		}
//		else
//		{
//			c = '#';
//		}
//		obj.insert("groupNameInitial", QString(c));
//		obj.insert("serverName", QString::fromStdString(group->server.value()));
//		obj.insert("groupPortraitURL", QString::fromStdString(group->avatarUrl.value()));
//		obj.insert("groupID", QString::number(group->groupId.value()));
//		arr.push_back(obj);
//	}
//	object.insert("groupsInfo", arr);
//
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//
//	emit callback(fname, uuid, strJSON);
//	splitLog(strJSON);
//}
//
//void WebBrowserController::getLocalPhotos(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getLocalPhotos()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonDocument doc = QJsonDocument::fromJson(uuid.toUtf8());
//	int size = doc.object().value("size").toInt(10);
//	Log(LOG_LEV_INFO, LOG_FILE, "size: %d", size);
//
//	QStringList images = QFileDialog::getOpenFileNames(NULL,
//		CHOOSE_IMAGES_DIALOG_TITlE, QDir::homePath(),
//		"Images (*.png *.xpm *.jpg *.bmp)");
//	if (images.size() > size)
//	{
//		QString tip = QString(IMAGES_NUMBER_ERROR_TIP).arg(size);
//		CMessageBox msgbox(CMessageBox::Warning, PROMPT, tip, CMessageBox::Ok, NULL);
//		msgbox.exec();
//		return;
//	}
//	else if (images.size() == 0)
//	{
//		QJsonObject object;;
//		object.insert("resultCode", -2);
//		object.insert("mPhotoPath", "[]");
//		object.insert("mThumbPhotoPath", "[]");
//		QJsonDocument document;
//		document.setObject(object);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//		emit callback(fname, uuid, strJSON);
//		return;
//	}
//
//	QJsonArray jsonArr;
//	QJsonArray jsontmbArr;
//	std::string imagesPath = images[0].toUtf8().data();
//	QString thumbImgPath;
//	scaledImage(QString::fromUtf8(imagesPath.c_str()), THUMP_PIC_WIDTH, THUMP_PIC_HEIGHT, thumbImgPath);
//	m_fileService->uploadImage(0, 0, imagesPath, thumbImgPath.toStdString(), "",
//		std::bind(&WebBrowserController::signalSerSendImage, this,
//			std::placeholders::_1, std::placeholders::_2,
//			std::placeholders::_3, std::placeholders::_4,
//			images, jsonArr, jsontmbArr, 0, fname, uuid));
//}
//void WebBrowserController::scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight, QString &outImagePath)
//{
//#ifdef  _WIN32
//
//#elif  defined(__linux__)
//	sourceImagePath = "/" + sourceImagePath;
//#elif  defined(__APPLE__)
//	sourceImagePath = "/" + sourceImagePath;
//#endif
//
//	QSize sourceSize;
//	int sourceWidth = 0;
//	int sourceHeight = 0;
//	int resultWidth = 0;
//	int resultHeight = 0;
//	float scaledNum = 0;      //缩放比例
//
//	QPixmap sourceImage;
//	bool isLoader = sourceImage.load(sourceImagePath);
//	if (!isLoader)
//	{
//		QFile tempFile(sourceImagePath);
//		if (tempFile.open(QFile::ReadOnly))
//		{
//			isLoader = sourceImage.loadFromData(tempFile.readAll());
//		}
//	}
//
//	sourceSize = sourceImage.size();
//	sourceWidth = sourceSize.width();
//	sourceHeight = sourceSize.height();
//
//	if (sourceWidth >= scaledWidth && sourceHeight >= scaledHeight)
//	{
//		if (sourceWidth >= sourceHeight)
//		{
//			scaledNum = scaledWidth / sourceWidth;
//			resultWidth = scaledWidth;
//			resultHeight = scaledNum*sourceHeight;
//		}
//		else
//		{
//			scaledNum = scaledHeight / sourceHeight;
//			resultHeight = scaledHeight;
//			resultWidth = scaledNum*sourceWidth;
//		}
//	}
//	else if (sourceWidth >= scaledWidth && sourceHeight <= scaledHeight)
//	{
//		scaledNum = scaledWidth / sourceWidth;
//		resultWidth = scaledWidth;
//		resultHeight = scaledNum*sourceHeight;
//	}
//	else if (sourceWidth <= scaledWidth && sourceHeight >= scaledHeight)
//	{
//		scaledNum = scaledHeight / sourceHeight;
//		resultHeight = scaledHeight;
//		resultWidth = scaledNum*sourceWidth;
//	}
//	else
//	{
//		resultWidth = sourceWidth;
//		resultHeight = sourceHeight;
//	}
//
//	if (resultWidth <10)
//	{
//		resultWidth = 10;
//	}
//	if (resultHeight < 10)
//	{
//		resultHeight = 10;
//	}
//	QPixmap destinationImage400x300 = sourceImage.scaled(QSize(resultWidth, resultHeight), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
//
//	QFileInfo fileInfo(sourceImagePath);
//
//	QString tempImagePath = QString::fromUtf8(m_configService->userImgPath().c_str()) + "cache";
//	QDir tempDir;
//	if (!tempDir.exists(tempImagePath))
//	{
//		tempDir.mkdir(tempImagePath);
//	}
//
//	outImagePath = tempImagePath + "/" + fileInfo.baseName() + "_" + QString::number(scaledWidth)
//		+ "x" + QString::number(scaledHeight) + ".png";
//
//	destinationImage400x300.save(outImagePath, "PNG", 99);
//
//	//解决背景透明，jpg为黑色背景问题
//	QImage pngImage;
//	bool isRet = pngImage.load(outImagePath);
//	QImage jpgImage(pngImage.size(), QImage::Format_ARGB32);
//	jpgImage.fill(QColor(Qt::white).rgb());
//	QPainter painter(&jpgImage);
//	painter.drawImage(0, 0, pngImage);
//	outImagePath = tempImagePath + "/" + fileInfo.baseName() + "_" + QString::number(scaledWidth)
//		+ "x" + QString::number(scaledHeight) + ".jpg";
//	jpgImage.save(outImagePath, "JPEG", 99);
//}
//void WebBrowserController::getLocalFiles(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getLocalFiles()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonDocument doc = QJsonDocument::fromJson(uuid.toUtf8());
//	int size = doc.object().value("size").toInt(10);
//	Log(LOG_LEV_INFO, LOG_FILE, "size: %d", size);
//
//	QStringList files = QFileDialog::getOpenFileNames(NULL,
//		CHOOSE_FILES_DIALOG_TITlE, QDir::homePath());
//	Log(LOG_LEV_INFO, LOG_FILE, "QFileDialog::getOpenFileNames size: %d", files.size());
//	if (files.size() > size)
//	{
//		QString tip = QString(FILES_NUMBER_ERROR_TIP).arg(size);
//		CMessageBox msgbox(CMessageBox::Warning, PROMPT, tip, CMessageBox::Ok, NULL);
//		msgbox.exec();
//		return;
//	}
//	
//	else if (files.size() == 0)
//	{
//		QJsonObject object;;
//		object.insert("resultCode",-2);
//		object.insert("mFilePath", "[]");
//		object.insert("mFileName", "[]");
//		QJsonDocument document;
//		document.setObject(object);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//		emit callback(fname, uuid, strJSON);
//		return;
//	}
//
//	UploadFileProperty fileProperty;
//	fileProperty.localid = 0;
//	fileProperty.targetid = 0;
//	fileProperty.type = MEDIA_MSG_FILE;
//	fileProperty.localPath = files[0].toUtf8().data();
//	fileProperty.msg = "";
//	fileProperty.encryptKey = "";
//	fileProperty.isP2p = 0;
//	QJsonArray jsonArrPath;
//	QJsonArray jsonArrName;
//	int64 fileID = m_fileService->uploadFile(fileProperty,
//		std::bind(&WebBrowserController::signalSerSendFile, this,
//		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
//		files, jsonArrPath, jsonArrName, 0, fname, uuid));
//}
//
//void WebBrowserController::getInfoWithSweep(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getInfoWithSweep()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//	emit callback(fname, uuid, "{}");
//}
//
//void WebBrowserController::showNavigationBar(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::showNavigationBar()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//}
//
//void WebBrowserController::closeView(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::closeView()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//	emit signalBtnCloseClicked();
//}
//
//void WebBrowserController::getLanguage(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getLanguage()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QString language = utils::Error::IsChinese()? "zh" : "en";
//	
//	QJsonObject object;
//	object.insert("language", language);
//
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//
//	emit callback(fname, uuid, strJSON);
//	Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toStdString().data());
//}
//
//void WebBrowserController::getVersionMark(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getVersionMark()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//	emit callback(fname, uuid, "{}");
//}
//
//void WebBrowserController::copyTextToPaste(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::copyTextToPaste()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonDocument doc = QJsonDocument::fromJson(uuid.toUtf8());
//	QJsonValue obj = doc.object().value("url");
//	if (obj.isString())
//	{
//		QString url = obj.toString();
//		QClipboard *clipboard = QGuiApplication::clipboard();
//		clipboard->setText(url);
//		clipboard = NULL;
//	}
//}
//
//void WebBrowserController::getGroupMembers(QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::getGroupMembers()", LOG_FILE);
//	Log(LOG_LEV_INFO, LOG_FILE, "uuid: %s", uuid.toStdString().data());
//
//	QJsonDocument doc = QJsonDocument::fromJson(uuid.toUtf8());
//	QJsonValue valGroupId = doc.object().value("groupID");
//	if (valGroupId.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "groupID error");
//		return;
//	}
//	int64 groupID = valGroupId.toVariant().toLongLong();
//	Log(LOG_LEV_INFO, LOG_FILE, "groupID: %d", groupID);
//
//	m_groupService->getMemberList(groupID, 
//		std::bind(&WebBrowserController::signalSerGetGroupMembers, this,
//			std::placeholders::_1, std::placeholders::_2, fname, uuid));
//}

//void WebBrowserController::createGroup(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::createGroup", LOG_FILE);
//	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8());
//	QJsonValue groupNameVal = doc.object().value("groupName");
//	QJsonValue userVal = doc.object().value("users");
//	if (groupNameVal.isUndefined() || userVal.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "groupNameVal or userVal error");
//		return;
//	}
//	
//	QString groupname;
//	if (groupNameVal.isString()){
//	  groupname = groupNameVal.toVariant().toString();
//	}
//	
//	QJsonArray userArray;
//	if ( userVal.isArray())
//	{
//		userArray = userVal.toArray();
//	}
//
//	std::vector<int64> users;
//	for (auto index : userArray)
//	{
//		users.push_back(index.toVariant().toLongLong());
//	}
//	Log(LOG_LEV_DEBUG, LOG_FILE, "paramjson=%s", paramjson.toLocal8Bit().data());
//	//调用sdk创建群接口
//	m_groupService->createGroup(1, groupname.toUtf8().data(), users,
//		std::bind(&WebBrowserController::signalSerCreateGroup, this,
//		std::placeholders::_1, std::placeholders::_2, fname, uuid));
//}
//void WebBrowserController::deleteGroup(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::deleteGroup", LOG_FILE);
//	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8());
//	QJsonValue groupIdVal = doc.object().value("groupId");
//	if (groupIdVal.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "groupIdVal error");
//		return;
//	}
//	int64 groupID = 0;
//	groupID = groupIdVal.toVariant().toLongLong();
//
//	if (!groupID)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "groupID is zero!");
//		return;
//	}
//	//删除群
//	m_groupService->removeGroup(1, groupID, 
//		std::bind(&WebBrowserController::signalSerDeleteGroup, this,
//		std::placeholders::_1,fname, uuid));
//}
//void WebBrowserController::openAudioVideo(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::openAudioVideo", LOG_FILE);
//	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8());
//	QJsonValue isVedio = doc.object().value("isVideoModel");
//	QJsonValue isConference = doc.object().value("isConferenceModel");
//	QJsonValue users = doc.object().value("users");
//
//
//	if (isVedio.isUndefined() || isConference.isUndefined() || users.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "isVideoModel or isConferenceModel or  users error");
//		Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//		return;
//	}
//	Log(LOG_LEV_DEBUG, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//	
//	bool isVedioModel = isVedio.isBool() ? isVedio.toBool():false;
//	bool isConferenceModel = isConference.isBool() ? isConference.isBool() : false;
//	QJsonArray  userarry = users.isArray() ? users.toArray(): QJsonArray();
//	std::vector<int64>conferenceUsers;
//	for (auto index : userarry)
//	{
//		conferenceUsers.push_back(index.toVariant().toLongLong());
//	}
//
//
//}
//void WebBrowserController::openVideoConference(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::openVideoConference", LOG_FILE);
//	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8());
//	QJsonValue  videoTypeVal = doc.object().value("videoType");
//	QJsonValue  paramVal = doc.object().value("param");
//	if (videoTypeVal.isUndefined() || paramVal.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "paramVal or videoTypeVal  error");
//		Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//		return;
//	}
//	Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//	int vedioType = videoTypeVal.isNull() ? 0 : videoTypeVal.toVariant().toInt();
//	QString parameter = paramVal.isString() ? paramVal.toVariant().toString() : "";
//
//}
//void WebBrowserController::getOAuthCode(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::getOAuthCode", LOG_FILE);
//	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8());
//	QJsonValue  appIdVal = doc.object().value("appId");
//	QJsonValue  appSecretVal = doc.object().value("appSecret");
//	if (appIdVal.isUndefined() || appSecretVal.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "appSecretVal or appIdVal  error");
//		Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//		return;
//	}
//	Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//
//	int64 appId = appIdVal.isNull() ? 0 : appIdVal.toVariant().toLongLong();
//	QString appSecret = appSecretVal.isString() ? appSecretVal.toVariant().toString() : "";
//
//	model::Account info;
//	m_userService->getAccountInfo(info);
//	std::vector<model::LoginInfo> longinlist = m_configService->getLoginInfos();
//	int usertype = 0;
//	for (auto index : longinlist)
//	{
//		if ( index.userId == info.id.value())
//		{
//			usertype = index.userType;
//			break;
//		}
//	}
//	Log(LOG_LEV_DEBUG, LOG_FILE, "userType=%d", usertype);
//	std::string strUsertype = QString::number(usertype).toStdString();
//	std::string strAppSecret = appSecret.toStdString();
//	m_authService->getAuthAccessToken(appId,strUsertype,strAppSecret,
//		std::bind(&WebBrowserController::signalSerAuthAccessToken, this,
//		std::placeholders::_1, std::placeholders::_2, fname, uuid));
//}
//void WebBrowserController::getUserIdMap(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::getUserIdMap", LOG_FILE);
//	QJsonDocument doc = QJsonDocument::fromJson(paramjson.toUtf8());
//	QJsonValue  accountTypeVal = doc.object().value("accountType");
//	QJsonValue  accountVal = doc.object().value("accounts");
//	if (accountTypeVal.isUndefined() || accountVal.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "accountTypeVal or accountVal  error");
//		Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//		return;
//	}
//	Log(LOG_LEV_ERROR, LOG_FILE, "paramjson:%s", paramjson.toLocal8Bit().data());
//
//	int accountType = accountTypeVal.isNull() ? 0 : accountTypeVal.toVariant().toInt();
//	QJsonArray account = accountVal.isArray() ? accountVal.toArray() : QJsonArray();
//	std::vector<std::string> acounts;
//	for (auto index : account)
//	{
//		acounts.push_back(index.toVariant().toString().toStdString());
//	}
//	m_userService->getIdByAccount(acounts, std::bind(&WebBrowserController::signalSerUserId, this,
//		std::placeholders::_1, std::placeholders::_2, fname, uuid));
//}
//void WebBrowserController::onSerUserId(service::ErrorInfo err, std::map<std::string, int64> acounts, QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::onSerUserId", LOG_FILE);
//	QJsonObject objAcount;
//	for (auto acount : acounts)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "userId: %lld, accounts: %s",
//			acount.second,
//			QString::fromStdString(acount.first).toLocal8Bit().data());
//
//		objAcount.insert(QString::fromStdString(acount.first), QString::number(acount.second));
//	}
//	QJsonDocument document;
//	document.setObject(objAcount);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	emit callback(fname, uuid, strJSON);
//	splitLog(strJSON);
//}
//void WebBrowserController::circleOfFriend(QString fname, QString paramjson, QString uuid){
//	LOG_METHOD("WebBrowserController::circleOfFriend", LOG_FILE);
//	std::string reqjson = paramjson.toUtf8().data();
//	Log(LOG_LEV_DEBUG, LOG_FILE, "reqjson=%s", reqjson.c_str());
//	std::string loginfoPath = "";
//	m_userService->circleOfFriend(reqjson, loginfoPath,
//		std::bind(&WebBrowserController::signalSerCircleOfFriend, this,
//		std::placeholders::_1, std::placeholders::_2, fname, uuid));
//
//}
//void WebBrowserController::getServerName(QString fname, QString uuid){
//	LOG_METHOD("WebBrowserController::getServerName", LOG_FILE);
//	QString  host("");
//	host = QString::fromStdString(getOutterIP());
//	if (host.right(0) != QString("/")){
//		host.append("/");
//	}
//	QJsonObject json;
//	json.insert("host", host);
//	QJsonDocument document;
//	document.setObject(json);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//
//	emit callback(fname, uuid, strJSON);
//	Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toStdString().data());
//}
//void WebBrowserController::onSerCircleOfFriend(service::ErrorInfo err, std::string&contentjson, QString fname, QString uuid){
//	LOG_METHOD("WebBrowserController::onSerCircleOfFriend", LOG_FILE);
//	QString strJSON;
//	strJSON = QString::fromStdString(contentjson);
//	emit callback(fname, uuid, strJSON);
//	splitLog(strJSON);
//}
//void WebBrowserController::onSerGetVisibleOrgUsers(service::ErrorInfo err,
//	int8 allowChat, int8 contactVisiable,
//	std::vector<model::OrganizationInfo>& orgs,
//	std::vector<model::EntpriseUserInfo>& users,
//	QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::onSerGetVisibleOrgUsers", LOG_FILE);
//	QJsonObject objJson;
//	QJsonArray arrOrg, arrUser;
//	for (auto org : orgs)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "orgID: %lld, orgName: %s",
//			org.orgID,
//			QString::fromStdString(org.orgName).toLocal8Bit().data());
//
//		QJsonObject obj;
//		obj.insert("orgID", QString::number(org.orgID));
//		obj.insert("orgName", QString::fromStdString(org.orgName));
//		arrOrg.push_back(obj);
//	}
//
//	for (auto user : users)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "staffID: %lld, staffName: %s",
//			user.userID,
//			QString::fromStdString(user.enName).toLocal8Bit().data());
//
//		QJsonObject obj;
//		QString mPortraitUrl;
//		obj.insert("staffID", QString::number(user.userID));
//		obj.insert("staffName", QString::fromStdString(user.enName));
//		mPortraitUrl = QString::fromStdString(user.userHeadUrl);
//		obj.insert("portraitURL", mPortraitUrl);
//		arrUser.push_back(obj);
//	}
//
//
//	objJson.insert("organization", arrOrg);
//	objJson.insert("staff", arrUser);
//	objJson.insert("serverName", QString::fromStdString(g_serverName));
//
//	QJsonDocument document;
//	document.setObject(objJson);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//
//	emit callback(fname, uuid, strJSON);
//	splitLog(strJSON);
//
//	
//}
//
//void WebBrowserController::onSerSendImage(service::ErrorInfo err, 
//	int64 targetId, const std::string& srcJson, const std::string& thumpJson,
//	QStringList images, QJsonArray arrImages, QJsonArray arrTmbImages, uint time,
//	QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::onSerSendImage", LOG_FILE);
//
//	QString imagePath = images[time];
//	QString imageName = imagePath.mid(imagePath.lastIndexOf('/') + 1);
//
//	if (err == 0)
//	{
//
//		service::jst_MediaMsgResult mediaResult(1, 0);
//		std::string tempJson = thumpJson;
//		service::logic_jsonTransToStruct(service::json_MediaMsgResult, tempJson, &mediaResult);
//		QJsonValue tmburl = QJsonValue(QString::fromUtf8(mediaResult.thumbUrl.c_str()));
//		mediaResult.isthumb = 0;
//		tempJson = srcJson;
//		service::logic_jsonTransToStruct(service::json_MediaMsgResult, tempJson, &mediaResult);
//		QJsonValue mainurl = QJsonValue(QString::fromUtf8(mediaResult.url.c_str()));
//
//		if (mainurl.isString())
//		{
//			arrImages.push_back(mainurl);
//			arrTmbImages.push_back(tmburl);
//		}
//
//		Log(LOG_LEV_INFO, LOG_FILE, "mainurl: %s,tmburl: %s", mainurl.toString().toStdString().data(), tmburl.toString().toStdString().data());
//	}
//	else {
//		QString tip = QString(FILE_UPLOAD_ERROR_TIP).arg(imageName);
//		CMessageBox msgbox(CMessageBox::Warning, PROMPT, tip, CMessageBox::Ok, NULL);
//		msgbox.exec();
//		Log(LOG_LEV_INFO, LOG_FILE, "%s upload failed", imageName.toStdString().data());
//		QJsonObject object;;
//		object.insert("resultCode", -1);
//		object.insert("mPhotoPath", "[]");
//		object.insert("mThumbPhotoPath", "[]");
//		QJsonDocument document;
//		document.setObject(object);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//		emit callback(fname, uuid, strJSON);
//		return;
//	}
//
//	time++;
//	if (images.size() <= time)
//	{
//		QJsonObject json;
//		json.insert("resultCode", 0);
//		json.insert("mPhotoPath", arrImages);
//		json.insert("mThumbPhotoPath", arrTmbImages);
//		QJsonDocument document;
//		document.setObject(json);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//
//		emit callback(fname, uuid, strJSON);
//		Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toStdString().data());
//	}
//	else{
//		std::string imagesPath = images[time].toUtf8().data();
//		m_fileService->uploadImage(0, 0, imagesPath, imagesPath, "",
//			std::bind(&WebBrowserController::signalSerSendImage, this,
//				std::placeholders::_1, std::placeholders::_2,
//				std::placeholders::_3, std::placeholders::_4,
//				images, arrImages, arrTmbImages,time, fname, uuid));
//	}
//}
//
//void WebBrowserController::onSerSendFile(service::ErrorInfo err,
//	int64 targetId, const std::string& fileJson, QStringList files,
//	QJsonArray arrFiles,QJsonArray arrFileNames, uint time, QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::onSerSendFile", LOG_FILE);
//
//	QString filePath = files[time];
//	QString fileName = filePath.mid(filePath.lastIndexOf('/') + 1);
//
//	if (err == 0)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "fileJson: %s", fileJson.data());
//		
//		//解析json
//		service::jst_MediaMsgResult mediaResult(0, 0);
//		std::string tempJson = fileJson;
//		bool bret = service::logic_jsonTransToStruct(service::json_MediaMsgResult, tempJson, &mediaResult);
//		if (!bret)
//		{
//			Log(LOG_LEV_ERROR, LOG_FILE, "logic_jsonTransToStruct failed, fileJson = %s", tempJson.c_str());
//		}
//		QString url = QString::fromUtf8(mediaResult.url.data());
//		arrFiles.push_back(url);
//		arrFileNames.push_back(fileName);
//		Log(LOG_LEV_INFO, LOG_FILE, "url: %s", url.toLocal8Bit().data());
//	}
//	else {
//		QString tip = QString(FILE_UPLOAD_ERROR_TIP).arg(fileName);
//		CMessageBox msgbox(CMessageBox::Warning, PROMPT, tip, CMessageBox::Ok, NULL);
//		msgbox.exec();
//		Log(LOG_LEV_INFO, LOG_FILE, "%s upload failed", fileName.toStdString().data());
//		QJsonObject object;;
//		object.insert("resultCode", -1);
//		object.insert("mFilePath", "[]");
//		object.insert("mFileName", "[]");
//		QJsonDocument document;
//		document.setObject(object);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//		emit callback(fname, uuid, strJSON);
//		return;
//	}
//
//	time++;
//	if (files.size() <= time)
//	{
//		QJsonObject json;
//		json.insert("resultCode", 0);
//		json.insert("mFilePath", arrFiles);
//		json.insert("mFileName", arrFileNames);
//		QJsonDocument document;
//		document.setObject(json);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//
//		emit callback(fname, uuid, strJSON);
//		Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJSON.toStdString().data());
//	}
//	else{
//		UploadFileProperty fileProperty;
//		fileProperty.localid = 0;
//		fileProperty.targetid = 0;
//		fileProperty.type = MEDIA_MSG_FILE;
//		fileProperty.localPath = files[time].toUtf8().data();
//		fileProperty.msg = "";
//		fileProperty.encryptKey = "";
//		fileProperty.isP2p = 0;
//		int64 fileID = m_fileService->uploadFile(fileProperty,
//			std::bind(&WebBrowserController::signalSerSendFile, this,
//			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
//			files, arrFiles, arrFileNames, time, fname, uuid));
//	}
//}
//
//void WebBrowserController::onSerGetGroupMembers(service::ErrorInfo err,
//	MemberList& members, QString fname, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::onSerGetGroupMembers", LOG_FILE);
//
//	if (err == 0)
//	{
//		QJsonObject object;
//		QJsonArray arr;
//		for (auto member : members)
//		{
//			if (!(member->isApp.value()))
//			{
//				Log(LOG_LEV_INFO, LOG_FILE, "memberName: %s, memberID: %lld",
//					QString::fromStdString(member->name.value()).toLocal8Bit().data(),
//					member->id.value());
//
//				QJsonObject obj;
//				obj.insert("memberName", QString::fromStdString(member->remark.value()));
//				object.insert("portraitURL", QString::fromStdString(member->thumbAvatarUrl.value()));
//				char c = utils::PinYinConvert::GetTeam(member->name.value());
//				obj.insert("memberNameInitial", QString(c));
//				obj.insert("memberID", QString::number(member->id.value()));
//				arr.push_back(obj);
//			}
//		}
//
//		object.insert("members", arr);
//
//		QJsonDocument document;
//		document.setObject(object);
//		QString strJSON(document.toJson(QJsonDocument::Compact));
//
//		emit callback(fname, uuid, strJSON);
//		splitLog(strJSON);
//	}
//	else 
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "err = %d", err);
//	}
//}
//void WebBrowserController::onSerCreateGroup(service::ErrorInfo err, int64 groupid, QString fname, QString uuid){
//	LOG_METHOD("WebBrowserController::onSerCreateGroup", LOG_FILE);
//	QJsonObject object;
//	object.insert("resultCode", err);
//	object.insert("groupID", QString::number(groupid));
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	Log(LOG_LEV_DEBUG, LOG_FILE, "strJson=%s", strJSON.toLocal8Bit().data());
//	emit callback(fname, uuid, strJSON);
//}
//void WebBrowserController::onSerDeleteGroup(service::ErrorInfo err, QString fname, QString uuid){
//	LOG_METHOD("WebBrowserController::onSerDeleteGroup", LOG_FILE);
//	QJsonObject object;
//	object.insert("resultCode", err);
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	Log(LOG_LEV_DEBUG, LOG_FILE, "strJson=%s", strJSON.toLocal8Bit().data());
//	emit callback(fname, uuid, strJSON);
//}
//void WebBrowserController::onSerAuthAccessToken(service::ErrorInfo err, const std::string autcode, QString fname, QString uuid){
//	LOG_METHOD("WebBrowserController::onSerAuthAccessToken", LOG_FILE);
//	QJsonObject object;
//	object.insert("resultCode", err);
//	object.insert("authCode", QString::fromLocal8Bit(autcode.data()));
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	Log(LOG_LEV_DEBUG, LOG_FILE, "strJson=%s", strJSON.toLocal8Bit().data());
//	emit callback(fname, uuid, strJSON);
//}
//
//QString WebBrowserController::onDownloadRequested(QString path)
//{
//	LOG_METHOD("WebBrowserController::onDownloadRequested", LOG_FILE);
//
//	QString filter;
//	int index = path.lastIndexOf('.');
//	if (index != -1)
//	{
//		filter = "(*" + path.mid(index) + ")";
//	}
//	else
//	{
//		filter = "(*)";
//	}
//
//	return QFileDialog::getSaveFileName(NULL, DIALOG_SAVE_FILE_TITLE, path, filter);
//}
//void WebBrowserController::scanQrCode(QString fname, QString param, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::scanQrCode", LOG_FILE);
//	QJsonObject object;
//	std::string reqjson = param.toUtf8().data();
//	Log(LOG_LEV_DEBUG, LOG_FILE, "reqjson=%s", reqjson.c_str());
//	QJsonDocument doc = QJsonDocument::fromJson(param.toUtf8());
//	QJsonValue path = doc.object().value("path");
//	if (path.isUndefined())
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "path error");
//		object.insert("resultCode", 1);
//		object.insert("resultContent","");
//	}
//	else
//	{
//		QString Path = path.toVariant().toString();
//		object.insert("resultCode", 0);
//		object.insert("resultContent", Path);
//	}
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	Log(LOG_LEV_DEBUG, LOG_FILE, "strJson=%s", strJSON.toLocal8Bit().data());
//	emit callback(fname, uuid, strJSON);
//}
//void WebBrowserController::shareTo(QString fname, QString param, QString uuid)
//{
//	LOG_METHOD("WebBrowserController::shareTo", LOG_FILE);
//	QJsonObject object;
//	std::string reqjson = param.toUtf8().data();
//	Log(LOG_LEV_DEBUG, LOG_FILE, "reqjson=%s", reqjson.c_str());
//	QJsonDocument doc = QJsonDocument::fromJson(param.toUtf8());
//	QJsonValue body = doc.object().value("body");
//	if (body.isUndefined())
//	{
//		object.insert("resultCode", 1);
//	}
//	else
//	{
//		object.insert("resultCode", 0);
//	}
//	QJsonDocument document;
//	document.setObject(object);
//	QString strJSON(document.toJson(QJsonDocument::Compact));
//	Log(LOG_LEV_DEBUG, LOG_FILE, "strJson=%s", strJSON.toLocal8Bit().data());
//	emit callback(fname, uuid, strJSON);
//}
//void WebBrowserController::splitLog(QString strJson)
//{
//	/* 单条log最大长度3000 */
//	const int bufSize = 2900;
//	while (strJson.length() > bufSize)
//	{
//		Log(LOG_LEV_INFO, LOG_FILE, "Json: %s",
//			strJson.left(bufSize).toLocal8Bit().data());
//		strJson = strJson.mid(bufSize);
//	}
//	Log(LOG_LEV_INFO, LOG_FILE, "Json: %s", strJson.toLocal8Bit().data());
//}
//std::string WebBrowserController::getOutterIP()
//{
//	std::string host = "";
//	std::string exLoginMes = m_configService->getLoginExData(g_serverName);
//	QJsonDocument doc = QJsonDocument::fromJson(exLoginMes.data());
//	if (doc.isObject())
//	{
//		QJsonObject object = doc.object();
//		if (object.contains("serverhost"))
//		{
//			QJsonValue value = object.value("serverhost");
//			if (value.isObject())
//			{  // Page 的 value 是对象
//				QJsonObject obj = value.toObject();
//				if (obj.contains("apHost"))
//				{
//					QJsonValue value = obj.value("apHost");
//					if (value.isString())
//					{
//						host = value.toString().toStdString();
//						int index = host.rfind(":");
//						if (-1 != index){
//							host = host.substr(0, index);
//						}
//					}
//				}
//			}
//		}
//	}
//	return host;
//}
//QString WebBrowserController::getAreaName()
//{
//	QString UpURL;
//	UpURL = gWinManger->getMultiChannelUrl(CHANNEL_ADDR_UPLOAD);
//	return UpURL;
//}
