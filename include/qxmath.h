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

#ifndef QXMATH_H
#define QXMATH_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxMath stellt mathematische Funktionen zur Verfügung.

  Die Klasse %QxMath stellt mathematische Funktionen zur Verfügung, bzw. vereinfacht die Verwendung der
  Standardbibliothek std::math.
*/
class QxMath
{
public:
    static double round(double value, int decimals);
    static double gross(double net, int vat);
    static double net(double gross, int vat);
};

} // namespace

#endif // QXMATH_H
