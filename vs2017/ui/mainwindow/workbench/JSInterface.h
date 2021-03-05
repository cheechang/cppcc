#pragma once

#include <QObject>
#include "common/controlptr.h"


class JSInterface : public QObject
{
	Q_OBJECT

public:
	JSInterface(QObject *parent);
	~JSInterface();
	Q_INVOKABLE void test();
	Q_INVOKABLE void takePhoto(QString fname, QString uuid);
	Q_INVOKABLE void getAccountInfo(QString fname, QString uuid);
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
	Q_INVOKABLE void openChat(QString fname,QString params, QString uuid);
	
signals:
	void callback(const QString, const QString, const QString&);
	void signalSerGetOrganization(std::string, QString, QString);
	void signalSerGetLocalPhotos(std::string, QString, QString);
	void signalSerGetLocalFiles(std::string, QString, QString);
	void signalSerGetGroupMembers(std::string, QString, QString);
	void signalSerFileUploadFailure(std::string);
	void signalSerOpenChatWidget(int64 targetId);
	void signalSerRecvMsg(QString);

public slots:
	void onSerGetOrganization(std::string str, QString fname, QString uuid);
	void onSerGetLocalPhotos(std::string str, QString fname, QString uuid);
	void onSerGetLocalFiles(std::string str, QString fname, QString uuid);
	void onSerGetGroupMembers(std::string str, QString fname, QString uuid);
	void onSerFileUploadFailure(std::string str);
	
private:
	IAppMgrControl_Ptr m_pAppMgr;
};