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
#ifndef OPTIONSTORE_H
#define OPTIONSTORE_H

#include <QString>
#include <QMap>
#include <QFont>
#include <QObject>
#include "misc.h"
class OptionStore : public QObject
{
    Q_OBJECT
public:
    static OptionStore* getInstance();
    void readSettings();
    void writeSettings();

    void setColorMap(QMap<WordType,SyntaxLight>* colorMap);

    void setShortCutMap(QMap<QString,QString>* shortcutMap);
    void setHeaderMap(QMap<QString,QString>* headerMap);
    void setMacroMap(QMap<QString,QString>* macroMap);

    QColor& bgColor(WordType p);
    QColor& fgColor(WordType p);
    QMap<WordType,SyntaxLight>* colorMap();

    void setBgColor(QColor& bg, WordType p);
    void setFgColor(QColor& fg, WordType p);
    QFont font();

    int maxStoredProjects();
    int maxStoredFiles();
public slots:
    void setNumberLine(bool nl);
    void setFont(QFont font);
    void setSpaceInstead(bool si);
    void setIndentSize(int is);

signals:
    void fontChanged(QFont);


private:
    OptionStore();


private:
    static OptionStore* m_singleton;
/*    QMap<int,QColor>* m_bgColorMap;
    QMap<int,QColor>* m_fgColorMap;*/
    QMap<WordType,SyntaxLight>* m_colors;
    QMap<QString,QString>* m_shortcutMap;
    QMap<QString,QString>* m_headerMap;
    QMap<QString,QString>* m_macroMap;

    bool m_numberLine;
    QFont m_font;
    bool m_spaceInstead;
    int m_indentSize;
    QTextCodec* m_codec;
    int m_numberStoredProjects;
    int m_numberStoredFiles;

};

#endif // OPTIONSTORE_H
