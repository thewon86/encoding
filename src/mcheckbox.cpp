#include "mcheckbox.h"
#include <QCheckBox>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QCursor>

mCheckBox::mCheckBox(QWidget *parent) :
    QCheckBox(parent),
    m_contextMenu(new QMenu(this)),
    m_delAct(new QAction(this))
{
    m_contextMenu->addAction(m_delAct);
    connect(m_delAct, SIGNAL(triggered()), this, SLOT(removeCurrItem()));
//    connect(m_contextMenu, SIGNAL(triggered(QAction*)), this, SLOT(removeCurrItem()));
}

mCheckBox::mCheckBox(const QString &text, QWidget *parent) :
    QCheckBox(text, parent),
    m_contextMenu(new QMenu(this)),
    m_delAct(new QAction(this))
{
    m_contextMenu->addAction(m_delAct);
    connect(m_delAct, SIGNAL(triggered()), this, SLOT(removeCurrItem()));
//    connect(m_contextMenu, SIGNAL(triggered(QAction*)), this, SLOT(removeCurrItem()));
}

void mCheckBox::removeCurrItem()
{
    emit delRequest(this);
}

void mCheckBox::mouseReleaseEvent(QMouseEvent *e)
{
    if(Qt::RightButton == e->button()){
        QString ckbText = this->text();
        m_delAct->setText(QString("Del %1").arg(ckbText));
        m_contextMenu->exec(QCursor::pos());
    }
    else {
        QCheckBox::mouseReleaseEvent(e);
    }
}
