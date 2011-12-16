#include "ftpnode.h"
#include <QDebug>
FtpNode::FtpNode(QString name,QString path,bool directory)
    : m_name(name),m_path(path),m_dir(directory),m_parent(NULL)
{
    //qDebug() << "is directory" << m_dir <<name;
    m_canfetchmore = m_dir;
}
bool FtpNode::canFetchMore() const
{
    return m_canfetchmore;
}

bool FtpNode::hasChildren() const
{
    if(m_canfetchmore)
        return true;
    if(!m_dir)
        return false;

    return m_childrenItems.size()>0 ? true : false;
}

int FtpNode::childrenCount() const
{
    return m_childrenItems.size();
}
const QString& FtpNode::path() const
{
    return m_path;
}
void FtpNode::addChild(QString nameChild,bool dir)
{
    FtpNode* tmp= new FtpNode(nameChild,m_path+"/"+m_name,dir);
    tmp->setParent(this);
    m_childrenItems.append(tmp);
}
FtpNode* FtpNode::parent() const
{
    return m_parent;
}
void FtpNode::setParent(FtpNode* p)
{
    m_parent = p;
}

int FtpNode::row()
{
    if (m_parent)
       return m_parent->m_childrenItems.indexOf(this);

     return 0;

}

const QString& FtpNode::name() const
{
    return m_name;
}
FtpNode* FtpNode::at(int i) const
{
    if((i>=m_childrenItems.size())||(i<0))
        return NULL;



    return m_childrenItems.at(i);
}
void FtpNode::setFullFilled()
{
    m_canfetchmore=false;
}
