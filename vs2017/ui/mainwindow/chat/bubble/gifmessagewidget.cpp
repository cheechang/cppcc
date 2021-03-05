#include "gifmessagewidget.h"
#include "flexaction.h"

#include <QMovie>
#include <QLabel>
#include <QDebug>

GifMessageWidget::GifMessageWidget(QWidget* parent) : ImageMessageWidget(parent), m_movie(0)
{

}

void GifMessageWidget::setImage(const QString &image)
{
    if (m_image != image) {
        m_image = image;

        if (!m_movie) {
            m_movie = new QMovie(this);
            label()->setMovie(m_movie);
        }

        m_movie->setFileName(image);
        m_movie->start();
        m_movieSize = m_movie->frameRect().size();
        resize(m_movieSize);
    }
}

QSize GifMessageWidget::suggestWidth(int width)
{
    if (!m_movie) return QSize();
	return QSize(120 + 50, 120 + 40);

    int movieWidth = m_movieSize.width();
    int movieHeight = m_movieSize.height();

    if (movieWidth > width) {
        int scaledHeight = width * movieHeight / movieWidth;
        QSize scaledSize(width, scaledHeight);
        m_movie->setScaledSize(scaledSize);
        label()->setMovie(m_movie);
        return scaledSize;
    }

    return QSize(movieWidth + 50, movieHeight + 40);
}

void GifMessageWidget::initializeContextActions()
{
    //FlexAction* playAction = new FlexAction(transfer("Play"), this);
//    connect(playAction, &QAction::triggered, this, [this] {
//        m_movie->setPaused(m_movie->state() == QMovie::Running);
//    });
    //addAction(playAction);

    // TODO: add more actions
   // addSeparator();
    AbstractMessageWidget::initializeContextActions();
}

void GifMessageWidget::setDnyMsg( CSharedPtr<data::Msg>& msg )
{
	if (msg)
	{
		AbstractMessageWidget::setMsg(msg);
		QString dnyEmoji = ":/img/smilies/dynamic_expression/"+QString::fromUtf8(msg->body.c_str());
		setImage(dnyEmoji);
	}
}

void GifMessageWidget::mouseDoubleClickEvent( QMouseEvent* event )
{

}
