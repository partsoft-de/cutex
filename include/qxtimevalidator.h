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

#ifndef QXTIMEVALIDATOR_H
#define QXTIMEVALIDATOR_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxTimeValidator ist ein Validator für Zeitangaben.

  Qt stellt mit QTimeEdit ein Widget zur Eingabe von Zeitangaben bereit. Sobald eine Uhrzeit aber nur optional
  eingegeben werden soll, stößt man jedoch an die Grenzen von QTimeEdit. Die Auswahl einer leeren Uhrzeit ist damit
  nicht möglich. Mit %QxTimeValidator kann ein normales Eingabefeld zur Eingabe von Zeitangaben verwendet und validiert
  werden.
*/
class QxTimeValidator : public QValidator
{
    Q_OBJECT

public:
    QxTimeValidator(QObject *parent = 0);
    QxTimeValidator(const QString &format, QObject *parent = 0);
    virtual void fixup(QString &input) const;
    virtual QValidator::State validate(QString &input, int &pos) const;

private:
    QString m_format;
    QChar m_separator;

private:
    void determineSeparator();
    void prepare(QString &input) const;
};

} // namespace

#endif // QXTIMEVALIDATOR_H
