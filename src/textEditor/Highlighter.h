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
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

class HighLighter : public QSyntaxHighlighter
{
public:
    HighLighter(QTextDocument *document)
            : QSyntaxHighlighter(document)
    {}

protected:
    virtual void readFile()=0;
    virtual void highlightBlock(const QString &text)=0;

    QMap<QString,QString>* m_map;
    QString m_filename;

};
#endif // HIGHLIGHTER_H
