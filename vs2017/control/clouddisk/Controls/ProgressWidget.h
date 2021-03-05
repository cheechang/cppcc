#pragma once
#include <QTableWidget >
#include <model/Packet.h>
namespace ui{
	class CloudDiskMenu;
	class ProgressWidgetItem;
	class ProgressWidget : public QTableWidget
	{
		Q_OBJECT
	public:
		ProgressWidget(QWidget *parent = 0);
		~ProgressWidget();
		void setColumnValue(const int &columnSum, const QStringList &header);   //set header value  
		void addItem(model::CloudFileInfo& data, QString name);
		void clearData();
		void setProgress(int32, int64, std::string&);
	signals:
		void signalProgress(int32, int64,std::string&);
		void signalCancle(int64);
		void signalRetry(int64);
		void signalDownFail(int64);
		void signalUpFail(int64);
		void signalDecryptFile(int64, model::CloudFileInfo&, std::string&);
	public slots:
		void onCancle(int64);
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
	private:
		int m_type;
		int m_previousColorRow;
		int m_currentRow;
		int tableWidth;
		int tableHeight;
		QList<int>rowHeghtList;
		QList<int>rowWidthList;
		ProgressWidgetItem* m_fourthWidget;
		QTableWidgetItem* m_previous;
		QTableWidgetItem* m_previousclickedItem;
		QTableWidgetItem *rightClickedItem;
		QMap<QTableWidgetItem *, QString>fileMap;
		bool dupFlag;
	private:
		QSharedPointer<CloudDiskMenu> m_menu;
	};
}


