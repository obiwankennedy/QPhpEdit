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
#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QtGui/QDialog>
#include "webproject.h"
namespace Ui {
    class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT
public:
    NewDialog(QWidget *parent = 0);
    ~NewDialog();

    bool isProject(){return m_projectType;}
    WebProject* getProject();
protected slots:
    void onOk();
    void onFinish();
    void onSelect();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewDialog *m_ui;
    WebProject* m_project;
    bool m_projectType;
};

#endif // NEWDIALOG_H
