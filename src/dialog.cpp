#include "mtypesdef.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QStringList>
#include <QTableWidget>
#include <QCheckBox>
#include <QWidget>
#include <QStringListModel>
#include <QTextCodec>
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QByteArray>
#include "identifyencoding.h"
#include <QDebug>
#include <QSettings>
#include <QtXml>
#include <QDomDocument>
#include <QXmlStreamWriter>
#include <QLineEdit>

#ifdef CONF_INI
#ifdef CONF_XML
#error "defined both CONF_INI and CONF_XML!"
#endif
#pragma message "USE INI CONF FILE"
#else
#ifndef CONF_XML
#error "NOT define either CONF_INI CONF_XML"
#endif
#pragma message "USE XML CONF FILE"
#endif

#ifdef CONF_INI
#define CONFIGFILENAME "./config.ini"
#else
#ifdef CONF_XML
#define CONFIGFILENAME "./config.xml"
#endif
#endif

bool suffix_is_matching(const QString &lsuffix, const QStringList &lsuffixlist);
QString getCurrentTime();

bool suffix_is_matching(const QString &lsuffix, const QStringList &lsuffixlist)
{
    foreach (QString isuffix, lsuffixlist) {
         if(0 == isuffix.mid(2).compare(lsuffix)){
            return 1;
        }
    }
    return 0;
}

QString getCurrentTime()
{
    return QDateTime::currentDateTime().toString(QString("[yyyy-MM-dd hh:mm:ss]"));
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_suffixlist(NULL),
    m_HistoryDir(new QString()),
    m_convertCounter(0)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowMaximizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

//    m_typeslist = new QStringList;
    loadConfig();
    ui->listWidget_tl->setTypeList(*m_typeslist);
    delete m_typeslist;
/*
    for(qint32 i = 0; i < typelist->size(); i++){
        QListWidgetItem *item = new QListWidgetItem("a",NULL);
        item->setSizeHint(QSize(90, 20));

        QCheckBox *ck = new QCheckBox();
        ck->setText(typelist->at(i));
        ck->setFixedSize(90, 20);

        ui->listWidget_tl->addItem(item);
        ui->listWidget_tl->setItemWidget(item, ck);
//        connect(ck, SIGNAL());
    }
    QListWidgetItem *item = new QListWidgetItem("b",NULL);
    item->setSizeHint(QSize(90, 20));

    QLineEdit *ck = new QLineEdit();

//    ck->setText(typelist->at(i));
    ck->setFixedSize(90, 20);

    ui->listWidget_tl->addItem(item);
    ui->listWidget_tl->setItemWidget(item, ck);
*/
//    QString strCodec = "GB2312,GBK,UTF-8,Big5,Big5-HKSCS,EUC-JP,EUC-KR,GB18030,IBM-Thai,IBM00858,IBM01140,IBM01141,IBM01142,IBM01143,IBM01144,IBM01145,IBM01146,IBM01147,IBM01148,IBM01149,IBM037,IBM1026,IBM1047,IBM273,IBM277,IBM278,IBM280,IBM284,IBM285,IBM297,IBM420,IBM424,IBM437,IBM500,IBM775,IBM850,IBM852,IBM855,IBM857,IBM860,IBM861,IBM862,IBM863,IBM864,IBM865,IBM866,IBM868,IBM869,IBM870,IBM871,IBM918,ISO-2022-CN,ISO-2022-JP,ISO-2022-JP-2,ISO-2022-KR,ISO-8859-1,ISO-8859-13,ISO-8859-15,ISO-8859-2,ISO-8859-3,ISO-8859-4,ISO-8859-5,ISO-8859-6,ISO-8859-7,ISO-8859-8,ISO-8859-9,JIS_X0201,JIS_X0212-1990,KOI8-R,KOI8-U,Shift_JIS,TIS-620,US-ASCII,UTF-16BE,UTF-16LE,UTF-32,UTF-32BE,UTF-32LE,windows-1250,windows-1251,windows-1252,windows-1253,windows-1254,windows-1255,windows-1256,windows-1257,windows-1258,windows-31j,x-Big5-HKSCS-2001,x-Big5-Solaris,x-euc-jp-linux,x-EUC-TW,x-eucJP-Open,x-IBM1006,x-IBM1025,x-IBM1046,x-IBM1097,x-IBM1098,x-IBM1112,x-IBM1122,x-IBM1123,x-IBM1124,x-IBM1381,x-IBM1383,x-IBM33722,x-IBM737,x-IBM833,x-IBM834,x-IBM856,x-IBM874,x-IBM875,x-IBM921,x-IBM922,x-IBM930,x-IBM933,x-IBM935,x-IBM937,x-IBM939,x-IBM942,x-IBM942C,x-IBM943,x-IBM943C,x-IBM948,x-IBM949,x-IBM949C,x-IBM950,x-IBM964,x-IBM970,x-ISCII91,x-ISO-2022-CN-CNS,x-ISO-2022-CN-GB,x-iso-8859-11,x-JIS0208,x-JISAutoDetect,x-Johab,x-MacArabic,x-MacCentralEurope,x-MacCroatian,x-MacCyrillic,x-MacDingbat,x-MacGreek,x-MacHebrew,x-MacIceland,x-MacRoman,x-MacRomania,x-MacSymbol,x-MacThai,x-MacTurkish,x-MacUkraine,x-MS932_0213,x-MS950-HKSCS,x-MS950-HKSCS-XP,x-mswin-936,x-PCK,x-SJIS_0213,x-UTF-16LE-BOM,X-UTF-32BE-BOM,X-UTF-32LE-BOM,x-windows-50220,x-windows-50221,x-windows-874,x-windows-949,x-windows-950,x-windows-iso2022jp";
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QString strCodec = "GB2312,GBK,GB18030-0,UTF-8,UTF-16,Apple Roman,Big5,Big5-HKSCS,CP949,EUC-JP,EUC-KR,EUC-JP,IBM 850,IBM 866,IBM 874,ISO 2022-JP,ISO 8859-1 to 10,ISO 8859-13 to 16,Iscii-Bng|Dev|Gjr|Knd|Mlm|Ori|Pnj|Tlg|Tml,JIS X 0201,JIS X 0208,KOI8-R,KOI8-U,Shift-JIS,TIS-620,TSCII,UTF-16BE,UTF-16LE,UTF-32,UTF-32BE,UTF-32LE,Windows-1250 to 1258";
#elif (QT_VERSION >= QT_VERSION_CHECK(4, 0, 0))
    QString strCodec = "GB2312,GBK,GB18030-0,UTF-8,UTF-16,Apple Roman,Big5,Big5-HKSCS,CP949,EUC-JP,EUC-KR,EUC-JP,IBM 850,IBM 866,IBM 874,ISO 2022-JP,ISO 8859-1 to 10,ISO 8859-13 to 16,Iscii-Bng|Dev|Gjr|Knd|Mlm|Ori|Pnj|Tlg|Tml,JIS X 0201,JIS X 0208,KOI8-R,KOI8-U,MuleLao-1,ROMAN8,Shift-JIS,TIS-620,TSCII,UTF-16BE,UTF-16LE,UTF-32,UTF-32BE,UTF-32LE,Windows-1250 to 1258,WINSAMI2";
#else
    QString strCodec = "GB2312,GBK,GB18030-0,UTF-8,UTF-16,Apple Roman,Big5,Big5-HKSCS,CP949,EUC-JP,EUC-KR,EUC-JP,IBM-Thai,IBM00858,IBM01140,IBM01141,IBM01142,IBM01143,IBM01144,IBM01145,IBM01146,IBM01147,IBM01148,IBM01149,IBM037,IBM1026,IBM1047,IBM273,IBM277,IBM278,IBM280,IBM284,IBM285,IBM297,IBM420,IBM424,IBM437,IBM500,IBM775,IBM850,IBM852,IBM855,IBM857,IBM860,IBM861,IBM862,IBM863,IBM864,IBM865,IBM866,IBM868,IBM869,IBM870,IBM871,IBM918,ISO-2022-CN,ISO-2022-JP,ISO-2022-JP-2,ISO-2022-KR,ISO-8859-1,ISO-8859-13,ISO-8859-15,ISO-8859-2,ISO-8859-3,ISO-8859-4,ISO-8859-5,ISO-8859-6,ISO-8859-7,ISO-8859-8,ISO-8859-9,JIS_X0201,JIS_X0212-1990,KOI8-R,KOI8-U,Shift_JIS,TIS-620,US-ASCII,UTF-16BE,UTF-16LE,UTF-32,UTF-32BE,UTF-32LE,windows-1250,windows-1251,windows-1252,windows-1253,windows-1254,windows-1255,windows-1256,windows-1257,windows-1258,windows-31j,x-Big5-HKSCS-2001,x-Big5-Solaris,x-euc-jp-linux,x-EUC-TW,x-eucJP-Open,x-IBM1006,x-IBM1025,x-IBM1046,x-IBM1097,x-IBM1098,x-IBM1112,x-IBM1122,x-IBM1123,x-IBM1124,x-IBM1381,x-IBM1383,x-IBM33722,x-IBM737,x-IBM833,x-IBM834,x-IBM856,x-IBM874,x-IBM875,x-IBM921,x-IBM922,x-IBM930,x-IBM933,x-IBM935,x-IBM937,x-IBM939,x-IBM942,x-IBM942C,x-IBM943,x-IBM943C,x-IBM948,x-IBM949,x-IBM949C,x-IBM950,x-IBM964,x-IBM970,x-ISCII91,x-ISO-2022-CN-CNS,x-ISO-2022-CN-GB,x-iso-8859-11,x-JIS0208,x-JISAutoDetect,x-Johab,x-MacArabic,x-MacCentralEurope,x-MacCroatian,x-MacCyrillic,x-MacDingbat,x-MacGreek,x-MacHebrew,x-MacIceland,x-MacRoman,x-MacRomania,x-MacSymbol,x-MacThai,x-MacTurkish,x-MacUkraine,x-MS932_0213,x-MS950-HKSCS,x-MS950-HKSCS-XP,x-mswin-936,x-PCK,x-SJIS_0213,x-UTF-16LE-BOM,X-UTF-32BE-BOM,X-UTF-32LE-BOM,x-windows-50220,x-windows-50221,x-windows-874,x-windows-949,x-windows-950,x-windows-iso2022jp";
#endif
    QStringList strListCodec = strCodec.split(",");
    ui->comboBox_srccodec->addItems(strListCodec);
    ui->comboBox_srccodec->setCurrentIndex(0);
    ui->comboBox_dstcodec->addItems(strListCodec);
    ui->comboBox_dstcodec->setCurrentIndex(3);

    *m_HistoryDir = QDir::currentPath();
}

Dialog::~Dialog()
{
    m_typeslist = this->ui->listWidget_tl->getTypesList();
//    foreach (QString itype, *m_typeslist) {
//        MDEBUG(itype);
//    }
    this->saveConfig();
    delete ui;
}

void Dialog::loadConfig()
{
#ifdef CONF_INI
    QString configfilename(CONFIGFILENAME);
#else
#ifdef CONF_XML
    QString configfilename("./config.xml");
#endif
#endif

    if(QFile(configfilename).exists()){
        m_typeslist = readConfig();
        if(!m_typeslist->isEmpty()){
            return;
        }
    }
    {
        loadDefaultConfig();
        saveConfig();
    }
}

void Dialog::loadDefaultConfig()
{
    m_typeslist = new QStringList();
    *m_typeslist = QStringList()
							<< QString::fromUtf8("*.c")
                            << QString::fromUtf8("*.cpp")
                            << QString::fromUtf8("*.cxx")
                            << QString::fromUtf8("*.h")
                            << QString::fromUtf8("*.hpp")
                            << QString::fromUtf8("*.s")
                            << QString::fromUtf8("*.asm")
                            << QString::fromUtf8("*.*");
//    QStringList typelist = QStringList()
//                            << QString::fromUtf8("*.o")
//                            << QString::fromUtf8("*.cpp")
//                            << QString::fromUtf8("*.cxx")
//                            << QString::fromUtf8("*.h")
//                            << QString::fromUtf8("*.c")
//                            << QString::fromUtf8("*.s")
//                            << QString::fromUtf8("*.asm")
//                            << QString::fromUtf8("*.*");
}

QStringList *Dialog::readConfig()
{
    const QString filename(CONFIGFILENAME);
    QStringList *typelistval = new QStringList;
#ifdef CONF_INI
    QSettings *settings;
#else
#ifdef CONF_XML
    QFile mconfigfile(filename);
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;
#else
    return *typelistval;
#endif
#endif

#ifdef CONF_INI
    settings = new QSettings(filename, QSettings::IniFormat);
    *typelistval = settings->value("Settings/FileTypes").toStringList();
#endif

#ifdef CONF_XML
    if (!domDocument.setContent(&mconfigfile, true, &errorStr, &errorLine,
                                &errorColumn)) {
//        QMessageBox::information(window(), tr("DOM Bookmarks"),
//                                 tr("Parse error at line %1, column %2:\n%3")
//                                 .arg(errorLine)
//                                 .arg(errorColumn)
//                                 .arg(errorStr));
        return typelistval;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "appSettings") {
//        QMessageBox::information(window(), tr("DOM Bookmarks"),
//                                 tr("The file is not an configure file."));
        return typelistval;
    } else if (root.hasAttribute("version")
               && root.attribute("version") != "1.0") {
//        QMessageBox::information(window(), tr("DOM Bookmarks"),
//                                 tr("The file is not version 1.0 "
//                                    "file."));
        return typelistval;
    }
    QDomElement child = root.firstChildElement("Settings");
    if(!child.isNull()){
        QString value;
        value = child.attribute("key");
        MDEBUG(value);
        value = child.attribute("value");
        MDEBUG(value);
        *typelistval = value.split(QChar(';'));
    }
    else{
        return typelistval;
    }
#endif
    MDEBUG(*typelistval);

    return typelistval;
}

void Dialog::saveConfig()
{
    const QString filename(CONFIGFILENAME);
#ifdef CONF_INI
    QSettings *settings;
    settings = new QSettings(filename, QSettings::IniFormat);
    settings->setValue("Settings/FileTypes", *m_typeslist);
    settings->sync();
    delete m_typeslist;
#endif

#ifdef CONF_XML
    QFile mconffile(filename);

    QDomDocument domDocument;

    QDomProcessingInstruction instruction;
    instruction = domDocument.createProcessingInstruction( "xml", "version=\"1.0\" encoding=\"utf-8\"" );
    domDocument.appendChild( instruction );

    QDomElement root = domDocument.createElement("appSettings");
    domDocument.appendChild(root);

    QDomElement settings = domDocument.createElement("Settings");
    settings.setAttribute(QString("key"), QString("FileTypes"));
    settings.setAttribute(QString("value"), m_typeslist->join(QString(";")));
    root.appendChild(settings);

    if(!mconffile.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream xmlstream(&mconffile);
    domDocument.save(xmlstream, 4);
    mconffile.close();
#endif
}

QStringList &Dialog::getFilesList(const QString &lpath)
{
    QDir ldir(lpath);
    QFileInfoList fileinfolist;
    QStringList *filelist = new QStringList;

    ldir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    fileinfolist = ldir.entryInfoList();

    foreach (QFileInfo ifile, fileinfolist){
        if(ifile.isDir()){
            if(ui->checkBox_subdir->isChecked()){
                filelist->append(getFilesList(ifile.absoluteFilePath()));
            }
        }
        if(ifile.isFile()){
            if(suffix_is_matching(ifile.suffix(), *m_suffixlist)){
                filelist->append(ifile.absoluteFilePath());
            }
        }
    }
    return *filelist;
}
#if 1
bool Dialog::getFileTypesList()
{
//    QStringList *filetypeslist = new QStringList;
//    QCheckBox *ck;
//    qint32 itemNumb = ui->listWidget_tl->count();

////    qDebug() << itemNumb;
//    for(qint32 i = 0; i < itemNumb; i++){
//        QListWidgetItem *item = ui->listWidget_tl->item(i);
//        if(item){
//            ck = qobject_cast<QCheckBox *> (ui->listWidget_tl->itemWidget(item));
//            if(ck->isChecked())
//                filetypeslist->append(ck->text());
//        }
//        else break;
//    }
//    QStringList *filetypeslist = ui->listWidget_tl->getTypesList();
//    return *filetypeslist;

    if(NULL != m_suffixlist){
        delete m_suffixlist;
        m_suffixlist = NULL;
    }
    m_suffixlist = this->ui->listWidget_tl->getFileTypesList();

    if(m_suffixlist->isEmpty()){
        QMessageBox::information(this,tr("提示"),tr("请至少选择一种文件类型"));
        return false;
    }
    return true;
}
#endif

void Dialog::on_pushButton_begain_clicked()
{
    QListWidgetItem *item;
    QCheckBox *ck;
    qint32 itemNumb = ui->listWidget_files->count();

    m_convertCounter = 0;       // 转换成功文件个数计数

    if(itemNumb < 1){
        qDebug() << "No File Select!";
        QMessageBox::information(this,tr("提示"),tr("请选择转换文件"));
        return;
    }
    showMessage(getCurrentTime() + ">" + "转换开始...");
    for(qint32 i = 0; i < itemNumb; i++){
        item = ui->listWidget_files->item(i);
        if(item){
            ck = static_cast<QCheckBox *> (ui->listWidget_files->itemWidget(item));
            if(ck->isChecked()){
                convertFile(ck->text(), ui->checkBox_bak->isChecked());
            }
        }
        else {};
    }
    showMessage(getCurrentTime() + ">" + "转换结束...");
    QMessageBox::information(this,tr("提示"),tr("转换完毕"));
}

void Dialog::convertFile(const QString &fileName, bool backup)
{
    QFile srcFile(fileName), dstFile(QString(""));
    QTextStream inTxtStream(&srcFile), outTxtStream(&dstFile);
    QString fileContent;
    QString fileEncodName;
    QTextCodec *srcCodec;
    QTextCodec *dstCodec;

    showMessage(getCurrentTime() + ">" + "开始对文件：{" + fileName + "}进行转换...");

    if(!ui->checkBox_auto->isChecked()){
        srcCodec = QTextCodec::codecForName(ui->comboBox_srccodec->currentText().toLatin1());
    }
    else {
        fileEncodName = identifyFileEncoding(fileName);
        if(!fileEncodName.isNull()){
            srcCodec = QTextCodec::codecForName(fileEncodName.toLatin1());
//            showMessage(getCurrentTime() + ">" + "原始编码格式：{" + fileEncodName + "}"
//                        + "目标编码格式：{" + ui->comboBox_dstcodec->currentText() + "}");
        }
        else{
            srcCodec = QTextCodec::codecForName("UTF-8");
//            showMessage(getCurrentTime() + ">" + "原始编码格式：{" + "UTF-8" + "}"
//                        + "目标编码格式：{" + ui->comboBox_dstcodec->currentText() + "}");
        }
    }
    dstCodec = QTextCodec::codecForName(ui->comboBox_dstcodec->currentText().toLatin1());
//    qDebug() << QString(dstCodec->name());
//    qDebug() << QString(srcCodec->name());
    showMessage(getCurrentTime() + ">" + "原始编码格式：{" + QString(srcCodec->name()) + "}" \
                + "目标编码格式：{" + QString(dstCodec->name()) + "}");

    if(!srcFile.open(QFile::ReadOnly)){
        showMessage(getCurrentTime() + ">" + "打开原文件错误: " + fileName);
        return;
    }
    inTxtStream.setAutoDetectUnicode(false);
    inTxtStream.setCodec(srcCodec);
    outTxtStream.setAutoDetectUnicode(false);

    fileContent = inTxtStream.readAll();
    srcFile.close();

    if(fileContent.isEmpty()){
//        QMessageBox::information(this,tr("提示"),tr("发现一个空文件！\n取消当前文件的转换！"));
        showMessage(getCurrentTime() + ">" + "发现一个空文件：" + fileName + "取消当前文件的转换！");
        return;
    }

    if(backup){
        dstFile.setFileName(fileName + QString(".bak"));
        if(!dstFile.open(QFile::WriteOnly | QFile::Truncate)){
            showMessage(getCurrentTime() + ">" + "打开备份文件错误：" + fileName);
            showMessage(getCurrentTime() + ">" + "备份文件失败，这将跳过当前文件的备份操作...");
            return;
        }
        outTxtStream.setCodec(srcCodec);
        outTxtStream << fileContent;
        dstFile.close();
        m_convertCounter ++;
        qDebug() << "Backup File Ok!";
        showMessage(getCurrentTime() + ">" + "成功备份文件，文件已另存为：" + fileName + QString(".bak"));
    }
    dstFile.setFileName(fileName);
    if(!dstFile.open(QFile::WriteOnly | QFile::Truncate)){
        showMessage(getCurrentTime() + ">" + "新建目标文件失败：" + fileName);
        return;
    }
    outTxtStream.setCodec(dstCodec);
    outTxtStream << fileContent;
    outTxtStream.flush();

    qDebug() << "File Code Convert Ok!";
    dstFile.close();
    showMessage(getCurrentTime() + ">" + "文件：{" + fileName + "}转换完成...");
}

void Dialog::on_pushButton_files_clicked()
{
//    QFileDialog::Options options;
//    options |= QFileDialog::DontUseNativeDialog;
//    QString *filesfilter = new QString("C/C++( ");

//    m_suffixlist->clear();
//    *m_suffixlist +=getFileTypesList();
//    if(NULL != m_suffixlist){
//        delete m_suffixlist;
//        m_suffixlist = NULL;
//    }
//    m_suffixlist = ui->listWidget_tl->getTypesList();

//    if(m_suffixlist->isEmpty()){
//        QMessageBox::information(this,tr("提示"),tr("请至少选择一种文件类型"));
//        return;
//    }
    if(false == this->getFileTypesList()){
        return;
    }

    QString *filesfilter = new QString("");
    foreach (QString ifilter, *m_suffixlist) {
        *filesfilter += ifilter + ";";
    }

    *filesfilter = filesfilter->left(filesfilter->length() - 1);

    QStringList fileslist = QFileDialog::getOpenFileNames(this,
                                         tr("Select Files"),
                                         *m_HistoryDir,
                                         *filesfilter);
    delete m_suffixlist;
    ui->listWidget_files->clear();
    if(fileslist.isEmpty()){
        return;
    }

    addFilesToListwidget(fileslist);
}

void Dialog::on_pushButton_dir_clicked()
{
//    QFileDialog::Options options;
//    options |= QFileDialog::DontUseNativeDialog;

//    *m_suffixlist = QStringList();
//    *m_suffixlist +=getFileTypesList();

//    if(m_suffixlist->isEmpty()){
//        QMessageBox::information(this,tr("提示"),tr("请至少选择一种文件类型"));
//        return;
//    }

    if(false == this->getFileTypesList()){
        return;
    }

    QString directory = QFileDialog::getExistingDirectory(this,
                                    tr("Select Dir"),
                                    *m_HistoryDir/*,
                                    options*/);
    ui->listWidget_files->clear();
//    qDebug() << "directory=" << directory;
    if(directory.isEmpty()){
        return;
    }
    *m_HistoryDir = directory;
    QStringList fileslist = getFilesList(directory);
    delete m_suffixlist;
    if(fileslist.isEmpty())
        return;

    addFilesToListwidget(fileslist);
}

void Dialog::addFilesToListwidget(QStringList &fileslist)
{
    fileslist.sort();

    foreach (QString filefullname, fileslist) {
        QListWidgetItem *lwi = new QListWidgetItem();
        QCheckBox *cb = new QCheckBox();
        cb->setChecked(1);
        cb->setText(filefullname);
        lwi->setSizeHint(QSize(cb->size().width() + 100, 20));
        cb->setFixedHeight(20);

        ui->listWidget_files->addItem(lwi);
        ui->listWidget_files->setItemWidget(lwi, cb);
    }
}

void Dialog::showMessage(const QString &lmsg)
{
            ui->listWidget_message->addItem(lmsg);
}

QString &Dialog::identifyFileEncoding(const QString &fileName)const
{
    QString *encodingName = new QString;
    IdentifyEncoding *ie = new IdentifyEncoding;

    QByteArray fileContext;
    QFile lfile(fileName);
    if(lfile.open(QFile::ReadOnly)){
        return *encodingName;
    }
    fileContext = lfile.readAll();
    lfile.close();

    *encodingName = ie->maybeEncodeName(fileContext);


    return *encodingName;
}

void Dialog::on_checkBox_auto_clicked()
{
    if(ui->checkBox_auto->isChecked()){
        ui->comboBox_srccodec->setEnabled(0);
        ui->checkBox_bak->setChecked(1);
    }
    else{
        ui->comboBox_srccodec->setEnabled(1);
    }
}
