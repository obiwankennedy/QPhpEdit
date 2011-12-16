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
#ifndef CENTRALTAB_H
#define CENTRALTAB_H

#include <QWidget>
#include <QToolBar>
#include <QVBoxLayout>
class FancyWidget : public QObject
{
    Q_OBJECT
public:
    FancyWidget(QWidget* widget,bool toolbar = true);
    void setWidget(QWidget* widget);




    QWidget* widget();/// \brief return the widget with the fancy toolBar on the top.
    QWidget* mainWidget();/// \brief return the same widget which has been given as parameter in the constructor.

    QToolBar* toolbar();

    QAction* addToolBarWidget(QWidget* p);
    QAction* addToolBarAction(const QIcon & icon,const QString & text);

private:
    QWidget* m_widget;
    QWidget* m_returned;
    QToolBar* m_toolbar;
    QVBoxLayout* m_layout;
};

#endif // CENTRALTAB_H
