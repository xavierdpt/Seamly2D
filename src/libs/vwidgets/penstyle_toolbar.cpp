/******************************************************************************
 *   @file   penstyle_toolbar.cpp
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

#include "penstyle_toolbar.h"

#include "../ifc/xml/vabstractpattern.h"
#include "../ifc/ifcdef.h"
#include "../vmisc/vabstractapplication.h"
#include "../vtools/tools/vabstracttool.h"

/**
 * Constructor
 */
PenStyleToolBar::PenStyleToolBar(VAbstractPattern *doc, const QString &title, QWidget *parent )
    : QToolBar(title, parent)
	, m_doc(doc)
	, m_currentColor("black")
	, m_currentLineType(LineTypeSolidLine)
    //, m_currentLineWeight()
	, m_colorBox(new ColorComboBox{40, 14, this, "colorbox"})
	, m_lineTypeBox(new LineTypeComboBox{40, 14, this, "lineTypebox"})
{
    setEnabled(false);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_colorBox->setToolTip(tr("Current Pen Color"));
    m_colorBox->setMaximumWidth(125);
    this->addWidget(m_colorBox);
    connect(m_colorBox, &ColorComboBox::colorChanged, this, &PenStyleToolBar::updateCurrentColor);

    m_lineTypeBox->setToolTip(tr("Current Pen LineType"));
    m_lineTypeBox->setMaximumWidth(125);
    this->addWidget(m_lineTypeBox);
	connect(m_lineTypeBox, &LineTypeComboBox::lineTypeChanged, this, &PenStyleToolBar::updateCurrentLineType);

    /**
        m_lineWeightBox->setToolTip(tr("Current Pen LineWeight"));
        m_lineWeightBox->setMaximumWidth(125);
        this->addWidget(m_lineWeightBox);
        connect(m_lineWeightBox, &LineWeightComboBox::lineWeightChangedSignal,
        this, &PenStyleToolBar::lineWeightChanged);
    **/

    resetAction = new QAction();
    resetAction->setIcon(QIcon(":/icon/16x16/reset.png"));
    resetAction->setToolTip ("Reset Pen to defaults (Alt+R)");
    resetAction->setEnabled(true);
    resetAction->setShortcut(QKeySequence("Alt+R"));
    this->addAction(resetAction);
    connect (resetAction, &QAction::triggered, this, &PenStyleToolBar::resetToolbar);
}

/**
 * Destructor
 */
PenStyleToolBar::~PenStyleToolBar() = default;

QString PenStyleToolBar::getCurrentColor()
{
    return m_currentColor;
}

void PenStyleToolBar::setCurrentColor(QString color)
{
    int index = m_colorBox->findText(color);
    if (index != -1)
    {
    	m_colorBox->setCurrentIndex(index);
    }
}

QString PenStyleToolBar::getCurrentLineType()
{
    return m_currentLineType;
}

void PenStyleToolBar::setCurrentLineType(QString type)
{
    int index = m_lineTypeBox->findText(type);
    if (index != -1)
    {
        m_lineTypeBox->setCurrentIndex(index);
    }
}

/**
QString PenStyleToolBar::getCurrentLineWeight()
{
    return m_currentLineWeight;
}

void PenStyleToolBar::setCurrentLineWeight(QString weight)
{
    int index = m_lineWeightBox->findText(weight);
    if (index != -1)
    {
        m_lineWeightBox->setCurrentIndex(index);
    }
}
**/

/**
 * @brief Sets current pen color. Called when the color was changed by the user.
 * @param color New current pen color
 */
void PenStyleToolBar::updateCurrentColor(const QString &color)
{
    m_currentColor = m_colorBox->currentText();
    m_doc->setDefaultLineColor(m_currentColor);
}

/**
 * @brief Sets current line type. Called when the type was changed by the user.
 * @param type New current line type
 * @result emits toolbarChanged
 */
void PenStyleToolBar::updateCurrentLineType(const QString &type)
{
    m_currentLineType = m_lineTypeBox->currentText();
    m_doc->setDefaultLineType(m_currentLineType);
}

/**
 * @brief Sets current pen width. Called when the width was changed by the user.
 * @param color New current pen width
 */
 /**
void PenStyleToolBar::updateCurrentLineWeight(const QString &weight)
{
    m_currentLineWeight = m_lineWeightBox->currentText();
    m_doc->setDefaultLineWeight(m_currentLineWeight);
}
**/

/**
 * @brief Reset the current pen attributes. Called when the toolbar was reset to defaults by the user.
 */
void PenStyleToolBar::resetToolbar()
{
    m_currentColor = qApp->Settings()->getDefaultLineColor();
    m_currentLineType = qApp->Settings()->getDefaultLineType();

    int index = m_colorBox->findText(m_currentColor);
    if (index != -1)
    {
        m_colorBox->setCurrentIndex(index);
    }
    m_doc->setDefaultLineColor(m_currentColor);

	index = m_lineTypeBox->findText(m_currentLineType);
    if (index != -1)
    {
        m_lineTypeBox->setCurrentIndex(index);
    }
    m_doc->setDefaultLineType(m_currentLineType);

    /**
        index = m_lineWeightBox->findText(qApp->Settings()->getDefaultLineWeight());
        if (index != -1)
        {
            m_lineWeightBox->setCurrentIndex(index);
        }
        m_doc->setDefaultLineWeight(this);
    **/
}
