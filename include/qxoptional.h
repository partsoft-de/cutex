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

#ifndef QXOPTIONAL_H
#define QXOPTIONAL_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxOptional speichert optionale Werte.

  %QxOptional ist eine Template-basierte Klasse, die sich an boost::optional, bzw. std::optional orientiert. %QxOptional
  hat allerdings keine Pointer-Semantik und die Schnittstelle ist auch nicht mit boost::optional, bzw. std::optional
  kompatibel.
*/
template<typename T> class QxOptional
{
public:
    QxOptional()
    {
        m_data = qMakePair(false, T());
    }

    QxOptional(const T &value)
    {
        m_data = qMakePair(true, value);
    }

    void clear()
    {
        m_data = qMakePair(false, T());
    }

    bool hasValue() const
    {
        return m_data.first;
    }

    T value(const T &defaultValue = T()) const
    {
        return (m_data.first ? m_data.second : defaultValue);
    }

    void setValue(const T &value)
    {
        m_data = qMakePair(true, value);
    }

private:
    QPair<bool, T> m_data;
};

} // namespace

#endif // QXOPTIONAL_H
