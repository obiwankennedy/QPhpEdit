#ifndef PROJECTPROPERTY_H
#define PROJECTPROPERTY_H

#include <QWidget>

namespace Ui {
    class projectProperty;
}

class projectProperty : public QWidget {
    Q_OBJECT
public:
    projectProperty(QWidget *parent = 0);
    ~projectProperty();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::projectProperty *ui;
};

#endif // PROJECTPROPERTY_H
