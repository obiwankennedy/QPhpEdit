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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>

#include "fancywidget.h"
#include "webproject.h"
#include "fancytabwidget.h"
#include "optionstore.h"


class EditorTab;
class OptionDialog;
class projectWidget;
class WebFile;
class QActionGroup;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();



protected:
      void closeEvent(QCloseEvent *event);
      void loadProject(const QString& filename);
      void loadFile(const QString& filename);
protected slots:
      void putInForGround();


private:
      void createActions();
      void createMenus();
      void createToolBars();
      void createStatusBar();
      void readSettings();
      void writeSettings();
      int maybeSave();

      bool saveFile( const QString &fileName);
      bool saveProject(const QString &fileName);

      void setCurrentFile(const QString &fileName);
      void setCurrentProject(WebProject *fileName);
      void updateRecentFilesActions();
      void updateRecentProjectsActions();



signals:
      void currentProjectChanged(WebProject* p);
private slots:
      void newFile();

      void open();
      void save();
      void saveAll();
      void saveAs();
      void saveProjectAs();

      void saveFileAs();
      void savefile(const QString& file);

      void about();
      void documentWasModified();
      void openRecentProject(QAction*);
      void editProject();

private:
    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_helpMenu;

    QAction* m_new;
    QAction* m_open;
    QAction* m_save;
    QAction* m_saveAs;
    QAction* m_saveAll;
    QAction* m_quit;

    QActionGroup* m_recentProjectActions;

    QAction *m_cutAct;
    QAction *m_copyAct;
    QAction *m_pasteAct;
    QAction *m_projectProperties;
    QAction *m_preferences;

    QAction *m_about;
    QAction *m_aboutQt;

    QToolBar* m_toolbar;

    EditorTab* m_editorTab;
    projectWidget* m_projectWidget;
    OptionDialog* m_optionPanel;

    QStringList m_recentfiles;
    QStringList m_recentprojects;

    FancyTabWidget* m_tabWidget;

    WebProject* m_currentProject;
    WebFile* m_currentEditedFile;


    OptionStore* m_options;
};

#endif // MAINWINDOW_H
