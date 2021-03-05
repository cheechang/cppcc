#pragma once

#include <QObject>
#include <QJsonArray>
#include "../../common/controlptr.h"

class WebBrowserController : public QObject
{
	Q_OBJECT

public:
	WebBrowserController(QObject *parent = NULL);
	~WebBrowserController();

	//void InitUI(QQuickView* view, QQuickItem* item);
	//void UnInitUI();
	Q_INVOKABLE void setJssdkVersion(QString param);
	Q_INVOKABLE void openChat(QString fname, QString paramjson, QString uuid);
	//Q_INVOKABLE void getLocalFiles(QString fname, QString uuid);
	/*Q_INVOKABLE void getAccountInfo(QString param, QString uuid);
	Q_INVOKABLE void takePhoto(QString fname, QString uuid);
	Q_INVOKABLE void getPosition(QString fname, QString uuid);
	Q_INVOKABLE void getContactList(QString fname, QString uuid);
	Q_INVOKABLE void getOrganization(QString fname, QString uuid);
	Q_INVOKABLE void getGroupList(QString fname, QString uuid);
	Q_INVOKABLE void getLocalPhotos(QString fname, QString uuid);
	Q_INVOKABLE void getLocalFiles(QString fname, QString uuid);
	Q_INVOKABLE void getInfoWithSweep(QString fname, QString uuid);
	Q_INVOKABLE void showNavigationBar(QString fname, QString uuid);
	Q_INVOKABLE void closeView(QString fname, QString uuid);
	Q_INVOKABLE void getLanguage(QString fname, QString uuid);
	Q_INVOKABLE void getVersionMark(QString fname, QString uuid);
	Q_INVOKABLE void copyTextToPaste(QString fname, QString uuid);
	Q_INVOKABLE void getGroupMembers(QString fname, QString uuid);
	Q_INVOKABLE void createGroup(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void deleteGroup(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void openAudioVideo(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void openVideoConference(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void getOAuthCode(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void getUserIdMap(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void circleOfFriend(QString fname, QString paramjson, QString uuid);
	Q_INVOKABLE void getServerName(QString fname,QString uuid);
	Q_INVOKABLE void scanQrCode(QString fname, QString param, QString uuid);
	Q_INVOKABLE void shareTo(QString fname, QString param, QString uuid);*/
private:
	/* 避免log长度超出限制，分段输出 */
	void splitLog(QString strJson);
	std::string  getOutterIP();
	QString getAreaName();
	void scaledImage(QString , float , float , QString &);
signals:
	void signalBtnCloseClicked();
	void callback(const QString fname, const QString uuid, const QString &text);
	void signalCtrlStartChat(int64);
	/*void signalCtrlStartChat(int64 ,QString);
	void signalSerGetVisibleOrgUsers(int, int8, int8, 
		std::vector<model::OrganizationInfo>&,
		std::vector<model::EntpriseUserInfo>&,
		QString, QString);
	void signalSerSendImage(service::ErrorInfo, int64, const std::string&,
		const std::string&, QStringList, QJsonArray, QJsonArray, uint, QString, QString);
	void signalSerSendFile(service::ErrorInfo, int64, const std::string&,
		QStringList, QJsonArray, QJsonArray , uint, QString, QString);
	void signalSerGetGroupMembers(service::ErrorInfo, MemberList&,
		QString, QString);
	void signalSerCreateGroup(service::ErrorInfo, int64, QString, QString);
	void signalSerDeleteGroup(service::ErrorInfo, QString, QString);
	void signalSerAuthAccessToken(service::ErrorInfo,const std::string,QString,QString);
	void signalSerCircleOfFriend(service::ErrorInfo, std::string&, QString, QString);
	void signalSerUserId(service::ErrorInfo, std::map<std::string, int64>&, QString, QString);
	void signalSerEntUserInfo(service::ErrorInfo, std::vector<EntpriseUserInfo>, QString, QString);*/
public slots:
	//QString onDownloadRequested(QString path);
	/*void onSerGetVisibleOrgUsers(service::ErrorInfo err, int8 allowChat, 
		int8 contactVisiable, std::vector<model::OrganizationInfo>& orgs,
		std::vector<model::EntpriseUserInfo>& users,
		QString fname, QString uuid);
	void onSerSendImage(service::ErrorInfo err, int64 targetId,
		const std::string& srcJson, const std::string& thumpJson,
		QStringList images, QJsonArray arrImages, QJsonArray, uint time, QString fname,
		QString uuid);
	void onSerSendFile(service::ErrorInfo err, int64 targetId,
		const std::string& fileJson, QStringList files,
		QJsonArray arrFiles, QJsonArray arrFileNames,uint time, QString fname, QString uuid);
	void onSerGetGroupMembers(service::ErrorInfo err,
		MemberList& members, QString fname, QString uuid);
	void onSerCreateGroup(service::ErrorInfo err, int64 groupid, QString fname, QString uuid);
	void onSerDeleteGroup(service::ErrorInfo err, QString fname, QString uuid);
	void onSerAuthAccessToken(service::ErrorInfo err, const std::string autcode, QString fname, QString uuid);
	void onSerUserId(service::ErrorInfo err, std::map<std::string, int64>, QString fname, QString uuid);
	void onSerCircleOfFriend(service::ErrorInfo err, std::string&contentjson, QString fname, QString uuid);
	void onSerEntUserInfo(service::ErrorInfo err, std::vector<EntpriseUserInfo>, QString, QString);*/
private:
	/*IUserService_Ptr m_userService;
	IContactService_Ptr m_contactService;
	ILddService_Ptr m_lddService;
	IGroupService_Ptr m_groupService;
	IFileService_Ptr m_fileService;
	IConfigService_Ptr m_configService;
	IAuthService_Ptr   m_authService;*/
};
