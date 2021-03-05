#pragma once
#include <QTableWidget >
#include <model/Packet.h>
#include "Common/ServiceDefine.h"
namespace ui{
	class CloudDiskMenu;
class TableWidget : public QTableWidget
{
	Q_OBJECT
public:
	TableWidget(QWidget *parent = 0);
	~TableWidget();
	void setColumnValue(const int &columnSum, const QStringList &header);   //set header value  
	void addItem(model::CloudFileInfo&data,bool isown = true,int row = -1);
	void insertItem(int row, model::CloudFileInfo&data, bool isown = true);
	void setType(int type);
	int  getType()const;
	void clearData();
	void sortDescByTime();
signals:
	void signalGetFolderFiles(int type, model::CloudFileInfo info);
	void signalGetFolderPermission(int type, model::CloudFileInfo info);
	void signalRename(qint64 fileid, QString&newname);
	void signalDelFile(std::vector<std::string>&);
	void signalDownLoad(model::CloudFileInfo);
	void signalAuthorMgr(model::CloudFileInfo);
	void signalRefresh();
	void signalUpdateName(QString&);
	void signalSerGetFileById(service::ErrorInfo, model::CloudFileInfo&, model::CloudFileInfo);
public slots:
	void onSerGetFileById(service::ErrorInfo err, model::CloudFileInfo& data, model::CloudFileInfo info);
protected:
	QString getFileSize(const int64 fileSize);
	void setHeaderWidth(const int &index, const int &width);    //set header and column widhth for each index  
	void setHeaderHeight(const int &height);							  //set header height  
	void addRowValue(const int &height, const QStringList &value);
	void setRowH(const int &index, const int &height);
	void setItemFixed(bool flag);
	bool getSelectedRow(QList<int> &rowList);
	QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
	void keyPressEvent(QKeyEvent *event);
	void setRowColor(int row, QColor color);
	void setRowSelect(int row, bool isselect);

protected:
	void contextMenuEvent(QContextMenuEvent *event);
	bool IsFileExist(model::CloudFileInfo&info);
	void decryptFile(model::CloudFileInfo&info, QString&outPath);
	void resetItemStatus(bool ischeckbox = false, QTableWidgetItem *item=nullptr);
private slots:
	void slotActionRename();
	void slotItemSelectionChanged();
	void onItemEntered(QTableWidgetItem *item);
	void onItemDoubleClicked(QTableWidgetItem *item);
	void onItemClicked(QTableWidgetItem *item);
	void onCellEntered(int row, int column);
	void onDownLoad(model::CloudFileInfo);
	void onDelFile();
	void onSortByTime();
	void onViewFile(model::CloudFileInfo&info);
private:
	int m_type;
	int m_previousColorRow;
	int m_currentRow;
	int tableWidth;
	int tableHeight;
	bool m_isDesSort;
	QList<int>rowHeghtList;
	QList<int>rowWidthList;
	QString m_fileRootPath;
	QTableWidgetItem* m_previous;
	QTableWidgetItem* m_previousclickedItem;
	QTableWidgetItem *rightClickedItem;
	QMap<QTableWidgetItem *, QString>fileMap;
	bool dupFlag;
private:
	QSharedPointer<CloudDiskMenu> m_menu;
private:
	ICloudService_Ptr m_cloudservice;
};
}


