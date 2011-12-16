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
#ifndef WEBPROJECT_H
#define WEBPROJECT_H
#include <QString>
#include <QSettings>
#include <QDateTime>
enum ProjectType {HTML,PHP};
enum LocationType {LOCAL,FTP};

class WebProject
{
public:
    WebProject();
    void setProjectType(int type);
    void setLocationType(int type);
    void setName(QString name);
    void setVersion(QString version);
    void setAuthor(QString author);
    void setPath(QString path);
    void setReachingPath(QString ReachingPath);
    void setUri(QString uri);

    int projectType();
    int locationType();
    QString& name();
    QString& author();
    QString& version();
    QString& path();
    QString& reachingPath();
    QString& uri();

    void readSettings(QSettings& read);
    void writeSettings(QSettings& write);
    bool isModified();

    void setModified(bool m);

    friend QDataStream& operator<<(QDataStream& os,const WebProject&);
    friend QDataStream& operator>>(QDataStream& is,WebProject&);

protected:
    void updateModifiedTime();




private:
    ProjectType m_type;
    LocationType m_location;
    QString m_name;
    QString m_version;
    QString m_author;
    /// @brief Should be local path or ftp path.
    QString m_path;
    /// should be the URL to see the project online (http)
    QString m_reachingPath;
    QDateTime m_createdDateTime;
    QDateTime m_LastModificationDateTime;
    QString m_uri;
    bool m_modified;


};

#endif // WEBPROJECT_H
