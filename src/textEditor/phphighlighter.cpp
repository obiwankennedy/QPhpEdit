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
#include "phphighlighter.h"
#include <QDebug>
#include <QFile>
PhpHighLighter::PhpHighLighter(QTextDocument *document)
         : HighLighter(document)
{
    m_filename = "php.txt";
    m_options = OptionStore::getInstance();
    m_map = new QMap<QString,QString>;
    readFile();
}
void PhpHighLighter::readFile()
{
    QFile file(":/QPhpedit/resources/keyword/"+m_filename);
    //resources/keyword/php.txt
    if(file.open(QIODevice::ReadOnly))
    {

        while (!file.atEnd())
        {
            QByteArray line = file.readLine();

            m_map->insert(QString(line).trimmed(),QString(""));
         }


    }




}
void PhpHighLighter::highlightBlock(const QString &text)
{

        enum { NormalState = -1, InsideCStyleComment = 2,InsideString = 8,InsideVariable=16,InsideStringSingle=32,InsideNumber=64,InsideWord =128,PhpState = 1024 ,OutState=2048 };

        QRegExp rx2("\\W");
        QStringList words = text.split(rx2,QString::SkipEmptyParts);
        foreach(QString mword, words)
        {
            QString a = m_map->value(mword);
            if(!a.isNull())
            {
                setFormat(text.indexOf(mword), mword.length(), m_options->fgColor(KEYWORDS));
            }
        }


        int state = previousBlockState();
        int start = 0;

        for(int i = 0; i < text.length(); ++i)
        {
            /*if((state & PhpState)&&(state!=-1))
            {*/
                if (state == InsideCStyleComment)
                {
                    if (text.mid(i, 2) == "*/")
                    {
                        state = NormalState;
                        setFormat(start, i - start + 2, m_options->fgColor(MCOMMENT));
                    }
                }
                else if(InsideVariable == state)
                {
                    QRegExp rx("\\W");
                    if(rx.indexIn(text.mid(i, 1))>-1)
                    {
                        state = NormalState;
                        setFormat(start, i - start, m_options->fgColor(VARIABLE));
                    }
                }
                else if(InsideString == state)
                {


                    if (text.mid(i, 1) == "\"")
                    {
                        state = NormalState;

                        setFormat(start, i - start+1, m_options->fgColor(STRING));
                    }
                }
                else if(InsideStringSingle == state)
                {
                    //QRegExp rx("[ \[-.)(]+-*%");

                    if (text.mid(i, 1) == "\'")
                    {
                        state = NormalState;

                        setFormat(start, i - start+1, m_options->fgColor(STRING));
                    }
               // }
                //state |= PhpState;
            }
            else
            {
                QRegExp rx("\\d");
                if(text.mid(i, 5) == "<?php")
                {
                    state = PhpState;
                    setFormat(i, 5, m_options->fgColor(NUMBER));

                }
                /*else if(state & PhpState)
                {*/
                    else if(text.mid(i, 2) == "//")
                    {
                        setFormat(i, text.length() - i, m_options->fgColor(COMMENT));
                        break;
                    }
                    else if(text.mid(i, 2) == "/*")
                    {
                        start = i;
                        state = InsideCStyleComment;
                    }
                    else if (text.mid(i, 1) == "$")
                    {
                        start = i;
                        state = InsideVariable ;
                    }
                    else if(text.mid(i, 1) == "\"")
                    {

                        start = i;
                        state = InsideString;
                    }
                    else if(text.mid(i, 1) == "\'")
                    {

                        start = i;
                        state = InsideStringSingle;
                    }
                    else if(rx.indexIn(text.mid(i, 1))>-1)
                    {
                        setFormat(i, 1, m_options->fgColor(NUMBER));
                    }
                    else if(text.mid(i, 2) == "?>")
                    {
                        setFormat(i, 2, m_options->fgColor(NUMBER));

                    }
                //}


           /*     if(state == NormalState)
                {
                    QRegExp rx("\\W");
                    if(rx.indexIn(text.mid(i, 1))>-1)
                    {



                    }
                    start = i;
                    state = InsideWord;
                }*/

            }
        }
        if (state == InsideCStyleComment)
            setFormat(start, text.length() - start, m_options->fgColor(MCOMMENT));

        setCurrentBlockState(state);


        //word












}
