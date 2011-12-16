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
#ifndef FTPFILEMODEL_H
#define FTPFILEMODEL_H

#include <QAbstractItemModel>
#include "webproject.h"
#include <QNetworkAccessManager>

#include <QStringList>

#include "populatechildvisitor.h"

class FTPFileModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    FTPFileModel(WebProject* p);
    ~FTPFileModel();

    void getFile();
    void saveFile();

    void createFile();

    virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    virtual QModelIndex parent ( const QModelIndex & index ) const;

   virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
   virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
   virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;

   virtual bool hasChildren ( const QModelIndex & parent  ) const;

   bool canFetchMore ( const QModelIndex & parent ) const ;
   virtual void fetchMore ( const QModelIndex & parent ) ;

private:
   void listDirectory(QString url);



   WebProject* m_project;
   //QNetworkAccessManager* m_ftpManager;
    FtpNode* m_rootItem;


   PopulateChildVisitor* m_visitor;
  //QStringList m_list;

};

#endif // FTPFILEMODEL_H
