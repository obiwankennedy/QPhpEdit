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
#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include "projectwizzard.h"
class projectWidget : public QWidget
{
public:
    projectWidget(QWidget * p =NULL);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    ProjectWizzard* m_wizzard;
    QHBoxLayout* m_hori;
    QVBoxLayout* m_verti;
    QVBoxLayout* m_bigverti;
    QToolBar* m_toolbar;
};

#endif // PROJECTWIDGET_H
