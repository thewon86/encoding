#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

QT_BEGIN_NAMESPACE
class QStringList;
//class Dialog_ft;
class QTableWidget;
class QLayout;
class QFile;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void on_pushButton_begain_clicked();
    void on_pushButton_files_clicked();
    void on_pushButton_dir_clicked();
    void on_checkBox_auto_clicked();

private:
    void loadConfig();
    void loadDefaultConfig();
    QStringList *readConfig();
    void saveConfig();
    QStringList &getFilesList(const QString &lpath);
    bool getFileTypesList();
    void convertFile(const QString &fileName, bool backup = 1);
    void addFilesToListwidget(QStringList &fileslist);
    void showMessage(const QString &lmsg);
    QString &identifyFileEncoding(const QString &fileName)const;

private:
    Ui::Dialog *ui;
    QStringList *m_suffixlist;
    QStringList *m_typeslist;
    QString *m_HistoryDir;
//    Dialog_ft *ftlist;
    qint32 m_convertCounter;
};

#endif // DIALOG_H
