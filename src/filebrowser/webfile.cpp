#include "webfile.h"

WebFile::WebFile()
{
}


bool WebFile::isModified()
{
    return m_modified;
}


QString WebFile::uri()
{
    return m_uri;
}

void WebFile::setUri(QString uri)
{
    m_uri = uri;
}
QString WebFile::getExtension()
{
    int pos = m_uri.lastIndexOf('.');

    return m_uri.remove(0,pos);
}
void WebFile::hasBeenModified()
{
    m_modified = true;
}
