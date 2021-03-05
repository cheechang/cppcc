#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include "common/Controlptr.h"
namespace ui{
    class UserExtendInfo : public  QWidget
    {
        Q_OBJECT
    public:
        UserExtendInfo(QWidget* parent);
        ~UserExtendInfo(void);
    signals:
        void signalSerExtendedField( std::vector<data::EnterpriseDictionary>& dicts);

    public slots:
        void setOrgId(int64 id);
        void onSerExtendedField(std::vector<data::EnterpriseDictionary>& dicts);

    protected:
        void initWidget();
        void addInfoItem(QString Infotype,QString info);
    private:
        CSharedPtr<QTableWidget>      m_tableWidget;
        CSharedPtr<QHBoxLayout>       m_mianLayout;
        IEntMgrControl_Ptr m_entcontrol;
        IContactMgrControl_Ptr m_contactControl;
        IContactMgrControl_Ptr m_contactcontrol;
        QMap<std::string, std::string> m_extMap;
        int64                          m_curentUserID;
    };
}


