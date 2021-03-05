#pragma once
#include<QWidget>
#include <model/Packet.h>
class QCheckBox;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QLineEdit;
class QTableWidgetItem;
namespace ui{
	class QClickLabel;
	class PushButton;
	class MyLineEdit;
	class TableWidgetItem : public QWidget
	{
		Q_OBJECT
	public:
		explicit TableWidgetItem(QWidget *parent = 0);
		~TableWidgetItem();
		void setItemRow(int row);
		int  getItemRow()const;
		void setItemData(model::CloudFileInfo&data,int type);
		model::CloudFileInfo getItemData()const;
		bool isOwner()const;
		void setIsOwner(bool isowned);
		bool isRootNode()const;
		void setTableItem(QTableWidgetItem* item);
		static void setItemPermission(model::CloudPermission&permission);
		static model::CloudPermission getItemPermission();
	public slots:
		void onRename();
		void onDelFile();
		void onRenameOkBtnClicked();
		void onRenameCancelBtnClicked();
		void onDownLoadBtnClick();
		void onGetAuthorMgrClick();
		void onCheckBtnClicked();
		void onViewBtnClicked();
		void onUpdateName(QString&newname);
		void onCancelEdit();
	signals:
		void signalRename(qint64 fileid, QString&newname);
		void signalDelFile();
		void signalDownLoad(model::CloudFileInfo);
		void signalAuthorMgr(model::CloudFileInfo);
		void signalViewFile(model::CloudFileInfo&);
		void signalItemClicked(QTableWidgetItem *item);
	protected:
		QString getFileIcon(QString fileSuffix);
		void setEnableRename(bool enabled);
	private:
		bool			m_iseditnameokbtn;
		bool			m_isowner;
		QCheckBox*		m_checkBox;
		QLabel*			m_foldericon;
		QLabel*			m_fromtip;
		QLabel*			m_fromName;
		MyLineEdit*	    m_name;
		PushButton*		m_okBtn;
		PushButton*		m_cancelBtn;
		PushButton*		m_dowanloadBtn;
		PushButton*     m_authormgrBtn;
		PushButton*		m_viewfile;
		QHBoxLayout*	m_mainlayout;
		QHBoxLayout*    m_renameLayout;
		QHBoxLayout*	m_fromLayout;
		QVBoxLayout*	m_namecontentLayout;
		QTableWidgetItem* m_item;
	private:
		int m_row; //保存item在列表中的行数
		model::CloudAddFileInfo m_adddata;
		model::CloudFileInfo m_data;
		static model::CloudPermission m_permission;
	};
}