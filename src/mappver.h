#ifndef MVERSION_H
#define MVERSION_H

#define VER_MAJOR   1
#define VER_MINOR   0
#define VER_STAGE   2
#define VER_APPEND  0

#define STR_X(x)    #x
#define _VERSION(a, b, c, d)  STR_X(a.b.c.d)

#define STR_Version  _VERSION(VER_MAJOR,VER_MINOR,VER_STAGE,VER_APPEND)


#define STR_AppName         "Encoding Convertor"
#define STR_Author          "lau"
#define STR_Corporation     "lau@163.com"
#define STR_Description     "Text Encoding Convertor"
#define STR_Copyright       "lau@163.com"

#endif // MVERSION_H
