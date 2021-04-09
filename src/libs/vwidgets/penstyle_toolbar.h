/******************************************************************************
 *   @file   penstyle_toolbar.h
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

#ifndef PENSTYLE_TOOLBAR_H
#define PENSTYLE_TOOLBAR_H

#include "../ifc/xml/vabstractpattern.h"

#include "color_combobox.h"
#include "linetype_combobox.h"
//#include "lineweight_combobox.h"

#include <memory>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QObject>
#include <QPixmap>
#include <QKeySequence>

class VAbstractPattern;
class ColorComboBox;
class LineTypeComboBox;
//class LineWeightComboBox;

/**
 * @brief A toolbar that offers widgets for choosing attributes for the current pen.
 */
class PenStyleToolBar: public QToolBar
{

 Q_OBJECT

public:
  	                                       PenStyleToolBar(VAbstractPattern *doc, const QString &title, QWidget *parent = 0 );
    virtual                               ~PenStyleToolBar();

    QString                                getCurrentColor();
    void                                   setCurrentColor(QString color);
    QString                                getCurrentLineType();
    void                                   setCurrentLineType(QString type);
    //QString                                getCurrentLineWeight();
    //void                                   setCurrentLineWeight(QString wight);

public slots:
    void                                   updateCurrentColor(const QString &color);
    void                                   updateCurrentLineType(const QString &type);
    //void                                   updateCurrentLineWeight(const QString &weight);
    void                                   resetToolbar();

signals:
    void                                   toolbarChanged();

private:
    QAction                               *resetAction;
    VAbstractPattern                      *m_doc;
    QString                                m_currentColor;
    QString                                m_currentLineType;
    //QString                                m_currentLineWeight;
    ColorComboBox                         *m_colorBox;
    LineTypeComboBox                      *m_lineTypeBox;
    //LineWeightComboBox                    *m_lineWeightBox;
};

#endif
