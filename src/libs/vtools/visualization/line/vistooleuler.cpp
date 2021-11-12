/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                             *
 *                                                                         *
 ***************************************************************************
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
 **************************************************************************

 ************************************************************************
 **
 **  @file   vistooleuler.cpp
 **  @author Xavier Dupont <xavierdpt(at)gmail.com>
 **  @date   12 11, 2021
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
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
 *************************************************************************/

#include "vistooleuler.h"

#include <QColor>
#include <QGuiApplication>
#include <QLineF>
#include <QPointF>
#include <QSharedPointer>
#include <Qt>
#include <new>

#include "../ifc/xml/vdomdocument.h"
#include "../vgeometry/vgobject.h"
#include "../vgeometry/vpointf.h"
#include "../vmisc/vabstractapplication.h"
#include "../vmisc/vcommonsettings.h"
#include "../vpatterndb/vcontainer.h"
#include "../visualization.h"
#include "visline.h"
#include "vtranslatevars.h"

//---------------------------------------------------------------------------------------------------------------------
VisToolEuler::VisToolEuler(const VContainer *data, QGraphicsItem *parent)
    : VisLine(data, parent), length(0), angle(0), point(nullptr)
{
    this->mainColor = Qt::red;

    point = InitPoint(mainColor, this);
}

//---------------------------------------------------------------------------------------------------------------------
void VisToolEuler::RefreshGeometry()
{
    const QSharedPointer<VPointF> first = Visualization::data->GeometricObject<VPointF>(object1Id);
    QLineF line;
    if (qFuzzyIsNull(length))
    {
        if (QGuiApplication::keyboardModifiers() == Qt::ShiftModifier)
        {
            line = QLineF(static_cast<QPointF>(*first), Visualization::scenePos);
            line.setAngle(CorrectAngle(line.angle()));
        }
        else
        {
            line = QLineF(static_cast<QPointF>(*first), Visualization::scenePos);
        }
    }
    else
    {
        line = VGObject::BuildLine(static_cast<QPointF>(*first), length, angle);
        DrawPoint(point, line.p2(), mainColor);
    }
    DrawLine(this, line, mainColor, lineStyle);
    static const QString prefix = UnitsToStr(qApp->patternUnit(), true);
    Visualization::toolTip = tr("<b>Point at distance and angle</b>: angle = %1°, length = %2%3; "
                                "<b>Shift</b> - sticking angle, <b>Enter</b> - finish creation")
            .arg(this->line().angle())
            .arg(qApp->TrVars()->FormulaToUser(QString::number(qApp->fromPixel(this->line().length())),
                                               qApp->Settings()->GetOsSeparator()))
            .arg(prefix);
}

//---------------------------------------------------------------------------------------------------------------------
QString VisToolEuler::Angle() const
{
    return QString("%1").arg(this->line().angle());
}

//---------------------------------------------------------------------------------------------------------------------
void VisToolEuler::SetAngle(const QString &expression)
{
    angle = FindVal(expression, Visualization::data->DataVariables());
}

//---------------------------------------------------------------------------------------------------------------------
QString VisToolEuler::Length() const
{
    return QString::number(qApp->fromPixel(this->line().length()));
}

//---------------------------------------------------------------------------------------------------------------------
void VisToolEuler::setLength(const QString &expression)
{
    length = FindLength(expression, Visualization::data->DataVariables());
}
