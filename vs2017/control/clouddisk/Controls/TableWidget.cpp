#include "TableWidget.h"
#include "NoFocusDelegate.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "TableWidgetItem.h"
#include <QCheckBox>
#include <QDesktopServices>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>
#include <QHeaderView>
#include <QMessageBox>
#include <QToolTip>
#include <QScrollBar>
#include <QHBoxLayout>
#include <qdatetime.h>
#include <QFileInfo>
#include <QDir>
#include <QUrl>
#include "CloudDiskMenu.h"
#include "MyMessageBox.h"
#include "../Utils/utils.h"
#include "../Common/Common.h"
namespace ui{
	TableWidget::TableWidget(QWidget *parent)
		: QTableWidget(parent)
		, rightClickedItem(NULL)
		, dupFlag(false)
		, m_currentRow(-1)
		, m_previousColorRow(-1)
		, m_previous(nullptr)
		, m_previousclickedItem(nullptr)
		, m_type(1)
		, m_isDesSort(true)
	{
		rowHeghtList.clear();
		rowWidthList.clear();
		fileMap.clear();

		setMouseTracking(true);
		verticalHeader()->setDefaultSectionSize(35);    //����Ĭ���и�  
		QHeaderView *headerGoods = this->horizontalHeader();
		//SortIndicatorΪˮƽ�����������Աߵ�����ָʾ��
		headerGoods->setSortIndicator(0, Qt::DescendingOrder);
		headerGoods->setSortIndicatorShown(false);
		//connect(horizontalHeader(), SIGNAL(sectionClicked(int)),this, SLOT(sortByColumn(int)));
		headerGoods->setDefaultSectionSize(100);
		QFont font = headerGoods->font();    //���ñ�ͷ����Ӵ�  
		font.setBold(false);
		font.setFamily("Microsoft YaHei");
		headerGoods->setFont(font);
		headerGoods->setStretchLastSection(true);    //���ó�������  
		//headerGoods->setSectionsMovable(false);       //��ͷ���һ���  
		//headerGoods->setSectionsClickable(false);//���ñ�ͷ���ɵ����Ĭ�ϵ����������� )
		headerGoods->setMovable(false);
		headerGoods->setClickable(false);
		
		//ȥ�����߿�
		setItemDelegate(new NoFocusDelegate());
		setFrameShape(QFrame::NoFrame);      //�����ޱ߿�  
		verticalHeader()->setVisible(false); //���ô�ֱͷ���ɼ�  
		setSelectionMode(QAbstractItemView::SingleSelection);  //���õ�ѡ 
		setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ����Ϊʱÿ��ѡ��һ��  
		setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭ 
		setAlternatingRowColors(false);
		setItemFixed(false);
		//��ֱ�����������ƶ�
		
		//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		//setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
		connect(this, SIGNAL(cellEntered(int, int)), this, SLOT(onCellEntered(int, int)));
		connect(this, SIGNAL(itemEntered(QTableWidgetItem*)), this, SLOT(onItemEntered(QTableWidgetItem *)));
		connect(this, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(onItemClicked(QTableWidgetItem *)));
		connect(this, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onItemDoubleClicked(QTableWidgetItem *)));
		this->resize(620, 600);

		IConfigService_Ptr configservice = CONFIGSERVICE;
		m_cloudservice = CLOUDSERVICE;
		CONNECT_SERVICE(GetFileById(service::ErrorInfo, model::CloudFileInfo&, model::CloudFileInfo));
		m_fileRootPath = QString::fromUtf8(configservice->userFilePath().data());
	}

	TableWidget::~TableWidget()
	{

	}

	void TableWidget::setColumnValue(const int &columnSum, const QStringList &header)
	{
		setColumnCount(columnSum);                //��������  
		setHorizontalHeaderLabels(header);  //�����еı�ǩ  
		setHeaderWidth(0, 380);
		setHeaderWidth(1, 70);
		setHeaderWidth(2, 134);
		setHeaderWidth(3, 124);
	}
	void TableWidget::setType(int type){
		m_type = type;
	}
	int  TableWidget::getType()const{
		return m_type;
	}
	void TableWidget::addItem(model::CloudFileInfo&data, bool isown, int row){
		QTableWidgetItem *itemFirst = nullptr;
		TableWidgetItem* firstWidget = nullptr;
		int foldertype = 1;

		if (-1 != row){
			m_currentRow = row;
		}
		else if (data.fileType>1){
			foldertype = 2;
			m_currentRow = 0;
		}
		else{
			m_currentRow = rowCount();
		}
		insertRow(m_currentRow);
		itemFirst = new QTableWidgetItem;
		itemFirst->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		itemFirst->setText(QString("  ") + QString::number(foldertype));
		setItem(m_currentRow, 0, itemFirst);
		firstWidget = new TableWidgetItem(this);
		firstWidget->setTableItem(itemFirst);
		firstWidget->setItemData(data,m_type);
		firstWidget->setItemRow(m_currentRow);
		firstWidget->setIsOwner(isown);
		setCellWidget(m_currentRow, 0, firstWidget);
		this->setRowHeight(m_currentRow,50);

		connect(m_menu.data(), SIGNAL(signalRenameMenu()), firstWidget, SLOT(onRename()));
		connect(firstWidget, SIGNAL(signalRename(qint64, QString&)), this, SIGNAL(signalRename(qint64, QString&)));
		connect(firstWidget, SIGNAL(signalDelFile()), this, SLOT(onDelFile()));
		connect(firstWidget, SIGNAL(signalDownLoad(model::CloudFileInfo)), this, SLOT(onDownLoad(model::CloudFileInfo)));
		connect(firstWidget, SIGNAL(signalAuthorMgr(model::CloudFileInfo)), this, SIGNAL(signalAuthorMgr(model::CloudFileInfo)));
		connect(firstWidget, SIGNAL(signalViewFile(model::CloudFileInfo&)), this, SLOT(onViewFile(model::CloudFileInfo&)));
		connect(firstWidget, SIGNAL(signalItemClicked(QTableWidgetItem*)), this, SLOT(onItemClicked(QTableWidgetItem*)));
		connect(this, SIGNAL(signalUpdateName(QString&)), firstWidget, SLOT(onUpdateName(QString&)));
		QTableWidgetItem *itemSecond = new QTableWidgetItem;
		QString fileSize("-");
		if (data.fileSize>0){
			fileSize = getFileSize(data.fileSize);
		}
		itemSecond->setTextAlignment(Qt::AlignCenter);
		itemSecond->setText(fileSize);
		setItem(m_currentRow, 1, itemSecond);

		QTableWidgetItem *itemThird = new QTableWidgetItem;
		QString createTime("-");
		QDateTime date;
		date.setMSecsSinceEpoch(data.createTime);
		createTime = date.toString("yyyy-MM-dd hh:mm:ss");
		itemThird->setTextAlignment(Qt::AlignCenter);
		itemThird->setText(createTime);
		setItem(m_currentRow, 2, itemThird);

		QTableWidgetItem *itemFourth = new QTableWidgetItem;
		QString updateTime("-");
		QDateTime dateupdate;
		dateupdate.setMSecsSinceEpoch(data.updateTime);
		updateTime = dateupdate.toString("yyyy-MM-dd hh:mm:ss");
		itemFourth->setTextAlignment(Qt::AlignCenter);
		itemFourth->setText(updateTime);
		setItem(m_currentRow, 3, itemFourth);
	}
	void TableWidget::insertItem(int row, model::CloudFileInfo&data, bool isown){
		addItem(data,isown,row);
	}
	void TableWidget::setHeaderWidth(const int &index, const int &width)
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

	void TableWidget::setHeaderHeight(const int &height)
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

	void TableWidget::addRowValue(const int &height, const QStringList &value)
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


	
	void TableWidget::setRowH(const int &index, const int &height)
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

	
	

	QModelIndex TableWidget::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
	{
		//��д�ƶ�����¼��������ڱ༭���ʱ���ù����Զλ�ڵ�ǰ��༭�,���򷵻ظ���  
		if (rightClickedItem && rightClickedItem->row() >= 0) {
			return currentIndex();
		}
		else {
			return QTableWidget::moveCursor(cursorAction, modifiers);
		}
	}


	void TableWidget::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
			QTableWidgetItem *item = currentItem();
			if (item) {
				/*closePersistentEditor(item);
				openPersistentEditor(item);
				slotItemSelectionChanged();
				dupFlag = false;*/
			}
		}
	}

	void TableWidget::slotItemSelectionChanged()
	{
		//�رձ༭��  
		if (rightClickedItem && dupFlag == false) {
			int editRow = rightClickedItem->row();
			QTableWidgetItem *item = this->item(editRow, 0);
			QMap<QTableWidgetItem *, QString>::iterator it;
			for (it = fileMap.begin(); it != fileMap.end(); ++it) {
				if (it.key() != item) {
					if (it.value() == item->text()) {
						dupFlag = true;
					}
				}
			}
			if (dupFlag == false) {
				this->closePersistentEditor(item);
				rightClickedItem = NULL;
			}
			else {
				QMessageBox::critical(this, tr("������ʾ"), tr("�ļ�����"), tr("ȷ��"));
				setCurrentItem(item);
			}
		}
		else {
			dupFlag = false;
		}
	}

	void TableWidget::setItemFixed(bool flag)
	{
		if (flag == true)
			//horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
			horizontalHeader()->setResizeMode(QHeaderView::Fixed);
		else
			//horizontalHeader()->setResizeContentsPrecision(QHeaderView::Interactive);
			horizontalHeader()->setResizeMode(QHeaderView::Interactive);
	}

	bool TableWidget::getSelectedRow(QList<int> &rowList)
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
	void TableWidget::onItemEntered(QTableWidgetItem *item){
		//����item״̬
		resetItemStatus();

		//���õ�ǰ��״̬
		if (nullptr != item){
			QWidget* firstWidget = nullptr;
			firstWidget = this->cellWidget(item->row(),0);
			if (nullptr != firstWidget){
				model::CloudFileInfo data = ((TableWidgetItem*)firstWidget)->getItemData();
				PushButton* downloadBtn = firstWidget->findChild<PushButton*>("downloadbtn");
				PushButton* viewBtn = firstWidget->findChild<PushButton*>("viewfilebtn");
				PushButton* authMgrBtn = firstWidget->findChild<PushButton*>("authormgrbtn");
				if (nullptr != downloadBtn && nullptr != viewBtn && nullptr != authMgrBtn){
					model::CloudPermission permis = TableWidgetItem::getItemPermission();
					bool isown = ((TableWidgetItem*)firstWidget)->isOwner();
					//bool isRootNode = ((TableWidgetItem*)firstWidget)->isRootNode();
					if (isown){
						downloadBtn->setVisible(isown&&1 == data.fileType && !IsFileExist(data));
						authMgrBtn->setVisible(isown&&data.fileType && 1 != data.fileType && SHARED_FILE == m_type);
						viewBtn->setVisible(isown&&1 == data.fileType && IsFileExist(data));
					}
					else{
						downloadBtn->setVisible(permis.isDownLoad && 1 == data.fileType && !IsFileExist(data));
						authMgrBtn->setVisible(permis.isManager && data.fileType && 1 != data.fileType);
						viewBtn->setVisible(permis.isRead && 1 == data.fileType && IsFileExist(data));
					}
					
				}
			}
		}
	}
	void TableWidget::onItemDoubleClicked(QTableWidgetItem *item){
		if (nullptr != item){
			int row = item->row();
			TableWidgetItem* itemWidget = static_cast<TableWidgetItem*>(this->cellWidget(item->row(),0));
			if (nullptr != itemWidget){
				model::CloudFileInfo info = itemWidget->getItemData();
				//���� 1.�ļ�  2.�ļ���  3.�Ŷ��ļ���  4 �����ļ���
				if (1 != info.fileType){
					clearData();
					emit signalGetFolderPermission(m_type,info);
				}
			}
		}
	}
	void TableWidget::onItemClicked(QTableWidgetItem *item){
		QWidget* firstWidget = nullptr;
		QCheckBox*  checkBtn = nullptr;

		//����item״̬
		resetItemStatus(true,item);

		//���õ�ǰ��״̬
		if (nullptr == item)return;
		firstWidget = this->cellWidget(item->row(), 0);
		if (nullptr == firstWidget)return;
		checkBtn = firstWidget->findChild<QCheckBox*>("checkbtn");
		if (nullptr == checkBtn)return;
	/*	bool ischecked = false;
		ischecked = !checkBtn->isChecked();*/
		checkBtn->setChecked(true);
		setRowSelect(item->row(), true);
		m_previousclickedItem = item;
	}
	void TableWidget::slotActionRename()
	{
		//��õ�ǰ�ڵ㲢��ȡ�༭����  
		if (rightClickedItem) {
			int editRow = rightClickedItem->row();
			QTableWidgetItem *item = this->item(editRow, 0);   //�༭���кż���һ��  
			this->setCurrentCell(editRow, 0);
			this->openPersistentEditor(item);                  //�򿪱༭��  
			this->editItem(item);
		}
	}
	void TableWidget::onCellEntered(int row, int column)
	{
		QTableWidgetItem *item = 0;

		//��ԭ��һ�е���ɫ  
		item = this->item(m_previousColorRow, 0);
		if (item != 0)
		{
			this->setRowColor(m_previousColorRow, QColor(255,255,255));
			item->setTextColor(Qt::transparent);
		}

		//���õ�ǰ�е���ɫ  
		item = this->item(row, column);
		if (item != 0 && !item->isSelected())
		{
			this->setRowColor(row, QColor(246, 250, 255));
		}
		//�����е�����  
		m_previousColorRow = row;
	}
	//����ĳһ�е���ɫ  
	void TableWidget::setRowColor(int row, QColor color)
	{
		for (int col = 0; col<this->columnCount(); col++)
		{
			QTableWidgetItem *item = this->item(row, col);
			if (nullptr != item){
				item->setBackgroundColor(color);
			}
		}
	}
	void TableWidget::setRowSelect(int row, bool isselect){
		for (int col = 0; col<this->columnCount(); col++)
		{
			QTableWidgetItem *item = this->item(row, col);
			if (nullptr != item){
				item->setSelected(isselect);
			}
		}
	}
	QString TableWidget::getFileSize(const int64 fileSize)
	{
		QString strFileSize = "";
		double iK = 1024;
		double iM = 1024 * 1024;
		double iG = 1024 * 1024 * 1024;
		double dSize = 0.0;
		if ((fileSize / iG) > 1.00)
		{
			dSize = fileSize / iG;
			strFileSize = QString::number(dSize, 'd',2) + "GB";
		}
		else if ((fileSize / iM) > 1.00)
		{
			dSize = fileSize / iM;
			strFileSize = QString::number(dSize, 'd', 2) + "MB";
		}
		else if ((fileSize / iK) > 1.00)
		{
			dSize = fileSize / iK;
			strFileSize = QString::number(dSize, 'd', 2) + "KB";
		}
		else
		{
			strFileSize = QString::number(fileSize, 'd', 2) + "B";
		}
		return strFileSize;
	}
	void TableWidget::clearData(){
		//ֻ����������ݣ��������ͷ����
		this->clearContents();
		//����Ҳ���
		this->setRowCount(0);
		m_previousColorRow = -1;
		m_previousclickedItem = nullptr;
		m_previous = nullptr;
		m_currentRow = 0;
	}
	void TableWidget::contextMenuEvent(QContextMenuEvent *event){
		QPoint point = event->pos(); //�õ���������
		QTableWidgetItem *item = this->itemAt(point);
		//�����˵�
		m_menu = QSharedPointer<CloudDiskMenu>(new CloudDiskMenu(this));
		connect(m_menu.data(), SIGNAL(signalDelMenu()), this, SLOT(onDelFile()));
		connect(m_menu.data(), SIGNAL(signalRefresh()), this, SIGNAL(signalRefresh()));
		connect(m_menu.data(), SIGNAL(signalSortByTime()), this, SLOT(onSortByTime()));
		if (nullptr != item)
		{
			onItemClicked(item);
			int row = 0;
			QWidget* firstWidget = nullptr;
			std::vector<std::string> hashcodes;
			QList<QTableWidgetItem *> items = this->selectedItems();
			int itemCount = items.count() / this->columnCount();
			if (itemCount <= 0) {
				m_menu->setMenuState(MENU_DEL, false);
				m_menu->setMenuState(MENU_RENAME, false);
			}
			else{
				for (int index = 0; index < itemCount; ++index){
					item = items.at(index);
				}
				row = item->row();
				QCheckBox* checkBtn = nullptr;
				firstWidget = this->cellWidget(row, 0);
				if (nullptr == firstWidget) return;
				checkBtn = firstWidget->findChild<QCheckBox*>("checkbtn");
				if (nullptr == checkBtn)return;
				bool isown = ((TableWidgetItem*)firstWidget)->isOwner();
				bool isrootnode = ((TableWidgetItem*)firstWidget)->isRootNode();
				m_menu->setIsOwner(isown);
				m_menu->setIsRootNode(isrootnode);
				connect(m_menu.data(), SIGNAL(signalRenameMenu()), firstWidget, SLOT(onRename()));
				m_menu->addSeparator();
				m_menu->setMenuState(MENU_RENAME, true);
				m_menu->setMenuState(MENU_DEL, true);
			}
		}
		else{
			m_menu->setMenuState(MENU_DEL, false);
			m_menu->setMenuState(MENU_RENAME, false);
		}
		m_menu->show(QCursor::pos());
	}
	void TableWidget::onDownLoad(model::CloudFileInfo data){
		m_cloudservice->getFileById(data.fileId, std::bind(&TableWidget::signalSerGetFileById, this, std::placeholders::_1, std::placeholders::_2, data));
		//emit signalDownLoad(data);
	}
	void TableWidget::onDelFile(){
		std::vector<std::string> hashcodes;
		QList<QTableWidgetItem *> items = this->selectedItems();
		int itemCount = items.count()/this->columnCount();
		if (itemCount <= 0) {
			return;
		}
		for (int index = 0; index < itemCount; ++index){
			QTableWidgetItem* item = items.at(index);
			if (nullptr == item) return;
			QWidget* firstWidget = this->cellWidget(item->row(),0);
			if (nullptr == firstWidget) return;
			model::CloudFileInfo data = ((TableWidgetItem*)firstWidget)->getItemData();
			//AddLog(LOG_LEV_DEBUG, "hashcodes=%s", data.fileCode.c_str());
			hashcodes.push_back(data.fileCode);
		}
		if (QMessageBox::Ok == showQuestion(nullptr, QString::fromUtf8("ȷ��ɾ��"), QString::fromUtf8("ȷ��Ҫ����ѡ�ļ�ɾ����"))){
			emit signalDelFile(hashcodes);
		}
	}
	void TableWidget::onSortByTime(){
		m_isDesSort = !m_isDesSort;
		if (m_isDesSort){
			this->sortByColumn(2, Qt::DescendingOrder);
		}
		else{
			this->sortByColumn(2, Qt::AscendingOrder);
		}
		this->sortByColumn(0, Qt::DescendingOrder);
	}
	void TableWidget::sortDescByTime(){
		this->sortByColumn(2, Qt::DescendingOrder);
		this->sortByColumn(0, Qt::DescendingOrder);
		m_isDesSort = true;
	}
	bool TableWidget::IsFileExist(model::CloudFileInfo&info){
		bool bret = false;
		QString filePath("");
		QFileInfo fileinfo;
		std::string url = info.filePath;
		int pos = url.find(".");
		if (-1 != pos){
			url = info.filePath.substr(0, pos);
		}
		fileinfo.setFile(filePath);
		filePath = m_fileRootPath + utils::GetNameByUrl(QString::fromUtf8(url.data()));
		filePath.replace(QString(".")+QString::fromUtf8(info.fileSuffix.data()),"");
		filePath.replace(QString(".") + QString::fromUtf8(info.fileSuffix.data()).toUpper(), "");
		fileinfo.setFile(filePath);
		bret = fileinfo.isFile() && fileinfo.exists();
		return bret;
	}
	void TableWidget::onViewFile(model::CloudFileInfo&info){
		QString filePath("");
		bool bret = false;
		QFileInfo fileinfo;
		QDir dir;
		std::string url = info.filePath;
		int pos = url.find(".");
		if (-1 != pos){
			url = info.filePath.substr(0, pos);
		}
		filePath = m_fileRootPath + QString("clouddisk/");
		dir.setPath(filePath);
		if (!dir.exists()){
			dir.mkdir(filePath);
		}
		filePath +=QString::fromUtf8(info.fileName.data())+QString(".")+QString::fromUtf8(info.fileSuffix.data());
		fileinfo.setFile(filePath);
		bret = fileinfo.isFile() && fileinfo.exists();
		if (bret){
			QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
	
		}
		else{
			QString outPath("");
			if (!info.encryptKey.empty()){
				decryptFile(info, outPath);
			}
			else{
				outPath = filePath;
				filePath = m_fileRootPath + utils::GetNameByUrl(QString::fromUtf8(url.data()));
				filePath.replace(QString(".") + QString::fromUtf8(info.fileSuffix.data()), "");
				filePath.replace(QString(".") + QString::fromUtf8(info.fileSuffix.data()).toUpper(), "");
				QFile::copy(filePath,outPath);
			}
			QDesktopServices::openUrl(QUrl::fromLocalFile(outPath));
		}
	}
	void TableWidget::decryptFile(model::CloudFileInfo&info, QString&outPath){
		QString cachePath("");
		QString filePath("");
		QDir tempDir;
		IFileService_Ptr fileservice = FILESERVICE;


		filePath = m_fileRootPath + utils::GetNameByUrl(QString::fromUtf8(info.filePath.data()));
		filePath.replace(QString(".") + QString::fromUtf8(info.fileSuffix.data()), "");
		filePath.replace(QString(".") + QString::fromUtf8(info.fileSuffix.data()).toUpper(), "");
		cachePath = m_fileRootPath + "clouddisk/";
		outPath.clear();
		outPath.append(cachePath);
		if (!tempDir.exists(outPath))
		{
			tempDir.mkpath(outPath);
		}
		outPath += QString::fromUtf8(info.fileName.data()) + QString(".") + QString::fromUtf8(info.fileSuffix.data());
		//���ڲ��Ҳ������Ϊ�ļ����ļ��������
		bool decyCode = fileservice->decryptFile(info.encryptKey.c_str(), filePath.toUtf8().data(), outPath.toUtf8().data());
		if (!decyCode)
		{
			outPath.clear();
		}
	}
	void TableWidget::resetItemStatus(bool ischeckbox,QTableWidgetItem *item){
		QWidget* firstWidget = nullptr;
		for (int index = 0; index < this->rowCount(); ++index){
			//������ǰ��״̬
			firstWidget = this->cellWidget(index, 0);
			if (nullptr == firstWidget)return;
			if (ischeckbox){
				QCheckBox*  checkBtn = nullptr;
				checkBtn = firstWidget->findChild<QCheckBox*>("checkbtn");
				if (nullptr == checkBtn)return;
				if (m_previousclickedItem != item){
					checkBtn->setChecked(false);
					setRowSelect(index,false);
				}
			}
			else{
				PushButton* downloadBtn = firstWidget->findChild<PushButton*>("downloadbtn");
				PushButton* viewBtn = firstWidget->findChild<PushButton*>("viewfilebtn");
				PushButton* authMgrBtn = firstWidget->findChild<PushButton*>("authormgrbtn");
				if (nullptr == downloadBtn || nullptr == viewBtn || nullptr == authMgrBtn)return;
				downloadBtn->setVisible(false);
				viewBtn->setVisible(false);
				authMgrBtn->setVisible(false);
			}
		}
	}
	void TableWidget::onSerGetFileById(service::ErrorInfo err, model::CloudFileInfo& data, model::CloudFileInfo info){
	if (!err){
		emit signalDownLoad(info);
	}
	else{
		if (9 == err){
			QString tipinfo(tr("�ļ��ѱ�ɾ��!"));
			showWarning(nullptr, tr("��ʾ"), tipinfo);
		}
	}
}
}
