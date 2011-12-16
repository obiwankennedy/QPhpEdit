#ifndef FTPNODE_H
#define FTPNODE_H

#include <QString>
#include <QList>
class FtpNode
{


public:

    FtpNode(QString name,QString path,bool directory);

    bool canFetchMore() const;
    bool hasChildren() const;
    int childrenCount() const;
    FtpNode* at(int i) const;


    void addChild(QString nameChild,bool dir);
    const QString& name() const;
    const QString& path() const;

    void setFullFilled();
    FtpNode* parent() const;
    void setParent(FtpNode*);

    int row();

private:

    QList<FtpNode*> m_childrenItems;


    QString m_name;
    QString m_path;
    bool m_dir;
    FtpNode* m_parent;
    bool m_canfetchmore;

};

#endif // FTPNODE_H
