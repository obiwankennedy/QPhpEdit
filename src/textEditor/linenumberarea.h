#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
class TextEditor;
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEditor* editor);
    QSize sizeHint() const ;

protected:
    void paintEvent(QPaintEvent *event);
private:
    TextEditor* m_testEditor;
};

#endif // LINENUMBERAREA_H
