#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextDocument>
#include "texteditor.h"
#include "Highlighter.h"
#include "optionstore.h"
#include "projectfilesbrowser.h"
#include "localfilemodel.h"
#include "webproject.h"



#define EditorList ;
class FancyWidget;
class QStringListModel;
class DocumentEditable
{


private:
    QTextDocument m_document;
    QString m_filename;
    QString m_path;
};
class WebFile;
class EditorTab : public QSplitter
{
    Q_OBJECT
public:
    EditorTab(WebFile* ,QWidget* parent = NULL);

    void editFile();
    void addEditor(TextEditor* editor,Qt::Orientation = Qt::Horizontal);
    void addAndEditFile(QFile& p);


    bool writeEditedFile(const QString& path);
public slots:
    void currentProjectChanged(WebProject* p);

signals:
    void askForeGround();
private:
    QVBoxLayout* m_verticalLayout;
    QHBoxLayout* m_horizontalLayout;

    HighLighter* p;

    OptionStore* m_options;

    QSplitter* m_leftcolumn;

    FancyWidget* m_view;

    FileBrowserModel* m_model;
    QList<TextEditor*> m_editorList;
    QList<QTextDocument*>* m_documentList;
    QStringList m_filenameList;
    QStringList m_fileList;

    QStringListModel* m_listmodel;

};

#endif // EDITWIDGET_H
