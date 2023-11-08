/***********************************************************************************************************************
**
** Copyright (C) 2016-2023 Partsoft UG (haftungsbeschränkt)
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

#include "qxfilterheaderview.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxFilterHeaderView::QxFilterHeaderView(QAbstractItemView *view) : QHeaderView(Qt::Horizontal, view)
{
    setSectionsClickable(true);
    setHighlightSections(true);
    setDefaultAlignment(Qt::AlignTop | Qt::AlignLeft);

    connect(this, SIGNAL(sectionCountChanged(int,int)), this, SLOT(createFilters()));
    connect(this, SIGNAL(sectionResized(int,int,int)), this, SLOT(adjustFilters()));
    connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(adjustFilters()));
}

/*!
  Gibt die empfohlene Größe für das Widget zurück.
*/
QSize QxFilterHeaderView::sizeHint() const
{
    QSize size = QHeaderView::sizeHint();

    if (!m_filters.isEmpty())
        size.setHeight(size.height() + m_filters.at(0)->height());

    return size;
}

/*!
  Wird aufgerufen wenn sich der Status geändert hat.
*/
void QxFilterHeaderView::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange:
    case QEvent::StyleChange:
        updateFilters();
        break;
    default:
        break;
    }

    QHeaderView::changeEvent(event);
}

/*!
  Wird aufgerufen um das Ereignis <i>event</i> zu verarbeiten.
*/
bool QxFilterHeaderView::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QLineEdit *filter = qobject_cast<QLineEdit*>(object);
        int index = m_filters.indexOf(filter);

        if (filter) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            switch (keyEvent->key()) {
            case Qt::Key_Tab:
                while (++index < m_filters.count()) {
                    filter = m_filters.at(index);
                    if (!isSectionHidden(index)) {
                        filter->setFocus();
                        filter->selectAll();
                        return true;
                    }
                }
                break;
            case Qt::Key_Backtab:
                while (--index >= 0) {
                    filter = m_filters.at(index);
                    if (!isSectionHidden(index)) {
                        filter->setFocus();
                        filter->selectAll();
                        return true;
                    }
                }
                break;
            }
        }
    }

    return QHeaderView::eventFilter(object, event);
}

/*!
  Passt die Position der Filter an.
*/
void QxFilterHeaderView::updateGeometries()
{
    QHeaderView::updateGeometries();

    adjustFilters();
}

void QxFilterHeaderView::updateFilters()
{
    QStyleOption option;
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &option));
    QString hex = color.name(QColor::HexRgb);

    for (QLineEdit *filter : m_filters) {
        filter->setPlaceholderText(tr("Filtern"));
        filter->setStyleSheet(QString("border: 1px solid %1;").arg(hex));
    }
}

void QxFilterHeaderView::createFilters()
{
    qDeleteAll(m_filters);
    m_filters.clear();

    for (int n = 0; n < count(); ++n) {
        QLineEdit *filter = new QLineEdit(this);
        filter->setClearButtonEnabled(true);
        filter->installEventFilter(this);

        connect(filter, SIGNAL(textChanged(QString)), this, SLOT(filterChanged()));

        m_filters.append(filter);
    }

    updateFilters();
    adjustFilters();
}

void QxFilterHeaderView::adjustFilters() const
{
    const int offs = offset();
    const int y = QHeaderView::sizeHint().height();

    for (int n = 0; n < m_filters.count(); ++n) {
        QLineEdit *filter = m_filters.at(n);
        filter->move(sectionPosition(n) - offs - 1, y);
        filter->resize(sectionSize(n) + 1, filter->height());
    }
}

void QxFilterHeaderView::filterChanged()
{
    QLineEdit *filter = qobject_cast<QLineEdit*>(sender());
    if (filter) {
        int index = m_filters.indexOf(filter);
        if (index != -1)
            emit filterChanged(index, filter->text());
    }
}

/*!
  \fn QxFilterHeaderView::filterChanged(int index, const QString &text)

  Das Signal wird ausgelöst wenn der Benutzer einen Filter geändert hat.
*/
