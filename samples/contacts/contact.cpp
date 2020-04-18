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

#include "contact.h"

Contact::Contact()
{
    m_anrede = tr("Herr");
    m_land = "DE";
}

QDataStream& operator <<(QDataStream &out, const Contact *contact)
{
    out << contact->m_anrede << contact->m_vorname << contact->m_name << contact->m_land << contact->m_postleitzahl
        << contact->m_ort << contact->m_strasse << contact->m_telefon << contact->m_mobil << contact->m_email;

    return out;
}

QDataStream& operator >>(QDataStream &in, Contact *contact)
{
    in >> contact->m_anrede >> contact->m_vorname >> contact->m_name >> contact->m_land >> contact->m_postleitzahl
        >> contact->m_ort >> contact->m_strasse >> contact->m_telefon >> contact->m_mobil >> contact->m_email;

    return in;
}
