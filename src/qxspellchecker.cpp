/***********************************************************************************************************************
**
** Copyright (C) 2016-2022 Partsoft UG (haftungsbeschränkt)
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

#include "qxspellchecker.h"
#include "qxwaitcursor.h"

using namespace cutex;

QSet<QString> QxSpellChecker::m_wordList;
bool QxSpellChecker::m_active = false;
int QxSpellChecker::m_delay = 1000;

/*!
  Erzeugt ein neues Objekt zur Rechtschreibprüfung für den Editor <i>editor</i>.
*/
QxSpellChecker::QxSpellChecker(QTextEdit *editor) : QObject(editor)
{
    QAbstractEventDispatcher *dispatcher = QAbstractEventDispatcher::instance();
    m_editor = editor;
    m_plainEditor = 0;
    m_finished = false;

    connect(dispatcher, SIGNAL(awake()), this, SLOT(wake()));
    connect(m_editor->document(), SIGNAL(contentsChanged()), this, SLOT(restart()));
}

/*!
  Erzeugt ein neues Objekt zur Rechtschreibprüfung für den Editor <i>editor</i>.
*/
QxSpellChecker::QxSpellChecker(QPlainTextEdit *editor) : QObject(editor)
{
    QAbstractEventDispatcher *dispatcher = QAbstractEventDispatcher::instance();
    m_plainEditor = editor;
    m_editor = 0;
    m_finished = false;

    connect(dispatcher, SIGNAL(awake()), this, SLOT(wake()));
    connect(m_plainEditor->document(), SIGNAL(contentsChanged()), this, SLOT(restart()));
}

/*!
  Aktualisiert die Wortliste mit dem Inhalt der Datei <i>fileName</i>.
*/
bool QxSpellChecker::setDictionary(const QString &fileName)
{
    QFile file(fileName);
    QTextStream inStream(&file);
    bool success = false;
    QxWaitCursor wait;
    Q_UNUSED(wait);

    m_wordList.clear();
    success = file.open(QFile::ReadOnly);
    if (success) {
        while (!inStream.atEnd())
            m_wordList.insert(inStream.readLine().toLower());
    }

    return success;
}

/*!
  Aktiviert oder deaktiviert die Rechtschreibprüfung.
*/
void QxSpellChecker::setActive(bool active)
{
    m_active = active;
}

/*!
  Setzt den Zeitraum zur Aktualisierung der Rechtschreibprüfung auf <i>delay</i> Millisekunden.
*/
void QxSpellChecker::setDelay(int delay)
{
    m_delay = delay;
}

/*!
  Führt die Rechtschreibprüfung durch und markiert alle ungültigen Wörter.
*/
void QxSpellChecker::run()
{
    QList<QTextEdit::ExtraSelection> selections;

    if (m_active) {
        QTextCursor cursor;
        QString word;
        QString text;
        QStringList allWords;
        QStringList invalidWords;

        if (m_editor) {
            cursor = m_editor->textCursor();
            text = m_editor->document()->toPlainText();
        } else if (m_plainEditor) {
            cursor = m_plainEditor->textCursor();
            text = m_plainEditor->document()->toPlainText();
        }

#if QT_VERSION >= QT_VERSION_CHECK(5,14,0)
        allWords = text.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
#else
        allWords = text.split(QRegularExpression("\\W+"), QString::SkipEmptyParts);
#endif
        for (QString word : allWords) {
            word = word.toLower();
            if (!invalidWords.contains(word)) {
                bool isNumber;
                word.toInt(&isNumber);
                if (!isNumber && !m_wordList.contains(word))
                    invalidWords.append(word);
            }
        }

        cursor.movePosition(QTextCursor::Start);
        while (!cursor.atEnd()) {
            cursor.select(QTextCursor::WordUnderCursor);
            word = cursor.selectedText().toLower();

            if (invalidWords.contains(word)) {
                QTextEdit::ExtraSelection extraSelection;
                extraSelection.cursor = cursor;
                extraSelection.format.setUnderlineColor(Qt::red);
                extraSelection.format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
                selections.append(extraSelection);
            }

            cursor.movePosition(QTextCursor::NextWord);
        }
    }

    if (m_editor) {
        m_editor->setExtraSelections(selections);
    } else if (m_plainEditor) {
        m_plainEditor->setExtraSelections(selections);
    }

    m_finished = true;
}

void QxSpellChecker::wake()
{
    if ((!m_interval.isValid() || m_interval.elapsed() > m_delay) && !m_finished) {
        m_interval.start();
        run();
    }
}

void QxSpellChecker::restart()
{
    m_interval.start();
    m_finished = false;
}
