#ifndef MCHECKBOX_H
#define MCHECKBOX_H

#include <QCheckBox>

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
QT_END_NAMESPACE

class mCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit mCheckBox(QWidget *parent=0);
    explicit mCheckBox(const QString &text, QWidget *parent=0);

protected:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void delRequest(mCheckBox *o);

private slots:
    void removeCurrItem();

private:
    QMenu *m_contextMenu;
    QAction *m_delAct;
};

#endif // MCHECKBOX_H
