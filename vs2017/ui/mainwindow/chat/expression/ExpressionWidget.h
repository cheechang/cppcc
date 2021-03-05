#ifndef MYEMOTIONWIDGET_H
#define MYEMOTIONWIDGET_H

#include <QWidget>
#include <QTableWidget>
namespace ui{
	class ExpressionWidget : public QTableWidget
	{
		Q_OBJECT

	public:
		ExpressionWidget(QWidget *parent = 0);
		~ExpressionWidget();

		void setRowAndColumn(int row , int column);
		void setEmotionSize(QSize emotionSize);
		void setEmotionMovieSize(QSize emotionMovieSize);
		void setMaxRow(int maxRow);
		void addEmotionItem(QString fileName, QString toolTip = "");

		void initTableWidget();
		void showDynamicEmotion(QPoint cursorPos);
	signals:
		void clicked(QString fileName);
	private:
		bool eventFilter(QObject *obj, QEvent *event);
		//bool nativeEvent(const QByteArray &eventType, void *message, long *result);

		private slots:

	private:

		int m_preRow;
		int m_preColumn;
		int m_tableRow;
		int m_tableColumn;
		int m_maxRow;
		QSize m_emotionSize;
		QSize m_emotionMovieSize;
		QList<QString> m_emotionList;
	};
}

#endif // MYEMOTIONWIDGET_H
