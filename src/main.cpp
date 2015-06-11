#include "dialog.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *gcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(gcodec);
#if(QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForCStrings(gcodec);
    QTextCodec::setCodecForTr(gcodec);
#endif

    Dialog w;
    w.show();

    return a.exec();
}
