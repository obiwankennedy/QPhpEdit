#ifndef CENTRALTAB_H
#define CENTRALTAB_H

#include <QWidget>
#include <QToolBar>
#include <QVBoxLayout>
class CentralTab : public QObject
{
    Q_OBJECT
public:
    CentralTab(QWidget* widget,bool toolbar = true);
    void setWidget(QWidget* widget);

    QWidget* widget();
private:
    QWidget* m_widget;
    QWidget* m_returned;
    QToolBar* m_toolbar;
    QVBoxLayout* m_layout;
};

#endif // CENTRALTAB_H
