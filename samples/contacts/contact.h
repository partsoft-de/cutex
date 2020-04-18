/***********************************************************************************************************************
**
** Copyright (C) 2016 Partsoft UG (haftungsbeschränkt)
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

#ifndef CONTACT_H
#define CONTACT_H

#include "contacts.h"

class Contact
{
    Q_DECLARE_TR_FUNCTIONS(Contact)

public:
    Contact();
    QString anrede() const { return m_anrede; }
    void setAnrede(const QString &anrede) { m_anrede = anrede; }
    QString vorname() const { return m_vorname; }
    void setVorname(const QString &vorname) { m_vorname = vorname; }
    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }
    QString land() const { return m_land; }
    void setLand(const QString &land) { m_land = land; }
    QString postleitzahl() const { return m_postleitzahl; }
    void setPostleitzahl(const QString &postleitzahl) { m_postleitzahl = postleitzahl; }
    QString ort() const { return m_ort; }
    void setOrt(const QString &ort) { m_ort = ort; }
    QString strasse() const { return m_strasse; }
    void setStrasse(const QString &strasse) { m_strasse = strasse; }
    QString telefon() const { return m_telefon; }
    void setTelefon(const QString &telefon) { m_telefon = telefon; }
    QString mobil() const { return m_mobil; }
    void setMobil(const QString &mobil) { m_mobil = mobil; }
    QString email() const { return m_email; }
    void setEmail(const QString &email) { m_email = email; }
    friend QDataStream& operator <<(QDataStream &out, const Contact *contact);
    friend QDataStream& operator >>(QDataStream &in, Contact *contact);

private:
    QString m_anrede;
    QString m_vorname;
    QString m_name;
    QString m_land;
    QString m_postleitzahl;
    QString m_ort;
    QString m_strasse;
    QString m_telefon;
    QString m_mobil;
    QString m_email;
};

#endif // CONTACT_H
