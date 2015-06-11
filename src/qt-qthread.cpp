/*!  
* \file main.cpp  
*  
* Copyright (C) 2010, dbzhang800  
* All rights reserved.  
*  
*/  
#include <QtCore/QCoreApplication>   
#include <QtCore/QObject>   
#include <QtCore/QThread>   
#include <QtCore/QDebug>    
class Dummy:public QObject
{
	Q_OBJECT
public:
	Dummy(QObject* parent=0):QObject(parent){}
public slots:
	void emitsig()
	{
		emit sig();
	}
signals:
	void sig();
};

class Object:public QObject
{
	Q_OBJECT
public: Object(){}
public slots:
	void slot()
	{
		qDebug()<<"from thread slot:" <<QThread::currentThreadId();
	}
};
#include "main.moc"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug()<<"main thread:"<<QThread::currentThreadId();
	QThread thread;
	Object obj;
	Dummy dummy;
	obj.moveToThread(&thread);
	QObject::connect(&dummy, SIGNAL(sig()), &obj, SLOT(slot()));
	thread.start();
	dummy.emitsig();
	return a.exec();
} 