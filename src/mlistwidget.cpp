#include "mtypesdef.h"
#include "mlistwidget.h"
//#include "mcheckbox.h"
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QDebug>
#include <QCheckBox>
#include <QLineEdit>
#include <QInputDialog>

mListWidget::mListWidget(QWidget *parent) :
    QListWidget(parent),
    m_contextMenu(new QMenu(this)),
    m_delAct(new QAction(this)),
    m_addAct(new QAction(QString("Add New"), this)),
    m_selectAllAct(new QAction(QString("Select All"), this)),
    m_selectInvAct(new QAction(QString("Select Invert"), this)),
    m_selectNonAct(new QAction(QString("Select Clear"), this)),
    m_typeslist(new QStringList)
{
//    m_contextMenu->addAction(m_delAct);
    m_contextMenu->addAction(m_addAct);
    m_contextMenu->addAction(m_selectAllAct);
    m_contextMenu->addAction(m_selectInvAct);
    m_contextMenu->addAction(m_selectNonAct);
    connect(m_delAct, SIGNAL(triggered()), this, SLOT(removeCurrItem()));
    connect(m_addAct, SIGNAL(triggered()), this, SLOT(addNewItem()));
    connect(m_selectAllAct, SIGNAL(triggered()), this, SLOT(selectAllItem()));
    connect(m_selectInvAct, SIGNAL(triggered()), this, SLOT(selectInvItem()));
    connect(m_selectNonAct, SIGNAL(triggered()), this, SLOT(selectNonItem()));
}

QStringList *mListWidget::getTypesList()
{
    QStringList *typeList_t = new QStringList;
    *typeList_t = *m_typeslist;
//    foreach (QString itype, *typeList_t) {
//        MDEBUG(itype);
//    }
    return typeList_t;
}

QStringList *mListWidget::getFileTypesList()
{
    QStringList *filetypeslist = new QStringList;
    QCheckBox *ck;
    qint32 itemNumb = this->count();

    for(qint32 i = 0; i < itemNumb; i++){
        QListWidgetItem *item = this->item(i);
        if(item){
            ck = qobject_cast<QCheckBox *> (this->itemWidget(item));
            if(ck->isChecked())
                filetypeslist->append(ck->text());
        }
        else break;
    }
    return filetypeslist;
}

void mListWidget::setTypeList(const QStringList &typeList)
{
    *m_typeslist = typeList;
    this->initTypeListWidget();
}

void mListWidget::initTypeListWidget()
{
//    qDebug() << this->count();
    for(qint32 i = 0; i < m_typeslist->size(); i++){
//        qDebug() << i;
        QListWidgetItem *item = new QListWidgetItem("a",NULL);
        item->setSizeHint(QSize(90, 20));

        QCheckBox *ck = new QCheckBox();
        ck->setText(m_typeslist->at(i));
        ck->setFixedSize(90, 20);
//        qDebug() << ck->text();
//        this->insertItem(this->count() - 1, item);
        this->addItem(item);
        this->setItemWidget(item, ck);
//        connect(ck, SIGNAL(delRequest(mCheckBox*)), this, SLOT(removeCurrItem(mCheckBox*)));
    }
//    qDebug() << this->count();
}

void mListWidget::removeAll()
{
    int cnt = this->count();
//    qDebug() << cnt;
    for(int i = 0; i < cnt; i++){
        QListWidgetItem *item_t = this->item(0);
        this->removeItemWidget(item_t);
        delete item_t;
    }
}

void mListWidget::mouseReleaseEvent(QMouseEvent *e)
{
//    qDebug() << "mListWidget::mouseReleaseEvent";
    if(Qt::RightButton == e->button()){
        m_curItem = this->itemAt(mapFromGlobal(QCursor::pos()));
//        qDebug() << m_curItem;
        if(NULL != m_curItem){
            QCheckBox *ck;
            ck = qobject_cast<QCheckBox *>(this->itemWidget(m_curItem));
//            qDebug() << ck;
            if(NULL != ck){
                QString actText = ck->text();
                m_delAct->setText(QString("Del %1").arg(actText));
                m_contextMenu->insertAction(m_addAct, m_delAct);
            }
            else{
                QListWidget::mouseReleaseEvent(e);
            }
        }
        m_contextMenu->exec(QCursor::pos());
        m_contextMenu->removeAction(m_delAct);
    }
    else{
        QListWidget::mouseReleaseEvent(e);
    }
}

void mListWidget::removeCurrItem()
{
    int i = this->row(m_curItem);
    this->m_typeslist->removeAt(i);
    this->removeItemWidget(m_curItem);
    delete m_curItem;
    emit listChanged();
}

void mListWidget::addNewItem()
{
    // show input dialog
    bool ok;
    QString fileType_t = QInputDialog::getText(this,
                                         QString("File Type"),
                                         QString("Input File Type:"),
                                         QLineEdit::Normal,
                                         QString("*"),
                                         &ok,
                                         Qt::SplashScreen,
                                         Qt::ImhNone);

    if(ok){
//        qDebug() << fileType_t;
        if(fileType_t.isEmpty() || 0 == fileType_t.compare(QString("*"))){
            return;
        }
//        qDebug() << fileType_t;
        this->m_typeslist->append(QString("*.") + fileType_t);
        this->removeAll();
        this->initTypeListWidget();
    }

//    foreach (QString itype, *m_typeslist) {
//        MDEBUG(itype);
//    }

}

void mListWidget::selectAllItem()
{
    QCheckBox *ck_t;
    qint32 itemsNumb_t = this->count();

    for(qint32 i = 0; i < itemsNumb_t; i++){
        QListWidgetItem *item_t = this->item(i);
        if(item_t){
            ck_t = qobject_cast<QCheckBox *> (this->itemWidget(item_t));
            if(ck_t){
                ck_t->setChecked(1);
            }
        }
        else break;
    }
}

void mListWidget::selectInvItem()
{
    QCheckBox *ck_t;
    qint32 itemsNumb_t = this->count();

    for(qint32 i = 0; i < itemsNumb_t; i++){
        QListWidgetItem *item_t = this->item(i);
        if(item_t){
            ck_t = qobject_cast<QCheckBox *> (this->itemWidget(item_t));
            if(ck_t){
                if(ck_t->isChecked())
                    ck_t->setChecked(0);
                else
                    ck_t->setChecked(1);
            }
        }
        else break;
    }
}

void mListWidget::selectNonItem()
{
    QCheckBox *ck_t;
    qint32 itemsNumb_t = this->count();

    for(qint32 i = 0; i < itemsNumb_t; i++){
        QListWidgetItem *item_t = this->item(i);
        if(item_t){
            ck_t = qobject_cast<QCheckBox *> (this->itemWidget(item_t));
            if(ck_t){
                ck_t->setChecked(0);
            }
        }
        else break;
    }
}


//void mListWidget::addType()
//{
//    qDebug() << "mListWidget::addType";

//    this->removeAll();
//    this->initTypeListWidget();
//}

//void mListWidget::removeCurrItem(mCheckBox *o)
//{
//    int cnt = this->count();
//    for(int i = 0; i < cnt; i++){
//        QListWidgetItem *item_t = this->item(i);
//        if(o == qobject_cast<mCheckBox*>(this->itemWidget(item_t))){
//            this->removeItemWidget(item_t);
//            delete item_t;
//        }
//    }
//    emit listChanged();
//}
