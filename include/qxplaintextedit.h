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

#ifndef QXPLAINTEXTEDIT_H
#define QXPLAINTEXTEDIT_H

#include "cutex.h"
#include "qxfindoptions.h"

namespace cutex {

/*!
  \brief Die Klasse %QxPlainTextEdit erweitert die Qt-Klasse QPlainTextEdit.

  %QxPlainTextEdit erleichtert die Implementierung von Texteditoren. Dazu stellt die Klasse Methoden bereit, die in
  QPlainTextEdit nicht direkt zur Verfügung stehen, sondern auf andere Qt-Klassen verteilt sind.
*/
class QxPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(bool showLineNumbers READ showLineNumbers WRITE setShowLineNumbers)
    Q_PROPERTY(bool showTabsAndSpaces READ showTabsAndSpaces WRITE setShowTabsAndSpaces)
    Q_PROPERTY(bool showLineAndParagraphSeparators READ showLineAndParagraphSeparators WRITE
        setShowLineAndParagraphSeparators)
    Q_PROPERTY(int tabSpaces READ tabSpaces WRITE setTabSpaces)
    //! @endcond

    friend class QxLineNumberArea;

public:
    QxPlainTextEdit(QWidget *parent = nullptr);
    void setCurrentLine(int lineNumber, bool select = false);
    bool canUndo() const;
    bool canRedo() const;
    bool canCopy() const;
    bool showLineNumbers() const;
    void setShowLineNumbers(bool show);
    bool showTabsAndSpaces() const;
    bool showLineAndParagraphSeparators() const;
    int tabSpaces() const;
    void setTabSpaces(int spaces);

public slots:
    virtual bool findOrReplace(const QxFindOptions &options);
    void setShowTabsAndSpaces(bool show);
    void setShowLineAndParagraphSeparators(bool show);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    QWidget *m_lineNumberArea;
    bool m_canUndo;
    bool m_canRedo;
    bool m_showLineNumbers;
    int m_tabSpaces;

private:
    int lineNumberAreaWidth() const;
    void paintLineNumberArea(QPaintEvent *event);

private slots:
    void setUndoEnabled(bool enabled);
    void setRedoEnabled(bool enabled);
    void updateViewportMargins();
    void updateLineNumberArea(const QRect &rect, int);
};

} // namespace

#endif // QXPLAINTEXTEDIT_H
