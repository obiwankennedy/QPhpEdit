#include "projectproperty.h"
#include "ui_projectproperty.h"

projectProperty::projectProperty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectProperty)
{
    ui->setupUi(this);
}

projectProperty::~projectProperty()
{
    delete ui;
}

void projectProperty::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
