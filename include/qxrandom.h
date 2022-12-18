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

#ifndef QXRANDOM_H
#define QXRANDOM_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Mit der Klasse %QxRandom können zufällige Werte erzeugt werden.

  Die Klasse %QxRandom vereinfacht das Erzeugen zufälliger Werte, wie z.B. Zufallszahlen. Der Zufallszahlengenerator
  wird bei der ersten Verwendung automatisch initialisiert.
*/
class QxRandom
{
public:
    static const QString NUMBERS;
    static const QString UPPERCHARS;
    static const QString LOWERCHARS;

public:
    static QString get(int length, const QString &pool = QxRandom::NUMBERS);

private:
    static bool m_initialized;

private:
    static void initialize();
};

} // namespace

#endif // QXRANDOM_H
