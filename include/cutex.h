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

#ifndef CUTEX_H
#define CUTEX_H

#include <QtGlobal>
#include <QtWidgets>
#include <QtNetwork>
#include <QtXml>
#include <QtSql>
#include <QtHelp>

namespace cutex {

#define QX_VERSION_MAJOR    1
#define QX_VERSION_MINOR    5
#define QX_VERSION_PATCH    16
#define QX_VERSION          QX_VERSION_CHECK(QX_VERSION_MAJOR, QX_VERSION_MINOR, QX_VERSION_PATCH)
#define QX_VERSION_STR      QString("%1.%2.%3").arg(QX_VERSION_MAJOR).arg(QX_VERSION_MINOR).arg(QX_VERSION_PATCH)
#define QX_VERSION_CHECK(major, minor, patch)   ((major << 16) | (minor << 8) | (patch))

#define CLASSNAME(obj)      QString(obj->metaObject()->className())
#define BREAKABLE_BLOCK     for (bool _b = false; _b == false; _b = true)

/*!
  @mainpage cutex

  Partsoft cutex ist eine Klassenbibliothek für den Qt-Framework, welche die Programmierung erheblich vereinfacht.
  cutex ist kompatibel zu Qt ab Version 5.5.1 und steht unter der LGPL-Lizenz, d.h. die Bibiothek darf auch für
  kommerzielle Projekte frei verwendet werden. Bitte beachten Sie das bei Verwendung der Bibliothek, gemäß den
  Bestimmungen der LGPL, ein Hinweis auf die Quelle (https://www.partsoft.de) erforderlich ist.

  Das Projekt entstand ursprünglich durch die Auskopplung einzelner Klassen aus unserer kommerziellen Software Partsoft
  Money 2016, mit dem Zweck der Wiederverwendung. Daraus entstand mit der Zeit eine komplette Bibliothek, auf der
  mittlerweile sämtliche Produkte von Partsoft basieren. Auch in Zukunft werden wir cutex weiterhin einsetzen und somit
  ständig weiter entwickeln.

  Beispiele zur Verwendung der Bibliothek finden Sie im Ordner <i>samples</i>, eine detailierte Beschreibung der
  einzelnen Klassen können Sie dieser Dokumentation entnehmen.
*/

} // namespace

#endif // CUTEX_H
