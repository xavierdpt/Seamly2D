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

﻿ ************************************************************************
 **
 **  @file   dialogeuler.cpp
 **  @author Xavier Dupont <xavierdpt(at)gmail.com>
 **  @date   November 12, 2021
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

#include "dialogeuler.h"

#include <QDialog>
#include <QLineEdit>
#include <QLineF>
#include <QPlainTextEdit>
#include <QPointF>
#include <QPointer>
#include <QPushButton>
#include <QSharedPointer>
#include <QTimer>
#include <QToolButton>
#include <new>

#include "../vgeometry/vpointf.h"
#include "../vpatterndb/vcontainer.h"
#include "../vpatterndb/vtranslatevars.h"
#include "../vwidgets/vmaingraphicsscene.h"
#include "../vwidgets/vabstractmainwindow.h"
#include "../../tools/vabstracttool.h"
#include "../../visualization/line/vistooleuler.h"
#include "../../visualization/visualization.h"
#include "../ifc/xml/vabstractpattern.h"
#include "../ifc/xml/vdomdocument.h"
#include "../support/dialogeditwrongformula.h"
#include "../vmisc/vabstractapplication.h"
#include "../vmisc/vcommonsettings.h"
#include "ui_dialogeuler.h"

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief DialogEuler create dialog
 * @param data container with data
 * @param parent parent widget
 */
DialogEuler::DialogEuler(const VContainer *data, const quint32 &toolId, QWidget *parent)
    : DialogTool(data, toolId, parent),
      ui(new Ui::DialogEuler),
      formulaLength(),
      formulaAngle(),
      formulaBaseHeight(0),
      formulaBaseHeightAngle(0),
      m_firstRelease(false)
{
    ui->setupUi(this);

    ui->lineEditNamePoint->setClearButtonEnabled(true);

    InitFormulaUI(ui);
    ui->lineEditNamePoint->setText(qApp->getCurrentDocument()->GenerateLabel(LabelType::NewLabel));
    labelEditNamePoint = ui->labelEditNamePoint;
    this->formulaBaseHeight = ui->plainTextEditFormula->height();
    this->formulaBaseHeightAngle = ui->plainTextEditAngle->height();

    ui->plainTextEditFormula->installEventFilter(this);
    ui->plainTextEditAngle->installEventFilter(this);

    InitOkCancelApply(ui);
    flagFormula = false;
    DialogTool::CheckState();

    FillComboBoxPoints(ui->comboBoxBasePoint);
    FillComboBoxTypeLine(ui->comboBoxLineType, LineStylesPics());
    FillComboBoxLineColors(ui->comboBoxLineColor);

    connect(ui->toolButtonExprLength, &QPushButton::clicked, this, &DialogEuler::FXLength);
    connect(ui->toolButtonExprAngle, &QPushButton::clicked, this, &DialogEuler::FXAngle);

    connect(ui->lineEditNamePoint, &QLineEdit::textChanged, this, &DialogEuler::NamePointChanged);

    connect(ui->plainTextEditFormula, &QPlainTextEdit::textChanged, this, &DialogEuler::FormulaTextChanged);
    connect(ui->plainTextEditAngle, &QPlainTextEdit::textChanged, this, &DialogEuler::AngleTextChanged);

    connect(ui->pushButtonGrowLength, &QPushButton::clicked, this, &DialogEuler::DeployFormulaTextEdit);
    connect(ui->pushButtonGrowLengthAngle, &QPushButton::clicked, this, &DialogEuler::DeployAngleTextEdit);

    connect(timerFormula, &QTimer::timeout, this, &DialogEuler::EvalAngle);

    vis = new VisToolEuler(data);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief EvalAngle calculate value of angle
 */
void DialogEuler::EvalAngle()
{
    labelEditFormula = ui->labelEditAngle;
    Eval(ui->plainTextEditAngle->toPlainText(), flagError, ui->labelResultCalculationAngle, degreeSymbol, false);
    labelEditFormula = ui->labelEditFormula;
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::FormulaTextChanged()
{
    this->FormulaChangedPlainText();
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::AngleTextChanged()
{
    labelEditFormula = ui->labelEditAngle;
    ValFormulaChanged(flagError, ui->plainTextEditAngle, timerFormula, degreeSymbol);
    labelEditFormula = ui->labelEditFormula;
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::DeployFormulaTextEdit()
{
    DeployFormula(ui->plainTextEditFormula, ui->pushButtonGrowLength, formulaBaseHeight);
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::DeployAngleTextEdit()
{
    DeployFormula(ui->plainTextEditAngle, ui->pushButtonGrowLengthAngle, formulaBaseHeightAngle);
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::FXAngle()
{
    DialogEditWrongFormula *dialog = new DialogEditWrongFormula(data, toolId, this);
    dialog->setWindowTitle(tr("Edit angle"));
    dialog->SetFormula(GetAngle());
    dialog->setPostfix(degreeSymbol);
    if (dialog->exec() == QDialog::Accepted)
    {
        SetAngle(dialog->GetFormula());
    }
    delete dialog;
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::FXLength()
{
    DialogEditWrongFormula *dialog = new DialogEditWrongFormula(data, toolId, this);
    dialog->setWindowTitle(tr("Edit length"));
    dialog->SetFormula(GetFormula());
    dialog->setPostfix(UnitsToStr(qApp->patternUnit(), true));
    if (dialog->exec() == QDialog::Accepted)
    {
        SetFormula(dialog->GetFormula());
    }
    delete dialog;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief ChoosedObject gets id and type of selected object. Save right data and ignore wrong.
 * @param id id of point or detail
 * @param type type of object
 */
void DialogEuler::ChosenObject(quint32 id, const SceneObject &type)
{
    if (prepare == false)// After first choose we ignore all objects
    {
        if (type == SceneObject::Point)
        {
            if (SetObject(id, ui->comboBoxBasePoint, ""))
            {
                vis->VisualMode(id);
                VAbstractMainWindow *window = qobject_cast<VAbstractMainWindow *>(qApp->getMainWindow());
                SCASSERT(window != nullptr)
                connect(vis.data(), &Visualization::ToolTip, window, &VAbstractMainWindow::ShowToolTip);
                prepare = true;
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief SetPointName set name of point
 * @param value name
 */
void DialogEuler::SetPointName(const QString &value)
{
    pointName = value;
    ui->lineEditNamePoint->setText(pointName);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief SetTypeLine set type of line
 * @param value type
 */
void DialogEuler::SetTypeLine(const QString &value)
{
    ChangeCurrentData(ui->comboBoxLineType, value);
    vis->setLineStyle(LineStyleToPenStyle(value));
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief SetFormula set string of formula
 * @param value formula
 */
void DialogEuler::SetFormula(const QString &value)
{
    formulaLength = qApp->TrVars()->FormulaToUser(value, qApp->Settings()->GetOsSeparator());
    // increase height if needed. TODO : see if I can get the max number of caracters in one line
    // of this PlainTextEdit to change 80 to this value
    if (formulaLength.length() > 80)
    {
        this->DeployFormulaTextEdit();
    }
    ui->plainTextEditFormula->setPlainText(formulaLength);

    VisToolEuler *line = qobject_cast<VisToolEuler *>(vis);
    SCASSERT(line != nullptr)
    line->setLength(formulaLength);

    MoveCursorToEnd(ui->plainTextEditFormula);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief SetAngle set angle of line
 * @param value angle in degree
 */
void DialogEuler::SetAngle(const QString &value)
{
    formulaAngle = qApp->TrVars()->FormulaToUser(value, qApp->Settings()->GetOsSeparator());
    // increase height if needed. TODO : see if I can get the max number of caracters in one line
    // of this PlainTextEdit to change 80 to this value
    if (formulaAngle.length() > 80)
    {
        this->DeployAngleTextEdit();
    }
    ui->plainTextEditAngle->setPlainText(formulaAngle);

    VisToolEuler *line = qobject_cast<VisToolEuler *>(vis);
    SCASSERT(line != nullptr)
    line->SetAngle(formulaAngle);

    MoveCursorToEnd(ui->plainTextEditAngle);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief SetBasePointId set id base point of line
 * @param value id
 */
void DialogEuler::SetBasePointId(const quint32 &value)
{
    setCurrentPointId(ui->comboBoxBasePoint, value);

    VisToolEuler *line = qobject_cast<VisToolEuler *>(vis);
    SCASSERT(line != nullptr)
    line->setObject1Id(value);
}

//---------------------------------------------------------------------------------------------------------------------
QString DialogEuler::GetLineColor() const
{
    return GetComboBoxCurrentData(ui->comboBoxLineColor, ColorBlack);
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::SetLineColor(const QString &value)
{
    ChangeCurrentData(ui->comboBoxLineColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief DialogEuler::ShowDialog show dialog after finish working with visual part
 * @param click true if need show dialog after click mouse
 */
void DialogEuler::ShowDialog(bool click)
{
    if (prepare)
    {
        if (click)
        {
            // The check need to ignore first release of mouse button.
            // User can select point by clicking on a label.
            if (not m_firstRelease)
            {
                m_firstRelease = true;
                return;
            }

            /*We will ignore click if pointer is in point circle*/
            VMainGraphicsScene *scene = qobject_cast<VMainGraphicsScene *>(qApp->getCurrentScene());
            SCASSERT(scene != nullptr)
            const QSharedPointer<VPointF> point = data->GeometricObject<VPointF>(GetBasePointId());
            QLineF line = QLineF(static_cast<QPointF>(*point), scene->getScenePos());

            //Radius of point circle, but little bigger. Need handle with hover sizes.
            if (line.length() <= defPointRadiusPixel*1.5)
            {
                return;
            }
        }
        this->setModal(true);

        VisToolEuler *line = qobject_cast<VisToolEuler *>(vis);
        SCASSERT(line != nullptr)

        this->SetAngle(line->Angle());//Show in dialog angle what user choose
        this->SetFormula(line->Length());
        emit ToolTip("");
        timerFormula->start();
        this->show();
    }
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::ShowVisualization()
{
    AddVisualization<VisToolEuler>();
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::SaveData()
{
    pointName = ui->lineEditNamePoint->text();

    formulaLength = ui->plainTextEditFormula->toPlainText();
    formulaLength.replace("\n", " ");

    formulaAngle = ui->plainTextEditAngle->toPlainText();
    formulaAngle.replace("\n", " ");

    VisToolEuler *line = qobject_cast<VisToolEuler *>(vis);
    SCASSERT(line != nullptr)

    line->setObject1Id(GetBasePointId());
    line->setLength(formulaLength);
    line->SetAngle(formulaAngle);
    line->setLineStyle(LineStyleToPenStyle(GetTypeLine()));
    line->RefreshGeometry();
}

//---------------------------------------------------------------------------------------------------------------------
void DialogEuler::closeEvent(QCloseEvent *event)
{
    ui->plainTextEditFormula->blockSignals(true);
    ui->plainTextEditAngle->blockSignals(true);
    DialogTool::closeEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
DialogEuler::~DialogEuler()
{
    delete ui;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief GetTypeLine return type of line
 * @return type
 */
QString DialogEuler::GetTypeLine() const
{
    return GetComboBoxCurrentData(ui->comboBoxLineType, TypeLineLine);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief GetFormula return string of formula
 * @return formula
 */
QString DialogEuler::GetFormula() const
{
    return qApp->TrVars()->TryFormulaFromUser(formulaLength, qApp->Settings()->GetOsSeparator());
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief GetAngle return formula angle of line
 * @return angle formula
 */
QString DialogEuler::GetAngle() const
{
    return qApp->TrVars()->TryFormulaFromUser(formulaAngle, qApp->Settings()->GetOsSeparator());
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief GetBasePointId return id base point of line
 * @return id
 */
quint32 DialogEuler::GetBasePointId() const
{
    return getCurrentObjectId(ui->comboBoxBasePoint);
}
