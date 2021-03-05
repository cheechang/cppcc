#include "UserExtendInfo.h"
#include <QHeaderView>
#include "controls/NoFocusDelegate.h"
#include <json.h>
namespace ui{
    UserExtendInfo::UserExtendInfo(QWidget* parent): QWidget(parent)
        ,m_curentUserID(0)
    {
        m_entcontrol = ENTMGRCONTROL;
        m_contactcontrol = CONTACTMGRCONTROL;
        m_contactControl = CONTACTMGRCONTROL;

        m_tableWidget = CMakePtr<QTableWidget>(this);
        m_mianLayout = CMakePtr<QHBoxLayout>();

        CONNECT_SERVICE(ExtendedField(std::vector<data::EnterpriseDictionary>&));
        initWidget();
        m_mianLayout->setContentsMargins(30,0,0,0);
        m_mianLayout->addWidget(m_tableWidget.get(),0,Qt::AlignCenter);
        this->setLayout(m_mianLayout.get());
    }


    UserExtendInfo::~UserExtendInfo(void)
    {

    }

    void UserExtendInfo::setOrgId(int64 id)
    {
        m_curentUserID = id;
      
        if (m_contactControl)
        {
            m_contactControl->GetBuddyExtendsInfo(id,CBind(&UserExtendInfo::signalSerExtendedField,this, CPlaceholders _1));
        }
    }

    void UserExtendInfo::onSerExtendedField(std::vector<data::EnterpriseDictionary>& dicts )
    {
        for(int i =0 ; i< dicts.size(); ++i)
        {
            QString val = QString::fromUtf8(dicts.at(i).dicValue.data());
            QString relVal = QString::fromUtf8(dicts.at(i).dicRealValue.data());
            addInfoItem(val,relVal);
        }
    }

    void UserExtendInfo::initWidget()
    {
        m_tableWidget->setColumnCount(2);  //两列
        m_tableWidget->horizontalHeader()->resizeSection(0,100);
        m_tableWidget->horizontalHeader()->resizeSection(1,140);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->setItemDelegate(new NoFocusDelegate());//去除虚线框
        m_tableWidget->setShowGrid(false);  //不显示网格
        m_tableWidget->setFrameShape(QFrame::NoFrame); //无边框
        m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
        m_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        m_tableWidget->horizontalHeader()->setVisible(false);
    }

    void UserExtendInfo::addInfoItem(QString Infotype,QString info)
    {
        QString tmp = Infotype;
        tmp.append(": ");
        int row = m_tableWidget->rowCount();
        m_tableWidget->insertRow(row);

        QTableWidgetItem *itemType = new QTableWidgetItem();
        QTableWidgetItem *itemInfo = new QTableWidgetItem();

        itemType->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        itemInfo->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        itemType->setText(tmp);
        itemInfo->setText(info);
        itemInfo->setTextColor(Qt::gray);

        m_tableWidget->setItem(row,0,itemType);
        m_tableWidget->setItem(row,1,itemInfo);
    }

}
