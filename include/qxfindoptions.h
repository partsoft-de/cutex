/***********************************************************************************************************************
**
** Copyright (C) 2016-2023 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXFINDOPTIONS_H
#define QXFINDOPTIONS_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxFindOptions verwaltet Optionen zur Textsuche.

  Die Klasse %QxFindOptions verwaltet Optionen zum Suchen und Ersetzen von Text.

  \sa QxFindDialog
*/
class QxFindOptions
{
public:
    enum Mode {
        Find = 1, Replace, ReplaceAll
    };

public:
    QxFindOptions();
    QxFindOptions::Mode mode() const;
    void setMode(QxFindOptions::Mode mode);
    QString findText() const;
    void setFindText(const QString &text);
    QString replaceText() const;
    void setReplaceText(const QString &text);
    bool wholeWords() const;
    void setWholeWords(bool wholeWords);
    bool caseSensitive() const;
    void setCaseSensitive(bool caseSensitive);
    bool regularExpression() const;
    void setRegularExpression(bool regularExpression);
    bool backward() const;
    void setBackward(bool backward);

private:
    QxFindOptions::Mode m_mode;
    QString m_findText;
    QString m_replaceText;
    bool m_wholeWords;
    bool m_caseSensitive;
    bool m_regularExpression;
    bool m_backward;
};

} // namespace

#endif // QXFINDOPTIONS_H
