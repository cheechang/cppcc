#ifndef LOADINDICATOR_H
#define LOADINDICATOR_H

#include <QWidget>

class LoadIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit LoadIndicator(QWidget *parent = 0);
    ~LoadIndicator();
	bool hasMoreData();
	void setNoMoreData();
	void setNoMoreDataState(bool isClicked);
public slots:
    void setLoading(bool loading);
    bool loading() const;

signals:
    void startLoading();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void onLabelClicked();
    void layoutWidgets();

private:
    class LoadIndicatorPrivate* d_ptr;
};

#endif // LOADINDICATOR_H
