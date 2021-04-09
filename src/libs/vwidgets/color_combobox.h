/******************************************************************************
 *   color_combobox.h
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

#ifndef COLOR_COMBOBOX_H
#define COLOR_COMBOBOX_H

#include <QComboBox>
#include <QString>
#include <QWidget>
#include <memory>

/**
 * A comboBox for choosing a color.
 */
class ColorComboBox: public QComboBox
{
    Q_OBJECT

public:
             ColorComboBox(QWidget *parent = nullptr , const char *name = nullptr );
             ColorComboBox(int width, int height, QWidget *parent = nullptr , const char *name = nullptr );
    virtual ~ColorComboBox();

    QString  getColor() const;
    void     setColor(const QString &color);
    void     init();
    int      getIconWidth();
    int      getIconHeight();

private slots:
    void     updateColor(int index);

signals:
    void     colorChanged(const QString &color);

private:
    QString  m_currentColor;
    int      m_colorIndexStart;
    int      m_iconWidth;
    int      m_iconHeight;
};

#endif
