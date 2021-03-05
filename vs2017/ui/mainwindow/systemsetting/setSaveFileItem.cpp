#include "setSaveFileItem.h"
#include <QLabel>
#include "common/ChineseInfos.hpp"
#include "log.h"
#include <data/UserData.h>
#include <QPushButton>
#include <QGridLayout>
#include <QUrl>
#include <QProcess> 
#include <QLineEdit>
#include <QFileDialog>

#include <QFileInfo>
#include <QDesktopServices>
#include "../../common/Common.h"
namespace ui{
    setSaveFileItem::setSaveFileItem(QWidget* parent):QWidget(parent)
    {
        mCurentPath =  QString::fromStdString(USERFILEPATH);
        mUserControl = USERCONTROL;
        intiWidgets();

        std::vector<std::string> keys;
        keys.push_back("savefilepath");

        std::vector<data::UserLocalSetting> retData;
        bool isGet = mUserControl->getLocalSettingSync(keys,retData);
        if (retData.empty())
        {
            data::UserLocalSetting set;
            set.key = "savefilepath";
            set.val = USERFILEPATH;

            std::vector<data::UserLocalSetting> vec;
            vec.push_back(set);

            bool ret = mUserControl->addLocalSettingSync(vec);
            AddLog(LOG_LEV_INFO,LOG_FILE,"add StartUP LocalSetting ret = %d",ret);
        }else{
            for (qint16 index = 0; index < retData.size(); ++index)
            {
                if (retData[index].key == std::string("savefilepath"))
                {
                    QString sdMsg = QString::fromUtf8(retData[index].val.data());
                    sdMsg = sdMsg.replace(" ", "");
                    sdMsg = sdMsg.toLower();
                    mCurentPath = sdMsg;
                }
            }
        }
        m_editPath->setText(mCurentPath);
    }


    setSaveFileItem::~setSaveFileItem(void)
    {
    }

    void setSaveFileItem::intiWidgets()
    {
        m_labFileTip = CMakePtr<QLabel>(this);
        m_labFileNotify = CMakePtr<QLabel>(this);
        m_editPath = CMakePtr<QLineEdit>(this);
        m_btnSetPath = CMakePtr<QPushButton>(this);
        m_btnOpenPath = CMakePtr<QPushButton>(this);
        
        m_labFileTip->setText(transfer("文件管理: "));
        m_labFileNotify->setText(transfer("默认把接收的文件保存在此文件目录下:"));

        m_editPath->setMinimumSize(QSize(420,28));
        m_editPath->setObjectName("HotKey");

        m_btnSetPath->setText(transfer("更改目录"));
        m_btnSetPath->setObjectName("sendbtn");
        m_btnSetPath->setMinimumSize(QSize(100,22));
        connect(m_btnSetPath.get(),SIGNAL(clicked()),SLOT(onSetPathClicked()));

        m_btnOpenPath->setText(transfer("打开目录"));
        m_btnOpenPath->setObjectName("sendbtn");
        m_btnOpenPath->setMinimumSize(QSize(100,24));
        connect(m_btnOpenPath.get(),SIGNAL(clicked()),SLOT(onOpenPathClicked()));

        m_gridLayout = CMakePtr<QGridLayout>();

        m_gridLayout->setHorizontalSpacing(50);
        m_gridLayout->setVerticalSpacing(10);
        m_gridLayout->addWidget(m_labFileTip.get(),0,0,1,1,Qt::AlignRight | Qt::AlignTop);
        m_gridLayout->addWidget(m_labFileNotify.get(),0,1,1,2,Qt::AlignLeft| Qt::AlignTop);
        m_gridLayout->addWidget(m_editPath.get(),1,1,1,2,Qt::AlignCenter);
        m_gridLayout->addWidget(m_btnSetPath.get(),2,1,1,1,Qt::AlignRight);
        m_gridLayout->addWidget(m_btnOpenPath.get(),2,2,1,1,Qt::AlignLeft);

        this->setLayout(m_gridLayout.get());
    }

    void setSaveFileItem::onSetPathClicked()
    {
        QString pathLocal= QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
#ifdef _WIN32
        QString path = QFileDialog::getExistingDirectory(NULL, CHOOSE_DIR_DIALOG_TITlE, pathLocal, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        //path = fileName;
#else
        QFileDialog dialog(NULL, "", path);
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dialog.setOptions(QFileDialog::HideNameFilterDetails);
        dialog.setViewMode(QFileDialog::Detail);
        dialog.setWindowFlags(dialog.windowFlags() ^ Qt::WindowContextHelpButtonHint);
        dialog.setOption(QFileDialog::DontUseNativeDialog);
        dialog.setOption(QFileDialog::DontResolveSymlinks);
        dialog.setLabelText(QFileDialog::Reject, CANCEL);
        dialog.setWindowTitle(CHOOSE_DIR_DIALOG_TITlE);
        QStringList fileNames;
        if (dialog.exec())
            fileNames = dialog.selectedFiles();
        path = fileNames.isEmpty() ? "" : fileNames[0];
#endif
        path.replace("\\","/");
        
        if (path.isEmpty())
        {
            return;
        }
        path.append("/");

        data::UserLocalSetting set;
        set.key = "savefilepath";
        set.val = path.toUtf8().data();

        std::vector<data::UserLocalSetting> vec;
        vec.push_back(set);

        bool ret = mUserControl->updateLocalSettingSync(vec);
        m_editPath->setText(path);
        mCurentPath = path;
        AddLog(LOG_LEV_INFO,LOG_FILE,"update LocalSetting ret = %d",ret);
    }

    void setSaveFileItem::onOpenPathClicked()
    {
#ifdef _WIN32
        mCurentPath.replace("/", "\\");
        if (mCurentPath.contains(" "))
        {
            //如果文件名中有空格，explorer会打开失败，用Qt打开
            QFileInfo tempFileInfo(mCurentPath);
            QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
        }
        else
        {
            bool isSucces = QProcess::startDetached("explorer "+ mCurentPath);//打开上面获取的目录
        }
#else
        QFileInfo tempFileInfo(fileDir);
        QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
#endif 
    }

}

