#ifndef MLISTWIDGET_H
#define MLISTWIDGET_H

#include <QListWidget>
//#include "mcheckbox.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class QListWidgetItem;
class QLineEdit;
QT_END_NAMESPACE

class mListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit mListWidget(QWidget *parent = 0);
    QStringList *getTypesList();
    QStringList *getFileTypesList();
    void setTypeList(const QStringList &typeList);

private:
    void initTypeListWidget();
    void removeAll();

protected:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void listChanged();

public slots:
    void removeCurrItem();
    void addNewItem();
    void selectAllItem();
    void selectInvItem();
    void selectNonItem();
//    void addType();
//    void removeCurrItem(mCheckBox *o);

private:
    QMenu *m_contextMenu;
    QAction *m_delAct;
    QAction *m_addAct;
    QAction *m_selectAllAct;
    QAction *m_selectInvAct;
    QAction *m_selectNonAct;
    QListWidgetItem *m_curItem;
    QStringList *m_typeslist;
};

#endif // MLISTWIDGET_H
