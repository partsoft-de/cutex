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

#include "qxtextedit.h"
#include "qxtextdocument.h"
#include "qxrandom.h"

using namespace cutex;

const QString QxTextEdit::MIMETYPE = "application/cutex/qxtextedit";

/*!
  Erzeugt einen neuen Texteditor mit dem Elternobjekt <i>parent</i>.
*/
QxTextEdit::QxTextEdit(QWidget *parent) : QTextEdit(parent)
{
    m_canUndo = false;
    m_canRedo = false;
    m_tabSpaces = 0;

    connect(this, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoEnabled(bool)));
    connect(this, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoEnabled(bool)));
}

/*!
  Setzt den Cursor in die Zeile <i>lineNumber</i>. Wenn das Flag <i>select</i> gesetzt ist, wird die Zeile markiert.
*/
void QxTextEdit::setCurrentLine(int lineNumber, bool select)
{
    QTextBlock block = document()->findBlockByLineNumber(lineNumber);
    QTextCursor cursor(block);

    if (select)
        cursor.select(QTextCursor::LineUnderCursor);
    setTextCursor(cursor);
}

/*!
  Gibt true zurück, wenn an der aktuellen Cursorposition Fettschrift aktiviert ist.

  \sa setFontBold(bool bold)
*/
bool QxTextEdit::fontBold() const
{
    return (fontWeight() == QFont::Bold);
}

/*!
  Aktiviert, bzw. deaktiviert Fettschrift an der aktuellen Cursorposition.

  \sa fontBold()
*/
void QxTextEdit::setFontBold(bool bold)
{
    if (bold) {
        setFontWeight(QFont::Bold);
    } else {
        setFontWeight(QFont::Normal);
    }
}

/*!
  Gibt das Listenformat an der aktuellen Cursorposition zurück.

  \sa setListFormat(QxTextEdit::ListFormat format)
*/
QxTextEdit::ListFormat QxTextEdit::listFormat()
{
    ListFormat format = QxTextEdit::ListNone;
    QTextList *list = textCursor().currentList();

    if (list) {
        switch (list->format().style()) {
        case QTextListFormat::ListDisc:
            format = QxTextEdit::ListDisc;
            break;
        case QTextListFormat::ListCircle:
            format = QxTextEdit::ListCircle;
            break;
        case QTextListFormat::ListSquare:
            format = QxTextEdit::ListSquare;
            break;
        case QTextListFormat::ListDecimal:
            format = QxTextEdit::ListDecimal;
            break;
        case QTextListFormat::ListLowerAlpha:
            format = QxTextEdit::ListLowerAlpha;
            break;
        case QTextListFormat::ListUpperAlpha:
            format = QxTextEdit::ListUpperAlpha;
            break;
        case QTextListFormat::ListLowerRoman:
            format = QxTextEdit::ListLowerRoman;
            break;
        case QTextListFormat::ListUpperRoman:
            format = QxTextEdit::ListUpperRoman;
            break;
        default:
            format = QxTextEdit::ListNone;
        }
    }

    return format;
}

/*!
  Setzt das Listenformat an der aktuellen Cursorposition auf den Wert <i>format</i>.

  \sa listFormat()
*/
void QxTextEdit::setListFormat(QxTextEdit::ListFormat format)
{
    QTextCursor cursor = textCursor();
    QTextList *list = cursor.currentList();

    if (format != QxTextEdit::ListNone) {
        QTextListFormat::Style listStyle = QTextListFormat::ListDisc;

        switch (format) {
        case QxTextEdit::ListNone:
            break;
        case QxTextEdit::ListDisc:
            listStyle = QTextListFormat::ListDisc;
            break;
        case QxTextEdit::ListCircle:
            listStyle = QTextListFormat::ListCircle;
            break;
        case QxTextEdit::ListSquare:
            listStyle = QTextListFormat::ListSquare;
            break;
        case QxTextEdit::ListDecimal:
            listStyle = QTextListFormat::ListDecimal;
            break;
        case QxTextEdit::ListLowerAlpha:
            listStyle = QTextListFormat::ListLowerAlpha;
            break;
        case QxTextEdit::ListUpperAlpha:
            listStyle = QTextListFormat::ListUpperAlpha;
            break;
        case QxTextEdit::ListLowerRoman:
            listStyle = QTextListFormat::ListLowerRoman;
            break;
        case QxTextEdit::ListUpperRoman:
            listStyle = QTextListFormat::ListUpperRoman;
            break;
        }

        QTextListFormat listFormat;
        listFormat.setStyle(listStyle);
        cursor.beginEditBlock();
        cursor.createList(listFormat);
        cursor.endEditBlock();
    } else {
        if (list) {
            list->remove(cursor.block());
            QTextBlockFormat blockFormat = cursor.blockFormat();
            blockFormat.setIndent(0);
            cursor.setBlockFormat(blockFormat);
        }
    }
}

/*!
  Gibt den Abstand des aktuellen Absatzes zum linken Seitenrand zurück.

  \sa setLeftMargin(double margin)
*/
double QxTextEdit::leftMargin() const
{
    QTextCursor cursor = textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    double margin = blockFormat.leftMargin();

    return margin;
}

/*!
  Setzt den Abstand des aktuellen Absatzes zum linken Seitenrand auf den Wert <i>margin</i>.

  \sa leftMargin()
*/
void QxTextEdit::setLeftMargin(double margin)
{
    QTextCursor cursor = textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();

    if (margin < 0.0)
        margin = 0.0;
    blockFormat.setLeftMargin(margin);
    cursor.setBlockFormat(blockFormat);
}

/*!
  Gibt den HTML-Cursor an der aktuellen Cursorposition zurück.
*/
QxHtmlCursor QxTextEdit::htmlCursor() const
{
    return QxHtmlCursor(textCursor());
}

/*!
  Gibt den HTML-Cursor an der Cursorposition <i>cursor</i> zurück.
*/
QxHtmlCursor QxTextEdit::htmlCursor(const QTextCursor &cursor) const
{
    return QxHtmlCursor(cursor);
}

/*!
  Gibt den Hyperlink an der aktuellen Cursorposition zurück.

  \sa setHyperlink(const QxHyperlink &link)
*/
QxHyperlink QxTextEdit::hyperlink() const
{
    return hyperlink(textCursor());
}

/*!
  Gibt den Hyperlink an der Cursorposition <i>cursor</i> zurück.
*/
QxHyperlink QxTextEdit::hyperlink(const QTextCursor &cursor) const
{
    QxHyperlink link;
    QString html = toHtml();
    QString url = cursor.charFormat().anchorHref();

    if (!url.isEmpty()) {
        int first = html.lastIndexOf("<a href", htmlCursor(cursor).position(), Qt::CaseInsensitive);
        int last = html.indexOf("</a>", first, Qt::CaseInsensitive) + 4;
        link.fromHtml(html.mid(first, last - first));
    } else {
        link.setText(cursor.selectedText());
    }

    return link;
}

/*!
  Fügt den Hyperlink <i>link</i> an der aktuellen Cursorposition ein.

  \sa hyperlink()
*/
void QxTextEdit::setHyperlink(const QxHyperlink &link)
{
    QxHyperlink originLink = hyperlink();
    QTextCursor cursor = textCursor();
    QTextCharFormat format = cursor.charFormat();
    QString html = link.toHtml();
    int position = 0;

    if (link == originLink)
        return;

    if (!originLink.text().isEmpty()) {
        cursor.setPosition(toPlainText().lastIndexOf(originLink.text(), cursor.position()));
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, originLink.text().length());
        cursor.removeSelectedText();
    }

    if (link.isValid()) {
        position = cursor.position();
        insertHtml(html);
        format.setAnchorHref(link.url());
        cursor.setPosition(position);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, link.text().length());
        cursor.mergeCharFormat(format);
    } else {
        insertPlainText(originLink.text());
    }
}

/*!
  Gibt den Namen der Sprungmarke an der aktuellen Cursorposition zurück.

  \sa insertAnchor(const QString &name, const QString &text)
*/
QString QxTextEdit::anchor() const
{
    QTextCursor cursor = textCursor();
    QTextCharFormat format = cursor.charFormat();
    QStringList names = format.anchorNames();
    QString anchor;

    if (!names.isEmpty())
        anchor = names.first();

    return anchor;
}

/*!
  Gibt die Namen aller Sprungmarken im Dokument zurück.
*/
QStringList QxTextEdit::anchors() const
{
    QxTextDocument *doc = qobject_cast<QxTextDocument*>(document());
    QStringList list = doc->anchors();

    return list;
}

/*!
  Fügt die Sprungmarke mit dem Namen <i>name</i> und dem Text <i>text</i> an der aktuellen Cursorposition ein.

  \sa anchor()
*/
void QxTextEdit::insertAnchor(const QString &name, const QString &text)
{
    QTextCursor cursor = textCursor();
    QFont font = currentFont();

    if (name.isEmpty() || anchors().contains(name))
        return;

    cursor.setPosition(cursor.position());
    setTextCursor(cursor);
    insertHtml(QString("<a name=\"%1\">%2</a>").arg(name).arg(text));
    setCurrentFont(font);
}

/*!
  Entfernt die Sprungmarke mit dem Namen <i>name</i> aus dem Dokument.
*/
void QxTextEdit::removeAnchor(const QString &name)
{
    QString html = toHtml();
    QTextCursor cursor = textCursor();
    int position = cursor.position();
    int first = html.indexOf(QString("<a name=\"%1\">").arg(name), Qt::CaseInsensitive);
    int last = html.indexOf(QString("</a>"), first, Qt::CaseInsensitive);

    if (first != -1 && last != -1) {
        html = html.remove(first, last - first);
        setHtml(html);
        cursor.setPosition(position);
        setTextCursor(cursor);
    }
}

/*!
  Fügt eine horizontale Linie an der aktuellen Cursorposition ein.
*/
void QxTextEdit::insertLine()
{
    QTextCursor cursor = textCursor();
    cursor.insertHtml("<hr /><p />");
}

/*!
  Fügt die Grafikdatei <i>fileName</i> an der aktuellen Cursorposition ein.
*/
void QxTextEdit::insertImage(const QString &fileName)
{
    insertImage(QImage(fileName));
}

/*!
  Gibt die Tabelle an der aktuellen Cursorposition zurück.

  \sa insertTable(int rows, int columns, const QTextTableFormat &format)
*/
QTextTable* QxTextEdit::currentTable() const
{
    QTextCursor cursor = textCursor();
    QTextTable *table = cursor.currentTable();

    return table;
}

/*!
  Fügt eine Tabelle mit <i>rows</i> Zeilen, <i>columns</i> Spalten und dem Format <i>format</i> an der aktuellen
  Cursorposition ein.

  \sa currentTable()
*/
QTextTable* QxTextEdit::insertTable(int rows, int columns, const QTextTableFormat &format)
{
    QTextCursor cursor = textCursor();
    QTextTable *table = cursor.insertTable(rows, columns, format);

    cursor = table->cellAt(0, 0).firstCursorPosition();
    setTextCursor(cursor);

    return table;
}

/*!
  Fügt eine Tabellenzeile an der aktuellen Cursorposition ein.

  \sa insertTableColumn()
*/
void QxTextEdit::insertTableRow()
{
    QTextCursor cursor = textCursor();
    QTextTable *table = cursor.currentTable();

    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid())
            table->insertRows(cell.row() + 1, 1);
    }
}

/*!
  Entfernt die Tabellenzeile an der aktuellen Cursorposition.
*/
void QxTextEdit::removeTableRow()
{
    QTextCursor cursor = textCursor();
    QTextTable *table = cursor.currentTable();

    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid())
            table->removeRows(cell.row(), 1);
    }
}

/*!
  Fügt eine Tabellenspalte an der aktuellen Cursorposition ein.

  \sa insertTableRow()
*/
void QxTextEdit::insertTableColumn()
{
    QTextCursor cursor = textCursor();
    QTextTable *table = cursor.currentTable();

    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid())
            table->insertColumns(cell.column() + 1, 1);
    }
}

/*!
  Entfernt die Tabellenspalte an der aktuellen Cursorposition.
*/
void QxTextEdit::removeTableColumn()
{
    QTextCursor cursor = textCursor();
    QTextTable *table = cursor.currentTable();

    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid())
            table->removeColumns(cell.column(), 1);
    }
}

/*!
  Gibt true zurück, wenn die letzte Aktion rückgängig gemacht werden kann.

  \sa canRedo()
*/
bool QxTextEdit::canUndo() const
{
    return m_canUndo;
}

/*!
  Gibt true zurück, wenn die letzte Aktion wiederhergestellt werden kann.

  \sa canUndo()
*/
bool QxTextEdit::canRedo() const
{
    return m_canRedo;
}

/*!
  Gibt true zurück, wenn Text in die Zwischenablage kopiert werden kann.
*/
bool QxTextEdit::canCopy() const
{
    QTextCursor cursor = textCursor();
    bool result = !cursor.selection().isEmpty();

    return result;
}

/*!
  Gibt true zurück, wenn der Editor Whitespaces anzeigt.
*/
bool QxTextEdit::showTabsAndSpaces() const
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    return flags.testFlag(QTextOption::ShowTabsAndSpaces);
}

/*!
  Legt fest, ob der Editor Whitespaces anzeigt.
*/
void QxTextEdit::setShowTabsAndSpaces(bool show)
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    if (show) {
        flags |= QTextOption::ShowTabsAndSpaces;
    } else {
        flags &= ~QTextOption::ShowTabsAndSpaces;
    }

    option.setFlags(flags);
    doc->setDefaultTextOption(option);
}

/*!
  Gibt true zurück, wenn der Editor Zeilenendezeichen anzeigt.
*/
bool QxTextEdit::showLineAndParagraphSeparators() const
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    return flags.testFlag(QTextOption::ShowLineAndParagraphSeparators);
}

/*!
  Legt fest, ob der Editor Zeilenendezeichen anzeigt.
*/
void QxTextEdit::setShowLineAndParagraphSeparators(bool show)
{
    QTextDocument *doc = document();
    QTextOption option = doc->defaultTextOption();
    QFlags<QTextOption::Flag> flags = option.flags();

    if (show) {
        flags |= QTextOption::ShowLineAndParagraphSeparators;
    } else {
        flags &= ~QTextOption::ShowLineAndParagraphSeparators;
    }

    option.setFlags(flags);
    doc->setDefaultTextOption(option);
}

/*!
  Gibt die Anzahl an Leerzeichen zurück, die beim drücken der Tabulatortaste eingefügt werden.
*/
int QxTextEdit::tabSpaces() const
{
    return m_tabSpaces;
}

/*!
  Fügt anstatt eines Tabulators <i>spaces</i> Leerzeichen ein wenn die Tabulatortaste gedrückt wurde.
*/
void QxTextEdit::setTabSpaces(int spaces)
{
    m_tabSpaces = spaces;
}

/*!
  Führt eine Textsuche mit den Suchoptionen <i>options</i> an der aktuellen Cursorposition durch.
*/
bool QxTextEdit::findOrReplace(const QxFindOptions &options)
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
  Wird bei einem Doppelklick mit der Maus aufgerufen.
*/
void QxTextEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    QxHyperlink link = hyperlink();

    if (link.isValid()) {
        emit linkActivated(link.url());
        return;
    }

    QTextEdit::mouseDoubleClickEvent(event);
}

/*!
  Wird aufgerufen wenn eine Taste gedrückt wurde.
*/
void QxTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        if (m_tabSpaces > 0) {
            insertPlainText(QString().fill(' ', m_tabSpaces));
            return;
        }
    }

    QTextEdit::keyPressEvent(event);
}

/*!
  Prüft ob die übergebenen MIME-Daten <i>source</i> eingefügt werden können.
*/
bool QxTextEdit::canInsertFromMimeData(const QMimeData *source) const
{
    QStringList formats = source->formats();

    if (formats.count() == 1) {
        if (formats.first() == "application/x-qt-image")
            return true;
    }

    return QTextEdit::canInsertFromMimeData(source);
}

/*!
  Erzeugt das Datenobjekt für die aktuelle Markierung.
*/
QMimeData* QxTextEdit::createMimeDataFromSelection() const
{
    QMimeData *data = QTextEdit::createMimeDataFromSelection();
    QxTextDocument *sourceDoc = static_cast<QxTextDocument*>(document());
    QxTextDocument doc;
    QTextDocumentFragment fragment(textCursor());

    doc.setHtml(fragment.toHtml());
    for (const QUrl &url : doc.images())
        doc.addResource(QTextDocument::ImageResource, url, sourceDoc->resource(QTextDocument::ImageResource, url));

    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QBuffer::WriteOnly);
    QDataStream out(&buffer);

    out << doc;
    data->setData(MIMETYPE, array);

    return data;
}

/*!
  Fügt die MIME-Daten <i>source</i> ein.
*/
void QxTextEdit::insertFromMimeData(const QMimeData *source)
{
    QStringList formats = source->formats();

    if (formats.contains(MIMETYPE)) {
        QxTextDocument *destDoc = static_cast<QxTextDocument*>(document());
        QxTextDocument doc;

        QByteArray array = source->data(MIMETYPE);
        QBuffer buffer(&array);
        buffer.open(QBuffer::ReadOnly);
        QDataStream in(&buffer);

        in >> doc;
        for (const QUrl &url : doc.images())
            destDoc->addResource(QTextDocument::ImageResource, url, doc.resource(QTextDocument::ImageResource, url));
        insertHtml(doc.toHtml());
    } else if (formats.contains("application/x-qt-image")) {
        insertImage(qvariant_cast<QImage>(source->imageData()));
    } else {
        QTextEdit::insertFromMimeData(source);
    }
}

void QxTextEdit::insertImage(const QImage &image)
{
    QString url;
    QVariant resource;

    do {
        url = "image://" + QxRandom::get(10, QxRandom::LOWERCHARS);
        resource = document()->resource(QTextDocument::ImageResource, url);
    } while (resource.isValid());

    document()->addResource(QTextDocument::ImageResource, QUrl(url), image);
    textCursor().insertImage(image, url);
}

void QxTextEdit::setUndoEnabled(bool enabled)
{
    m_canUndo = enabled;
}

void QxTextEdit::setRedoEnabled(bool enabled)
{
    m_canRedo = enabled;
}

/*!
  \var QxTextEdit::ListNone

  Kein Listenformat
*/

/*!
  \var QxTextEdit::ListDisc

  Gefüllter Kreis
*/

/*!
  \var QxTextEdit::ListCircle

  Kreis
*/

/*!
  \var QxTextEdit::ListSquare

  Gefülltes Rechteck
*/

/*!
  \var QxTextEdit::ListDecimal

  Nummerierung (aufsteigend)
*/

/*!
  \var QxTextEdit::ListLowerAlpha

  Kleinbuchstaben in alphabetischer Folge
*/

/*!
  \var QxTextEdit::ListUpperAlpha

  Großbuchstaben in alphabetischer Folge
*/

/*!
  \var QxTextEdit::ListLowerRoman

  Römische Ziffern in Kleinbuchstaben (bis 4999)
*/

/*!
  \var QxTextEdit::ListUpperRoman

  Römische Ziffern in Großbuchstaben (bis 4999)
*/

/*!
  \fn QxTextEdit::linkActivated(const QString &url)

  Das Signal wird ausgelöst wenn der Anwender auf einen Link mit dem Sprungziel <i>url</i> geklickt hat.

  \sa QxFindOptions
*/
