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
#include "newdialog.h"
#include "ui_newdialog.h"

#include <QDebug>
#include <QFileDialog>
NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::NewDialog),
    m_project(NULL)
{
    m_ui->setupUi(this);
    m_projectType = false;
    m_ui->m_stackedWidget->setCurrentIndex(0);
    m_ui->m_image->setPixmap(QPixmap(":/QPhpedit/resources/icon/logo.svg").scaled(200,200));
    QTreeWidgetItem * item = m_ui->m_typeFile->invisibleRootItem();
    for(int  i = 0; i<item->childCount() ; i++)
    {
        m_ui->m_typeFile->expandItem(item->child(i));
    }

    connect(m_ui->m_ok,SIGNAL(clicked()),this,SLOT(onOk()));
    connect(m_ui->m_finish,SIGNAL(clicked()),this,SLOT(onFinish()));
    connect(m_ui->m_browser,SIGNAL(clicked()),this,SLOT(onSelect()));
}

NewDialog::~NewDialog()
{
    delete m_ui;
}

void NewDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            m_ui->retranslateUi(this);
            break;
        default:
            break;
    }
}
void NewDialog::onFinish()
{

    m_project->setName(m_ui->m_name->text());
    m_project->setVersion(m_ui->m_version->text());
    m_project->setAuthor(m_ui->m_author->text());
    m_project->setPath(m_ui->m_root->text());
    m_project->setReachingPath(m_ui->m_url->text());
    accept();

}
WebProject* NewDialog::getProject()
{

    return m_project;
}
void NewDialog::onOk()
{

    foreach(QTreeWidgetItem *index, m_ui->m_typeFile->selectedItems())
    {

        int pos = m_ui->m_typeFile->indexOfTopLevelItem(index->parent());
        int pos2 = index->parent()->indexOfChild(index);


        if(pos==0)//project
        {
            m_projectType = true;
            /*switch(pos2)
            {
                case 0://php

                    break;
                case 1://html

                    break;

            }*/
            m_project = new WebProject;
            m_project->setProjectType(pos2);
            m_ui->m_stackedWidget->setCurrentIndex(1);
        }
        else if(pos==1)
        {
            switch(pos2)
            {
                case 0://php

                    break;
                case 1://html

                    break;
                case 2://html

                    break;
               case 3://html

                    break;
               case 4://html

                    break;


            }


        }

    }


}
void NewDialog::onSelect()
{

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOptions ( QFileDialog::ShowDirsOnly);

   if(dialog.exec())
   {
          m_project->setPath(dialog.selectedFiles().first());
          m_ui->m_root->setText(m_project->path());

   }



}
