#include "ContactBlacklistWin.h"
#include "controls/headimage.h"
#include "controls/PushButton.h"
#include "log.h"
#include <QLabel>
#include <QSize>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include "../../common/Common.h"
namespace ui{
    BlacklistItem::BlacklistItem( QWidget* parent ): QWidget(parent)
    {
        //this->setMinimumWidth(100);
        m_curentID = 0;
        InitWidgets();
        connect(m_delBtn.get(), SIGNAL(clicked()),this,SLOT(removeBtnClicekd()));
    }

    BlacklistItem::~BlacklistItem( void )
    {

    }

    void BlacklistItem::InitWidgets()
    {
        m_Head = CMakePtr<HeadImage>(this,QSize(38,38),true);
        m_Name = CMakePtr<QLabel>(this);
        m_delBtn = CMakePtr<PushButton>(this);
        m_mainLayout = CMakePtr<QHBoxLayout>(this);

        m_delBtn->setPicName(":/chat/delete");
        m_delBtn->setToolTip(transfer("移除黑名单"));
        m_delBtn->setVisible(false);
        m_mainLayout->setContentsMargins(15,0,25,0);
        m_mainLayout->addWidget(m_Head.get());
        m_mainLayout->addSpacing(10);
        m_mainLayout->addWidget(m_Name.get());
        m_mainLayout->addWidget(m_delBtn.get());

        this->setLayout(m_mainLayout.get());
    }

    void BlacklistItem::setItemData( int64 id,QString head, QString name )
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"setItemData id = %lld, name = %s",name.toLocal8Bit().data());
        m_Head->setAvatarPath(head);
        m_Name->setText(name);
        m_curentID = id;
    }

    void BlacklistItem::leaveEvent( QEvent *event )
    {
        m_delBtn->setVisible(false);
    }

    void BlacklistItem::enterEvent( QEvent *event )
    {
        m_delBtn->setVisible(true);
    }

    void BlacklistItem::removeBtnClicekd()
    {
        BEGIN;
        emit removeBlackList(m_curentID);
        END;
    }


    ContactBlacklistWin::ContactBlacklistWin(QWidget* parent):BaseWindow(parent)
    {
        this->setTitle(transfer("通讯录黑名单"));
        setMouseTracking(true);
        m_contactServer = CONTACTMGRCONTROL;
        initWidgets();
        connect(this,SIGNAL(closeClicked()),this,SLOT(onWinClose()));
        CONNECT_SERVICE(GetBlackList(int, data::UserBasicData));
        CONNECT_SERVICE(RemoveBlackListResult(int,int64));

        if (m_contactServer)
        {
            m_contactServer->getBlackList(CBind(&ContactBlacklistWin::signalSerGetBlackList,this,CPlaceholders _1, CPlaceholders _2));
        }

    }


    ContactBlacklistWin::~ContactBlacklistWin(void)
    {

    }

    void ContactBlacklistWin::initWidgets()
    {
        m_listWidget = CMakePtr<QListWidget>(this);
        m_listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        m_listWidget->setObjectName("blackList");
        m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mMainLayout->addWidget(m_listWidget.get());
    }

    void ContactBlacklistWin::addItem(int64 id, QString head,QString name )
    {
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"addItem id = %lld",id);
       QListWidgetItem* item = new QListWidgetItem();
       BlacklistItem* widget = new BlacklistItem(this);

       widget->setItemData(id,head,name);
       item->setSizeHint(QSize(this->width(),50));
       int row = m_listWidget->count();

       m_listWidget->insertItem(row,item);
       m_listWidget->setItemWidget(item,widget);

       BlackInfo tmp;
       tmp.ptritem = item;
       tmp.ptrWidget = widget;
       connect(widget,SIGNAL(removeBlackList(int64)),this, SLOT(RemoveBlackList(int64)));
       m_mapItems.insert(id,tmp);
    }

    void ContactBlacklistWin::onWinClose()
    {
        this->close();
    }

    void ContactBlacklistWin::RemoveBlackList( int64 id)
    {
          AddLog(LOG_LEV_DEBUG,LOG_FILE,"RemoveBlackList id = %lld",id);
          if (m_contactServer)
          {
              std::vector<int64> vec;
              vec.push_back(id);

              m_contactServer->removeBlackList(vec,CBind(&ContactBlacklistWin::signalSerRemoveBlackListResult,this,CPlaceholders _1,id));
          }
    }

    void ContactBlacklistWin::onSerGetBlackList( int err ,data::UserBasicData result )
    {
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"onSerSearchFormNetResult err =%d",err);
        if (err != 0 || (!result.id.isSet()))
        {
            return;
        }

        QString head = QString::fromStdString(result.thumbAvatar.value());
        QString name = QString::fromUtf8(result.name.value().data());
		addItem(result.id.value(),head,name);

       /* for (int i = 0; i< 5; i++)
        {
            addItem(result.id.value(),head,name);
        }*/
    }

    void ContactBlacklistWin::onSerRemoveBlackListResult( int result, int64 id)
    {
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"onSerRemoveBlackListResult result = %d",result);
        if (result == 0)
        { 
            QMap<int64, BlackInfo>::iterator iter = m_mapItems.find(id);
            if (iter != m_mapItems.end())
            {
                m_listWidget->takeItem(m_listWidget->row(iter.value().ptritem));
                m_mapItems.remove(id);
            }
        }
        
    }

}

