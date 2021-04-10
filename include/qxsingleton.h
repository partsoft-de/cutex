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

#ifndef QXSINGLETON_H
#define QXSINGLETON_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSingleton ist eine Singleton-Implementierung für allgemeine Objekte.

  %QxSingleton ist eine Template-basierte Singleton-Implementierung, die mit beliebigen Objekten verwendet werden kann.
*/
template<typename T> class QxSingleton
{
public:
   static T* instance()
   {
       if (!m_instance)
           m_instance = new T();

       return m_instance;
   }
   virtual ~QxSingleton()
   {
       m_instance = nullptr;
   }

protected:
   QxSingleton()
   {
   }

private:
   static T* m_instance;
};

template<typename T> T* QxSingleton<T>::m_instance = nullptr;

} // namespace

#endif // QXSINGLETON_H
