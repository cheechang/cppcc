#include "TreeViewItemDelegate.h"
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QTextItem>
#include <QPoint>
#include <QImage>
#include <QFileInfo>
#include <QToolTip>
#include "treeviewmodel.h"
#include "../controls/headimage.h"
#include "common/common.h"
namespace ui{
	TreeViewItemDelegate::TreeViewItemDelegate(QObject *parent)
		: QStyledItemDelegate(parent)
	{
	
	}

	TreeViewItemDelegate::~TreeViewItemDelegate()
	{

	}

	void TreeViewItemDelegate::paint( QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index ) const
	{
		

		QStyleOptionViewItem  viewOption(option);
		bool isFocus= (viewOption.state & QStyle::State_HasFocus)
			||(viewOption.state & QStyle::State_MouseOver)
			||(viewOption.state & QStyle::State_Selected);

		if ( viewOption.state & QStyle::State_HasFocus )
		{
			viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
		}
		QStyledItemDelegate::paint(painter, viewOption, index);
		
		if (m_treeView != NULL)
		{
			bool isLeaf = index.data(IsLeafRole).toBool();
			bool isTipNode = isLeaf && (index.data(TipNodeRole).toBool());
			if(isFocus && (!TreeModel::isInit||viewOption.state & QStyle::State_MouseOver||viewOption.state & QStyle::State_Selected)){
				painter->fillRect(option.rect,QBrush(TREEVIEW_HOVER_CLOLOR));
			}else{
				painter->fillRect(option.rect,QBrush(TREEVIEW_NORMAL_CLOLOR));
			}

			if(isLeaf && !isTipNode){
				QString headPath = index.data(HeadRole).toString();

				QImage srcImage(headPath);
				if(srcImage.isNull()){
					srcImage.load(QString(DEFAULT_AVATAR));
				}
				QImage pixmap = getRoundQImage(srcImage,QSize(ImageSize,ImageSize));
		
				
				int poxY = viewOption.rect.top()+(viewOption.rect.height() - ImageSize)/2;
				QRect decorationRect(viewOption.rect.left(),poxY,ImageSize,ImageSize);

				if(!pixmap.isNull()){
					painter->drawImage(decorationRect, pixmap);
				}
				QPoint pos = decorationRect.topRight();
				int y  =viewOption.rect.top()+(viewOption.rect.height())/2+5;
				int x= pos.x()+10;
				pos.setY(y);
				pos.setX(x);
				painter->setFont(option.font);
				painter->drawText(pos,index.data(TileRole).toString());
				
			}else if(!index.model()->hasChildren(index)&& !isLeaf){

				painter->drawImage(option.rect.topLeft().x()-12,option.rect.topLeft().y()+DepartHeigth/3,QImage(QString(":/contact/branchClose")));
				painter->drawText(option.rect.topLeft().x()+6,option.rect.topLeft().y()+DepartHeigth/2+4,index.data(TileRole).toString());
			}else if(isTipNode){
				painter->drawText(option.rect.topLeft().x(),option.rect.topLeft().y()+UserHeight/2,index.data(TileRole).toString());
	
			}else{
				painter->drawText(option.rect.topLeft().x()+6,option.rect.topLeft().y()+DepartHeigth/2+4,index.data(TileRole).toString());
			}
			
		}
		
	}

	QImage TreeViewItemDelegate::getRoundQImage(QImage& img,QSize size)const
	{
		if (img.isNull())
		{
			return QImage();
		}
		QImage resultImage(size,QImage::Format_ARGB32_Premultiplied);
		QImage mask(QString(":/contact/mask_max"));
		mask = mask.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

		
		QPainter painter(&resultImage);

		painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing,true);

		painter.setCompositionMode(QPainter::CompositionMode_Source);
		painter.fillRect(mask.rect(),Qt::transparent);
		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.drawImage(0, 0, mask);
		painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
		painter.drawImage(0, 0, img.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
		painter.end();	
		return resultImage;
	}

	bool TreeViewItemDelegate::editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index )
	{
		    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

		    if (event->type() == QEvent::MouseMove && option.rect.contains(mouseEvent->pos()))
		    {
		        //QCursor cursor(Qt::PointingHandCursor);
		       // QApplication::setOverrideCursor(cursor);

		        QString strText =index.data(ToolTipRole).toString();
		        QToolTip::showText(mouseEvent->globalPos(), strText);
		    }
		    else
		    {
		        //QCursor cursor(Qt::ArrowCursor);
		       // QApplication::setOverrideCursor(cursor);
		    }

		return QStyledItemDelegate::editorEvent(event, model, option, index);
	}

	void TreeViewItemDelegate::setView( QTreeView *treeView )
	{
		m_treeView = treeView;
	}

	QSize TreeViewItemDelegate::sizeHint( const QStyleOptionViewItem &option,const QModelIndex &index ) const
	{
		if(index.data(IsLeafRole).toBool()){
			return QSize(option.rect.width(),UserHeight);
		}else{
			return QSize(option.rect.width(),DepartHeigth);
		}
	}
}
