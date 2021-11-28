/***********************************************************************************************************************
**
** Copyright (C) 2016-2021 Partsoft UG (haftungsbeschränkt)
** Contact: https://www.partsoft.de/index.php/kontakt
**
** This file is part of cutex
**
** cutex is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
** version.
**
** cutex is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License along with cutex. If not, see
** http://www.gnu.org/licenses.
**
***********************************************************************************************************************/

#include "qxplaintextedit.h"
#include "qxlinenumberarea.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Texteditor mit dem Elternobjekt <i>parent</i>.
*/
QxPlainTextEdit::QxPlainTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    m_lineNumberArea = new QxLineNumberArea(this);
    m_canUndo = false;
    m_canRedo = false;
    m_showLineNumbers = false;
    m_tabSpaces = 0;

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateViewportMargins()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoEnabled(bool)));
    connect(this, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoEnabled(bool)));

    updateViewportMargins();
}

/*!
  Setzt den Cursor in die Zeile <i>lineNumber</i>. Wenn das Flag <i>select</i> gesetzt ist, wird die Zeile markiert.
*/
void QxPlainTextEdit::setCurrentLine(int lineNumber, bool select)
{
    QTextBlock block = document()->findBlockByLineNumber(lineNumber);
    QTextCursor cursor(block);

    if (select)
        cursor.select(QTextCursor::LineUnderCursor);
    setTextCursor(cursor);
}

/*!
  Gibt true zurück, wenn die letzte Aktion rückgängig gemacht werden kann.

  \sa canRedo()
*/
bool QxPlainTextEdit::canUndo() const
{
    return m_canUndo;
}

/*!
  Gibt true zurück, wenn die letzte Aktion wiederhergestellt gemacht werden kann.

  \sa canUndo()
*/
bool QxPlainTextEdit::canRedo() const
{
    return m_canRedo;
}

/*!
  Gibt true zurück, wenn Text in die Zwischenablage kopiert werden kann.
*/
bool QxPlainTextEdit::canCopy() const
{
    QTextCursor cursor = textCursor();
    bool result = !cursor.selection().isEmpty();

    return result;
}

/*!
  Gibt true zurück, wenn der Editor Zeilennummern anzeigt.
*/
bool QxPlainTextEdit::showLineNumbers() const
{
    return m_showLineNumbers;
}

/*!
  Legt fest, ob der Editor Zeilennummern anzeigt.
*/
void QxPlainTextEdit::setShowLineNumbers(bool show)
{
    m_showLineNumbers = show;
    updateViewportMargins();
    update();
}

/*!
  Gibt true zurück, wenn der Editor Whitespaces anzeigt.
*/
bool QxPlainTextEdit::showTabsAndSpaces() const
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    return flags.testFlag(QTextOption::ShowTabsAndSpaces);
}

/*!
  Gibt true zurück, wenn der Editor Zeilenendezeichen anzeigt.
*/
bool QxPlainTextEdit::showLineAndParagraphSeparators() const
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    return flags.testFlag(QTextOption::ShowLineAndParagraphSeparators);
}

/*!
  Gibt die Anzahl an Leerzeichen zurück, die beim drücken der Tabulatortaste eingefügt werden.
*/
int QxPlainTextEdit::tabSpaces() const
{
    return m_tabSpaces;
}

/*!
  Fügt anstatt eines Tabulators <i>spaces</i> Leerzeichen ein wenn die Tabulatortaste gedrückt wurde.
*/
void QxPlainTextEdit::setTabSpaces(int spaces)
{
    m_tabSpaces = spaces;
}

/*!
  Führt eine Textsuche mit den Suchoptionen <i>options</i> an der aktuellen Cursorposition durch.
*/
bool QxPlainTextEdit::findOrReplace(const QxFindOptions &options)
{
    bool success = true;
    QTextDocument::FindFlags flags;
    Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;
    QTextCursor cursor;

    if (options.wholeWords())
        flags = flags | QTextDocument::FindWholeWords;
    if (options.caseSensitive()) {
        flags = flags | QTextDocument::FindCaseSensitively;
        caseSensitivity = Qt::CaseSensitive;
    }
    if (options.backward() && options.mode() != QxFindOptions::ReplaceAll)
        flags = flags | QTextDocument::FindBackward;

#if QT_VERSION >= QT_VERSION_CHECK(5,13,0)
    QRegularExpression::PatternOption patternOption = QRegularExpression::NoPatternOption;
    if (caseSensitivity == Qt::CaseInsensitive)
        patternOption = QRegularExpression::CaseInsensitiveOption;
#endif

    switch (options.mode()) {
    case QxFindOptions::Find:
        if (options.regularExpression()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,13,0)
            success = find(QRegularExpression(options.findText(), patternOption), flags);
#else
            success = find(QRegExp(options.findText(), caseSensitivity), flags);
#endif
        } else {
            success = find(options.findText(), flags);
        }
        break;
    case QxFindOptions::Replace:
        if (options.regularExpression()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,13,0)
            success = find(QRegularExpression(options.findText(), patternOption), flags);
#else
            success = find(QRegExp(options.findText(), caseSensitivity), flags);
#endif
        } else {
            success = find(options.findText(), flags);
        }
        if (success) {
            cursor = textCursor();
            cursor.setKeepPositionOnInsert(true);
            cursor.insertText(options.replaceText());
            cursor.setKeepPositionOnInsert(false);
            setTextCursor(cursor);
        }
        break;
    case QxFindOptions::ReplaceAll:
        if (options.regularExpression()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,13,0)
            success = find(QRegularExpression(options.findText(), patternOption), flags);
#else
            success = find(QRegExp(options.findText(), caseSensitivity), flags);
#endif
        } else {
            cursor = document()->find(options.findText());
        }
        if (!cursor.isNull()) {
            setTextCursor(QTextCursor(document()));
            while (find(options.findText(), flags))
                textCursor().insertText(options.replaceText());
        }
        break;
    }

    return success;
}

/*!
  Legt fest, ob der Editor Whitespaces anzeigt.
*/
void QxPlainTextEdit::setShowTabsAndSpaces(bool show)
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    flags.setFlag(QTextOption::ShowTabsAndSpaces, show);
    option.setFlags(flags);
    doc->setDefaultTextOption(option);
}

/*!
  Legt fest, ob der Editor Zeilenendezeichen anzeigt.
*/
void QxPlainTextEdit::setShowLineAndParagraphSeparators(bool show)
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    flags.setFlag(QTextOption::ShowLineAndParagraphSeparators, show);
    option.setFlags(flags);
    doc->setDefaultTextOption(option);
}

/*!
  Wird aufgerufen wenn die Größe des Editors verändert wird.
*/
void QxPlainTextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect rect = contentsRect();
    m_lineNumberArea->setGeometry(QRect(rect.left(), rect.top(), lineNumberAreaWidth(), rect.height()));
}

/*!
  Wird aufgerufen wenn die Position des Mausrades verändert wurde.
*/
void QxPlainTextEdit::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->angleDelta().y() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
        return;
    }

    QPlainTextEdit::wheelEvent(event);
}

/*!
  Wird aufgerufen wenn eine Taste gedrückt wurde.
*/
void QxPlainTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        if (m_tabSpaces > 0) {
            insertPlainText(QString().fill(' ', m_tabSpaces));
            return;
        }
    }

    QPlainTextEdit::keyPressEvent(event);
}

int QxPlainTextEdit::lineNumberAreaWidth() const
{
    int space = 0;

    if (m_showLineNumbers) {
        int digits = 2;
        int max = qMax(1, blockCount());
        while (max >= 10) {
            max /= 10;
            ++digits;
        }

#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
        space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
#else
        space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
#endif
    }

    return space;
}

void QxPlainTextEdit::paintLineNumberArea(QPaintEvent *event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1) + ' ';
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void QxPlainTextEdit::setUndoEnabled(bool enabled)
{
    m_canUndo = enabled;
}

void QxPlainTextEdit::setRedoEnabled(bool enabled)
{
    m_canRedo = enabled;
}

void QxPlainTextEdit::updateViewportMargins()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QxPlainTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        m_lineNumberArea->scroll(0, dy);
    else
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateViewportMargins();
}
