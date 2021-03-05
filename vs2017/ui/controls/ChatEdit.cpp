#include "ChatEdit.h"
#include <QImageReader>
#include <QFileInfo>
#include <QUrl>
#include <QMovie>
#include <QScrollBar>
#include <QUuid> 
#include <QDragEnterEvent> 
#include <QDropEvent>
#include <QFileIconProvider>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "common/Common.h"
#include "common/ChineseInfos.hpp"
#include "common/Controlptr.h"
#include "common/UIUtils.h"
#include <QTextBlock>
#include <QPainter>
#include <qcursor.h>
#include "control/chatmgrcontrol/GlobalDef.h"
#include "../mainwindow/chat/GroupAtSelectListWidget.h"
#include <QDebug>
#include <QDir>
#include <QToolTip>
#include <QMimeData>
#include <qdebug.h>
#include <QDesktopServices>
namespace ui{
	ChatEdit::ChatEdit(QWidget*parent,bool isreadonly):QTextEdit(parent),m_isburn(false),m_isdelay(false),m_isreceipt(false),m_textmsg(""),
	m_sendshortcut(1),m_isReadOnly(isreadonly)
	{
		m_imagepathlist.clear();
		m_filepathlist.clear();
		m_atmemlist.clear();
		mAtMemsWin = CNull;
		mGroupAtNameLen = 0;
		m_list.clear();

		this->setObjectName("chatedit");
		this->installEventFilter(this);
		this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		connect(this,SIGNAL(textChanged()),this,SLOT(onContentsChanged()));
		//this->setFocusPolicy(Qt::StrongFocus); 

	}
	ChatEdit::~ChatEdit(){

	}
	bool ChatEdit::canInsertFromMimeData(const QMimeData* source) const 
	{ 
		return source->hasImage() || source->hasUrls() ||source->hasHtml()||source->hasText()||QTextEdit::canInsertFromMimeData(source); 
	} 
	void ChatEdit::insertFromMimeData(const QMimeData* source) 
	{ 
		QString path("");
		if (source->hasImage()) 
		{
			QImage image = qvariant_cast<QImage>(source->imageData()); 
			path = QString::fromUtf8(USERIMGPATH)+QUuid::createUuid().toString()+QString(".png");
			bool bret = image.save(path,"PNG",99);
			if ( bret)
			{
				insertImage(path);
			}
		} 
		else if (source->hasUrls()) 
		{ 
			foreach (QUrl url, source->urls()) 
			{ 
				QFileInfo info(url.toLocalFile()); 
				if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1())){
					path =info.filePath();
					insertImage(path);
				}
				else {
					dropFile(url); 
				}
			} 
		} 
		else if(source->hasHtml()){
			QString html = source->html();
			dealWebData(html);
		}
		else 
		{ 
			QTextEdit::insertFromMimeData(source); 
		}
		this->setFocus();
		this->repaint();
	} 
	bool ChatEdit::eventFilter( QObject *obj, QEvent *e )
	{
		if(QEvent::InputMethod == e->type() && this == obj)  //输入法事件  
		{  
			QInputMethodEvent* iEvent = dynamic_cast<QInputMethodEvent*> (e);
			if (!hasFocus())
			{
				iEvent->setCommitString(""); 
				return false;
			}
			if(!m_isReadOnly){
				return false;
			}
			else{
				QInputMethodEvent* iEvent = dynamic_cast<QInputMethodEvent*>(e);   
				iEvent->setCommitString(""); 
				emit noticeInputEditFocus();
				return true;
			}
		} 
		else if (e->type() == QEvent::KeyPress)  
		{  
			QKeyEvent *event = static_cast<QKeyEvent*>(e); 
			if (mAtMemsWin != CNull && mAtMemsWin->isVisible()){
				emit keyPress(e);
				if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
					e->accept();
					return true;
				}
				return false;
			}
			if (((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)&& (event->modifiers() & Qt::ControlModifier)))
			{
				if ( ENTER_SEND == m_sendshortcut)
				{
					this->insertPlainText(QString("\n"));
					this->moveCursor(QTextCursor::EndOfLine);
				}
				else{
					emit clicked();
				}
				return true;
			}
			else if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))  
			{ 
				if ( ENTER_SEND == m_sendshortcut)
				{
					emit clicked();
				}
				else{
					this->insertPlainText(QString("\n"));
					this->moveCursor(QTextCursor::EndOfLine);
				}
				return true;  
			}  
			else if ( event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
			{
				if(!m_isReadOnly){
					cleargif();
					QTextCursor cursor = this->textCursor();
					if (event->key() == Qt::Key_Delete) {
						cursor.deleteChar();
					}
					else {
						cursor.deletePreviousChar();
					}
					if (mAtMemsWin != CNull && mAtMemsWin->isVisible())
					{
						mAtMemsWin->hide();
					}
				}
				else{
					this->clearFocus();
					this->setCursorWidth(0);
					emit noticeInputEditFocus();
				}
				return true; 
			}
		}
		else if(e->type() == QEvent::Show){
			if(!m_isReadOnly){
		      	this->setFocus();
				this->repaint();
			}
			return true;  
		 }
		return false;  
	}
	void ChatEdit::dropFile(const QUrl& url) 
	{ 
		QString path = url.toLocalFile();
		QFileInfo file(path); 
		if (file.isDir()){
			return;
		}
		QFileIconProvider provider;
		QIcon icon = provider.icon(QFileInfo(file.absoluteFilePath()));
		QPixmap pixmap = icon.pixmap(40,40);
		QString filekey("");

		QTextCursor cursor = this->textCursor();
		QTextDocument *document = this->document();

		
		QPainter p(this);
		QFontMetrics fm =  p.fontMetrics();
		QString flieName = file.fileName();
		if (flieName.length()>30)
		{
			flieName = flieName.left(10)+"..."+flieName.right(10);
		}
		int wid = fm.width(flieName)+10;
		int height = fm.height()+pixmap.height()+12;

		QImage jpgImage(wid,height,QImage::Format_RGB32);
		jpgImage.fill(QColor(Qt::white).rgb());
		QPainter painter(&jpgImage);
		int x = (wid-pixmap.width())/2;
		QPen old = painter.pen();
		painter.setPen(Qt::gray);
		painter.drawRect(QRect(0,0,wid-2,height-2));
		painter.setPen(old);
		painter.drawImage(QRect(x,1,pixmap.width()-5,pixmap.height()),pixmap.toImage());
		painter.drawText(QRect(5,pixmap.height()+12,wid-5,fm.height()),flieName);

		// 下面的addResource代码非常重要, 内存增加很少
		filekey=QString("file:///@6")+path;
		document->addResource(QTextDocument::UserResource, QUrl(filekey), jpgImage);
		cursor.insertImage(filekey);
		cursor.insertText(" ");
		cursor.movePosition(QTextCursor::End);
		this->setFocus();
		this->repaint();
	} 
	void ChatEdit::insertImage(const QString& imagepath){
		QImage image(imagepath);
		QString imagekey("");

		if (image.isNull()){ return; }
		int width = this->viewport()->width();
		int height = this->viewport()->height();
		int scaledHeight = width * image.height()/image.width();
		int scaleWidth = height*image.width()/image.height();
		if (image.width() > width || image.height() > height) {
			image = image.scaled(scaleWidth,scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}
		//判断图片类型
		QFileInfo file(imagepath);
		const QString lowerSuffix = file.suffix().toLower();
		imagekey = QUuid::createUuid().toString();
		imagekey = imagekey.mid(1, imagekey.length() - 2);
		m_imagelist.insert(imagekey,imagepath);
		if (lowerSuffix.compare("gif", Qt::CaseInsensitive) == 0){
			addAnimation(imagekey,imagepath,QSize(GIF_SIZE,GIF_SIZE));
		}
		else{
			addImage(imagekey,image);
		}
		this->setFocus();
	}
	void ChatEdit::insertEmoji(const QString& emojipath){
		insertHtml(emojipath);
		this->setFocus();
		this->repaint();
	}
	void ChatEdit::insertFile(const QString& filepath){
		dropFile(QUrl::fromLocalFile(filepath));
	}
	void ChatEdit::addImage(const QUrl& url,QImage& image){
		QTextDocument *document = this->document();
		// 下面的addResource代码非常重要, 内存增加很少
		document->addResource(QTextDocument::ImageResource, url, image);

		QTextCursor cursor = this->textCursor();
		cursor.insertImage(url.toString());
		cursor.insertText(" ");
		cursor.movePosition(QTextCursor::End);
	}
	void ChatEdit::addAnimation(const QUrl& url, const QString& fileName,const QSize&size){

		QMovie* movie = new QMovie(this);  
		movie->setFileName(fileName);  
		movie->setCacheMode(QMovie::CacheNone); 
		movie->setScaledSize(size);
	
		m_gifmap.insert(url.toString(),movie);

		//换帧时刷新  
		connect(movie, SIGNAL(frameChanged(int)), this, SLOT(onAnimate(int)));  
		movie->start(); 

		QTextCursor cursor = this->textCursor();
		// 下面的addResource代码非常重要, 内存增加很少
		cursor.insertImage(url.toString());
		cursor.insertText(" ");
		cursor.movePosition(QTextCursor::End);
	}
	void ChatEdit::onAnimate(int a)  
	{  
		if (QMovie* movie = qobject_cast<QMovie*>(sender()))  
		{         
			document()->addResource(QTextDocument::ImageResource,   //替换图片为当前帧  
				QUrl(m_gifmap.key(movie)), movie->currentPixmap());     
			setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); //刷新显示  
		}  
	}
	void ChatEdit::cleargif(){
		if ( m_gifmap.empty())
		{
			return;
		}
		QHash<QString,QMovie*>::iterator itr = m_gifmap.begin();
		while ( itr != m_gifmap.end())
		{
			if ( CNull != itr.value())
			{
				itr.value()->stop();
				delete itr.value();
				itr = m_gifmap.erase(itr);
			}
			else{
				++itr;
			}
		}
		m_textmsg.clear();
		m_imagelist.clear();
		m_imagepathlist.clear();
		m_filepathlist.clear();
		m_gifmap.clear();
	}
	void ChatEdit::onSendMsg(){
		//不允许发送空消息
		QString txt = this->toPlainText();
		txt = txt.trimmed();
		if (txt.isEmpty())
		{
			QPoint pos = this->mapToGlobal(this->rect().bottomRight());
			pos.setX(pos.x()-80);
			pos.setY(pos.y()-50);
			QToolTip::showText(pos,transfer("不能发送空白信息"));
			return;
		}
		paraseMsgContent(this->document(),true);
		m_textmsg = m_textmsg.trimmed();
		emit SendMsg(m_textmsg,m_imagepathlist,m_filepathlist,m_atmemlist,m_isburn,m_isdelay,m_isreceipt);
		m_textmsg.clear();
		m_imagelist.clear();
		m_imagepathlist.clear();
		m_filepathlist.clear();
		m_atmemlist.clear();
		this->clear();
	}
	void ChatEdit::paraseMsgContent(QTextDocument* textdocu, bool isSendMsg){
		QStringList imgkeylist;

		if (CNull == textdocu)return;
		//遍历解析内容
		int blockCount = textdocu->blockCount();
		//Log(LOG_LEV_INFO, LOG_FILE, "blockCount:%d", blockCount);
		for (int index = 0; index < textdocu->blockCount(); index++)
		{
			QTextBlock block = textdocu->findBlockByNumber(index);
			QTextBlock::iterator itr;
			QTextBlock::iterator itrtemp;
			if (isSendMsg){
				QString text = block.text();
				if (text.isEmpty())
				{
					m_textmsg += "\n";
				}
			}
			for (itr = block.begin(); itr != block.end(); ++itr)
			{
				QTextFragment fragment = itr.fragment();
				//处理图片
				bool isImageFormat = (fragment.isValid() && fragment.charFormat().isValid() && fragment.charFormat().isImageFormat());
				if (isImageFormat)
				{
					QTextImageFormat imageformat = fragment.charFormat().toImageFormat();
					QString imagekey = imageformat.name();

					QFileInfo fileInfo(imagekey);
					QString fileName = fileInfo.baseName();
					fileName.replace("_", "/");
					QByteArray byteArr(fileName.toLocal8Bit());
					QString imageName = QString::fromLocal8Bit(byteArr.fromBase64(byteArr));

					if (imageName.contains(tr("@_")) && fileInfo.exists())
					{
						QStringList strList = imageName.split("@_");
						if (strList.size() == 2)
						{
							QString atName = strList.at(1);
							int64 id = strList.at(0).toLongLong();
							m_atmemlist.push_back(id);
							m_textmsg += "@" + atName + " ";
							continue;
						}
					}
					if (!imagekey.isEmpty() && !imagekey.contains("file:///@6"))
					{
						QString imgpath("");
						imgkeylist << imagekey;

						if (!m_imagelist.isEmpty() && m_imagelist.contains(imagekey))
						{
							imgpath = m_imagelist[imagekey];
							if (!imgpath.isEmpty() && UIUtils::IsFileExist(imgpath))
							{
								m_imagepathlist.push_back(imgpath);
							}
							else{
								imgpath = GetDefaultPicPath();
								m_imagepathlist.push_back(imgpath);
							}
						}
						//是表情
						else if (imagekey.contains(":/img/smilies/")){
							QString fmt;
							if (!isSendMsg)
							{
								fmt = "<img src=\"%1\" width=\"24\" height=\"24\"/>";
								fmt = fmt.arg(imagekey);
								insertEmoji(fmt);
							}
							else{
								fmt.append(QString::fromLocal8Bit(EMOJI_IMAGE));
								fmt.append(imagekey);
								fmt.append(QString::fromLocal8Bit(EMOJI_IMAGE));
								m_textmsg += fmt;
							}
						}
						//图片来自网页
						else{
							imgpath = imagekey.replace("file:///", "");
							if (UIUtils::IsFileExist(imgpath))
							{
								//imgpath = GetDefaultPicPath();
								insertImage(imgpath);
							}
							//insertImage(imgpath);
						}
					}
					else{
						m_filepathlist << imagekey.replace("file:///@6", "");
					}
				}
				else{
					QString text = fragment.text();
					if (!text.isEmpty() && text != QString(" "))
					{
						if ((index + 1)<textdocu->blockCount()){
							text.append("\n");
						}
						m_textmsg += text;
						if (!isSendMsg)
						{
							this->insertPlainText(text);
						}
					}
				}
			}
		}
	}
	void ChatEdit::dealWebData(QString& html){
		CSharedPtr<QTextDocument> textdoc = CMakePtr<QTextDocument>();
		textdoc->setHtml(html);
		paraseMsgContent(textdoc.get());
		m_textmsg.clear();
	}
	void ChatEdit::ontextChanged(){
		QScrollBar *scrollbar = verticalScrollBar();
		if (CNull != scrollbar){
			scrollbar->setSliderPosition(scrollbar->maximum());
		}

	}
	QString ChatEdit::GetDefaultPicPath(){
		QString path("");
		path = QString::fromUtf8(USERIMGPATH)+QUuid::createUuid().toString()+QString(".jpg");
		QPixmap pixmap(QString(DEFAULT_PICTURE));
		bool bret = pixmap.save(path,"JPEG",99);
		return path;
	}
	void ChatEdit::onContentsChanged(){
		if(!m_isReadOnly){
			showAtWin();
		}
		else{
			this->clearFocus();
			this->setCursorWidth(0);
			emit noticeInputEditFocus();
		}
	}
	void ChatEdit::onSetSendMsgShorcut(int val){
		m_sendshortcut = val;
	}
	void ChatEdit::mouseDoubleClickEvent ( QMouseEvent *event ){
		if( event->buttons() == Qt::LeftButton) //判断是否左键双击
		{
			this->selectAll();
			event->accept();
		}
	}
	void ChatEdit::mousePressEvent(QMouseEvent *event){
		if( event->buttons() == Qt::LeftButton) //判断是否左键双击
		{
			if(m_isReadOnly){
				int index = this->textCursor().anchor();
				//qDebug() << "index" << index;
				for (int i = 0; i< m_list.count(); i++)
				{
					if (index > m_list.at(i).firstPos && index <m_list.at(i).lastPos)
					{
						QDesktopServices::openUrl(QUrl(m_list.at(i).url));
						//qDebug() << m_list.at(i).url;
					}
				}
				this->setCursorWidth(1);
			}
		}
		QTextEdit::mousePressEvent(event);
	}

	void ChatEdit::focusInEvent(QFocusEvent *e)
	{
		QTextEdit::focusInEvent(e);
	}

	void ChatEdit::focusOutEvent(QFocusEvent *e)
	{
		QTextEdit::focusOutEvent(e);
	}
	//鼠标移动时，什么都不干，因为一般情况下当鼠标移动文本都会被选中
	void ChatEdit::mouseMoveEvent(QMouseEvent *event)
	{
		QTextEdit::mouseMoveEvent(event);
	}
	void ChatEdit::setTargetInfo( TargetInfo info )
	{
		mTargetInfo = info;
		if (mTargetInfo.chattype == data::GROUP_CHAT)
		{
			mAtMemsWin = new GroupAtSelectListWidget(this);
			mAtMemsWin->setVisible(false);
			connect(mAtMemsWin, SIGNAL(memInfo(QString)), this, SLOT(onInserAtImg(QString)));
			connect(mAtMemsWin, SIGNAL(dataFinish()), this, SLOT(onGroupAtDataFinish()));
			connect(this, SIGNAL(keyPress(QEvent*)), mAtMemsWin, SLOT(onKeyPressed(QEvent*)));
		}
	}

	void ChatEdit::showAtWin()
	{
		if(mTargetInfo.chattype == data::GROUP_CHAT){
			int pos = __super::textCursor().position()-1;
			QString txt = __super::toPlainText();
			bool isNewInputAt = mOldText != txt;
			//qDebug()<<Q_FUNC_INFO<<"cur text:"<<txt;
			//qDebug()<<Q_FUNC_INFO<<"old text:"<<mOldText;
			mOldText = txt;
		   
			if (pos >= 0 && txt.size()>0 && (txt.at(pos) == '@' || txt.at(pos) == '@') && isNewInputAt && mGroupAtNameLen <= 0)
			{
				QPoint pos(this->cursorRect().x(),this->cursorRect().y());
				pos =  this->mapToGlobal(pos);
				mGroupAtNameLen = 1;
				mAtMemsWin->showWin(mTargetInfo.targetId,pos);
			}else{
				QString  changeTxt= txt.left(pos+1);
				QString tipText("");
				//tipText = changeTxt;
				if(changeTxt.contains("@") ||changeTxt.contains("@") ){

					for (int index= changeTxt.length()-1;index>=0;--index)
					{
						if (changeTxt.at(index) == '@' || changeTxt.at(index) == '@')
						{
							break;
						}
						tipText.push_front(changeTxt.at(index));
					}
				}
				if (!tipText.isEmpty())//&& (txt.contains("@")|| txt.contains("@"))
				{
					//qDebug()<<Q_FUNC_INFO<<"@====================text:"<<tipText;
					mGroupAtNameLen = tipText.length();
					QPoint pos(this->cursorRect().x(),this->cursorRect().y());
					pos =  this->mapToGlobal(pos);
					mAtMemsWin->showWin(mTargetInfo.targetId,pos,tipText);
				}else{
					mGroupAtNameLen= 0;
					mAtMemsWin->hide();
				}
			}
			this->setFocus();
			this->repaint();
		}
	}

	void ChatEdit::onInserAtImg( QString imgPath )
	{
		this->setFocus();
	    this->repaint();
		QTextCursor cursor = this->textCursor();
		for (int i=0;i<=mGroupAtNameLen;++i)
		{
			cursor.deletePreviousChar();
		}
		int pos = __super::textCursor().position()-1;
		QString txt = __super::toPlainText();
		if(pos>=0 && txt.length()>pos){
			txt = txt.at(pos);
			if (txt.endsWith("@")||txt.endsWith("@"))
			{
				cursor.deletePreviousChar();
			}
		}
		cursor.insertImage(imgPath);
		cursor.insertText(" ");
		cursor.movePosition(QTextCursor::End);
		mGroupAtNameLen=0;
		mAtMemsWin->hide();
	}

	void ChatEdit::keyReleaseEvent( QKeyEvent *e )
	{
		int key = e->key();	
		QTextEdit::keyPressEvent(e);
	}

	void ChatEdit::onGroupAtDataFinish()
	{
		this->setFocus();
		this->repaint();
	}  
	void ChatEdit::dropEvent(QDropEvent *event){
		QWidget* source = (QWidget*)event->source();
		if(0 != source)
		{
			insertFromMimeData(event->mimeData());
			event->setDropAction(Qt::CopyAction);
			event->accept();
		}
		else{
		    QTextEdit::dropEvent(event);
		}
	}

	void ChatEdit::insertText(QString txt)
	{
		this->setText(txt);
	}

	void ChatEdit::SetEditState(bool isRead,int type)
	{
		type == -1 ? setText(SUBJECT_NOSTART) : type == 1 ? setText(SUBJECT_END) : clear();
		if(isRead){
			this->setReadOnly(true);
		}else{
			this->setReadOnly(false);
			clear();
		}
	}
	bool ChatEdit::hasWebUrl(QString text){
		QRegExp regexp(LINK_RegulaString);
		int pos = text.indexOf(regexp);
		qDebug() << Q_FUNC_INFO << "pos" << pos;
		return (pos >= 0);
	}

	QString ChatEdit::getLinkUrl(QString text){
		if (isReceive){
			return "<a  href='" + text + "'>" + text + "</a>";
		}
		else{
			return "<a  style=color:'white' href='" + text + "'>" + text + "</a>";
		}
		
	}

	void ChatEdit::setContentSrc(bool isRcv)
	{
		isReceive = isRcv;
	}

	void ChatEdit::setWebUrlContext(QString text){
		m_list.clear();
		if (!hasWebUrl(text)){
			this->insertText(text);
			return;
		}
		UrlData  data;
		QString content = text;
		QRegExp regexp(LINK_RegulaString);
		int pos = content.indexOf(regexp);
		while (pos >= 0)
		{
			QString tmp1 = content.mid(0, pos);
			this->append(tmp1);
			int count1 = this->toPlainText().size();
			QString tmp2 = content.mid(pos, regexp.matchedLength());
			QString txt = this->getLinkUrl(tmp2);
			qDebug() << Q_FUNC_INFO << txt;
			this->append(this->getLinkUrl(tmp2));
			int count2 = this->toPlainText().size();
			//
			data.firstPos = count1;
			data.lastPos = count2;
			data.url = tmp2;
			m_list << data;
			//
			content = content.mid(pos + regexp.matchedLength());
			pos = content.indexOf(regexp);
		}
		qDebug() << Q_FUNC_INFO << content;
		this->append(content);
	}

	void ChatEdit::setAtListWidgetVisible(bool isVis)
	{
		if (mAtMemsWin != CNull){
			QPoint point = QCursor::pos();
			point = mAtMemsWin->mapFromGlobal(point);
			if (mAtMemsWin->isVisible() && mAtMemsWin->rect().contains(point)){
				return;
			}
			mAtMemsWin->setVisible(false);
		}
	}
}