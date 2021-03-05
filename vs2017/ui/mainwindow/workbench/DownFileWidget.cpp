#include "DownFileWidget.h"
#include <QStackedWidget>
#include <QDesktopServices>
#include "controls/ToolButton.h"
#include <QSettings>
#include <QCoreApplication>
#include <QDateTime>
#include <QFileInfo>
#include <QProcess>
#include "controls/ToolButton.h"
#include "../../../utils/aes.h"
#include "../../common/UIUtils.h"

namespace ui{
	DownFileWidgetListItem::DownFileWidgetListItem(QWidget *parent) :QWidget(parent), mFilePath("")
	{
		m_pMainLayout = CMakePtr<QGridLayout>(this);
		m_NameLbl = CMakePtr<QLabel>(this);
		m_FileIocnLbl = CMakePtr<QLabel>(this);
		m_pProgressBar = CMakePtr<QProgressBar>(this);
		m_pLabelSize = CMakePtr<QLabel>(this);
		m_pLabelTime = CMakePtr<QLabel>(this);
		m_pButtonOpenFile = new ToolButton(":/group/openFile", this, false);
		m_pButtonOpenFile->setToolTip(transfer("打开所在目录"));
		m_pButtonOpenFile->hide();

		m_pProgressBar->setMinimum(0);
		m_pProgressBar->setMaximum(100);
		m_pProgressBar->setMinimumWidth(260);
		m_pProgressBar->setFixedHeight(2);
		m_pMainLayout->addWidget(m_FileIocnLbl.get(),0,0,2,1);
		m_pMainLayout->addWidget(m_NameLbl.get(),0,1,1,2,Qt::AlignLeft);
		m_pMainLayout->addWidget(m_pLabelSize.get(), 1, 1, 1, 1, Qt::AlignLeft);
		m_pMainLayout->addWidget(m_pProgressBar.get(), 1, 2, 1, 2, Qt::AlignLeft);
		m_pMainLayout->addWidget(m_pLabelTime.get(), 0, 3, Qt::AlignRight);
		m_pMainLayout->addWidget(m_pButtonOpenFile, 0, 4, 2, 1, Qt::AlignRight);
		m_pMainLayout->setSpacing(5);
		m_pMainLayout->setContentsMargins(4,6,10,6);
		this->setLayout(m_pMainLayout.get());

		connect(m_pButtonOpenFile, SIGNAL(clicked()), this, SLOT(openFileDir()));
	}

	DownFileWidgetListItem::~DownFileWidgetListItem()
	{

	}

	void DownFileWidgetListItem::setdata(QString name, QString filepath,qint64 FileSize)
	{
		QPixmap pixmap(getFileType(name));
		m_FileIocnLbl->setPixmap(pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		m_FileIocnLbl->setFixedSize(QSize(40, 40));

		m_NameLbl->setText(name);
		QString size =  QString::fromStdString(convertFileSize(FileSize));
		m_pLabelSize->setText(size);

		QString strDate = QDateTime::currentDateTime().toString("MM-dd");
		mFilePath = filepath;
		m_pLabelTime->setText(strDate);
	}

	std::string DownFileWidgetListItem::convertFileSize(double size)
	{
		std::string str[4] = { "KB", "MB", "GB", "TB" };
		std::string unit = "Bytes";

		for (int i = 0; size >= 1024.0 && i < 4; i++)
		{
			unit = str[i];
			size /= 1024.0;
		}

		std::string strSize = std::to_string((long double)size);

		int len = strSize.size();
		int pos = strSize.find_first_of('.');
		std::string tmp = strSize.substr(0, pos + 2);
		if (tmp.at(tmp.length() - 1) == '.')
		{
			tmp += "0";
		}
		tmp += " " + unit;
		return tmp;
	}

	void DownFileWidgetListItem::onSersetProgress(qint64 Value, qint64 globalValue)
	{
		int Prosessvalue = Value * 100 / globalValue;

		m_pLabelSize->setText(QString::fromStdString(convertFileSize(globalValue)));
		m_pProgressBar->setValue(Prosessvalue);
		if (Prosessvalue == 100)
		{
			SetOpenFileVisible(true);
			m_pProgressBar->setVisible(false);
		}
	}

	void DownFileWidgetListItem::SetOpenFileVisible(bool isTrue)
	{
		if (isTrue)
		{
			m_pButtonOpenFile->show();
		}
		else
		{
			m_pButtonOpenFile->hide();
		}
		
	}

	void DownFileWidgetListItem::openFileDir()
	{
		//QString destPath = enctrptFile();//!m_media.issaveas ? enctrptFile() : m_strFilePath;
		QString destPath = mFilePath;
		destPath.replace("/", "\\");
		if (destPath.contains(" "))
		{
			//如果文件名中有空格，explorer会打开失败，用Qt打开
			QFileInfo tempFileInfo(destPath);
			QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
		}
		else
		{
			//打开上面获取的目录
			bool isSucces = QProcess::startDetached("explorer /select, " + destPath);
		}
	}

	QString DownFileWidgetListItem::getFileType(QString fileName)
	{
		//文件类型 0.未知文件类型 1.图片 2.word 3.execl 4.ppt 5.视频 6.安装文件 7.压缩文件 8.文本文件 9.pdf
		QString strImageName = "";
		QString strFileExtension = "";
		QString fileIcon(":/fileicon/unknown");

		if (fileName.isEmpty())
		{
			return fileIcon;
		}
		else
		{
			//匹配文件类型对应的文件图标
			QStringList strList = fileName.split(".");
			if (strList.count() <= 1)
			{
				return fileIcon;
			}
			else
			{
				strFileExtension = strList.at(strList.length() - 1);
			}
		}
		QString tempStr = strFileExtension;
		strFileExtension = tempStr.toLower();
		if (0 == strFileExtension.compare("txt"))
		{
			fileIcon = QString(":/fileicon/txt");
		}
		else if ((0 == strFileExtension.compare("doc")) || (0 == strFileExtension.compare("docx")))
		{
			fileIcon = QString(":/fileicon/word");
		}
		else if ((0 == strFileExtension.compare("xls")) || 0 == strFileExtension.compare("xlsx"))
		{
			fileIcon = QString(":/fileicon/execl");
		}
		else if ((0 == strFileExtension.compare("png")) || (0 == strFileExtension.compare("bmp"))
			|| (0 == strFileExtension.compare("jpg")) || (0 == strFileExtension.compare("xpm"))
			|| (0 == strFileExtension.compare("gif")) || (0 == strFileExtension.compare("jpeg"))
			|| (0 == strFileExtension.compare("ico")) || (0 == strFileExtension.compare("tiff")))
		{
			fileIcon = QString(":/fileicon/picture");
		}
		else if ((0 == strFileExtension.compare("ppt")) || (0 == strFileExtension.compare("pptx")))
		{
			fileIcon = QString(":/fileicon/ppt");
		}
		else if ((0 == strFileExtension.compare("rar")) || (0 == strFileExtension.compare("zip")))
		{
			fileIcon = QString(":/fileicon/package");
		}
		else if ((0 == strFileExtension.compare("avi")) || (0 == strFileExtension.compare("3gp"))
			|| (0 == strFileExtension.compare("rmvb")) || (0 == strFileExtension.compare("wav"))
			|| (0 == strFileExtension.compare("flv")) || (0 == strFileExtension.compare("rm"))
			|| (0 == strFileExtension.compare("wmv")) || (0 == strFileExtension.compare("mkv"))
			|| (0 == strFileExtension.compare("mov")) || (0 == strFileExtension.compare("raw"))
			|| (0 == strFileExtension.compare("wma")) || (0 == strFileExtension.compare("amr"))
			|| (0 == strFileExtension.compare("mp4")) || (0 == strFileExtension.compare("mp3"))
			)
		{
			fileIcon = QString(":/fileicon/vidio");
		}
		else if ((0 == strFileExtension.compare("exe")))
		{
			fileIcon = QString(":/fileicon/install");
		}
		else if ((0 == strFileExtension.compare("pdf")))
		{
			fileIcon = QString(":/fileicon/pdf");
		}
		else
		{
			fileIcon = QString(":/fileicon/unknown");
		}
		return fileIcon;
	}

	DownFileWidget::DownFileWidget(QWidget *parent): BaseWindow(parent)
	{
		connect(this, SIGNAL(closeClicked()), this, SLOT(close()));
		this->setMinimumWidth(500);
		this->setMinimumHeight(440);
		m_DownFileList = CMakePtr<QListWidget>(this);
		m_Widget = CMakePtr<QWidget>(this);
		m_Vlayout = CMakePtr<QVBoxLayout>(this);
		m_Vlayout->addWidget(m_DownFileList.get());
		m_Widget->setLayout(m_Vlayout.get());
		mMainLayout->addWidget(m_Widget.get());
	}

	DownFileWidget::~DownFileWidget()
	{
	
	}

	bool DownFileWidget::FileIdIsExit(int32 id)
	{
		if (m_DownFileMap.find(id) != m_DownFileMap.end())
		{
			return true;
		}
		return false;
	}

	void DownFileWidget::SetMap(int32 id, QString FilePath)
	{
		m_DownFileMap[id] = FilePath;
	}

	void DownFileWidget::SetItemWidget(int32 id, DownFileWidgetListItem* widget)
	{
		m_ItemwidgetMap[id] = widget;
	}

	void DownFileWidget::EraserMap(int32 id)
	{
		if (m_DownFileMap.find(id) != m_DownFileMap.end())
		{
			m_DownFileMap.erase(id);
		}

		if (m_ItemwidgetMap.find(id) != m_ItemwidgetMap.end())
		{
			m_ItemwidgetMap[id]->SetOpenFileVisible(true);
			m_ItemwidgetMap.erase(id);
		}

	}

	DownFileWidgetListItem* DownFileWidget::GetItemWidget(int32 id)
	{
		if (m_ItemwidgetMap.find(id) != m_ItemwidgetMap.end())
		{
			return m_ItemwidgetMap[id];
		}
		return CNull;
	}

	void DownFileWidget::SetData(QString Name, int32 id, QString filepath,qint64 filesieze)
	{
		if (!FileIdIsExit(id))
		{
			QListWidgetItem* item = new QListWidgetItem();
			DownFileWidgetListItem* widget = new DownFileWidgetListItem();
			connect(widget, SIGNAL(signalSersetProgress(qint64, qint64)), widget, SLOT(onSersetProgress(qint64, qint64)));
			widget->setdata(Name, filepath,filesieze);
			SetMap(id,filepath);
			SetItemWidget(id, widget);
			m_DownFileList->addItem(item);
			m_DownFileList->setItemWidget(item, widget);
		}
	}

	QString DownFileWidget::GetFilePath(int32 id)
	{
		if (m_DownFileMap.find(id) != m_DownFileMap.end())
		{
			return m_DownFileMap[id];
		}
		return "";
	}

}
