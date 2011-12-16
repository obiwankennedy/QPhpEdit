#include "linenumberarea.h"
#include "texteditor.h"
LineNumberArea::LineNumberArea(TextEditor* editor)
    : QWidget(editor)
{
    m_testEditor = editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(m_testEditor->lineNumberAreaWidth(), 0);
}


void LineNumberArea::paintEvent(QPaintEvent *event)
{
    m_testEditor->lineNumberAreaPaintEvent(event);
}

