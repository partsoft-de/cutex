/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXAPPLICATION_H
#define QXAPPLICATION_H

#include "cutex.h"

namespace cutex {

class QxApplication;
extern QxApplication *qxApp;

/*!
  \brief Die Klasse %QxApplication erweitert QApplication um cutex-spezifische Features.

  Es wird empfohlen die Klasse %QxApplication anstelle von QApplication zu verwenden. %QxApplication lädt automatisch
  die landesspezifischen Qt-Übersetzungsdateien und definiert Hotkeys für den Framework. In zukünftigen Versionen wird
  die Klasse um Datenbankfunktionen erweitert.
*/
class QxApplication : public QApplication
{
public:
    QxApplication(int &argc, char **argv);
    void setFieldButtonHotkey(Qt::Key key);
    int fieldButtonHotkey() const;
    bool addTranslator(const QString &name, const QString &locale = QString());
    void changeLanguage(const QString &locale);
    static bool setTranslationsPath(const QString &path);

private:
    Qt::Key m_fieldButtonHotkey;
    QMap<QString, QTranslator*> m_translators;
    static QString m_translationsPath;

private:
    bool loadTranslation(QTranslator *translator, const QString &fileName);
};

} // namespace

#endif // QXAPPLICATION_H
