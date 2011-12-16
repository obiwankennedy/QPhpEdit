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
#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include <QPalette>
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>
#include <QTableView>
#include "mainwindow.h"
#include "manhattanstyle.h"
#include "editwidget.h"
#include "projectwidget.h"
#include "optiondialog.h"
#include "newdialog.h"
#include "webfile.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    m_options = OptionStore::getInstance();
    readSettings();

    m_tabWidget = new FancyTabWidget(this);
    setWindowTitle(tr("%1[*] - %2").arg(tr("untitled.qweb")).arg(tr("QPhpEdit - V0.1")));
    m_currentProject = NULL;
    m_currentEditedFile = new WebFile();


    m_recentProjectActions = new QActionGroup(this);
    connect(m_recentProjectActions, SIGNAL(triggered(QAction*)),
            this, SLOT(openRecentProject(QAction*)));

    QIcon icon(":/QPhpedit/resources/icon/logo.svg");

    setWindowIcon(icon);
    createActions();
    createMenus();


        /** @todo make the centralWidget as the real central widget */
    m_editorTab = new EditorTab(m_currentEditedFile);
    m_projectWidget = new  projectWidget();
    m_optionPanel = new OptionDialog();
    connect(this,SIGNAL(currentProjectChanged(WebProject*)),m_editorTab,SLOT(currentProjectChanged(WebProject*)));
    connect(m_editorTab,SIGNAL(askForeGround()),this,SLOT(putInForGround()));
    /*m_editor = new FancyWidget(m_editorWidget,false);
    m_projectsWizzard = new FancyWidget(new projectWidget(),false);
    m_optionPanel = new FancyWidget(new OptionDialog());*/



    this->setCentralWidget(m_tabWidget);

    m_tabWidget->insertTab(0,m_projectWidget,QIcon(),tr("Projects"));
    m_tabWidget->insertTab(1,m_editorTab,QIcon(),tr("Edit"));
    m_tabWidget->insertTab(2,m_optionPanel,QIcon(),tr("Options"));
  //m_fancyWidget->insertTab(3,m_editor->widget(),QIcon(),tr("Help"));



    QString baseName = qApp->style()->objectName();
#ifdef Q_WS_X11
    if (baseName == QLatin1String("windows"))
    {
        QByteArray desktopEnvironment = qgetenv("DESKTOP_SESSION");
        if (desktopEnvironment == "kde")
            baseName = QLatin1String("plastique");
        else
            baseName = QLatin1String("cleanlooks");
    }
#endif
    qApp->setStyle(new ManhattanStyle(baseName));
}

MainWindow::~MainWindow()
{

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isWindowModified())
    {
        int ret = maybeSave();
      if (ret==1)
      {
            writeSettings();
            event->accept();
        }
      else if(ret == -1)
          event->ignore();
      else if(ret== 0)
            event->accept();

    } else {
           event->accept();
    }
}
void MainWindow::createActions()
{
    m_new=new QAction(tr("&New..."),this);
    m_new->setShortcut(tr("Ctrl+N"));
    m_new->setStatusTip(tr("Create New file"));
    connect(m_new,SIGNAL(triggered()),this,SLOT(newFile()));

    m_open =new QAction(tr("&Open..."),this);
    m_open->setShortcut(tr("Ctrl+O"));
    m_open->setStatusTip(tr("Open file"));
    connect(m_open,SIGNAL(triggered()),this,SLOT(open()));

    m_save=new QAction(tr("&Save"),this);
    m_save->setShortcut(tr("Ctrl+S"));
    connect(m_save,SIGNAL(triggered()),this,SLOT(save()));

    m_saveAs=new QAction(tr("&Save As"),this);
    connect(m_saveAs,SIGNAL(triggered()),this,SLOT(saveAs()));

    m_saveAll=new QAction(tr("&Save As project"),this);
    m_saveAll->setShortcut(tr("Ctrl+Shift+S"));

    m_quit=new QAction(tr("&Quit"),this);
    m_quit->setShortcut(tr("Ctrl+Q"));

    m_cutAct=new QAction(tr("&Cut"),this);
    m_cutAct->setShortcut(tr("Ctrl+X"));
    m_copyAct=new QAction(tr("&Copy"),this);
    m_copyAct->setShortcut(tr("Ctrl+C"));
    m_pasteAct=new QAction(tr("&Paste"),this);
    m_pasteAct->setShortcut(tr("Ctrl+V"));
    m_preferences=new QAction(tr("Option..."),this);
    m_preferences->setShortcut(tr("Ctrl+,"));

    m_projectProperties=new QAction(tr("Project Properties..."),this);
    connect(m_projectProperties,SIGNAL(triggered()),this,SLOT(editProject()));

    m_about=new QAction(tr("&About"),this);

    connect(m_about,SIGNAL(triggered()),this,SLOT(about()));

    m_aboutQt=new QAction(tr("&About Qt"),this);
    connect(m_aboutQt,SIGNAL(triggered()), qApp,SLOT(aboutQt()));

}


void MainWindow::createMenus()
{
    QMenuBar* menubar = this->menuBar();

    m_fileMenu = new QMenu(tr("&File"),this);
    QPalette pal = m_fileMenu->palette();
    pal.setColor(QPalette::Highlight,QColor(180,40,40));
    m_fileMenu->setPalette(pal);
    m_fileMenu->addAction(m_new);
    m_fileMenu->addAction(m_open);
    m_fileMenu->addSeparator();


    for(int i = m_recentprojects.size()-1 ;i>=0 ;i--)
    {
        QAction* tmp = new QAction(m_recentprojects.at(i),this);
        m_recentProjectActions->addAction(tmp);
        m_fileMenu->addAction(tmp);
    }

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_save);
    m_fileMenu->addAction(m_saveAs);
    m_fileMenu->addAction(m_saveAll);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_quit);
    connect(m_quit, SIGNAL(triggered()), this, SLOT(close()));
    menubar->addMenu(m_fileMenu);

    m_editMenu = new QMenu(tr("&Edit"),this);
    m_editMenu->setPalette(pal);
    m_editMenu->addAction(m_cutAct);
    m_editMenu->addAction(m_copyAct);
    m_editMenu->addAction(m_pasteAct);
    m_editMenu->addSeparator();
    m_editMenu->addAction(m_projectProperties);
    m_editMenu->addSeparator();
    m_editMenu->addAction(m_preferences);
    menubar->addMenu(m_editMenu);

    m_helpMenu = new QMenu(tr("&Help"),this);
    m_helpMenu->setPalette(pal);
    m_helpMenu->addAction(m_about);
    m_helpMenu->addAction(m_aboutQt);
    menubar->addMenu(m_helpMenu);


}
void MainWindow::putInForGround()
{
 m_tabWidget->setCurrentIndex(1);
}
void MainWindow::newFile()
{
    NewDialog p;

    if(p.exec())
    {

        if(p.isProject())
        {

//            m_currentProject = p.getProject();
                setCurrentProject( p.getProject());
            //m_recentprojects.prepend(m_currentProject->path()+"/"+m_currentProject->name()+".qweb");


        }



    }


}

void MainWindow::open()
{
        QString fileName = QFileDialog::getOpenFileName(this,tr("QPhpEdit"),".",tr(
            "Project file (*.qweb)\nPhp files (*.php *.php3 *.php4 *.php5)\nHtml files (*.html *.htm)\nOther web files (*.css *.js)\nAnyfile"));
        if (!fileName.isEmpty())
        {
            //loadFile(fileName);
            if(fileName.endsWith(".qweb"))
                loadProject(fileName);
            else
                loadFile(fileName);
        }

}
void MainWindow::loadProject(const QString& filename)
{
    QFile project(filename);


    if (!project.open(QFile::ReadOnly)) {
          QMessageBox::warning(this, tr("QPhpEdit"),
                               tr("Cannot read file %1:\n%2.")
                                   .arg(filename)
                                   .arg(project.errorString()));
          return;
        }


        WebProject* projectfile = new WebProject;
        QDataStream in(&project);
        in.setVersion(QDataStream::Qt_4_5);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        in >> (*projectfile);
        QApplication::restoreOverrideCursor();
        m_recentprojects.removeAll(filename);
        m_recentprojects.prepend(filename);

        setCurrentProject(projectfile);
        //statusBar()->showMessage(tr("Project loaded"), 2000);

}

void MainWindow::loadFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
          QMessageBox::warning(this, tr("QPhpEdit"),
                               tr("Cannot read file %1:\n%2.")
                                   .arg(filename)
                                   .arg(file.errorString()));
          return;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        m_editorTab->addAndEditFile(file);
        QApplication::restoreOverrideCursor();
        //statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::save()
{
    if(m_currentProject)
    {
        if(m_currentProject->isModified())
        {
            //m_currentProject->currentFile->uri()
             if((m_currentProject->uri().isEmpty())||(!QFile::exists(m_currentProject->uri())))
              {
                        saveProjectAs();
              }
             else
             {
                        saveProject(m_currentProject->uri());
              }
        }
    }
    if(m_currentEditedFile)
    {
        if(m_currentEditedFile->isModified())
        {
            if((m_currentEditedFile->uri().isEmpty())||(!QFile::exists(m_currentEditedFile->uri())))
             {
                       saveFileAs();
             }
            else
            {
                       saveFile(m_currentProject->uri());
             }
        }
    }

}
void MainWindow::saveFileAs()
{
    qDebug() << "save as fonction ";
}

void MainWindow::savefile(const QString& file)
{
    m_editorTab->writeEditedFile(file);
}

void MainWindow::saveProjectAs()
{
      QString fileName = QFileDialog::getSaveFileName(this,tr("QPhpEdit"),".",tr("Project file (*.qweb )"));
      m_currentProject->setUri(fileName);
      if (fileName.isEmpty())
            return;

      saveProject(m_currentProject->uri());
}
bool MainWindow::saveProject(const QString &fileName)
{
    m_recentprojects.append(fileName);
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
    {
          QMessageBox::warning(this, tr("QPhpedit"),
                               tr("Cannot write file %1:\n%2.")
                                   .arg(fileName)
                                   .arg(file.errorString()));
          return false;
    }
    QDataStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << (*m_currentProject);
    QApplication::restoreOverrideCursor();
    m_currentProject->setModified(false);
    setWindowModified(false);

    return true;
}
void MainWindow::saveAs()
{
if(m_currentEditedFile==NULL)
    return;

       QString extension = m_currentEditedFile->getExtension();
    QString fileName = QFileDialog::getSaveFileName(this,tr("QPhpEdit"),".",tr("Supported file (*.%1 )").arg(extension));
    m_currentProject->setUri(fileName);
    if (fileName.isEmpty())
          return;

    saveFile(m_currentProject->uri());
}
void MainWindow::saveAll()
{
    return ;
}
void MainWindow::createToolBars()
{

}
void MainWindow::createStatusBar()
{

}
void MainWindow::about()
{
    QMessageBox::about(this,tr("About QPhpEdit"),tr("<h1>QPhpEdit</h1> QPhpEdit is a free software. It has been developed for help you to manage all steps of web sites creation. It provides many features, such as: <ul><li>Text Editing</li><li>Syntax Highlight</li><li>Project management</li><li>What you see is what you get mechanism</li><li>FTP synchronisation</li></ul> <h2>Author</h2>Renaud Guezennec"));

}
void MainWindow::readSettings()
{
        QSettings settings("Renaud Guezennec", "QPhpEdit");
        QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
        QSize size = settings.value("size", QSize(600, 400)).toSize();
        resize(size);
        move(pos);
        m_recentfiles = settings.value("recentFiles").toStringList();
        m_recentprojects = settings.value("recentProjects").toStringList();
        m_options->readSettings();
}
void MainWindow::writeSettings()
{
      QSettings settings("Renaud Guezennec", "QPhpEdit");
      settings.setValue("pos", pos());
      settings.setValue("size", size());
      settings.setValue("recentFiles", m_recentfiles);
      settings.setValue("recentProjects", m_recentprojects);
      m_options->writeSettings();
}
int MainWindow::maybeSave()
{
    if (isWindowModified())
    {
            int ret = QMessageBox::warning(this, tr("QPhpEdit"),
                        tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
            if (ret == QMessageBox::Yes)
            {
                return 1;
            }
            else if (ret == QMessageBox::Cancel)
                return -1;
      }

        return 0;
}
void MainWindow::openRecentProject(QAction* tmp)
{
    loadProject(tmp->text());
}
bool MainWindow::saveFile( const QString &fileName)
{

    if(m_currentEditedFile==NULL)
        return false;

    return m_editorTab->writeEditedFile(fileName);
}
void MainWindow::documentWasModified()
{
      setWindowModified(true);
}
void MainWindow::setCurrentProject(WebProject* project)
{
    setWindowModified(true);
    m_currentProject = project;
    //m_currentProject->setModified(true);
    if(m_currentProject == NULL)
        setWindowTitle(tr("%1[*] - %2").arg(tr("Untitle.qweb")).arg(tr("QPhpEdit - V0.1")));
    else
        setWindowTitle(tr("%1[*] - %2").arg(m_currentProject->name()).arg(tr("QPhpEdit - V0.1")));
    emit currentProjectChanged(m_currentProject);
}
void MainWindow::editProject()
{

}
