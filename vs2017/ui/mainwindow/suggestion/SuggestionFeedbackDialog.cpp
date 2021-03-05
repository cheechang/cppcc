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
		__super::setTitle(transfer("�������"));
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
		m_pLabelThank->setText(transfer("��л���ķ��������ǻᾡ�촦��"));
		m_pLabelQuastion->setText(transfer("�������⣺"));
		m_pRadioCrash->setText(transfer("����"));
		m_pRadioOffline->setText(transfer("����"));
		m_pRadioBlock->setText(transfer("����"));
		m_pRadioOther->setText(transfer("��������"));
		m_pRadioSuggestion->setText(transfer("�Ľ�����"));
		m_pEditSuggestion->setPlaceHolderText(transfer("��ϸ���������磺һ������Ƶ�ͱ���"));
		m_pCheckEveryOperate->setText(transfer("ÿ�β������������������"));
		m_pButtonSave->setText(transfer("����"));

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
		QString fileName = QFileDialog::getSaveFileName(0, transfer("�ļ����Ϊ"), "/suggestions", transfer("*.zip"));
		AddLog(LOG_LEV_INFO, "%s", fileName.data());
		if (fileName != "")
		{
			/* �����ļ��У���������������ļ� */
			QDir dirTemp;
			if (!dirTemp.exists("temp"))
			{
				dirTemp.mkdir("temp");
			}

			QString suggestionFileName = "temp/suggestions.txt";
			QFile file(suggestionFileName);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
			{
				QMessageBox::warning(this, transfer("�������"), transfer("��TXT�ļ�ʧ��"));
			}
			
			/* ��֯�����ļ����� */
			QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
			QString strError;
			if (m_pCheckEveryOperate->isChecked())
			{
				strError.push_front(transfer("ÿ�β�����������"));
			}

			if (m_pRadioCrash->isChecked())
			{
				strError.push_front(transfer("������"));
			}
			else if (m_pRadioOffline->isChecked())
			{
				strError.push_front(transfer("���ߡ�"));
			}
			else if (m_pRadioBlock->isChecked())
			{
				strError.push_front(transfer("���١�"));
			}
			else if (m_pRadioOther->isChecked())
			{
				strError.push_front(transfer("�������⡣"));
			}
			else if (m_pRadioSuggestion->isChecked())
			{
				strError.push_front(transfer("�Ľ����顣"));
			}
			
			QString strSuggestion = m_pEditSuggestion->toPlainText() == ""
				? "" : "\n�����" + m_pEditSuggestion->toPlainText();

			QTextStream in(&file);
			in << strTime + ":" + strError + "\n" + strSuggestion << "\n";
			file.close();

			/* �����ļ���temp�ļ��У���������ѹ���ļ� */


			const int LogDayNum = 3; //Ҫ�������־����
			QStringList Latelylogfile;  //Ҫ�������־�ļ���
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
			
			/* ������zip�ļ��ŵ�ָ��·���� */
			utils::DirCompress::zipdircompress("./temp", fileName.toLocal8Bit().data());

			/* ѹ����Ϻ�ɾ�������ʹ������ļ� */
			DelDir("./temp");

			//ѹ���ļ�ת������
			if(0 == QMessageBox::information(NULL,"��ʾ",transfer("���Ƿ�Ҫ������־�ļ��������ϵ�� ?"),transfer("ȷ��"),transfer("ȡ��")))
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
			{    /**< ���Ŀ��Ŀ¼�����ڣ�����д��� */  
				if(!targetDir.mkdir(targetDir.absolutePath()))  
					return false;  
			}

			QFileInfoList fileInfoList = sourceDir.entryInfoList();
			foreach(QFileInfo fileInfo, fileInfoList)
			{
				if (fileInfo.fileName() == "." || fileInfo.fileName() == ".." || !filenamelist.contains(fileInfo.fileName()))			
					continue;

				if (fileInfo.isDir() )
				{    /**< ��ΪĿ¼ʱ���ݹ�Ľ���copy */
					if (!copyDirectoryFiles(fileInfo.filePath(),
						targetDir.filePath(fileInfo.fileName()),
						coverFileIfExist))
						//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
						return false;
				}
				else
				{            /**< �������ǲ���ʱ�������ļ�����ɾ������ */
					if (coverFileIfExist && targetDir.exists(fileInfo.fileName()))
					{
						targetDir.remove(fileInfo.fileName());
					}

					/// �����ļ�copy  
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
		{    /**< ���Ŀ��Ŀ¼�����ڣ�����д��� */  
			if(!targetDir.mkdir(targetDir.absolutePath()))  
				return false;  
		}

		QFileInfoList fileInfoList = sourceDir.entryInfoList();
		foreach(QFileInfo fileInfo, fileInfoList)
		{
			if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
				continue;

			if (fileInfo.isDir())
			{    /**< ��ΪĿ¼ʱ���ݹ�Ľ���copy */
				if (!copyDirectoryFiles(fileInfo.filePath(),
					targetDir.filePath(fileInfo.fileName()),
					coverFileIfExist))
					//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
					return false;
			}
			else
			{            /**< �������ǲ���ʱ�������ļ�����ɾ������ */
				if (coverFileIfExist && targetDir.exists(fileInfo.fileName()))
				{
					targetDir.remove(fileInfo.fileName());
				}

				/// �����ļ�copy  
				if (!QFile::copy(fileInfo.filePath(),
					targetDir.filePath(fileInfo.fileName()))){
					//qDebug() << "copyDirectoryFiles(" << fileInfo.filePath().toStdString().c_str() << "--->" << targetDir.filePath(fileInfo.fileName()).toStdString().c_str() << ")failed!";
					return false;
				}
			}
		}
		return true;
	}

	/* ɾ���ļ��� */
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
		dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //���ù���  
		QFileInfoList fileList = dir.entryInfoList(); // ��ȡ���е��ļ���Ϣ  
		foreach(QFileInfo file, fileList)
		{ //�����ļ���Ϣ  
			if (file.isFile()){ // ���ļ���ɾ��  
				file.dir().remove(file.fileName());
			}
			else{ // �ݹ�ɾ��  
				DelDir(file.absoluteFilePath());
			}
		}
		return dir.rmpath(dir.absolutePath()); // ɾ���ļ���  
	}
}