/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                            *
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
 **  @file   mainwindow.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   November 15, 2013
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindowsnogui.h"

#include "core/vcmdexport.h"
#include "../vmisc/vlockguard.h"
#include "../vwidgets/penstyle_toolbar.h"

#include <QPointer>

namespace Ui
{
    class MainWindow;
}

class VToolOptionsPropertyBrowser;
class VMeasurements;
class QFileSystemWatcher;
class QLabel;
class DialogVariables;
class DialogTool;
class DialogHistory;
class VWidgetGroups;
class VWidgetDetails;
class QToolButton;
class QDoubleSpinBox;
class PenStyleToolBar;

/**
 * @brief The MainWindow class main windows.
 */
class MainWindow : public MainWindowsNoGUI
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() Q_DECL_OVERRIDE;

    bool LoadPattern(const QString &fileName, const QString &customMeasureFile = QString());

public slots:
    void ProcessCMD();

    virtual void ShowToolTip(const QString &toolTip) Q_DECL_OVERRIDE;
    virtual void zoomToSelected() Q_DECL_OVERRIDE;

signals:
    void RefreshHistory();
    void EnableItemMove(bool move);
    void ItemsSelection(SelectionType type) const;

    void EnableLabelSelection(bool enable) const;
    void EnablePointSelection(bool enable) const;
    void EnableLineSelection(bool enable) const;
    void EnableArcSelection(bool enable) const;
    void EnableElArcSelection(bool enable) const;
    void EnableSplineSelection(bool enable) const;
    void EnableSplinePathSelection(bool enable) const;
    void EnableNodeLabelSelection(bool enable) const;
    void EnableNodePointSelection(bool enable) const;
    void EnableDetailSelection(bool enable) const;

    void EnableLabelHover(bool enable) const;
    void EnablePointHover(bool enable) const;
    void EnableLineHover(bool enable) const;
    void EnableArcHover(bool enable) const;
    void EnableElArcHover(bool enable) const;
    void EnableSplineHover(bool enable) const;
    void EnableSplinePathHover(bool enable) const;
    void EnableNodeLabelHover(bool enable) const;
    void EnableNodePointHover(bool enable) const;
    void EnableDetailHover(bool enable) const;

    void signalZoomToAreaActive(bool enable) const;
    void signalZoomPanActive(bool enable) const;

protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    virtual void changeEvent(QEvent* event) Q_DECL_OVERRIDE;
    virtual void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    virtual void customEvent(QEvent * event) Q_DECL_OVERRIDE;
    virtual void CleanLayout() Q_DECL_OVERRIDE;
    virtual void PrepareSceneList() Q_DECL_OVERRIDE;
    virtual void ExportToCSVData(const QString &fileName, const DialogExportToCSV &dialog) Q_DECL_FINAL;

private slots:
    void zoomScaleChanged(qreal scale);
    void MouseMove(const QPointF &scenePos);
    void Clear();
    void PatternChangesWereSaved(bool saved);
    void LastUsedTool();
    void FullParseFile();
    void SetEnabledGUI(bool enabled);
    void GlobalChangePP(const QString &patternPiece);
    void ToolBarStyles();
    void showLayoutPages(int index);
    void Preferences();
#if defined(Q_OS_MAC)
    void CreateMeasurements();
#endif
    void exportLayoutAs();
    void exportPiecesAs();

    void handleArrowTool();
    void handlePointAtDistanceAngleTool(bool checked);
    void handleAlongLineTool(bool checked);
    void handleMidpointTool(bool checked);
    void handleShoulderPointTool(bool checked);
    void handleNormalTool(bool checked);
    void handleBisectorTool(bool checked);
    void handleHeightTool(bool checked);
    void handleTriangleTool(bool checked);
    void handleLineIntersectAxisTool(bool checked);
    void handlePointOfContactTool(bool checked);
    void handlePointOfIntersectionTool(bool checked);

    void handleLineTool(bool checked);
    void handleLineIntersectTool(bool checked);

    void handleCurveTool(bool checked);
    void handleSplineTool(bool checked);
    void handleCurveWithControlPointsTool(bool checked);
    void handleSplineWithControlPointsTool(bool checked);
    void handlePointAlongCurveTool(bool checked);
    void handlePointAlongSplineTool(bool checked);
    void handleCurveIntersectCurveTool(bool checked);
    void handleCurveIntersectAxisTool(bool checked);

    void handleArcTool(bool checked);
    void handlePointAlongArcTool(bool checked);
    void handlePointFromArcAndTangentTool(bool checked);
    void handleArcWithLengthTool(bool checked);
    void handleArcIntersectAxisTool(bool checked);
    void handlePointOfIntersectionArcsTool(bool checked);
    void handlePointOfIntersectionCirclesTool(bool checked);
    void handlePointFromCircleAndTangentTool(bool checked);

    void handleEllipticalArcTool(bool checked);

    void handleGroupTool(bool checked);
    void handleRotationTool(bool checked);
    void handleMirrorByLineTool(bool checked);
    void handleMirrorByAxisTool(bool checked);
    void handleMoveTool(bool checked);
    void handleTrueDartTool(bool checked);

    void handleInternalPathTool(bool checked);
    void handleAnchorPointTool(bool checked);
    void handleInsertNodeTool(bool checked);

    void handlePatternPieceTool(bool checked);
    void handleUnionDetailsTool(bool checked);

    void handleNewLayout(bool checked);

    void draftMode_Action(bool checked);
    void ActionDetails(bool checked);
    void ActionLayout(bool checked);

    void New();
    bool SaveAs();
    bool Save();
    void Open();

    void ClosedDialogUnionDetails(int result);
    void ClosedDialogGroup(int result);
    void ClosedDialogInternalPath(int result);
    void ClosedDialogAnchorPoint(int result);
    void ClosedDialogInsertNode(int result);

    void zoomToPrevious();
    void zoomToArea();
    void zoomPan();

    void LoadIndividual();
    void LoadMultisize();
    void UnloadMeasurements();
    void ShowMeasurements();
    void MeasurementsChanged(const QString &path);
    void SyncMeasurements();
#if defined(Q_OS_MAC)
    void OpenAt(QAction *where);
#endif //defined(Q_OS_MAC)

    void ChangedSize(const QString &text);
    void ChangedHeight(const QString &text);

private:
    Q_DISABLE_COPY(MainWindow)
    /** @brief ui keeps information about user interface */
    Ui::MainWindow                   *ui;

    QFileSystemWatcher               *watcher;

    /** @brief tool current tool */
    Tool                              currentTool;

    /** @brief tool last used tool */
    Tool                              lastUsedTool;

    /** @brief sceneDraw draw scene. */
    VMainGraphicsScene               *sceneDraw;

    /** @brief sceneDetails details scene. */
    VMainGraphicsScene               *sceneDetails;

    /** @brief mouseCoordinate pointer to label who show mouse coordinate. */
    QPointer<QLabel>                  mouseCoordinate;

    /** @brief helpLabel help show tooltip. */
    QLabel                           *helpLabel;

    /** @brief isInitialized true after first show window. */
    bool                              isInitialized;

    /** @brief mChanges true if measurement file was changed. */
    bool                              mChanges;
    bool                              mChangesAsked;

    bool                              patternReadOnly;

    QPointer<DialogVariables>         dialogTable;
    QSharedPointer<DialogTool>        dialogTool;
    QPointer<DialogHistory>           dialogHistory;

    /** @brief comboBoxDraws comboc who show name of pattern peaces. */
    QComboBox                        *comboBoxDraws;
    QLabel                           *patternPieceLabel;

    /** @brief mode keep current draw mode. */
    Draw                              mode;

    /** @brief currentDrawIndex save current selected pattern peace. */
    qint32                            currentDrawIndex;

    /** @brief currentToolBoxIndex save current set of tools. */
    qint32                            currentToolBoxIndex;

    bool                              isToolOptionsDockVisible;
    bool                              isGroupsDockVisible;
    bool                              isLayoutsDockVisible;
    bool                              isToolboxDockVisible;

    /** @brief drawMode true if we current draw scene. */
    bool                              drawMode;

    enum { MaxRecentFiles = 5 };
    QAction                          *recentFileActs[MaxRecentFiles];
    QAction                          *separatorAct;

    QLabel                           *leftGoToStage;
    QLabel                           *rightGoToStage;
    QTimer                           *autoSaveTimer;
    bool                              guiEnabled;
    QPointer<QComboBox>               gradationHeights;
    QPointer<QComboBox>               gradationSizes;
    QPointer<QLabel>                  gradationHeightsLabel;
    QPointer<QLabel>                  gradationSizesLabel;
    VToolOptionsPropertyBrowser      *toolProperties;
    VWidgetGroups                    *groupsWidget;
    VWidgetDetails                   *patternPiecesWidget;
    std::shared_ptr<VLockGuard<char>> lock;

    QList<QToolButton*>               toolButtonPointerList;
    QDoubleSpinBox                   *zoomScaleSpinBox;
    PenStyleToolBar                  *m_penStyleToolBar;

    void                              SetDefaultHeight();
    void                              SetDefaultSize();

    void                              initStatusToolBar();
    void                              initModesToolBar();
    void                              initPenStyleToolBar();
    void                              initDraftToolBar();
    void                              initToolsToolBar();
    void                              InitToolButtons();

    void                              handlePointsMenu();
    void                              handleLinesMenu();
    void                              handleArcsMenu();
    void                              handleCurvesMenu();
    void                              handleCirclesMenu();
    void                              handleEllipsesMenu();
    void                              handleModifyMenu();
    void                              handlePatternPiecesMenu();
    void                              handleDetailsMenu();
    void                              handleLayoutMenu();
    void                              handleImagesMenu();

    void                              CancelTool();

    void               SetEnableWidgets(bool enable);
    void               setEnableTools(bool enable);
    void               SetLayoutModeActions();

    void               SaveCurrentScene();
    void               RestoreCurrentScene();
    void               MinimumScrollBar();

    template <typename Dialog, typename Func>
    void               SetToolButton(bool checked, Tool t, const QString &cursor, const QString &toolTip,
                                     Func closeDialogSlot);
    template <typename Dialog, typename Func, typename Func2>
    void               SetToolButtonWithApply(bool checked, Tool t, const QString &cursor, const QString &toolTip,
                                              Func closeDialogSlot, Func2 applyDialogSlot);
    template <typename DrawTool>
    void               ClosedDialog(int result);

    template <typename DrawTool>
    void ClosedDialogWithApply(int result, VMainGraphicsScene *scene);
    template <typename DrawTool>
    void ApplyDialog(VMainGraphicsScene *scene);
    template <typename DrawTool>
    void ClosedDrawDialogWithApply(int result);
    template <typename DrawTool>
    void ApplyDrawDialog();
    template <typename DrawTool>
    void ClosedDetailsDialogWithApply(int result);
    template <typename DrawTool>
    void ApplyDetailsDialog();

    bool               SavePattern(const QString &fileName, QString &error);
    void               AutoSavePattern();
    void               setCurrentFile(const QString &fileName);

    void               ReadSettings();
    void               WriteSettings();

    bool               MaybeSave();
    void               UpdateRecentFileActions();
    void               createMenus();
    void               CreateActions();
    void               InitAutoSave();
    QString            PatternPieceName(const QString &text);
    QString            CheckPathToMeasurements(const QString &patternPath, const QString &path);
    QComboBox          *SetGradationList(QLabel *label, const QStringList &list);
    void               ChangePP(int index, bool zoomBestFit = true);
    /**
     * @brief EndVisualization try show dialog after and working with tool visualization.
     */
    void               EndVisualization(bool click = false);
    void               zoomFirstShow();
    void               UpdateHeightsList(const QStringList &list);
    void               UpdateSizesList(const QStringList &list);

    void               addDocks();
    void               InitDocksContain();
    bool               OpenNewSeamly2D(const QString &fileName = QString())const;
    void               FileClosedCorrect();
    QStringList        GetUnlokedRestoreFileList()const;

    void               AddPP(const QString &PPName);
    QPointF            StartPositionNewPP() const;

    void               InitScenes();

    QSharedPointer<VMeasurements> OpenMeasurementFile(const QString &path);
    bool               LoadMeasurements(const QString &path);
    bool               UpdateMeasurements(const QString &path, int size, int height);
    void               CheckRequiredMeasurements(const VMeasurements *m);

    void               ReopenFilesAfterCrash(QStringList &args);
    void               DoExport(const VCommandLinePtr& expParams);

    bool               SetSize(const QString &text);
    bool               SetHeight(const QString & text);

    QString            GetPatternFileName();
    QString            GetMeasurementFileName();

    void               UpdateWindowTitle();

    bool               IgnoreLocking(int error, const QString &path);

    void ToolSelectPoint() const;
    void ToolSelectPointByPress() const;
    void ToolSelectPointByRelease() const;
    void ToolSelectSpline() const;
    void ToolSelectSplinePath() const;
    void ToolSelectArc() const;
    void ToolSelectPointArc() const;
    void ToolSelectCurve() const;
    void ToolSelectAllDrawObjects() const;
    void ToolSelectOperationObjects() const;
    void ToolSelectGroupObjects() const;
    void ToolSelectDetail() const;
};

#endif // MAINWINDOW_H
