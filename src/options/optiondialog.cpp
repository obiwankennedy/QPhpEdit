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
#include "optiondialog.h"
#include <QColorDialog>
#include <QDebug>
#include "phphighlighter.h"

OptionDialog::OptionDialog()
{
    m_from = new Ui::optionsForm;
    m_from->setupUi(this);

    m_options = OptionStore::getInstance();


    foreach(WordType str, m_options->colorMap()->keys())
    {
        m_from->m_colorScheme->addItem(m_options->colorMap()->value(str).name);
    }


    m_from->m_fontComboBox->setFont(m_options->font());

    connect(m_from->m_fontComboBox,SIGNAL(currentFontChanged(QFont)),this,SLOT(fontChanged(QFont)));

    m_from->m_fontSizeSelector->setValue(m_options->font().pointSize());

    m_phphighligter = new PhpHighLighter(m_from->m_exempleedit->document());
    //m_from->m_exempleedit->setAutoFormatting(QTextEdit::AutoNone);

    m_from->m_fontSizeSelector->setValue(m_options->font().pointSize());
    connect(m_from->m_colorScheme,SIGNAL(currentRowChanged(int)),this,SLOT(colorChanged(int)));

    connect(m_from->m_fontSizeSelector,SIGNAL(valueChanged(int)),this,SLOT(fontSizeChanged(int)));

    connect(m_from->m_lineNumber,SIGNAL(toggled(bool)),m_options,SLOT(setNumberLine(bool)));

    connect(m_from->m_fgColorButton,SIGNAL(pressed()),this,SLOT(onChooseColor()));
    connect(m_from->m_bgColorButton,SIGNAL(pressed()),this,SLOT(onChooseColor()));

    connect(m_from->m_boldBox,SIGNAL(clicked(bool)),this,SLOT(onClickBold(bool)));
    connect(m_from->m_italicBox,SIGNAL(clicked(bool)),this,SLOT(onClickItalic(bool)));


}
void OptionDialog::fontSizeChanged(int p)
{
    QFont ft = m_options->font();
    ft.setPointSize(p);
    m_options->setFont(ft);
    m_from->m_exempleedit->setFont(ft);
}
void OptionDialog::colorChanged(int a)
{

    WordType b = m_options->colorMap()->keys().at(a);
    SyntaxLight sl = m_options->colorMap()->value(b);
    QString pa("background-color: rgb(%1,%2,%3);");

    m_from->m_fgColorButton->setStyleSheet(pa.arg(m_options->fgColor(b).red()).arg(m_options->fgColor(b).green()).arg(m_options->fgColor(b).blue()));
    m_from->m_bgColorButton->setStyleSheet(pa.arg(m_options->bgColor(b).red()).arg(m_options->bgColor(b).green()).arg(m_options->bgColor(b).blue()));
    m_from->m_boldBox->setChecked(sl.isBold);
    m_from->m_italicBox->setChecked(sl.isItalic);

    m_currentColor = b;
}
void OptionDialog::fontChanged(QFont p)
{
    m_options->setFont(p);
    m_from->m_exempleedit->setFont(p);

}

void OptionDialog::onChooseColor()
{
    QObject* mysender = sender();
    QColorDialog cd;
    cd.setOption(QColorDialog::ShowAlphaChannel);
    if(m_from->m_colorScheme->selectedItems().size()<=0)
        return;
    if(mysender == m_from->m_fgColorButton)
        cd.setCurrentColor(m_options->fgColor(m_currentColor));
    else
        cd.setCurrentColor(m_options->bgColor(m_currentColor));

    if(cd.exec())
    {
        QColor tmp = cd.selectedColor();

        if(mysender == m_from->m_fgColorButton)
        {

            m_options->setFgColor(tmp,m_currentColor);


        }
        else
        {

            m_options->setBgColor(tmp,m_currentColor);

        }
        colorChanged(m_currentColor);
    }
    m_phphighligter->rehighlight();
}
void OptionDialog::onClickItalic(bool p)
{

    SyntaxLight sl = m_options->colorMap()->value(m_currentColor);
    sl.isItalic = p;
    m_options->colorMap()->insert(m_currentColor,sl);
}
void OptionDialog::onClickBold(bool p)
{

    SyntaxLight sl = m_options->colorMap()->value(m_currentColor);
    sl.isBold = p;
    m_options->colorMap()->insert(m_currentColor,sl);
}
