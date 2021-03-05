#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDateTime>
#include <QCoreApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include "SuggestionFeedbackDialog.h"
#include "controls/PlaceHolderEdit.h"
#include "SuggestionFeedbackSend.h"
#include "../../../utils/dircompress.h"
#include "log.h"
#include "../../common/Common.h"


namespace ui
{
	SuggestionFeedbackDialog::SuggestionFeedbackDialog(QWidget *parent)
		: BaseWindow(parent)
		, m_pLabelThank(NULL)
		, m_pLabelQuastion(NULL)
		, m_pRadioCrash(NULL)
		, m_pRadioOffline(NULL)
		, m_pRadioBlock(NULL)
		, m_pRadioOther(NULL)
		, m_pRadioSuggestion(NULL)
		, m_pEditSuggestion(NULL)
		, m_pCheckEveryOperate(NULL)
		, m_pButtonSave(NULL)
	{
		__super::setTitle(transfer("意见反馈"));
		connect(this,SIGNAL(closeClicked()),this,SLOT(close()));

		initWidget();
		setLayout();
		setAttribute();
		setConnections();
	}

	SuggestionFeedbackDialog::~SuggestionFeedbackDialog()
	{

	}

	void SuggestionFeedbackDialog::showWin()
	{
		this->exec();
	}

	void SuggestionFeedbackDialog::initWidget(void)
	{
		m_pLabelThank = new QLabel(this);
		m_pLabelQuastion = new QLabel(this);
		m_pRadioCrash = new QRadioButton(this);
		m_pRadioOffline = new QRadioButton(this);
		m_pRadioBlock = new QRadioButton(this);
		m_pRadioOther = new QRadioButton(this);
		m_pRadioSuggestion = new QRadioButton(this);
		m_pEditSuggestion = new PlaceHolderEdit(this);
		m_pCheckEveryOperate = new QCheckBox(this);
		m_pButtonSave = new QPushButton(this);
	}

	void SuggestionFeedbackDialog::setLayout(void)
	{
		QHBoxLayout* pRadioLayout = new QHBoxLayout();
		pRadioLayout->addWidget(m_pRadioCrash);
		pRadioLayout->addWidget(m_pRadioOffline);
		pRadioLayout->addWidget(m_pRadioBlock);
		pRadioLayout->addWidget(m_pRadioOther);
		pRadioLayout->addWidget(m_pRadioSuggestion);

		m_pButtonSave->setMinimumSize(100, 30);
		QVBoxLayout* pLayout = new QVBoxLayout();
		pLayout->addWidget(m_pLabelThank, 0, Qt::AlignLeft);
		pLayout->addWidget(m_pLabelQuastion, 0, Qt::AlignLeft);
		pLayout->addLayout(pRadioLayout);
		pLayout->addWidget(m_pEditSuggestion);
		pLayout->addWidget(m_pCheckEveryOperate, 0, Qt::AlignLeft);
		pLayout->addWidget(m_pButtonSave, 0, Qt::AlignHCenter);
		pLayout->setSpacing(5);
		pLayout->setContentsMargins(10, 10, 10, 10);

		QWidget* pWidget = new QWidget();
		pWidget->setLayout(pLayout);

		mMainLayout->addWidget(pWidget);
		//mMainLayout->addStretch();
		//this->setMinimumSize();
	}

	void SuggestionFeedbackDialog::setAttribute(void)
	{
		m_pLabelThank->setText(transfer("感谢您的反馈，我们会尽快处理！"));
		m_pLabelQuastion->setText(transfer("常见问题："));
		m_pRadioCrash->setText(transfer("崩溃"));
		m_pRadioOffline->setText(transfer("掉线"));
		m_pRadioBlock->setText(transfer("卡顿"));
		m_pRadioOther->setText(transfer("其他问题"));
		m_pRadioSuggestion->setText(transfer("改进建议"));
		m_pEditSuggestion->setPlaceHolderText(transfer("详细描述，例如：一打开音视频就崩溃"));
		m_pCheckEveryOperate->setText(transfer("每次操作都会遇到这个问题"));
		m_pButtonSave->setText(transfer("保存"));

		m_pButtonSave->setObjectName("sendbtn");

		m_pRadioCrash->setChecked(true);
		m_pEditSuggestion->setMaxLength(500);
	}

	void SuggestionFeedbackDialog::setConnections(void)
	{
		connect(m_pButtonSave, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
	}

	void SuggestionFeedbackDialog::onSaveClicked(void)
	{
		QString fileName = QFileDialog::getSaveFileName(0, transfer("文件另存为"), "/suggestions", transfer("*.zip"));
		AddLog(LOG_LEV_INFO, "%s", fileName.data());
		if (fileName != "")
		{
			/* 创建文件夹，并创建意见反馈文件 */
			QDir dirTemp;
			if (!dirTemp.exists("temp"))
			{
				dirTemp.mkdir("temp");
			}

			QString suggestionFileName = "temp/suggestions.txt";
			QFile file(suggestionFileName);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
			{
				QMessageBox::warning(this, transfer("意见反馈"), transfer("打开TXT文件失败"));
			}
			
			/* 组织建议文件内容 */
			QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
			QString strError;
			if (m_pCheckEveryOperate->isChecked())
			{
				strError.push_front(transfer("每次操作都会遇到"));
			}

			if (m_pRadioCrash->isChecked())
			{
				strError.push_front(transfer("崩溃。"));
			}
			else if (m_pRadioOffline->isChecked())
			{
				strError.push_front(transfer("掉线。"));
			}
			else if (m_pRadioBlock->isChecked())
			{
				strError.push_front(transfer("卡顿。"));
			}
			else if (m_pRadioOther->isChecked())
			{
				strError.push_front(transfer("其他问题。"));
			}
			else if (m_pRadioSuggestion->isChecked())
			{
				strError.push_front(transfer("改进建议。"));
			}
			
			QString strSuggestion = m_pEditSuggestion->toPlainText() == ""
				? "" : "\n意见：" + m_pEditSuggestion->toPlainText();

			QTextStream in(&file);
			in << strTime + ":" + strError + "\n" + strSuggestion << "\n";
			file.close();

			/* 拷贝文件到temp文件夹，并且制作压缩文件 */


			const int LogDayNum = 3; //要打包的日志天数
			QStringList Latelylogfile;  //要打包的日志文件名
			for(int i=1; i<=LogDayNum; i++)
			{
				QString TLogFileName = "sdklog_" + QDateTime::currentDateTime().addDays(0-i).toString("yyyy-MM-dd") + ".zip";
				Latelylogfile.insert(i-1,TLogFileName) ;
			}
			Latelylogfile.append("coreDump");
			Latelylogfile.append("commLog");
			Latelylogfile.append("sdklog_"+QDateTime::currentDateTime().toString("yyyy-MM-dd"));
			

			QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
			QString tempPath = dirTemp.absolutePath();//QDesktopServices::storageLocation(QDesktopServices::DataLocation);
			tempPath.append("/");
			copyFileToPath(tempPath + "linkdood-xp.log", "./temp/linkdood-xp.log", true);
			copyFileToPath(tempPath + "update.log", "./temp/update.log", true);
			copyFileToPath(tempPath + "public/" + date, "./temp/" + date, true);
			copyFileToPath(tempPath + "sdk_core.dmp", "./temp/sdk_core.dmp", true);
			copyFileToPath(tempPath + "public/commLog", "./temp/commLog", true);
			copyDirectoryFiles(tempPath+ "public/coreDump", "./temp/coreDump",true);
			copyDirectoryFilterFiles(tempPath+ "public/", "./temp/",Latelylogfile,true);
			
			copyDirectoryFiles(tempPath + "dump", "./temp/dump", true);
			
			/* 将拷贝zip文件放到指定路径下 */
			utils::DirCompress::zipdircompress("./temp", fileName.toLocal8Bit().data());

			/* 压缩完毕后，删除拷贝和创建的文件 */
			DelDir("./temp");

			//压缩文件转发好友
			if(0 == QMessageBox::information(NULL,"提示",transfer("您是否要发送日志文件给相关联系人 ?"),transfer("确认"),transfer("取消")))
			{
				emit ShowSuggestionDialog(fileName);
			}
		}		
		accept();	
	}
	
	bool SuggestionFeedbackDialog::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
	{
		toDir.replace("\\", "/");
		if (sourceDir == toDir)
		{
			return true;
		}  
		if (!QFile::exists(sourceDir))
		{  
			return false;  
		}
		QDir *createfile = new QDir;
		bool exist = createfile->exists(toDir);
		if (exist){
			if (coverFileIfExist)
			{
				createfile->remove(toDir);
			}
		}

		if (!QFile::copy(sourceDir, toDir))
		{
			return false;
		}
		return true;
	}

	bool SuggestionFeedbackDialog::copyDirectoryFilterFiles(const QString &fromDir, const QString &toDir, QStringList& filenamelist, bool coverFileIfExist)
	{
			QDir sourceDir(fromDir);
			QDir targetDir(toDir);
			if(!targetDir.exists())
			{    /**< 如果目标目录不存在，则进行创建 */  
				if(!targetDir.mkdir(targetDir.absolutePath()))  
					return false;  
			}

			QFileInfoList fileInfoList = sourceDir.entryInfoList();
			foreach(QFileInfo fileInfo, fileInfoList)
			{
				if (fileInfo.fileName() == "." || fileInfo.fileName() == ".." || !filenamelist.contains(fileInfo.fileName()))			
					continue;

				if (fileInfo.isDir() )
				{    /**< 当为目录时，递归的进行copy */
					if (!copyDirectoryFiles(fileInfo.filePath(),
						targetDir.filePath(fileInfo.fileName()),
						coverFileIfExist))
						//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
						return false;
				}
				else
				{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
					if (coverFileIfExist && targetDir.exists(fileInfo.fileName()))
					{
						targetDir.remove(fileInfo.fileName());
					}

					/// 进行文件copy  
					if (!QFile::copy(fileInfo.filePath(),
						targetDir.filePath(fileInfo.fileName()))){
							//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
							return false;
					}
				}
			}
			return true;
	}
	bool SuggestionFeedbackDialog::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
	{
		QDir sourceDir(fromDir);
		QDir targetDir(toDir);
		if(!targetDir.exists())
		{    /**< 如果目标目录不存在，则进行创建 */  
			if(!targetDir.mkdir(targetDir.absolutePath()))  
				return false;  
		}

		QFileInfoList fileInfoList = sourceDir.entryInfoList();
		foreach(QFileInfo fileInfo, fileInfoList)
		{
			if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
				continue;

			if (fileInfo.isDir())
			{    /**< 当为目录时，递归的进行copy */
				if (!copyDirectoryFiles(fileInfo.filePath(),
					targetDir.filePath(fileInfo.fileName()),
					coverFileIfExist))
					//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
					return false;
			}
			else
			{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
				if (coverFileIfExist && targetDir.exists(fileInfo.fileName()))
				{
					targetDir.remove(fileInfo.fileName());
				}

				/// 进行文件copy  
				if (!QFile::copy(fileInfo.filePath(),
					targetDir.filePath(fileInfo.fileName()))){
					//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
					return false;
				}
			}
		}
		return true;
	}

	/* 删除文件夹 */
	bool SuggestionFeedbackDialog::DelDir(const QString &path)
	{
		if (path.isEmpty())
		{
			return false;
		}
		QDir dir(path);
		if (!dir.exists())
		{
			return true;
		}
		dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤  
		QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息  
		foreach(QFileInfo file, fileList)
		{ //遍历文件信息  
			if (file.isFile()){ // 是文件，删除  
				file.dir().remove(file.fileName());
			}
			else{ // 递归删除  
				DelDir(file.absoluteFilePath());
			}
		}
		return dir.rmpath(dir.absolutePath()); // 删除文件夹  
	}
}