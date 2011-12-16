#include "editwidget.h"
#include "phphighlighter.h"
#include "fancywidget.h"
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>
#include "ftpfilemodel.h"
#include <QFileSystemModel>


#include "webfile.h"
EditorTab::EditorTab(WebFile* file, QWidget* parent)
        : QSplitter(parent)
{
    m_options = OptionStore::getInstance();

    m_listmodel =new QStringListModel;
    m_documentList = new QList<QTextDocument*>;
    TextEditor* textedit = new TextEditor(this);//qobject_cast<TextEditor*>(m_editor->widget());

    if(file)
        connect(textedit,SIGNAL(textChanged()),file,SLOT(hasBeenModified()));

    p = new PhpHighLighter(textedit->document());
    connect(m_options,SIGNAL(fontChanged(QFont)),textedit,SLOT(setCurrentFont(QFont)));
    textedit->setCurrentFont(m_options->font());
    m_leftcolumn = new QSplitter(Qt::Vertical,this);
    ProjectFilesBrowser* tmpBrowser=new ProjectFilesBrowser();
    m_view = new  FancyWidget(tmpBrowser);
    m_leftcolumn->addWidget(m_view->widget());

    addWidget(m_leftcolumn);
    setStretchFactor(0,1);
    addEditor(textedit);
    setStretchFactor(1,3);




}
void EditorTab::editFile()
{

}
bool EditorTab::writeEditedFile(const QString& path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream out(&file);


    foreach(TextEditor* tmp,m_editorList)
    {
        out << tmp->document();
        //m_editorList.at(0)->setPlainText(in.readAll());
        //m_documentList->append(m_editorList.at(0)->document());
    }



    return false;
}

void EditorTab::addEditor(TextEditor* editor,Qt::Orientation )
{
    FancyWidget* tmp = new FancyWidget(editor);
    m_editorList.append(editor);
    QComboBox* tmpCombox = new QComboBox();
    tmpCombox->setModel(m_listmodel);

    tmp->addToolBarWidget(tmpCombox);
    this->addWidget(tmp->widget());

}
void EditorTab::addAndEditFile(QFile& p)
{
    QFileInfo info(p);
    m_fileList << info.absoluteFilePath();
    m_filenameList << info.fileName();
    m_listmodel->setStringList(m_filenameList);

    QTextStream in(&p);
    if(!m_editorList.empty())
    {
        m_editorList.at(0)->setPlainText(in.readAll());
        m_documentList->append(m_editorList.at(0)->document());
    }
    emit askForeGround();
}

void  EditorTab::currentProjectChanged(WebProject* p)
{
    /*must be remove*/
    m_model = new FileBrowserModel(p);
    if(p->locationType()==0)
    {
        QFileSystemModel* model = new QFileSystemModel();
        model->setRootPath(p->path());       
        m_model->setFileModel(model);
    }
    else
    {
        FTPFileModel* model = new FTPFileModel(p);

        m_model->setFileModel(model);
    }

    static_cast<ProjectFilesBrowser*>(m_view->mainWidget())->setModel(m_model->fileModel());
}
