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

#include "qxmath.h"
#include "math.h"

using namespace cutex;

/*!
  Rundet den Wert <i>value</i> auf die angegebenen Nachkommastellen <i>decimals</i>.
*/
double QxMath::round(double value, int decimals)
{
    value *= std::pow(10, decimals);
    if (value >= 0.0) {
        value = std::floor(value + 0.5);
    } else {
        value = std::ceil(value - 0.5);
    }

    value /= std::pow(10, decimals);

    return value;
}

/*!
  Berechnet den Bruttobetrag aus dem Nettowert <i>net</i> für den Steuersatz <i>vat</i>.
*/
double QxMath::gross(double net, double vat)
{
    return net + ((net * vat) / 100.0);
}

/*!
  Berechnet den Nettobetrag aus dem Bruttowert <i>gross</i> für den Steuersatz <i>vat</i>.
*/
double QxMath::net(double gross, double vat)
{
    return gross - ((gross / (100.0 + vat)) * vat);
}
