#include "ProgressWidget.h"
#include "NoFocusDelegate.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "ProgressWidgetItem.h"
#include <QCheckBox>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>
#include <QHeaderView>
#include <QMessageBox>
#include <QToolTip>
#include <QScrollBar>
#include <QHBoxLayout>
#include <qdatetime.h>
#include "CloudDiskMenu.h"
namespace ui{
	ProgressWidget::ProgressWidget(QWidget *parent)
		: QTableWidget(parent)
		, rightClickedItem(NULL)
		, dupFlag(false)
		, m_currentRow(-1)
		, m_previousColorRow(-1)
		, m_previous(nullptr)
		, m_previousclickedItem(nullptr)
		, m_type(0)
	{
		rowHeghtList.clear();
		rowWidthList.clear();
		fileMap.clear();

		setMouseTracking(true);
		horizontalHeader()->setDefaultSectionSize(100);
		verticalHeader()->setDefaultSectionSize(35);    //����Ĭ���и�  
		//horizontalHeader()->setSectionsClickable(false); //���ñ�ͷ���ɵ����Ĭ�ϵ�����������  
		horizontalHeader()->setClickable(false);
		//ȥ�����߿�
		setItemDelegate(new NoFocusDelegate());
		QFont font = horizontalHeader()->font();    //���ñ�ͷ����Ӵ�  
		font.setBold(false);
		font.setFamily("Microsoft YaHei");
		horizontalHeader()->setFont(font);
		horizontalHeader()->setStretchLastSection(true);    //���ó�������  
		//horizontalHeader()->setSectionsMovable(false);       //��ͷ���һ��� 
		horizontalHeader()->setMovable(false);
		setFrameShape(QFrame::NoFrame);      //�����ޱ߿�  
		verticalHeader()->setVisible(false); //���ô�ֱͷ���ɼ�  
		setSelectionMode(QAbstractItemView::SingleSelection);  //���õ�ѡ 
		setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ����Ϊʱÿ��ѡ��һ��  
		setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭ 
		setAlternatingRowColors(false);
		setItemFixed(false);
		//��ֱ�����������ƶ�
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		this->setVerticalScrollMode(ScrollPerItem);
		this->resize(490, 295);
	}

	ProgressWidget::~ProgressWidget()
	{

	}

	void ProgressWidget::setColumnValue(const int &columnSum, const QStringList &header)
	{
		setColumnCount(columnSum);                //��������  
		setHorizontalHeaderLabels(header);  //�����еı�ǩ  
		setHeaderWidth(0, 140);
		setHeaderWidth(1, 70);
		setHeaderWidth(2, 90);
		setHeaderWidth(3, 190);
	}
	void ProgressWidget::addItem(model::CloudFileInfo& data, QString name){
		QTableWidgetItem *itemFirst = new QTableWidgetItem;
		m_currentRow = rowCount();
		insertRow(m_currentRow);

		//���� ֱ�Ӵ�model::CloudFileInfo���ļ���
		QString fileName = QString::fromUtf8(data.fileName.c_str());
		
		QString fileSuffix = QString::fromUtf8(data.fileSuffix.c_str());
		if (!fileSuffix.isEmpty()){
			fileName += QString(".");
			fileName += fileSuffix;
		}
		itemFirst->setText(fileName);
		itemFirst->setToolTip(fileName);
		itemFirst->setTextAlignment(Qt::AlignCenter);
		setItem(m_currentRow, 0, itemFirst);

		QTableWidgetItem *itemSecond = new QTableWidgetItem;
		QString fileSize("");
		if (data.fileSize>0){
			fileSize = getFileSize(data.fileSize);
		}
		itemSecond->setTextAlignment(Qt::AlignCenter);
		itemSecond->setText(fileSize);
		setItem(m_currentRow, 1, itemSecond);

		QTableWidgetItem *itemThird = new QTableWidgetItem;
		//�ϴ�Ŀ¼
		itemThird->setTextAlignment(Qt::AlignCenter);
		itemThird->setText(name);
		setItem(m_currentRow, 2, itemThird);

		QTableWidgetItem *itemforth = new QTableWidgetItem;
		itemforth->setTextAlignment(Qt::AlignCenter);
		itemforth->setText("");
		setItem(m_currentRow, 3, itemforth);
		//AddLog(LOG_LEV_INFO, "fileName =%s,fileSize=%s,name=%s", fileName.toLocal8Bit().data(), fileSize.toLocal8Bit().data(),name.toLocal8Bit().data());
		//״̬ ����������ͣ��ȡ���������ԣ����Լ� �ϴ����ش���(ʧ��������) ���
		m_fourthWidget = new ProgressWidgetItem(this);
		m_fourthWidget->setItemRow(m_currentRow);
				
		connect(this, SIGNAL(signalProgress(int32, int64, std::string&)), m_fourthWidget, SLOT(onProgress(int32, int64, std::string&)));
		connect(m_fourthWidget, SIGNAL(signalCancle(int64)), this, SLOT(onCancle(int64)));
		connect(m_fourthWidget, SIGNAL(signalRetry(int64)), this, SIGNAL(signalRetry(int64)));
		connect(this, SIGNAL(signalDownFail(int64)), m_fourthWidget, SLOT(onFailed(int64)));
		connect(this, SIGNAL(signalUpFail(int64)), m_fourthWidget, SLOT(onFailed(int64)));
		connect(this, SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)), m_fourthWidget, SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)));
		setCellWidget(m_currentRow, 3, m_fourthWidget);
		this->setRowHeight(m_currentRow,m_fourthWidget->height());
		int max = this->verticalScrollBar()->maximum();
		this->verticalScrollBar()->setSliderPosition(max);
	}
	void ProgressWidget::setProgress(int32 pro, int64 localId,std::string& filename){
		emit signalProgress(pro, localId,filename);
	}
	void ProgressWidget::setHeaderWidth(const int &index, const int &width)
	{
		horizontalHeader()->resizeSection(index, width);
		if (rowWidthList.count() <= index + 1) {
			rowWidthList.append(width);
		}
		else {
			rowWidthList[index + 1] = width;
		}
		tableWidth = 0;
		for (int index = 0; index < rowWidthList.count(); index++)
			tableWidth += rowWidthList.at(index);
		resize(tableWidth, tableHeight);
	}

	void ProgressWidget::setHeaderHeight(const int &height)
	{
		horizontalHeader()->setFixedHeight(height);        //���ñ�ͷ�ĸ߶�  
		if (rowHeghtList.isEmpty()) {
			rowHeghtList.append(height);
		}
		else {
			rowHeghtList[0] = height;
		}
		tableHeight = 0;
		for (int index = 0; index < rowHeghtList.count(); index++)
			tableHeight += rowHeghtList.at(index);
		resize(tableWidth, tableHeight);
	}

	void ProgressWidget::addRowValue(const int &height, const QStringList &value)
	{
		int row_count = rowCount();    //��ȡ������  
		insertRow(row_count);          //��������  
		setRowHeight(row_count, height);
		for (int index = 0; index < columnCount(); index++) {
			QTableWidgetItem *item = new QTableWidgetItem;
			if (index == 0) {
				item->setTextAlignment(Qt::AlignCenter);
				fileMap.insert(item, value.at(index));
			}
			else {
				item->setTextAlignment(Qt::AlignCenter);
			}
			item->setText(value.at(index));
			setItem(row_count, index, item);
		}
		rowHeghtList.append(height);
		tableHeight += height;
		resize(tableWidth, tableHeight);
	}
	void ProgressWidget::setRowH(const int &index, const int &height)
	{
		setRowHeight(index, height);
		if (rowHeghtList.count() <= index + 1) {
			rowHeghtList.append(height);
		}
		else {
			rowHeghtList[index + 1] = height;
		}
		tableHeight = 0;
		for (int index = 0; index < rowHeghtList.count(); index++)
			tableHeight += rowHeghtList.at(index);
		resize(tableWidth, tableHeight);
	}

	QModelIndex ProgressWidget::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
	{
		//��д�ƶ�����¼��������ڱ༭���ʱ���ù����Զλ�ڵ�ǰ��༭�,���򷵻ظ���  
		if (rightClickedItem && rightClickedItem->row() >= 0) {
			return currentIndex();
		}
		else {
			return QTableWidget::moveCursor(cursorAction, modifiers);
		}
	}


	void ProgressWidget::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
			QTableWidgetItem *item = currentItem();
			if (item) {
				closePersistentEditor(item);
				openPersistentEditor(item);
				dupFlag = false;
			}
		}
	}

	void ProgressWidget::setItemFixed(bool flag)
	{
		if (flag == true)
			//horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
			horizontalHeader()->setResizeMode(QHeaderView::Fixed);
		else
			//horizontalHeader()->setResizeContentsPrecision(QHeaderView::Interactive);
			horizontalHeader()->setResizeMode(QHeaderView::Interactive);
	}

	bool ProgressWidget::getSelectedRow(QList<int> &rowList)
	{
		//��ѡ����ȡ��ѡ��  
		QList<QTableWidgetItem *> items = this->selectedItems();
		int itemCount = items.count();
		if (itemCount <= 0) {
			return false;
		}
		for (int index = 0; index < itemCount; index++) {
			int itemRow = this->row(items.at(index));
			rowList.append(itemRow);
		}
		return  true;
	}

	QString ProgressWidget::getFileSize(const int64 fileSize)
	{
		QString strFileSize = "";
		double iK = 1024;
		double iM = 1024 * 1024;
		double iG = 1024 * 1024 * 1024;
		double dSize = 0.0;
		if ((fileSize / iG) > 1.0)
		{
			dSize = fileSize / iG;
			strFileSize = QString::number(dSize, 'd', 2) + "GB";
		}
		else if ((fileSize / iM) > 1.0)
		{
			dSize = fileSize / iM;
			strFileSize = QString::number(dSize, 'd', 2) + "MB";
		}
		else if ((fileSize / iK) > 1.0)
		{
			dSize = fileSize / iK;
			strFileSize = QString::number(dSize, 'd', 2) + "KB";
		}
		else
		{
			strFileSize = QString::number(fileSize, 'f', 1) + "B";
		}
		return strFileSize;
	}
	void ProgressWidget::clearData(){
		//ֻ����������ݣ��������ͷ����
		this->clearContents();
		//����Ҳ���
		this->setRowCount(0);
		m_previousColorRow = -1;
		m_previousclickedItem = nullptr;
		m_previous = nullptr;
		m_currentRow = 0;
	}
	void ProgressWidget::onCancle(int64 localid){
		emit signalCancle(localid);
	}
}
