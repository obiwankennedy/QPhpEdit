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
#include "optionstore.h"
#include <QSettings>
#include <QColor>
#include <QDebug>
OptionStore::OptionStore()
    : m_colors(NULL)
{
   /*m_bgColorMap = new QMap<int,QColor>;
    m_fgColorMap = new QMap<int,QColor>;*/
    m_colors = new QMap<WordType,SyntaxLight>;


    m_numberStoredProjects = 5;
    m_numberStoredFiles=5;

    SyntaxLight * tmp = new SyntaxLight;
    tmp->type = MCOMMENT;
    tmp->name = tr("Multi-line Comment");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::darkGreen;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(MCOMMENT,*tmp);



    tmp = new SyntaxLight;
    tmp->type = COMMENT;
    tmp->name = tr("Comment");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::darkGreen;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(COMMENT,*tmp);



    tmp = new SyntaxLight;
    tmp->type = STRING;
    tmp->name = tr("String");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::black;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(STRING,*tmp);

    tmp = new SyntaxLight;
    tmp->type = VARIABLE;
    tmp->name = tr("Variable");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = QColor(20,240,240);
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(VARIABLE,*tmp);

    tmp = new SyntaxLight;
    tmp->type = FUNCTION;
    tmp->name = tr("Function");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::darkBlue;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(FUNCTION,*tmp);

    tmp = new SyntaxLight;
    tmp->type = KEYWORDS;
    tmp->name = tr("Keywords");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::darkBlue;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(KEYWORDS,*tmp);

    tmp = new SyntaxLight;
    tmp->type = MARKUP;
    tmp->name = tr("MarkUp");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = QColor(140,180,10);
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(MARKUP,*tmp);

    tmp = new SyntaxLight;
    tmp->type = LINENUMBER;
    tmp->name = tr("Line Number");
    tmp->bgColor = Qt::gray;
    tmp->fgColor = Qt::darkGray;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(LINENUMBER,*tmp);

    tmp = new SyntaxLight;
    tmp->type = LINK;
    tmp->name = tr("Link");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = QColor(240,220,10);
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(LINK,*tmp);

    tmp = new SyntaxLight;
    tmp->type = NUMBER;
    tmp->name = tr("Number");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::darkCyan;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(NUMBER,*tmp);

    tmp = new SyntaxLight;
    tmp->type = SELECTION;
    tmp->name = tr("Selection");
    tmp->bgColor = QColor(240,200,200);
    tmp->fgColor = Qt::black;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(SELECTION,*tmp);

    tmp = new SyntaxLight;
    tmp->type = DOXYGENTAG;
    tmp->name = tr("Doxygen Tag");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::green;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(DOXYGENTAG,*tmp);

    tmp = new SyntaxLight;
    tmp->type = DOXYGENCOMMENT;
    tmp->name = tr("Doxygen Comment");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::cyan;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(DOXYGENCOMMENT,*tmp);

    tmp = new SyntaxLight;
    tmp->type = OPERATOR;
    tmp->name = tr("Operator");
    tmp->bgColor = Qt::transparent;
    tmp->fgColor = Qt::black;
    tmp->isBold = false;
    tmp->isItalic = false;
    m_colors->insert(OPERATOR,*tmp);


qRegisterMetaTypeStreamOperators<SyntaxLight>("SyntaxLight");
}

OptionStore* OptionStore::m_singleton = NULL;
OptionStore* OptionStore::getInstance()
{

    if(m_singleton==NULL)
        m_singleton = new OptionStore();

    return m_singleton;


}
void OptionStore::readSettings()
{

        QSettings settings("Renaud Guezennec", "QPhpEdit.options");

        m_numberLine = settings.value("option/numberline", true).toBool();
         m_font = settings.value("option/font", QFont()).value<QFont>();
        m_spaceInstead = settings.value("option/spaceInstead", true).toBool();
        m_indentSize = settings.value("option/indentSize", true).toInt();
      QString tmpID("option/color%1");

      foreach(QString str, settings.allKeys())//(SyntaxLight tmp , *m_colors)//int i = 0 ; i<= OPERATOR ; i++)
      {

          if(settings.value(str).canConvert<SyntaxLight>())
          {
                   SyntaxLight tmp = settings.value(str).value<SyntaxLight>();
                 /*  if(tmp.type == NUMBER)
                    qDebug() << "read "<<tmp.fgColor;*/

                   m_colors->insert(tmp.type,tmp);
          }

      }

}
int OptionStore::maxStoredProjects()
{
   return m_numberStoredProjects;

}
int OptionStore::maxStoredFiles()
{
    return m_numberStoredFiles;
}
void OptionStore::writeSettings()
{
      QSettings settings("Renaud Guezennec", "QPhpEdit.options");
      settings.setValue("option/numberline",m_numberLine);
      settings.setValue("option/font", m_font);
      settings.setValue("option/spaceInstead", m_spaceInstead);
      settings.setValue("option/indentSize", m_indentSize);
      //settings.setValue("option/textcodex", m_codec);


      /*settings.setValue("option/shortcutMap", *m_shortcutMap);
      settings.setValue("option/headerMap", *m_headerMap);
      settings.setValue("option/macroMap", *m_macroMap);*/


        QString tmpID("option/color%1");

       foreach(SyntaxLight tmp , *m_colors)//int i = 0 ; i<= OPERATOR ; i++)
      {
            QVariant variant = QVariant::fromValue(tmp);
           /*  if(tmp.type == NUMBER)
                    qDebug() << " write "<<tmp.fgColor;*/
            settings.setValue(tmpID.arg(tmp.name), variant);


      }
}
QColor& OptionStore::bgColor(WordType p)
{
    return (*m_colors)[p].bgColor;
}
QColor& OptionStore::fgColor(WordType p)
{
    return (*m_colors)[p].fgColor;
}
QFont OptionStore::font()
{
    return m_font;
}
void OptionStore::setNumberLine(bool nl)
{
    m_numberLine = nl;
}
void OptionStore::setFont(QFont font)
{
    m_font=font;
    emit fontChanged(m_font);
}
void OptionStore::setSpaceInstead(bool si)
{
    m_spaceInstead = si;
}
void OptionStore::setIndentSize(int is)
{
    m_indentSize = is;
}
void OptionStore::setBgColor(QColor& bg, WordType p)
{
    (*m_colors)[p].bgColor = bg;
}
void OptionStore::setFgColor(QColor& fg, WordType p)
{
    (*m_colors)[p].fgColor = fg;
}
QMap<WordType,SyntaxLight>* OptionStore::colorMap()
{
    return m_colors;
}
