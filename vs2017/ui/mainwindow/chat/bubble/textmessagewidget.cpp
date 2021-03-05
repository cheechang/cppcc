#include "textmessagewidget.h"
#include "flexaction.h"
#include "detail/dynamicfontsizelabel.h"
#include "detail/textutils.h"

#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QStaticText>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

TextMessageWidget::TextMessageWidget(QWidget* parent) : AbstractMessageWidget(parent)
{
    m_label = new QLabel(this);
    m_textColor = Qt::black;
	//m_label->setStyleSheet("background-color:transparent;");
    m_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_label->setWordWrap(true);
    m_label->setMargin(2);
    setCentralWidget(m_label);
}

void TextMessageWidget::setText(const QString &text)
{
    m_label->setText(text);
}

QString TextMessageWidget::text() const
{
    return m_label->text();
}

void TextMessageWidget::setFont(const QFont &f)
{
    m_label->setFont(f);
}

QFont TextMessageWidget::font() const
{
    return m_label->font();
}

void TextMessageWidget::setTextColor(const QColor& clr)
{
    if (m_textColor != clr) {
        m_textColor = clr;
        m_label->setStyleSheet(TextUtils::textColorStyle(clr));
    }
}

QColor TextMessageWidget::textColor() const
{
    return m_textColor;
}

QSize TextMessageWidget::suggestWidth(int width)
{
    int availableTextSpace = width - 50 ;//width - 50 - 16（2020年8月31日)
    const QFontMetrics& fm = m_label->fontMetrics();
    int textWidth = fm.width(m_label->text());
    int rowHeight = fm.height();
    int len = 0;
    int hei = rowHeight + 15; // 16 top & bottom margins
    QString txt = this->text();
    QString::iterator txtIter = txt.begin();
    int rows = 1; // default to 1
    int rowMaxWidth = 0;
    int charWidth = 0;
    int rowWidth = 0;
    bool multiline = false;
    while (txtIter != txt.end()) {
        charWidth = fm.width(*txtIter);
        len += charWidth;
        rowWidth += charWidth;

        if (len > availableTextSpace || *txtIter == '\n') {
            rowMaxWidth = qMax<int>(rowWidth, rowMaxWidth);
            rowWidth = 0;
            multiline = true;
            len = 0;
            ++rows;
            hei += rowHeight + 12; // line's top & bottom margin
        }
        ++txtIter;
    }
    QSize sz((multiline ? rowMaxWidth : textWidth) + 50, hei);
    return sz;
}

QLabel* TextMessageWidget::label()
{
    return m_label;
}

void TextMessageWidget::initializeContextActions()
{
    FlexAction* action = new FlexAction(transfer("复制"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(copyMsg()));
    addAction(action);

    action = new FlexAction(transfer("删除"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(deleteMsg()));
    addAction(action);

    addSeparator();

    action = new FlexAction(transfer("搜索"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(searchMsg()));
    addAction(action);
}

void TextMessageWidget::copyMsg()
{
    QString msg;
    if (m_label->hasSelectedText())
        msg = m_label->selectedText();
    else
        msg = m_label->text();
    QApplication::clipboard()->setText(msg);
}

void TextMessageWidget::searchMsg()
{
    // TODO
    if (m_label->hasSelectedText())
        QMessageBox::information(this, transfer("Search"), transfer("Searching \"%1\"").arg(m_label->selectedText()));
}

void TextMessageWidget::deleteMsg()
{
    // TODO
}

