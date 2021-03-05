#pragma once
#include <QWidget>
#include <core/BaseDialog.h>
#include <interface/Defines.h>
#include "common/Controlptr.h"
#include "../contact/createGroup/BaseWindow.h"
#include <QMap>

class QLabel;
class QListWidget;
class QHBoxLayout;
class QVBoxLayout;
class QListWidgetItem;

namespace ui{
    class HeadImage;
    class PushButton;
    class BlacklistItem : public QWidget
    {
        Q_OBJECT
    public:
        explicit BlacklistItem(QWidget* parent);
        ~BlacklistItem(void);
        void setItemData(int64 id,QString head, QString name);
    public slots:
        void removeBtnClicekd();
    signals:
        void removeBlackList(int64 id);
    protected:
        void InitWidgets();

        virtual void leaveEvent(QEvent *event);

        virtual void enterEvent(QEvent *event);

    private:
        CSharedPtr<HeadImage>   m_Head;
        CSharedPtr<QLabel>      m_Name;
        CSharedPtr<PushButton>  m_delBtn;
        CSharedPtr<QHBoxLayout> m_mainLayout;

        int64                   m_curentID;
    };

    struct BlackInfo 
    {
        BlackInfo(){
            ptritem = CNull;
            ptrWidget = CNull;
        }

        QListWidgetItem*  ptritem;
        BlacklistItem*    ptrWidget;
    };
    class ContactBlacklistWin :     public BaseWindow
    {
        Q_OBJECT
    public:
        ContactBlacklistWin(QWidget* parent);
        ~ContactBlacklistWin(void);
    signals:
        void signalSerGetBlackList(int,data::UserBasicData result);
        void signalSerRemoveBlackListResult(int result, int64 id);
    public slots:
        void onWinClose();
        void RemoveBlackList(int64 id);

        void onSerGetBlackList(int,data::UserBasicData result);
        void onSerRemoveBlackListResult(int result, int64 id);
    protected:
        void initWidgets();
        void addItem(int64 id, QString head,QString name);
    private:
        CSharedPtr<QListWidget>  m_listWidget;
        QMap<int64,BlackInfo>    m_mapItems;
        IContactMgrControl_Ptr   m_contactServer;
    };
}


