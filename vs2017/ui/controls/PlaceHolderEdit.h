#pragma  once
#include <QTextEdit>
#include "interface/Defines.h"

namespace ui
{
	class PlaceHolderEdit : public QTextEdit
	{
		Q_OBJECT
	public:
		explicit PlaceHolderEdit(QWidget* parent = CNull);
		virtual ~PlaceHolderEdit();
		void setPlaceHolderText(const QString text);
		void setMaxLength(const unsigned int iMaxLength);

	signals:

	protected slots:
		void onTextChanged();

	protected:
		virtual void showEvent(QShowEvent* e);
		virtual void focusInEvent(QFocusEvent* e);
		virtual void focusOutEvent(QFocusEvent* e);

		QString m_strPlaceHolderText;
		unsigned int m_iMaxLength;
	};
}