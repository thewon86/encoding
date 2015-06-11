#ifndef MYTYPEDEF_H
#define MYTYPEDEF_H

#include <QDebug>

#ifdef _MAPPDEBUG
#define STR_X(x)    #x
#define MDEBUG(x)   qDebug() << "LINE:" << __LINE__ <<STR_X(x) << "=" << x << "}" << __FILE__
#define MMASSGE(x)    qDebug() << "LINE:" << __LINE__ << "{" << STR_X(x) << "}" << __FILE__
#endif

typedef unsigned char BYTE;
typedef unsigned char *PBYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef  int LONG;

//#pragma pack(1)

#endif // MYTYPEDEF_H
