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
#include "ftpfilemodel.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QRegExp>


FTPFileModel::FTPFileModel(WebProject* p)
  : m_project(p)
{
    m_rootItem = new FtpNode("","",true);
    m_visitor = new PopulateChildVisitor(p->path());
    m_visitor->setNode(m_rootItem);
    m_visitor->populateNode();
}
FTPFileModel::~FTPFileModel()
{
    delete m_rootItem;
    delete m_visitor;
}

void FTPFileModel::getFile()
{

}
void FTPFileModel::saveFile()
{



}
void FTPFileModel::createFile()
{



}
QModelIndex FTPFileModel::index ( int row, int column, const QModelIndex & parent) const
{
    FtpNode* parentItem;

    if(!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<FtpNode*>(parent.internalPointer());



    FtpNode* childItem = parentItem->at(row);
    if(childItem)
        return createIndex(row,column,childItem);
    else
        return QModelIndex();
}
bool FTPFileModel::canFetchMore ( const QModelIndex & parent ) const
{

    FtpNode* item = static_cast<FtpNode*>(parent.internalPointer());

    if(item ==NULL)
        item=  m_rootItem ;

    return item->canFetchMore();
}
void FTPFileModel::fetchMore ( const QModelIndex & parent )
{
    if(!parent.isValid())
        return;

    FtpNode * item = static_cast<FtpNode*>(parent.internalPointer());

    if(item ==NULL)
        return;

    m_visitor->setNode(item);
    m_visitor->populateNode();

}
bool FTPFileModel::hasChildren ( const QModelIndex & parent  ) const
{
    FtpNode* item = static_cast<FtpNode*>(parent.internalPointer());

    if(item ==NULL)
        item=  m_rootItem ;

    return item->hasChildren();
}


int FTPFileModel::rowCount ( const QModelIndex & parent ) const
{

    FtpNode* parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<FtpNode*>(parent.internalPointer());

    return parentItem->childrenCount();

}
int FTPFileModel::columnCount ( const QModelIndex & parent  ) const
{
    return 1;
}
QVariant FTPFileModel::data ( const QModelIndex & index, int role  ) const
{
    if (!index.isValid())
            return QVariant();


    if(role == Qt::DisplayRole)
    {
        //if(!index.isValid())

        FtpNode* item = static_cast<FtpNode*>(index.internalPointer());

        return item->name();
    }
    else
        return QVariant();
}
QModelIndex FTPFileModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    FtpNode *childItem = static_cast<FtpNode*>(index.internalPointer());
    FtpNode *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}



