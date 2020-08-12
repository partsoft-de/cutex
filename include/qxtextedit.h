/***********************************************************************************************************************
**
** Copyright (C) 2016-2020 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXTEXTEDIT_H
#define QXTEXTEDIT_H

#include "cutex.h"
#include "qxhtmlcursor.h"
#include "qxhyperlink.h"
#include "qxfindoptions.h"

namespace cutex {

/*!
  \brief Die Klasse %QxTextEdit erweitert die Qt-Klasse QTextEdit.

  %QxTextEdit erleichtert die Implementierung von Texteditoren. Dazu stellt die Klasse Methoden bereit, die in
  QTextEdit nicht direkt zur Verfügung stehen, sondern auf andere Qt-Klassen verteilt sind.
*/
class QxTextEdit : public QTextEdit
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(bool showTabsAndSpaces READ showTabsAndSpaces WRITE setShowTabsAndSpaces)
    Q_PROPERTY(bool showLineAndParagraphSeparators READ showLineAndParagraphSeparators WRITE
        setShowLineAndParagraphSeparators)
    Q_PROPERTY(int tabSpaces READ tabSpaces WRITE setTabSpaces)
    //! @endcond

public:
    enum ListFormat {
        ListNone = 0, ListDisc, ListCircle, ListSquare, ListDecimal, ListLowerAlpha, ListUpperAlpha, ListLowerRoman,
        ListUpperRoman
    };

public:
    QxTextEdit(QWidget *parent = 0);
    void setCurrentLine(int lineNumber, bool select = false);
    bool fontBold() const;
    void setFontBold(bool bold);
    QxTextEdit::ListFormat listFormat();
    void setListFormat(QxTextEdit::ListFormat format);
    double leftMargin() const;
    void setLeftMargin(double margin);
    QxHtmlCursor htmlCursor() const;
    QxHtmlCursor htmlCursor(const QTextCursor &cursor) const;
    QxHyperlink hyperlink() const;
    QxHyperlink hyperlink(const QTextCursor &cursor) const;
    void setHyperlink(const QxHyperlink &link);
    QString anchor() const;
    QStringList anchors() const;
    void insertAnchor(const QString &name, const QString &text);
    void removeAnchor(const QString &name);
    void insertLine();
    void insertImage(const QString &fileName);
    QTextTable* currentTable() const;
    QTextTable* insertTable(int rows, int columns, const QTextTableFormat &format = QTextTableFormat());
    void insertTableRow();
    void removeTableRow();
    void insertTableColumn();
    void removeTableColumn();
    bool canUndo() const;
    bool canRedo() const;
    bool canCopy() const;
    bool showTabsAndSpaces() const;
    void setShowTabsAndSpaces(bool show);
    bool showLineAndParagraphSeparators() const;
    void setShowLineAndParagraphSeparators(bool show);
    int tabSpaces() const;
    void setTabSpaces(int spaces);

public slots:
    virtual bool findOrReplace(const QxFindOptions &options);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    bool m_canUndo;
    bool m_canRedo;
    int m_tabSpaces;

private slots:
    void setUndoEnabled(bool enabled);
    void setRedoEnabled(bool enabled);

signals:
    void linkActivated(const QString &url);
};

} // namespace

#endif // QXTEXTEDIT_H
