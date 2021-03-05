#include <QCoreApplication>

#include "GroupFileList.h"
#include "GroupFileListItem.h"
#include "common/Connect.h"
#include "common/Common.h"
#include "../../../../utils/common.h"
#include <QFileInfo>
#include <QDateTime>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QDateTime>

namespace ui
{
	GroupFileList::GroupFileList(QWidget *parent)
		: TWidget(parent)
		, m_groupId(0)
	{
		m_pGroupControl = GROUPMGRCONTROL;
		m_pChatControl = CHATMGRCONTROL;
		m_pMainLayout = new QVBoxLayout(this);
		m_FuncLayout = new QHBoxLayout(this);
		m_btnBottomUpFile = new QPushButton();

		m_btnBottomUpFile->setFixedSize(16*gDdpi,16*gDdpi);
		m_btnBottomUpFile->setObjectName("upButton");
		m_btnBottomUpFile->setIcon(QPixmap(QString(":/chat/upFile")));
		m_btnBottomUpFile->setToolTip(transfer("上传文件"));
		m_FuncLayout->addStretch();
		m_FuncLayout->addWidget(m_btnBottomUpFile);
		m_FuncLayout->setContentsMargins(0,0,30*gDdpi,0);

		Funcwidget = new QWidget(this);
		Funcwidget->setFixedSize(443*gDdpi, 30*gDdpi);
		Funcwidget->setLayout(m_FuncLayout);
		Funcwidget->setVisible(false);

		m_fileStackWidget = new QStackedWidget(this);
		m_fileLayout = new QVBoxLayout(this);
		m_FileWidget = new QWidget(this);
		m_fileLayout->addWidget(m_fileStackWidget);
		m_fileLayout->setContentsMargins(0,0,10,0);
		m_FileWidget->setLayout(m_fileLayout);

		popMenu = std::make_shared<QMenu>(this);

		m_delaction = std::make_shared<QAction>(transfer("删除"), this);
		connect(m_delaction.get(), SIGNAL(triggered()), this, SLOT(onSerDelFile()));

		m_cancelaction = std::make_shared<QAction>(transfer("取消"), this);
		connect(m_cancelaction.get(), SIGNAL(triggered()), this, SLOT(onSerCancelFile()));

		popMenu->addAction(m_delaction.get());
		popMenu->addAction(m_cancelaction.get());
		//m_pMainLayout->addWidget(Funcwidget);
		m_pMainLayout->addWidget(m_FileWidget);
		//m_pMainLayout->addWidget(m_pListWidget);
		this->setLayout(m_pMainLayout);
		m_pMainLayout->setContentsMargins(0, 2*gDdpi, 0, 0);
		m_pMainLayout->setSpacing(0);
		setObjectName("bg_fa");

		mlblBg = new QLabel(this);
		mlblBg->setPixmap(QPixmap(":/base/default"));
		mlblBg->setVisible(false);
		mlblBg->setFixedSize(100*gDdpi,100*gDdpi);
		mlblBg->setScaledContents(true);
		mlblBg->move(154*gDdpi,80*gDdpi);

		CONNECT_SERVICE(GetGroupFiles(int, std::vector<CSharedPtr<data::FileInfo>>&));
		CONNECT_SERVICE(GetProgress(int32, int32, const std::string&, QString, int64));
		CONNECT_SERVICE(DelGroupfile(int64, QListWidgetItem*));
		CONNECT_SERVICE(SendFile(int, int64, const std::string&,QString,int64));
		CONNECT_SERVICE(CancelFile(int,QListWidgetItem*,int));
		connect(m_btnBottomUpFile, SIGNAL(clicked()), this, SLOT(onSerUpFile()));
	}

	GroupFileList::~GroupFileList()
	{
	}

	void GroupFileList::updateData(int64 groupId)
	{

		m_groupId = groupId;
		SetCurrentFileList(m_groupId);
		if(m_pGroupControl != CNull)
		{
			m_pGroupControl->getGroupFileList(m_groupId, CBind(&GroupFileList::signalSerGetGroupFiles,
				this, CPlaceholders _1, CPlaceholders _2));
		}
	}

	void GroupFileList::onSerGetGroupFiles(int code, std::vector<CSharedPtr<data::FileInfo>>& files)
	{
		if(clearList())
			return;
		for (int i=0; i < files.size(); i++)
		{
			addItemToList(*files.at(i));
			QCoreApplication::processEvents();
		}
		mlblBg->setVisible(files.size() == 0);
	}

	bool GroupFileList::clearList()
	{
		bool isExistNoFinish = false;
		for (int i=0;i<m_pListWidgetMap[m_groupId]->count();i++)
		{
			QListWidgetItem* item = m_pListWidgetMap[m_groupId]->item(i);
			GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);
			if(widget->GetUpFileState())
			{
				isExistNoFinish = true;
				//continue;
				break;
			}
		}
		if(!isExistNoFinish)
		{
			for (int i=0;i<m_pListWidgetMap[m_groupId]->count();i++)
			{
				QListWidgetItem* item = m_pListWidgetMap[m_groupId]->item(i);
				GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);
				m_pListWidgetMap[m_groupId]->removeItemWidget(item);
				if(item != CNull){
					delete item;
				}
				if(widget != CNull){
					delete widget;
				}
				QCoreApplication::processEvents();
			}
			m_pListWidgetMap[m_groupId]->clear();
		}
		return isExistNoFinish;
	}

	int GroupFileList::addItemToList(const data::FileInfo& data)
	{
		QListWidgetItem* item = new QListWidgetItem();
		GroupFileListItem* widget = new GroupFileListItem(this, data.fileid);
		
		widget->setData(data);
		widget->SetUpFileState(false);
		m_pListWidgetMap[m_groupId]->addItem(item);
		m_pListWidgetMap[m_groupId]->setItemWidget(item, widget);
		return m_pListWidgetMap[m_groupId]->row(item);
	}

	void GroupFileList::contextMenuEvent(QContextMenuEvent *ev)
	{
		QListWidgetItem*item = m_pListWidgetMap[m_groupId]->currentItem();
		if (item == CNull)
		{
			return;
		}
		GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);
		if(widget->GetUpFileState() || widget->GetIsDowning())
		{
			m_delaction->setVisible(false);
			m_cancelaction->setVisible(true);
		}
		else
		{
			if(widget->GetUpFileState())
			{
				m_delaction->setVisible(false);
			}
			else
			{
				m_delaction->setVisible(true);
			}		
			m_cancelaction->setVisible(false);
		}
		if(item != CNull)
		{
			popMenu->exec(QCursor::pos());		
		}		
	}

	void GroupFileList::onSerDelFile()
	{
		QListWidgetItem*item = m_pListWidgetMap[m_groupId]->currentItem();
		GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);
		std::vector<int64> vfileid;
		vfileid.push_back( widget->id());
		m_pGroupControl->DeleteGroupFile(vfileid,m_groupId, std::bind(&GroupFileList::signalSerDelGroupfile,this, std::placeholders::_1, item));
	}

	void GroupFileList::onSerCancelFile()
	{
		QListWidgetItem*item = m_pListWidgetMap[m_groupId]->currentItem();
		GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);		
		if(widget->GetUpFileState())
		{
			widget->SetOperType(FILECANCELUP);
			m_pGroupControl->cancelTransfer(widget->Getfilelocalid(),1,std::bind(&GroupFileList::signalSerCancelFile,this, std::placeholders::_1,item,0));
		}
		if(widget->GetIsDowning())
		{
			widget->SetOperType(FILECANCELDOWN);
			m_pGroupControl->cancelTransfer(widget->id(),2,std::bind(&GroupFileList::signalSerCancelFile,this, std::placeholders::_1,item,1));
		}
		
	}

	void GroupFileList::onSerCancelFile(int code, QListWidgetItem* item,int type)
	{
		GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);
		if(!code)
		{
			if( 0 == type)
			{
				//emit signalSerDelUiFile(widget->id());
				widget->SetUpFileState(false);
				m_pListWidgetMap[m_groupId]->removeItemWidget(item);
				//m_mapData.remove(widget->id());
				if(item != nullptr)
				{
					delete item;
					item = nullptr;
				}

				if(widget != nullptr)
				{
					delete widget;
					widget = nullptr;
				}
			}
			
			if(1 == type)
			{
				updateData(m_groupId);
			}
		}
		else
		{
			if(widget->GetOperType() == FILECANCELUP)
			{
				widget->SetUpFileState(false);
			}
			widget->StartTimer(6000);
			widget->SetTipVisible(true,2);
		}
	}

	bool GroupFileList::isGroupOwner()
	{
		int64 accountId = 0;
		CSharedPtr<control::IUserControl> userControl = USERCONTROL;
		if(userControl){
			CSharedPtr<data::AccountInfo> account = userControl->GetAccountInfo();
			accountId = account->id.value();
		}

		if(m_pGroupControl)
		{
			data::Member self, mem;
			m_pGroupControl->GetMemberInfo(m_groupId, accountId, self);
			if(self.memberType.value() == 3 ||self.memberType.value() == 2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void GroupFileList::AddDataToList(QString filepath,int64 filelocalid)
	{
		data::FileInfo data;
		QFileInfo  fileAllInfo(filepath);
		data.size = convertFileSize(fileAllInfo.size());
		data.path = filepath.toStdString();
		data.name = UIUtils::GetNameByUrl(filepath).toUtf8();
		data.time = QDateTime::currentDateTime().currentMSecsSinceEpoch();//.toString("MM-dd");
		insertItemToList(data,filelocalid);
	}

	int GroupFileList::insertItemToList(const data::FileInfo& data,int64 filelocalid)
	{
		QListWidgetItem* item = new QListWidgetItem();
		GroupFileListItem* widget = new GroupFileListItem(this, filelocalid);

		widget->setNewData(data);
		widget->setProgressVisible(true);
		widget->setfilelocalid(filelocalid);
		widget->SetUpFileState(true);
		widget->SetOperType(FILEUPOP);
		connect(this, SIGNAL(signalSerFileProgress(qint32)),widget, SLOT(onSerFileUpProGress(qint32)));

		m_pListWidgetMap[m_groupId]->insertItem(0,item);
		m_pListWidgetMap[m_groupId]->setItemWidget(item, widget);
		m_fileListItem[filelocalid] = widget;
		return m_pListWidgetMap[m_groupId]->row(item);
	}

	std::string GroupFileList::convertFileSize(double size)
	{
		std::string str[4] = {"KB", "MB", "GB", "TB"};
		std::string unit = "Bytes";

		for (int i = 0; size >= 1024.0 && i < 4; i++)
		{
			unit = str[i];
			size /= 1024.0;
		}

		std::string strSize = std::to_string((long double)size);

		int len = strSize.size();
		int pos = strSize.find_first_of('.');
		std::string tmp = strSize.substr(0, pos+2);
		if (tmp.at(tmp.length()-1) == '.')
		{
			tmp +="0";
		}
		tmp+= " " + unit;
		return tmp;
	}

	void GroupFileList::onSerUpFile()
	{
		data::Group group;
		if(m_pGroupControl)
		{
			m_pGroupControl->GetGroupInfo(m_groupId,group);
			QString file = QFileDialog::getOpenFileName(this, transfer("发送文件"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toLocal8Bit().data(), transfer("所有文件(*.*)"));
			QFileInfo tempfile(file);
			if(tempfile.size() == 0)
			{
				return;
			}
			data::UploadFileProperty fileProperty;
			/*QDateTime test;
			test.msecsTo(QDateTime::currentDateTime());*/
			fileProperty.localid = QDateTime::currentDateTime().toMSecsSinceEpoch();
			fileProperty.targetid = group.info.value().groupId.value();
			fileProperty.type = 6;
			fileProperty.localPath = file.toUtf8().data();
			fileProperty.dirPath = UIUtils::GetPicNameDirPrefix(file).toUtf8();
			fileProperty.filename = UIUtils::GetNameByUrl(file).toUtf8();
			fileProperty.msg = "";
			fileProperty.encryptKey = "";
			fileProperty.noStore = 1;
			fileProperty.isP2p = 0;
			fileProperty.isJS = 0;
			fileProperty.isResume = false;
			QFileInfo  fileAllInfo(file);
			fileProperty.filesize = fileAllInfo.size();
			Json::Value arr;
			m_pChatControl->uploadFile(fileProperty,
				CBind(&GroupFileList::signalSerSendFile, this,
				CPlaceholders  _1, CPlaceholders  _2,
				CPlaceholders  _3,file,fileProperty.localid),
				CBind(&GroupFileList::signalSerGetProgress,this,
				CPlaceholders  _1, CPlaceholders  _2,
				CPlaceholders  _3, file, fileProperty.localid));

			AddDataToList(file,fileProperty.localid);
		}
	}

	void GroupFileList::onSerSendFile(int err, int64 targetId, const std::string& fileJson,QString filepath,int64 filelocalid/*, std::vector<std::string> files, Json::Value arrFiles, unsigned int time*/)
	{
		if(err == 0)
		{
			std::string  strurl="";
			Json::Reader reader;
			Json::Value root,fieldsarry, mJvalue;
			int ret = reader.parse(fileJson, root);

			if(!ret)
				return ;
			if(root["files"].isArray())
			{
				int count = root["files"].size();
				for(int i=0; i<count; i++)
				{
					mJvalue = root["files"][i];
					if(mJvalue["url"].isString())
					{
						strurl = mJvalue["url"].asString();
					}
				}
			}

			if(m_fileListItem.contains(filelocalid))
			{
				GroupFileListItem* widget = m_fileListItem[filelocalid];
				widget->Setfileurl(strurl);
			}	
		}
		else
		{
			
			if(m_fileListItem.contains(filelocalid))
			{
				GroupFileListItem* widget = m_fileListItem[filelocalid];
				if(widget->GetOperType() == FILEUPOP)
				{
					widget->SetUpFileState(false);
					widget->SetTipVisible(true,1);
					m_fileListItem.remove(filelocalid);
				}
				else
				{
					if(widget->GetOperType() == FILECANCELUP)
					{
						m_fileListItem.remove(filelocalid);
					}
				}
			}
			
		}
		
	}

	void GroupFileList::onSerDelGroupfile(int64 code, QListWidgetItem* item)
	{
		if(!code)
		{
			GroupFileListItem* widget = (GroupFileListItem*)m_pListWidgetMap[m_groupId]->itemWidget(item);
			emit signalSerDelUiFile(widget->id());
			m_pListWidgetMap[m_groupId]->removeItemWidget(item);
			//m_mapData.remove(widget->id());
			if(item != nullptr)
			{
				delete item;
				item = nullptr;
			}

			if(widget != nullptr)
			{
				delete widget;
				widget = nullptr;
			}
		}
		else
		{

		}
	}

	void GroupFileList::onSerGetProgress(int32 extra_req, int32 progress, const std::string& pstr, QString filepaths, int64 filelocalid)
	{
		GroupFileListItem* widget = m_fileListItem[filelocalid];
		if (widget == NULL)
			return;
		if(100 == progress)
		{
			if(m_fileListItem.contains(filelocalid))
			{
				widget->onSerFileUpProGress(progress);
				//GroupFileListItem* widget = m_fileListItem[filelocalid];
				UpFileFinish(filepaths,widget->GetfileUrl());
				m_fileListItem.remove(filelocalid);
				return;
			}
		}
		widget->onSerFileUpProGress(progress);
		//emit signalSerFileProgress(progress);
	}

	void GroupFileList::UpFileFinish(QString filepaths,QString fileurl)
	{	
		sleep(1000);
		updateData(m_groupId);
	}

	void GroupFileList::SetCurrentFileList(int64 Groupid)
	{
		if(m_pListWidgetMap.contains(Groupid))
		{
			if(m_fileStackWidget->currentWidget() != m_pListWidgetMap[Groupid])
			{
				m_fileStackWidget->setCurrentWidget(m_pListWidgetMap[Groupid]);
			}
		}
		else
		{
			QListWidget* m_pListWidget = new QListWidget(this);
			m_pListWidgetMap[Groupid] = m_pListWidget;
			m_fileStackWidget->addWidget(m_pListWidgetMap[Groupid]);
			m_fileStackWidget->setCurrentWidget(m_pListWidgetMap[Groupid]);
		}	
	}

	void GroupFileList::sleep(int n)
	{
		QElapsedTimer t;
		t.start();
		while(t.elapsed()<n)
			QCoreApplication::processEvents();
	}

}