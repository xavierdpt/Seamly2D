/******************************************************************************
 *   @file   color_combobox.cpp
 **  @author DS Caskey
 **  @date   April 6, 2021
 **
 **  @brief
 **  @copyright
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *****************************************************************************/

#include "color_combobox.h"

#include "../ifc/ifcdef.h"
#include "../vtools/tools/vabstracttool.h"

#include <QColor>
#include <QPixmap>
#include <QMap>
#include <QAbstractItemView>
#include <QComboBox>

/*
 * Default Constructor.
 */
ColorComboBox::ColorComboBox(QWidget *parent, const char *name)
    : QComboBox(parent)
    , m_currentColor(ColorBlack)
    , m_iconWidth(40)
    , m_iconHeight(14)
{
    setObjectName(name);
    setEditable (false);
    init();
}

/*
 * Constructor that provides width and height for icon.
 */
ColorComboBox::ColorComboBox(int width, int height, QWidget *parent, const char *name)
    : QComboBox(parent)
    , m_currentColor(ColorBlack)
    , m_iconWidth(width)
    , m_iconHeight(height)
{
    setObjectName(name);
    setEditable (false);
    init();
}

/**
 * Destructor
 */
ColorComboBox::~ColorComboBox(){}

/*
 * Initialisation called from constructor or manually but only once.
 */
void ColorComboBox::init()
{
    this->blockSignals(true);

#if defined(Q_OS_MAC)
    // Mac pixmap should be little bit smaller
    setIconSize(QSize(m_iconWidth-= 2 ,m_iconHeight-= 2));
#else
    // Windows
    setIconSize(QSize(m_iconWidth, m_iconHeight));
#endif

    this->view()->setTextElideMode(Qt::ElideNone);
    QMap<QString, QString> map = VAbstractTool::ColorsList();
    map.remove(ColorByGroup);
    QMap<QString, QString>::const_iterator i = map.constBegin();
    while (i != map.constEnd())
    {
        QPixmap pixmap = VAbstractTool::createColorIcon(m_iconWidth, m_iconHeight, i.key());
        addItem(QIcon(pixmap), i.value(), QVariant(i.key()));
        ++i;
    }

    this->blockSignals(false);
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ColorComboBox::updateColor);

    setCurrentIndex(0);
    updateColor(currentIndex());
}

/*
 * Sets the color shown in the combobox to the given color.
 */
void ColorComboBox::setColor(const QString &color)
{
    m_currentColor = color;

    setCurrentIndex(findData(color));

    if (currentIndex()!= count() -1 )
    {
        updateColor(currentIndex());
    }
}

/*
 * Called when the color has changed. This method sets the current color to the
 * value chosen.
 */
void ColorComboBox::updateColor(int index)
{
    QVariant color = itemData(index);
    if(color != QVariant::Invalid )
    {
       m_currentColor = QVariant(color).toString();
    }

    emit colorChanged(m_currentColor);
}

QString ColorComboBox::getColor() const
{
    return m_currentColor;
}

int ColorComboBox::getIconWidth()
{
    return m_iconWidth;
}

int ColorComboBox::getIconHeight()
{
    return m_iconHeight;
}
