#include "globaldata.h"

GlobalData::GlobalData()
{
    this->tagname.insert(data::ipAddress,"ipAddress");
    this->attribute.insert(data::ipAddress,"value");
}

QString GlobalData::getTagName(int tagname)
{
    return this->tagname[tagname];
}

QString GlobalData::getattribute(int tagname)
{
    return this->attribute[tagname];
}
