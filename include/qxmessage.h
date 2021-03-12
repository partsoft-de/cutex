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

#ifndef QXMESSAGE_H
#define QXMESSAGE_H

#include "cutex.h"

namespace cutex {

/*!
  \brief %QxMessage ist eine Container-Klasse zum Sammeln von Meldungen.

  Mit Hilfe der Klasse %QxMessage können bei größeren Operationen Meldungen (Statushinweise, Fehlermeldungen, etc.)
  gesammelt und im Anschluß an den Benutzer ausgegeben werden.

  \sa QxMessageDialog
*/
class QxMessage
{
public:
    QxMessage(const QString &titel = QObject::tr("Meldung"));
    void append(const QString &text);
    void prepend(const QString &text);
    static void append(QxMessage *message, const QString &text);
    static void prepend(QxMessage *message, const QString &text);
    void show(QWidget *parent = 0);

private:
    QString m_title;
    QStringList m_messages;
};

} // namespace

#endif // QXMESSAGE_H
