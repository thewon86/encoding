#ifndef IDENTIFYENCODING_H
#define IDENTIFYENCODING_H

#include <QString>
//#include <QByteArray>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
class QByteArray;
QT_END_NAMESPACE

class EncodeParser;
class GB2312Parser;
class GBKParser;
class BIG5Parser;
class UTF8Parser;
class UnicodeParser;
class ASCIIParser;
class HZParser;
class EUC_TWParser;
class ISO2022CNParser;


class IdentifyEncoding
{
public:
    explicit IdentifyEncoding();
    ~IdentifyEncoding();

    int numbOfParser(void){return parserNumb;}
    QString &maybeEncodeName(const QByteArray &rawByte);

private:
    int Identify(EncodeParser *penpar);

private:
    const int parserNumb;
    EncodeParser *parserArray;
    QByteArray *sampelByte;
};

class EncodeParser
{
public:
    explicit EncodeParser();
    ~EncodeParser();

    virtual int Probability(const QByteArray &rawByte)const;
    virtual const QString &ParserName()const{ QString *t = new QString(""); return *t;}
    virtual void Initialize_Frequencies();

};

class GB2312Parser : public EncodeParser
{
    friend class ISO2022CNParser;
    friend class GBKParser;
    friend class HZParser;
public:
    explicit GB2312Parser();
    ~GB2312Parser();

    int Probability(const QByteArray &rawByte)const;
    const QString &ParserName()const{ return *m_Name; }

private:
    void Initialize_Frequencies();

private:
    const QString *m_Name;
public:
    int (**GB2312Freq);

};

class GBKParser : public EncodeParser
{
public:
    explicit GBKParser();
    ~GBKParser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

private:
    void Initialize_Frequencies();

private:
    QString *m_Name;
    int (**GBKFreq);
};

class BIG5Parser : public EncodeParser
{
public:
    explicit BIG5Parser();
    ~BIG5Parser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

private:
    void Initialize_Frequencies();

private:
    QString *m_Name;
    int (**Big5Freq);
};

class UTF8Parser : public EncodeParser
{
public:
    explicit UTF8Parser();
    ~UTF8Parser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

//private:
//    void Initialize_Frequencies();

private:
    QString *m_Name;
//    static int (**GB2312Freq);
};

class UnicodeParser : public EncodeParser
{
public:
    explicit UnicodeParser();
    ~UnicodeParser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

//private:
//    void Initialize_Frequencies();

private:
    QString *m_Name;
//    static int (**GB2312Freq);
};

class ASCIIParser : public EncodeParser
{
public:
    explicit ASCIIParser();
    ~ASCIIParser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

//private:
//    void Initialize_Frequencies();

private:
    QString *m_Name;
//    static int (**GB2312Freq);
};

class HZParser : public EncodeParser
{
public:
    explicit HZParser();
    ~HZParser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

//private:
//    void Initialize_Frequencies();

private:
    QString *m_Name;
//    static int (**HZFreq);
};

class EUC_TWParser : public EncodeParser
{
    friend class ISO2022CNParser;
public:
    explicit EUC_TWParser();
    ~EUC_TWParser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

private:
    void Initialize_Frequencies();

private:
    QString *m_Name;
    int (**EUC_TWFreq);

};

class ISO2022CNParser : public EncodeParser
{
public:
    explicit ISO2022CNParser();
    ~ISO2022CNParser();

    int Probability(const QByteArray &rawByte)const;
    QString &ParserName()const{ return *m_Name; }

//private:
//    void Initialize_Frequencies();

private:
    QString *m_Name;
//    static int (**EUC_TWFreq);
};




#endif // IDENTIFYENCODING_H
