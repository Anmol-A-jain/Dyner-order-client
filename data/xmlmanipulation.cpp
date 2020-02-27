#include "xmlmanipulation.h"

XmlManipulation::XmlManipulation()
{

}

QString XmlManipulation::getData(QString tagname, QString attribute)
{
    QString xmlFile = QDir::currentPath() + "/init.xml" ;
    QString value = "" ;
    QFile myfile(xmlFile);
    QDomDocument document;
    if(myfile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        if(document.setContent(&myfile))
        {
            QDomElement firstNode = document.firstChildElement() ;
            QDomNodeList itemlist = firstNode.elementsByTagName(tagname);

            for (int i = 0; i < itemlist.count() ; ++i)
            {
                QDomNode itemNode = itemlist.at(i);
                if(itemNode.isElement())
                {
                    qDebug() << "XmlManipulation.cpp (getData) : tagname =" + tagname + " attribute = " <<itemNode.toElement().attribute(attribute);
                    value = itemNode.toElement().attribute(attribute);
                }
            }
        }
    }
    return value;
}

void XmlManipulation::setData(QString tagname, QString attribute, QString value)
{
    QString xmlFile = QDir::currentPath() + "/init.xml" ;
    QFile myfileRead(xmlFile);

    if(QFile::exists(xmlFile))
    {
        QDomDocument document;
        if(myfileRead.open(QIODevice::ReadWrite | QIODevice::Text) )
        {
            if(document.setContent(&myfileRead))
            {
                //Write xml
                QDomElement root = document.firstChildElement() ;
                QDomNodeList itemlist = root.elementsByTagName(tagname);
                if(itemlist.count() == 0 )
                {
                    QDomElement db = document.createElement(tagname);
                    db.setAttribute(attribute,value);
                    root.appendChild(db);
                    document.appendChild(root);
                    myfileRead.close();

                    QFile myfileWrite(xmlFile);
                    if(myfileWrite.open(QIODevice::WriteOnly | QIODevice::Text) )
                    {
                        QTextStream stream(&myfileWrite);
                        stream << document.toString();
                        myfileWrite.close();
                    }
                }
                else
                {
                    XmlManipulation::updateData(tagname,attribute,value);
                }
            }
        }
    }
    else
    {
        //Write xml
        QDomDocument document;
        QDomElement root = document.createElement("Dyner");
        document.appendChild(root);
        QDomElement db = document.createElement(tagname);
        db.setAttribute(attribute,value);
        root.appendChild(db);

        QFile myfile(xmlFile);
        if(myfile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream stream(&myfile);
            stream << document.toString();
            myfile.close();
        }

    }
    qDebug() << "XmlManipulation.cpp (setData) : xml file location :" << xmlFile ;
}

void XmlManipulation::updateData(QString tagname, QString attribute, QString value)
{
    QString xmlFile = QDir::currentPath() + "/init.xml" ;
    QFile myfile(xmlFile);
    QDomDocument document;
    if(myfile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        if(document.setContent(&myfile))
        {
            QDomElement firstNode = document.firstChildElement() ;
            QDomNodeList itemlist = firstNode.elementsByTagName(tagname);

            if(itemlist.count() == 1)
            {
                QDomNode itemNode = itemlist.at(0);
                if(itemNode.isElement())
                {
                    qDebug() << "XmlManipulation.cpp (getData) : attribute data :" << itemNode.toElement().attribute(attribute);
                    if(itemNode.toElement().tagName() == tagname)
                    {
                        QDomElement element = itemNode.toElement();
                        element.setAttribute(attribute,value);
                        qDebug() << "XmlManipulation.cpp (getData) : new attribute data: " << element.attribute(attribute);

                        firstNode.appendChild(element);
                        document.appendChild(firstNode);
                        myfile.close();

                        QFile myfileWrite(xmlFile);
                        if(myfileWrite.open(QIODevice::WriteOnly | QIODevice::Text) )
                        {
                            QTextStream stream(&myfileWrite);
                            stream << document.toString();

                            qDebug() << "XmlManipulation.cpp (getData) : whole document : " << document.toString();
                            myfileWrite.close();
                        }
                    }
                }
            }
            else
            {
                XmlManipulation::setData(tagname,attribute,value);
            }
        }
    }
}
