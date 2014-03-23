#include "populatechildvisitor.h"
#include <QRegExp>
#include <QDebug>

PopulateChildVisitor::PopulateChildVisitor(QString url)
{
    QRegExp tmp("ftp://(.*):(.*)@(.*)/(.*)");
   int pos =0;

    if(tmp.indexIn(url+"/", pos) != -1)
    {

       m_login= tmp.cap(1);
       m_passwd= tmp.cap(2);
       m_host=tmp.cap(3);
       m_path =tmp.cap(4);
    }
    m_ftpsite = new QNetworkAccessManager();
    connect(m_ftpsite, SIGNAL(finished(const finished & )),
             this, SLOT(replyFinished(const QNetworkReply & )));
    connect(m_ftpsite,SIGNAL(commandFinished(int,bool)),this,SLOT(commandFinished()));

}
void PopulateChildVisitor::setNode(FtpNode* p)
{
    m_internal = p;
}

void PopulateChildVisitor::populateNode()
{
    /*m_ftpsite->connectToHost(m_host);

    m_ftpsite->login(m_login,m_passwd);


    if(m_path!=NULL)
    {
       m_ftpsite->cd(m_path);
    }

    m_ftpsite->cd(m_internal->path()+"/"+m_internal->name());
    qDebug()<< m_path << m_internal->path() << m_internal->name() << m_internal->path()+"/"+m_internal->name();

    m_ftpsite->list();
    m_ftpsite->close();*/
}

void PopulateChildVisitor::replyFinished(const QNetworkReply & i)
{
    //m_internal->addChild(i.name(),i.isDir());
}
void PopulateChildVisitor::commandFinished()
{
    m_internal->setFullFilled();

}
