#pragma  once
#include <memory>
#include <QGraphicsProxyWidget>
class LoadIndicator;
class LoadMsgWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    LoadMsgWidget(QGraphicsItem *parent =0);
    ~LoadMsgWidget();

	 int type() const;
	 void setLoading(bool loading);
	 void setNoMoreData();
	 bool isLoading();
	 bool hasMoreData();
	 void setNoMoreState(bool isClicked);
signals:
	 void getHistoryMsg();
private:
	LoadIndicator* m_loadIndicator;
};
