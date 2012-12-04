/*
 * Copyright 2001, 2004, 2011 C Thing Software
 *
 * This file is part of Meazure.
 * 
 * Meazure is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Meazure is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Meazure.  If not, see <http://www.gnu.org/licenses/>.
 */

/// @file
/// @brief Header file for the application view.

#pragma once

#include "DataDisplay.h"
#include "Magnifier.h"
#include "Preferences.h"
#include "Profile.h"
#include "Tool.h"
#include "Timer.h"


/// The view class for the application. There is only a single view
/// in this app and it is owned directly by the application frame window.
///
class CChildView : public CWnd
{
public:
    static const bool   kDefToolbarVisible;     ///< Indicates if the toolbar is visible by default.
    static const bool   kDefStatusbarVisible;   ///< Indicates if the status bar is visible by default.
    static const bool   kDefToolInfoVisible;    ///< Indicates if the measurement information section is visible by default.
    static const bool   kDefScreenInfoVisible;  ///< Indicates if the screen information section is visible by default.
    static const bool   kDefMagnifierVisible;   ///< Indicates if the magnifier is visible by default.


    /// Constructs the view.
    ///
    CChildView();

    /// Destroys the view.
    ///
    virtual ~CChildView();


    /// A number of tools (e.g. pointer tool, magnifier) need to track
    /// the pointer position. This method is called by the application
    /// class when the system mouse hook is called. The method forwards
    /// the mouse hook information to the tools that are interested.
    ///
    /// @param wParam   [in] Message id.
    /// @param lParam   [in] MOUSEHOOKSTRUCT.
    ///
    void    OnMouseHook(WPARAM wParam, LPARAM lParam);


    /// Persists the state of the view to the specified profile object.
    /// In addition, this method calls the SaveProfile method on all
    /// objects it contains.
    ///
    /// @param profile      [in] Profile object into which the state
    ///                     is persisted.
    ///
    void    SaveProfile(MeaProfile& profile);

    /// Restores the state of the view from the specified profile object.
    /// In addition, this method calls the LoadProfile method on all
    /// objects it contains.
    ///
    /// @param profile      [in] Profile object from which the state
    ///                     is restored.
    ///
    void    LoadProfile(MeaProfile& profile);

    /// Called when the application master reset is initiated. This method
    /// restores the view to its default state and calls the MasterReset
    /// method on all contained objects.
    ///
    void    MasterReset();

    /// This method handles the processing of any files specified on the
    /// command-line or specified in preferences. The following processing
    /// is performed:
    /// <ol>
    ///     <li>If a profile file is specified on the command-line, that file
    ///         is loaded.</li>
    ///     <li>If no file is specified on the command-line, or the file is not
    ///         a profile, the preferences are checked to see if a startup profile
    ///         file has been specified. If it has, that file is loaded.</li>
    ///     <li>If a position log file is specified on the command-line, that file
    ///         is loaded.</li>
    /// </ol>
    ///
    /// @param cmdLineFile      [in] File pathname specified on the command-line.
    ///
    void    LoadStartupFile(const CString& cmdLineFile) const;

    /// Called at startup right before the app windows are shown. Shows/hides
    /// the portions of the view according to the registry profile.
    ///
    void    InitView();

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChildView)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

    /// @fn PreCreateWindow(CREATESTRUCT& cs)
    /// Called before the window is created. Sets up the View window class.
    /// @param cs       [in] Window creation information structure.
    /// @return TRUE if the pre-creation process was successful.

protected:
    /// Called when new units are selected from the Units menu.
    /// @param nID      [in] ID of the Units menu item that was selected.
    afx_msg void OnUnits(UINT nID);

    /// Called when the degrees or radians units are selected.
    /// @param nID      [in] ID of the Units menu angle item that was selected.
    afx_msg void OnAngles(UINT nID);

    /// Called when a radio tool is selected.
    /// @param nID      [in] ID of the tool menu item.
    afx_msg void OnRadioTool(UINT nID);

    /// Called when a new color display format is requested.
    /// @param nID      [in] ID of the color format menu item.
    afx_msg void OnColorFmt(UINT nID);

    /// Called when data is entered into a field in the data display or
    /// a spin button is used. Tells the current tool to set a new position.
    /// @param wParam   [in] New data value in pixels.
    /// @param lParam   [in] Data field that we modified.
    /// @return Always returns 0.
    afx_msg LRESULT OnDataChange(WPARAM wParam, LPARAM lParam);

    /// Called when the Apply button is pressed on the preferences dialog.
    /// @param wParam   [in] Not used.
    /// @param lParam   [in] Not used.
    /// @return Always returns 0.
    afx_msg LRESULT OnPrefsApply(WPARAM wParam, LPARAM lParam);

    /// Called when the show calibration preferences message is received.
    /// This message is issued by the resolution calibration warning
    /// dialogs and the calibration warning button.
    /// @param wParam   [in] Not used.
    /// @param lParam   [in] Not used.
    /// @return Always returns 0.
    afx_msg LRESULT OnShowCalPrefs(WPARAM wParam, LPARAM lParam);

    /// Called when the magnifier wants the current position.
    /// @param wParam   [in] Not used.
    /// @param lParam   [in] POINT structure to fill with current position.
    /// @return Always returns TRUE.
    afx_msg LRESULT OnGetPosition(WPARAM wParam, LPARAM lParam);

    /// Called when the region snapshot timer expires.
    /// @param wParam   [in] Not used
    /// @param lParam   [in] Not used.
    /// @return Always returns 0.
    afx_msg LRESULT OnHPTimer(WPARAM wParam, LPARAM lParam);

    //{{AFX_MSG(CChildView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnUpdateUnits(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAngles(CCmdUI* pCmdUI);
    afx_msg void OnUpdateRadioTool(CCmdUI* pCmdUI);
    afx_msg void OnDestroy();
    afx_msg void OnEditCopy();
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    afx_msg void OnEditClear();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);
    afx_msg void OnInvertY();
    afx_msg void OnUpdateInvertY(CCmdUI* pCmdUI);
    afx_msg void OnOrigin();
    afx_msg void OnResetOrigin();
    afx_msg void OnRuler();
    afx_msg void OnUpdateRuler(CCmdUI* pCmdUI);
    afx_msg void OnPreferences();
    afx_msg void OnMagnifier();
    afx_msg void OnUpdateMagnifier(CCmdUI* pCmdUI);
    afx_msg void OnShowMagGrid();
    afx_msg void OnUpdateShowMagGrid(CCmdUI* pCmdUI);
    afx_msg void OnScreenInfo();
    afx_msg void OnUpdateScreenInfo(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorFmt(CCmdUI* pCmdUI);
    afx_msg void OnRunState();
    afx_msg void OnUpdateRunState(CCmdUI* pCmdUI);
    afx_msg void OnScreenGrid();
    afx_msg void OnUpdateScreenGrid(CCmdUI* pCmdUI);
    afx_msg void OnScreenGridSpacing();
    afx_msg void OnSaveProfile();
    afx_msg void OnLoadProfile();
    afx_msg void OnCopyRegion();
	afx_msg void OnGrabRegion();
    afx_msg void OnUpdateCopyRegion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGrabRegion(CCmdUI* pCmdUI);
    afx_msg void OnToolInfo();
    afx_msg void OnUpdateToolInfo(CCmdUI* pCmdUI);
    afx_msg void OnCollapse();
    afx_msg void OnUpdateCollapse(CCmdUI* pCmdUI);
    afx_msg void OnFindCrosshair();
    afx_msg void OnUpdateFindCrosshair(CCmdUI* pCmdUI);
    afx_msg void OnRecordPosition();
    afx_msg void OnDeletePositions();
    afx_msg void OnUpdateDeletePositions(CCmdUI* pCmdUI);
    afx_msg void OnLoadPositions();
    afx_msg void OnSavePositions();
    afx_msg void OnSavePositionsAs();
    afx_msg void OnUpdateSavePositions(CCmdUI* pCmdUI);
    afx_msg void OnManagePositions();
    afx_msg void OnZoomIn();
    afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
    afx_msg void OnZoomOut();
    afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
    afx_msg void OnHideCrosshairs();
    afx_msg void OnUpdateHideCrosshairs(CCmdUI* pCmdUI);
    afx_msg void OnDefineCustomUnits();
    afx_msg void OnUpdateCustomUnits(CCmdUI* pCmdUI);
    afx_msg void OnCustomUnits();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    /// @fn OnCreate(LPCREATESTRUCT lpCreateStruct)
    /// Creates the view and the data display. Also enables the
    /// appropriate tools.
    /// @param lpCreateStruct   [in] Window creation structure.
    /// @return 0 if the creation was successful.

    /// @fn OnUpdateUnits(CCmdUI* pCmdUI)
    /// Updates the radio button state on the Units menu right
    /// before the menu is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateAngles(CCmdUI* pCmdUI)
    /// Updates the radio button state on the Units menu right
    /// before the menu is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateRadioTool(CCmdUI* pCmdUI)
    /// Called right before the Tool menu is displayed to update
    /// its radio state.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnDestroy()
    /// Disables all tools including the magnifier and destroys the window.

    /// @fn OnEditCopy()
    /// Wires the application Edit menu Copy item into the data display text
    /// field that has the keyboard focus so that its contents are copied to
    /// the clipboard.

    /// @fn OnEditCut()
    /// Wires the application Edit menu Cut item into the data display text
    /// field that has the keyboard focus so that its contents are cut into
    /// the clipboard.

    /// @fn OnEditPaste()
    /// Wires the application Edit menu Paste item into the data display text
    /// field that has the keyboard focus so that the clipboard contents are
    /// pasted into the field.

    /// @fn OnEditClear()
    /// Wires the application Edit menu Delete item into the data display text
    /// field that has the keyboard focus so that its contents are deleted.

    /// @fn OnUpdateEditCopy(CCmdUI* pCmdUI)
    /// Updates the application Edit menu Copy item so that its state reflects
    /// the Copy state of the data display text field that has the keyboard focus.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateEditCut(CCmdUI* pCmdUI)
    /// Updates the application Edit menu Cut item so that its state reflects
    /// the Cut state of the data display text field that has the keyboard focus.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateEditPaste(CCmdUI* pCmdUI)
    /// Updates the application Edit menu Paste item so that its state reflects
    /// the Paste state of the data display text field that has the keyboard focus.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateEditClear(CCmdUI* pCmdUI)
    /// Updates the application Edit menu Delete item so that its state reflects
    /// the Delete state of the data display text field that has the keyboard focus.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnInvertY()
    /// Called when the Invert Y menu item is selected. The y-axis inversion is
    /// toggled.

    /// @fn OnUpdateInvertY(CCmdUI* pCmdUI)
    /// Updates the state of the Invert Y menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnOrigin()
    /// Called when the Set Origin menu item is selected. The origin is repositioned
    /// to the current point.

    /// @fn OnResetOrigin()
    /// Called to reset the origin to its default location (0, 0). The default origin
    /// location is (0, 0) at the upper left corner of the screen. In y-axis inversion
    /// is in effect, the origin is located at (0, 0) in the lower left corner of the
    /// screen.

    /// @fn OnRuler()
    /// Called when the ruler menu item is selected to toggle the display of the
    /// screen measurement rulers.

    /// @fn OnUpdateRuler(CCmdUI* pCmdUI)
    /// Updates the state of the ruler menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnPreferences()
    /// Called when the Preferences menu item is selected to bring up the preferences
    /// dialog.

    /// @fn OnMagnifier()
    /// Called when the magnifier menu item is selected to toggle between showing and
    /// hiding the magnifier.

    /// @fn OnUpdateMagnifier(CCmdUI* pCmdUI)
    /// Updates the state of the magnifier item on the view menu before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnShowMagGrid()
    /// Called when the magnifier grid menu item is selected to toggle the display of
    /// the pixel grid on the magnifier window.

    /// @fn OnUpdateShowMagGrid(CCmdUI* pCmdUI)
    /// Updates the state of the magnifier grid menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnScreenInfo()
    /// Called when the Screen Info view menu item is selected. Toggles the display
    /// of the screen information section.

    /// @fn OnUpdateScreenInfo(CCmdUI* pCmdUI)
    /// Updates the state of the Screen Info view menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateColorFmt(CCmdUI* pCmdUI)
    /// Updates the state of the pixel color format menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnRunState()
    /// Called to toggle between paused and running states on the magnifier window.

    /// @fn OnUpdateRunState(CCmdUI* pCmdUI)
    /// Updates the state of the pause button on the magnifier window and on the
    /// menu.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnScreenGrid()
    /// Called to toggle the display of the screen grid.

    /// @fn OnUpdateScreenGrid(CCmdUI* pCmdUI)
    /// Updates the state of the screen grid menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnScreenGridSpacing()
    /// Called when the screen grid spacing menu item is selected. Brings up the
    /// screen grid spacing dialog.

    /// @fn OnSaveProfile()
    /// Saves the current application configuration to the user selected profile file.

    /// @fn OnLoadProfile()
    /// Loads the user specified profile file to set the application configuration.

    /// @fn OnCopyRegion()
    /// Enabled when the Rectangle, Circle or Window tool is selected. Copies the area of
    /// the screen bounded by the tool to the Clipboard.

    /// @fn OnGrabRegion()
    /// Enabled when the Rectangle, Circle or Window tool is selected. Exports the are of the screen
	/// bounded by the tool to a jpeg file. Location as defined in advanced prefs.

    /// @fn OnUpdateCopyRegion(CCmdUI* pCmdUI)
    /// If a tool reports that it has a region that can be copied, the Copy Region menu
    /// item is enabled. Otherwise the menu item is disabled.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnUpdateGrabRegion(CCmdUI* pCmdUI)
    /// If a tool reports that it has a region that can be copied, the Grab Region menu
    /// item is enabled. Otherwise the menu item is disabled.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnToolInfo()
    /// Called when the Tool Info view menu item is selected. Toggles the display of
    /// the measurement section.

    /// @fn OnUpdateToolInfo(CCmdUI* pCmdUI)
    /// Updates the state of the Tool Info menu item before it is displayed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnCollapse()
    /// Called to toggle the application window between a collapsed presentation
    /// and an expanded presentation. Note that the expanded state maintains the
    /// the display state of individual sections of the application so that expanding
    /// the app does not display sections that have been explicitly hidden.

    /// @fn OnUpdateCollapse(CCmdUI* pCmdUI)
    /// Updates the state of the collapse menu item to reflect whether the app is
    /// currently in a collapsed presentation.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnFindCrosshair()
    /// Called to flash the current radio tool's crosshair(s).

    /// @fn OnUpdateFindCrosshair(CCmdUI* pCmdUI)
    /// Updates the flash menu item to reflect whether the tool has crosshairs that
    /// can be flashed.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnRecordPosition()
    /// Called to record the current radio tool's position.

    /// @fn OnDeletePositions()
    /// Called to delete all recorded positions.

    /// @fn OnUpdateDeletePositions(CCmdUI* pCmdUI)
    /// Updates the state of the delete positions menu item to reflect whether there
    /// are any positions that can be deleted.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnLoadPositions()
    /// Called to load a position log file.

    /// @fn OnSavePositions()
    /// Called to save a position log file.

    /// @fn OnSavePositionsAs()
    /// Called to save a position log file with a new pathname.

    /// @fn OnUpdateSavePositions(CCmdUI* pCmdUI)
    /// Called to update the state of the position save menu items. If there are
    /// no positions currently in memory, the menu items are disabled.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnManagePositions()
    /// Called to bring up the position management dialog.

    /// @fn OnZoomIn()
    /// Called to increase magnification on the magnifier window.

    /// @fn OnUpdateZoomIn(CCmdUI* pCmdUI)
    /// Updates the state of the Zoom In menu item before it is displayed.
    /// If the magnifier is at maximum zoom, the Zoom In menu item is disabled.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnZoomOut()
    /// Called to decrease magnification on the magnifier window.

    /// @fn OnUpdateZoomOut(CCmdUI* pCmdUI)
    /// Updates the state of the Zoom Out menu item before it is displayed.
    /// If the magnifier is at minimum zoom, the Zoom Out menu item is disabled.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnHideCrosshairs()
    /// Called to toggle between showing and hiding the tool crosshair(s).

    /// @fn OnUpdateHideCrosshairs(CCmdUI* pCmdUI)
    /// Updates the state of the Hide Crosshairs menu item to reflect whether
    /// the tool crosshair(s) are shown or hidden.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnDefineCustomUnits()
    /// Called when the user selects the Define Custom units menu item.
    /// This method brings up the preferences dialog with the Custom Units
    /// property page selected.

    /// @fn OnUpdateCustomUnits(CCmdUI* pCmdUI)
    /// Updates the custom units menu item to show the name of the custom
    /// units, if custom units have been defined.
    /// @param pCmdUI   [in] UI command object for updating the menu item.

    /// @fn OnCustomUnits()
    /// If custom units have been defined, this method is called to select
    /// them for use.

private:
    /// Determines the desired width of the application menu.
    ///
    /// @return Pixel width to fit all menu items in one row.
    ///
    int     GetMenuWidth();

    /// Applies the preferences currently specified on the Preferences dialog.
    ///
    /// @param prefPage     [in] Index of preference page whose settings
    ///                     should be applied.
    ///
    void    ApplyPreferences(int prefPage = MeaPreferences::kAllPages);

    /// If no sections are shown, nuke the app margins. Otherwise add app margins.
    ///
    void    CheckMargins();
    
    /// Determines whether all sections of the display are hidden.
    ///
    /// @return <b>true</b> if all sections hidden.
    ///
    bool    IsCollapsed() const;

    /// Indicates whether the toolbar is being shown.
    ///
    /// @return <b>true</b> if the toolbar is displayed.
    ///
    bool    IsToolbarVisible() const {
        return GetParentFrame()->GetControlBar(AFX_IDW_TOOLBAR)->IsVisible() ? true : false;
    }

    /// Indicates whether the status bar is being shown.
    ///
    /// @return <b>true</b> if the status bar is displayed.
    ///
    bool    IsStatusbarVisible() const {
        return GetParentFrame()->GetControlBar(AFX_IDW_STATUS_BAR)->IsVisible() ? true : false;
    }

    /// Displays or hides the measurement data section.
    ///
    /// @param enable       [in] <b>true</b> if the section should be shown.
    ///
    void    ViewToolInfo(bool enable);

    /// Displays or hides the screen information section.
    ///
    /// @param enable       [in] <b>true</b> if the section should be shown.
    ///
    void    ViewScreenInfo(bool enable);

    /// Displays or hides the magnifier section
    ///
    /// @param enable       [in] <b>true</b> if the section should be shown.
    ///
    void    ViewMagnifier(bool enable);

    CSize           m_margin;                   ///< Vertical and horizontal margins around major sections.
    bool            m_enabled;                  ///< Used in determining margins when the app is collapsed.
    bool            m_profileMagnifierEnabled;  ///< Indicates if the stored user preference is to show
                                                ///< the magnifier window.
    bool            m_profileScreenEnabled;     ///< Indicates if the stored user preference is to show
                                                ///< the screen information section.
    bool            m_profileRegionEnabled;     ///< Indicates if the stored user preference is to show
                                                ///< the measurement data window.
    MeaDataDisplay  m_dataDisplay;              ///< Tool and screen measurement data display object.
    MeaMagnifier    m_magnifier;                ///< Screen capture and magnifier object.
    MeaPreferences  m_prefs;                    ///< Application preferences.
    CString         m_startupProfile;           ///< Pathname for the startup profile, if any.
	CString         m_screenGrabDirectory;      ///< Pathname for the screen grab directory, if any.
    MeaTimer        m_snapshotTimer;            ///< Timer used in copying a tool's region to the clipboard.
	MeaTimer        m_screenGrabTimer;          ///< Timer used in grabbing a tool's region to file.
    int             m_adjustHeight;             ///< Adjustment used when computing the height of the application, in pixels.

    bool            m_expandToolbar;            ///< Indicates if the toolbar is displayed.
    bool            m_expandStatusbar;          ///< Indicates if the status bar is displayed.
    bool            m_expandMagnifier;          ///< Indicates if the magnifier is displayed.
    bool            m_expandScreenInfo;         ///< Indicates if the screen information section is displayed.
    bool            m_expandToolInfo;           ///< Indicates if the tool measurement section is displayed.
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
