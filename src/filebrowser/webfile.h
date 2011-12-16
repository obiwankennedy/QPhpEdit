#ifndef WEBFILE_H
#define WEBFILE_H

#include <QString>
#include <QObject>
class WebFile : public QObject
{
    Q_OBJECT
public:
    WebFile();

    bool isModified();
    QString uri();

    void setUri(QString);

    QString getExtension();
public slots:
    void hasBeenModified();

private:
    QString m_uri;
    bool m_modified;
};

#endif // WEBFILE_H
