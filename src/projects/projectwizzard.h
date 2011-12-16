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
#ifndef PROJECTWIZZARD_H
#define PROJECTWIZZARD_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QTimeLine>
class RedTabBar : public QTabBar
{
    Q_OBJECT

public:
    RedTabBar(QWidget *parent = 0);
    ~RedTabBar();

    QSize tabSizeHint(int index) const;

    void paintTab(QPainter *painter, int tabIndex) const;
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void tabInserted(int index);
    void tabRemoved(int index);



public slots:
    void updateHover();

protected:
    virtual void paintEvent(QPaintEvent *event);


private:
    static const int m_rounding;
    static const int m_textPadding;
    QTimeLine m_hoverControl;
    QRect m_hoverRect;
    int m_parenwidth;
};

class ProjectWizzard : public QTabWidget
{
public:
    ProjectWizzard(QWidget* p =NULL);
    void paintEvent(QPaintEvent *event);

    private:
    QStringList* m_recentProject;
    //QTabWidget* m_tabs;
};

#endif // PROJECTWIZZARD_H
