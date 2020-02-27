#ifndef XMLMANIPULATION_H
#define XMLMANIPULATION_H

#include <QtXml>
#include <QDir>
#include <QFile>

class XmlManipulation
{
public:
    XmlManipulation();
    static QString getData(QString tagname,QString attribute);
    static void setData(QString tagname,QString attribute, QString value);
    static void updateData(QString tagname,QString attribute, QString value);

};

#endif // XMLMANIPULATION_H
