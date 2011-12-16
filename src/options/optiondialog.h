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
#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H


#include "ui_optiongui.h"
#include "optionstore.h"
#include "Highlighter.h"
//#include "misc.h"
class OptionDialog : public QWidget
{
    Q_OBJECT
public:
    OptionDialog();


protected slots:
    void colorChanged(int a);
    void onChooseColor();
    void fontChanged(QFont p);
    void onClickItalic(bool);
    void onClickBold(bool);
    void fontSizeChanged(int);

protected:
     Ui::optionsForm* m_from;

     OptionStore* m_options;
     WordType m_currentColor;
     HighLighter* m_phphighligter;
};

#endif // OPTIONDIALOG_H
