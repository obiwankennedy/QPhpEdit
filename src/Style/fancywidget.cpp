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
#include "fancywidget.h"
#include "stylehelper.h"
#include <QDebug>

FancyWidget::FancyWidget(QWidget* widget ,bool toolbar)
        : m_widget(widget)
{

    if(toolbar)
    {
        m_toolbar = new QToolBar(m_widget->parentWidget());
     //   m_toolbar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        m_toolbar->setFixedHeight(StyleHelper::navigationWidgetHeight());

        m_layout = new QVBoxLayout();
        m_layout->addWidget(m_toolbar);

        if(m_widget)
        {
            m_layout->addWidget(m_widget);
        }
        m_returned = new QWidget;
        m_layout->setMargin(0);
        m_layout->setSpacing(0);
        m_returned->setLayout(m_layout);
    }
    else
    {
        m_returned = m_widget;
    }
}
void FancyWidget::setWidget(QWidget* widget)
{
    m_widget = widget;
    if(m_widget)
    {
        m_layout->addWidget(m_widget);
    }
}

QWidget* FancyWidget::widget()
{
        return m_returned;
}

QWidget* FancyWidget::mainWidget()
{

    return m_widget;

}

QToolBar* FancyWidget::toolbar()
{

    return m_toolbar;

}

QAction* FancyWidget::addToolBarWidget(QWidget* p)
{

    return m_toolbar->addWidget(p);

}
QAction* FancyWidget::addToolBarAction(const QIcon & icon,const QString & text)
{
    return m_toolbar->addAction(icon, text);
}
