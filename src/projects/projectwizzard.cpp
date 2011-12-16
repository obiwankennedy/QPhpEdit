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
#include "projectwizzard.h"
#include "stylehelper.h"
#include <QWindowsStyle>
#include <QStyleOptionTabV2>
#include <QMouseEvent>
#include <QDebug>
const int RedTabBar::m_rounding = 22;
const int RedTabBar::m_textPadding = 4;

RedTabBar::RedTabBar(QWidget *parent)
    : QTabBar(parent)
{
    setStyle(new QWindowsStyle);
    if(parent!=NULL)
        m_parenwidth = parent->geometry().width();
    setDrawBase(false);
    setElideMode(Qt::ElideNone);
    setMinimumWidth(qMax(2 * m_rounding, 40));
    setAttribute(Qt::WA_Hover, true);
    setFocusPolicy(Qt::NoFocus);
    m_hoverControl.setFrameRange(0, 20);
    m_hoverControl.setDuration(130);
    m_hoverControl.setCurveShape(QTimeLine::EaseInCurve);
    connect(&m_hoverControl, SIGNAL(frameChanged(int)), this, SLOT(updateHover()));
    setMouseTracking(true); // Needed for hover events
    setExpanding(false);
}

RedTabBar::~RedTabBar()
{
    delete style();
}

QSize RedTabBar::tabSizeHint(int index) const
{
    QFont boldFont(font());
    QStyleOptionTabV2 tab;
    initStyleOption(&tab, index);
    boldFont.setPointSizeF(StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    QFontMetrics fm(boldFont);
    int realwidth = fm.width(tab.text);
    //int realwidth = 80;
    int spacing = 6;
    //int width = realwidth + spacing + 2;
    //qDebug() << width;
    int width = this->count() > 0 ? m_parenwidth/this->count() : 200;
    return QSize(width,spacing + fm.height()*1.5);
}

void RedTabBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);

    for (int i = 0; i < count(); ++i)
        if (i != currentIndex())
            paintTab(&p, i);

    //p.drawRect(this->geometry());
   // qDebug() << this->geometry();
    paintTab(&p, currentIndex());
}

// Handle hover events for mouse fade ins
void RedTabBar::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_hoverRect.contains(e->pos())) {
        for (int i = 0; i < count(); ++i) {
            QRect area = tabRect(i);
            if (area.contains(e->pos())) {
                QRect oldHoverRect = m_hoverRect;
                m_hoverRect = area;
                update(oldHoverRect);
                m_hoverControl.stop();
                m_hoverControl.start();
                break;
            }
        }
    }
}

void RedTabBar::updateHover()
{
    update(m_hoverRect);
}

// Resets hover animation on mouse enter
void RedTabBar::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
    m_hoverRect = QRect();
}

// Resets hover animation on mouse enter
void RedTabBar::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);

    m_hoverControl.stop();
    m_hoverControl.start();
}

void RedTabBar::paintTab(QPainter *painter, int tabIndex) const
{
    QStyleOptionTabV2 tab;
    initStyleOption(&tab, tabIndex);
    QRect rect = tab.rect;
    painter->save();


    bool selected = tab.state & QStyle::State_Selected;
    bool hover = tab.state & QStyle::State_MouseOver;

#ifdef Q_WS_MAC
    hover = false; // Dont hover on Mac
#endif

    QColor background = QColor(180, 40, 40, 255);
    QColor hoverColor;

    if (hover) {
        hoverColor = QColor(255, 255, 255, m_hoverControl.currentFrame());
    }

    if(selected)
    {
        QLinearGradient selectedGradient(QPoint(rect.center().x(),rect.top()), QPoint(rect.center().x(),rect.bottom()));
        selectedGradient.setColorAt(0, Qt::white);
        selectedGradient.setColorAt(0.3, Qt::white);
        selectedGradient.setColorAt(0.7, QColor(230, 230, 230));

        painter->fillRect(rect, selectedGradient);
    }
    else
    {
        QLinearGradient selectedGradient(QPoint(rect.center().x(),rect.top()), QPoint(rect.center().x(),rect.bottom()));
        selectedGradient.setColorAt(0, background);
        selectedGradient.setColorAt(0.3, background);
        selectedGradient.setColorAt(0.7, QColor(88, 0, 0));

        painter->fillRect(rect, selectedGradient);


    }
    painter->drawRect(rect.adjusted(0,0,-1,-1));
    QString tabText(tab.text);
    QRect tabTextRect(tab.rect);
    QRect tabIconRect(tab.rect);
    QFont boldFont(painter->font());
    boldFont.setPointSizeF(StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    painter->setFont(boldFont);
    painter->setPen(selected ? StyleHelper::panelTextColor() : QColor(30, 30, 30, 80));
    int textFlags = Qt::AlignCenter | Qt::ElideRight | Qt::TextWordWrap;
    painter->drawText(tabTextRect, textFlags, tabText);
    painter->setPen(selected ? QColor(60, 60, 60) : StyleHelper::panelTextColor());
    int textHeight = painter->fontMetrics().boundingRect(QRect(0, 0, width(), height()), Qt::TextWordWrap, tabText).height();
    tabIconRect.adjust(0, 4, 0, -textHeight);
    style()->drawItemPixmap(painter, tabIconRect, Qt::AlignCenter | Qt::AlignVCenter,
                            tab.icon.pixmap(QSize(64, 64)));
    painter->translate(0, -1);
    painter->drawText(tabTextRect, textFlags, tabText);
    painter->restore();
}

void RedTabBar::tabInserted(int index)
{
    Q_UNUSED(index)
}

void RedTabBar::tabRemoved(int index)
{
    Q_UNUSED(index)
}

ProjectWizzard::ProjectWizzard(QWidget* p)
        : QTabWidget(p)
{
    resize(400,400);

    setTabBar(new RedTabBar(this));
    addTab(new QWidget(),tr("Getting Started"));
    addTab(new QWidget(),tr("Project History"));

    this->setStyleSheet("border-color:rgba(255, 255, 255, 0);background-color: rgba(255, 255, 255, 0);");

}
void ProjectWizzard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);

    //p.setBackgroundMode(Qt::TransparentMode);
//    p.setBackground(QBrush(QColor(255,255,255,0)));

  /*  QStyleOption styleOption;
    styleOption.init(this);

    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &p, this);*/
    /*p.drawLine(this->geometry().topLeft(),this->geometry().topRight());
    p.drawLine(this->geometry().topRight(),this->geometry().bottomRight());*/
   // QTabWidget::paintEvent(event);
}
