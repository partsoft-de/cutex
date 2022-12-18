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

#ifndef QXDATEVALIDATOR_H
#define QXDATEVALIDATOR_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxDateValidator ist ein Validator für Datumswerte.

  Qt stellt mit QDateEdit ein Widget zur Eingabe von Datumswerten bereit. Sobald ein Datum aber nur optional eingegeben
  werden soll, stößt man jedoch an die Grenzen von QDateEdit. Die Auswahl eines leeren Datums ist damit nicht möglich.
  Mit %QxDateValidator kann ein normales Eingabefeld zur Eingabe von Datumswerten verwendet und validiert werden.

  \sa QxDateEdit
*/
class QxDateValidator : public QValidator
{
    Q_OBJECT

public:
    QxDateValidator(QObject *parent = nullptr);
    QxDateValidator(const QString &format, QObject *parent = nullptr);
    QString format() const;
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

#endif // QXDATEVALIDATOR_H
