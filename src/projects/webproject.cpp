/***************************************************************************
 *   Copyright (C) 2009 by Renaud Guezennec                                *
 *   renaud.guezennec at gmail.com                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "webproject.h"
#include <QRegExp>
WebProject::WebProject()
{

    m_createdDateTime = m_createdDateTime.currentDateTime();
    m_modified = true;
    //m_location = LOCAL;
}


void WebProject::readSettings(QSettings& read)
{


}
void WebProject::writeSettings(QSettings& read)
{

}
bool WebProject::isModified()
{
    return m_modified;
}
void WebProject::setModified(bool m)
{
    m_modified = m;
}
void WebProject::setProjectType(int type)
{
    m_type = (ProjectType)type;
}
void WebProject::setName(QString name)
{
    m_name = name;
}
void WebProject::setUri(QString uri)
{
    if(!uri.endsWith(".qweb"))
    {
        uri.append(".qweb");
    }
    m_uri = uri;
}

void WebProject::setAuthor(QString author)
{
m_author = author;
}
void WebProject::setPath(QString path)
{
    m_path = path;
}
void WebProject::setReachingPath(QString uri)
{

    m_reachingPath = uri;
}
void WebProject::setVersion(QString version)
{
    m_version = version;

}
int WebProject::projectType()
{
    return m_type;
}

int WebProject::locationType()
{

    m_location= LOCAL;
    QRegExp exp("ftp://.*:.*@.*");

    if(exp.exactMatch(m_path))
    {
        m_location= FTP;
    }




    return m_location;


}
void WebProject::setLocationType(int type)
{
    m_location = (LocationType)type;
}

QString& WebProject::version()
{
    return m_version;
}
QString& WebProject::uri()
{
    return m_uri;
}
QString& WebProject::name()
{
    return m_name;
}
QString& WebProject::author()
{
return m_author;
}
QString& WebProject::path()
{
    return m_path;
}
QString& WebProject::reachingPath()
{
    return m_reachingPath;
}
void WebProject::updateModifiedTime()
{
    m_LastModificationDateTime = m_LastModificationDateTime.currentDateTime();
}
QDataStream& operator<<(QDataStream& Out, const WebProject& project)
{
 // Out << ((quint32)project.m_type);
  Out << project.m_name;
  Out << project.m_author;
  Out << project.m_path;
  Out << project.m_reachingPath;
  return Out;
}

QDataStream& operator>>(QDataStream& is,WebProject& project)
{
    /// @todo enable reading and writing project type.
    quint32 ab = 0;
 //   is >> ab;
    project.m_type = (ProjectType)ab;
  is >> project.m_name;
  is >> project.m_author;
  is >> project.m_path;
  is >> project.m_reachingPath;
  return is;


}
