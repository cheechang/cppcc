#pragma once
#include <QWidget>
#include <interface/Defines.h>
#include "common/Controlptr.h"

class QGridLayout;
class QLabel;
class QPushButton;
class QLineEdit;

namespace ui{
    class setSaveFileItem : public QWidget
    {
        Q_OBJECT;
    public:
        setSaveFileItem(QWidget* parent);
        ~setSaveFileItem(void);
    protected:
        void intiWidgets();
    public slots:
        void onSetPathClicked();
        void onOpenPathClicked();
    private:
        CSharedPtr<QGridLayout>   m_gridLayout;
        CSharedPtr<QLabel>        m_labFileTip;
        CSharedPtr<QLabel>        m_labFileNotify;
        CSharedPtr<QLineEdit>     m_editPath;
        CSharedPtr<QPushButton>   m_btnSetPath;
        CSharedPtr<QPushButton>   m_btnOpenPath;
        IUserControl_Ptr          mUserControl;
        QString                   mCurentPath;
    };

}


