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

#include "qxapplication.h"
#include "qxmainwindow.h"
#include "qxresource.h"

using namespace cutex;

namespace cutex {
QxApplication *qxApp;
}

QString QxApplication::m_translationsPath = QString();
QString QxApplication::m_themesPath = QString();

/*!
  Erzeugt ein neues Applikations-Objekt (siehe Qt-Hilfe zu QApplication). Lädt zusätzlich die landesspezifischen
  Qt-Übersetzungsdateien und initialisiert die cutex-eigenen Resourcen.
*/
QxApplication::QxApplication(int &argc, char **argv) : QApplication(argc, argv)
{
    qxApp = this;
    m_fieldButtonHotkey = Qt::Key_F5;

    // Bei Verwendung von QGtkStyle werden cutex-spezifische Stylesheets nicht korrekt dargestellt
    if (CLASSNAME(style()) == "QGtkStyle") {
#if QT_VERSION >= 0x050000
        setStyle(QStyleFactory::create("Fusion"));
#else
        setStyle(new QCleanlooksStyle());
#endif
    }

    addTranslator("qt_", QLocale::system().name());
    addTranslator("cutex_", QLocale::system().name());

    initResource();
}

/*!
  Setzt den anwendungsweiten Hotkey für Field-Buttons. Ein Field in cutex ist ein beliebiges Eingabefeld
  (z.B. QLineEdit) und kann mit einem QPushButton verbunden werden, indem der Button genauso wie das Eingabefeld
  und dem Suffix "Button" benannt wird (z.B. FileField, FileFieldButton). Besitzt das Eingabefeld den Fokus,
  kann ein Klick auf den zugehörigen Button durch den hier übergebenen Hotkey ausgelöst werden.

  \sa fieldButtonHotkey()
*/
void QxApplication::setFieldButtonHotkey(Qt::Key key)
{
    m_fieldButtonHotkey = key;
}

/*!
  Gibt den anwendungsweiten Hotkey für Field-Buttons zurück.  Ein Field in cutex ist ein beliebiges Eingabefeld
  (z.B. QLineEdit) und kann mit einem QPushButton verbunden werden, indem der Button genauso wie das Eingabefeld
  und dem Suffix "Button" benannt wird (z.B. FileField, FileFieldButton). Besitzt das Eingabefeld den Fokus,
  kann ein Klick auf den zugehörigen Button durch den hier übergebenen Hotkey ausgelöst werden.

  \sa setFieldButtonHotkey(Qt::Key key)
*/
int QxApplication::fieldButtonHotkey() const
{
    return m_fieldButtonHotkey;
}

/*!
  Fügt der Anwendung einen neuen Translator mit dem Namen <i>name</i> für die Sprache <i>locale</i> hinzu.
*/
bool QxApplication::addTranslator(const QString &name, const QString &locale)
{
    if (m_translators.contains(name))
        return false;

    QTranslator *translator = new QTranslator(this);
    QString fileName;

    if (locale.isEmpty()) {
        fileName = name + QLocale::system().name();
    } else {
        fileName = name + locale;
    }

    m_translators.insert(name, translator);
    loadTranslation(translator, fileName);
    installTranslator(translator);

    return true;
}

/*!
  Ändert die Sprache der Anwendung in die in <i>locale</i> angegebene Sprache.
*/
void QxApplication::changeLanguage(const QString &locale)
{
    foreach (QString fileName, m_translators.keys()) {
        QTranslator *translator = m_translators.value(fileName);
        removeTranslator(translator);
        loadTranslation(translator, fileName + locale);
        installTranslator(translator);
    }
}

/*!
  Setzt den Pfad für die Übersetzungsdateien auf den Wert <i>path</i>.
*/
bool QxApplication::setTranslationsPath(const QString &path)
{
    bool success = QDir(path).exists();

    if (success)
        m_translationsPath = path;

    return success;
}

/*!
  Setzt das Stylesheet der Anwendung auf den Inhalt der Datei <i>theme</i>.
*/
void QxApplication::changeTheme(const QString &theme)
{
    QDir dir;
    QString sheet;

    if (!theme.isEmpty()) {
        if (m_themesPath.isEmpty()) {
            dir = QDir(QString("%1/themes/").arg(applicationDirPath()));
        } else {
            dir = QDir(m_themesPath);
        }

        QFile file(dir.absoluteFilePath(theme));

        if (file.open(QIODevice::ReadOnly))
            sheet = file.readAll();
    }

    setStyleSheet(sheet);
}

/*!
  Setzt den Pfad für die Themendateien auf den Wert <i>path</i>.
*/
bool QxApplication::setThemesPath(const QString &path)
{
    bool success = QDir(path).exists();

    if (success)
        m_themesPath = path;

    return success;
}

/*!
  Gibt eine Liste aller Themendateien zurück.
*/
QStringList QxApplication::themes()
{
    QStringList files;
    QDir dir;

    if (m_themesPath.isEmpty()) {
        dir = QDir(QString("%1/themes/").arg(applicationDirPath()));
    } else {
        dir = QDir(m_themesPath);
    }

    QDirIterator it(dir.absolutePath(), QDir::Files);
    while (it.hasNext()) {
        QString fileName = it.next();
        QFileInfo info(fileName);

        if (info.completeSuffix().toLower() == "qss")
            files.append(info.fileName());
    }

    return files;
}

bool QxApplication::loadTranslation(QTranslator *translator, const QString &fileName)
{
    if (!m_translationsPath.isEmpty() && translator->load(fileName, m_translationsPath))
        return true;

    if (translator->load(fileName, applicationDirPath()))
        return true;

    if (translator->load(fileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        return true;

    return false;
}
