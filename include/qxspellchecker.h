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

#ifndef QXSPELLCHECKER_H
#define QXSPELLCHECKER_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Mit %QxSpellChecker kann eine Rechtschreibprüfung für QTextEdit, bzw. QPlainTextEdit realisiert werden.

  %QxSpellChecker vergleicht die Inhalte eines QTextEdit mit einer Wortliste und markiert alle Wörter, die nicht in der
  Liste enthalten sind.
*/
class QxSpellChecker : public QObject
{
    Q_OBJECT

public:
    QxSpellChecker(QTextEdit *editor);
    QxSpellChecker(QPlainTextEdit *editor);
    static bool setDictionary(const QString &fileName);
    static void setActive(bool active);
    static void setDelay(int delay);

public slots:
    void run();

private:
    static QSet<QString> m_wordList;
    static bool m_active;
    static int m_delay;
    QTextEdit *m_editor;
    QPlainTextEdit *m_plainEditor;
    bool m_finished;
    QTime m_interval;

private slots:
    void wake();
    void restart();
};

} // namespace

#endif // QXSPELLCHECKER_H
