#ifndef POPULATECHILDVISITOR_H
#define POPULATECHILDVISITOR_H

#include "ftpnode.h"
#include <QObject>
#include <QNetworkAccessManager>

class PopulateChildVisitor : public QObject
{
    Q_OBJECT
public:
    PopulateChildVisitor(QString url);

    void setNode(FtpNode* p);
    void populateNode();
private slots:
    void replyFinished(const QNetworkReply & i);
    void commandFinished();
private:
    FtpNode* m_internal;


    QNetworkAccessManager* m_ftpsite;

    QString m_host;
    QString m_login;
    QString m_passwd;
    QString m_path;
};

#endif // POPULATECHILDVISITOR_H
