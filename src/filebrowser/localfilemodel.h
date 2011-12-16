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
#ifndef LOCALFILEMODEL_H
#define LOCALFILEMODEL_H

#include "filebrowsermodel.h"


class LocalFileModel : public FileBrowserModel
{
public:
    LocalFileModel(WebProject* p);



    void getFile();
    void saveFile();

    void createFile();

    virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() );
    virtual QModelIndex parent ( const QModelIndex & index );

   virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
   virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
   virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;


};

#endif // LOCALFILEMODEL_H
