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
#include "projectwidget.h"
#include <QPaintEvent>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
projectWidget::projectWidget(QWidget* p)
        : QWidget(p)
{
     m_wizzard = new ProjectWizzard();
    m_wizzard->setMinimumSize(400,400);
    m_wizzard->setMaximumSize(400,400);

    m_toolbar = new QToolBar;

    m_toolbar->addAction("here");

    QHBoxLayout* icons= new QHBoxLayout;

    QLabel* logo = new QLabel;
    QLabel* application = new QLabel;

    logo->setPixmap(QPixmap(":/QPhpedit/resources/icon/logo.svg").scaled(75,75));
    application->setPixmap(QPixmap(":/QPhpedit/resources/icon/qphpedit.png").scaled(200,75));
    icons->addSpacerItem(new QSpacerItem(20,62));
     icons->addWidget(logo);
    icons->addSpacerItem(new QSpacerItem(20,62));

    icons->addWidget(application);

    m_verti =new QVBoxLayout;
    m_verti->setMargin(0);

    m_verti->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Expanding));
    m_verti->addLayout(icons);
    m_verti->addWidget(m_wizzard);
    m_verti->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Expanding));



    m_hori =new QHBoxLayout;
    m_hori->addSpacerItem(new QSpacerItem(20,20));
    m_hori->addLayout(m_verti);
    m_hori->addSpacerItem(new QSpacerItem(20,20));


    m_bigverti =new QVBoxLayout;
    m_bigverti->setMargin(0);
    m_bigverti->addWidget(m_toolbar);
    m_bigverti->addLayout(m_hori);

   // p.setBrush();

    /*QPalette a = this->palette();
    a.setBrush(this->palette().currentColorGroup(),QPalette::Window,QBrush(selectedGradient));
    this->setPalette(a);*/
    this->setLayout(m_bigverti);
}
void projectWidget::paintEvent(QPaintEvent *event)
{

    QPainter p(this);

QLinearGradient selectedGradient(QPoint(this->rect().center().x(),this->rect().top()), QPoint(this->rect().center().x(),this->rect().bottom()));
        selectedGradient.setColorAt(0,QColor(240, 240, 240) );
        selectedGradient.setColorAt(0.8, QColor(140, 120, 120));
        selectedGradient.setColorAt(0.9, QColor(100, 80, 80));
        p.setBrush(QBrush(selectedGradient));

    p.drawRoundedRect(this->rect().width()/2-201,this->rect().height()/2-250,401,500,15.0,15.0);

   // QWidget::paintEvent(event);
}
