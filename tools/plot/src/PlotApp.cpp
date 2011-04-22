/*
 * Copyright (C) 2011 Robotics at Maryland
 * Copyright (C) 2011 Jonathan Wonders <jwonders@umd.edu>
 * All rights reserved.
 *
 * Author: Jonathan Wonders <jwonders@umd.edu>
 * File:  tools/plot/src/PlotApp.cpp
 */

#include "../include/PlotApp.h"
#include "../include/PlotPanel.h"
#include "../include/TelemetryPanel.h"
#include "core/include/EventHub.h"
#include "network/include/NetworkHub.h"


IMPLEMENT_APP(PlotApp)

bool PlotApp::OnInit()
{
    /* start the network hub */
    /* note: this is currently using the default constructor */
    m_eventHub = core::EventHubPtr(new network::NetworkHub());

    // create settings for what the panels can do
    wxAuiPaneInfo defaultInfo = wxAuiPaneInfo();
    defaultInfo.Gripper(true);
    defaultInfo.GripperTop(true);
    defaultInfo.MinSize(240, 240);
    defaultInfo.Movable(true);
    defaultInfo.Resizable(true);
    defaultInfo.CaptionVisible(true);
    defaultInfo.Floatable(true);

    // initialize the frame
    PlotFrame *frame = new PlotFrame( wxT("R@M Realtime Plotting"), wxPoint(0, 0), wxSize(1024, 768) );
    frame->SetMinSize(wxSize(480,480));

    // Set up the inner windows
    PlotPanel *depthPanel = new DepthPanel(frame, m_eventHub);
    wxAuiPaneInfo depthPanelInfo = wxAuiPaneInfo(defaultInfo);
    depthPanelInfo.Caption(wxT("Depth Plot"));
    depthPanelInfo.Left();

    PlotPanel *depthRatePanel = new DepthRatePanel(frame, m_eventHub);
    wxAuiPaneInfo depthRatePanelInfo = wxAuiPaneInfo(defaultInfo);
    depthRatePanelInfo.Caption(wxT("Depth Rate Plot"));
    depthRatePanelInfo.Left();

    PlotPanel *positionPanel = new VelocityPanel(frame, m_eventHub);
    wxAuiPaneInfo positionPanelInfo = wxAuiPaneInfo(defaultInfo);
    positionPanelInfo.Caption(wxT("Position Plot"));
    positionPanelInfo.Right();

    PlotPanel *velocityPanel = new PositionPanel(frame, m_eventHub);
    wxAuiPaneInfo velocityPanelInfo = wxAuiPaneInfo(defaultInfo);
    velocityPanelInfo.Caption(wxT("Velocity Plot"));
    velocityPanelInfo.Right();

    PlotPanel *testPanel = new TestPanel(frame, m_eventHub);
    wxAuiPaneInfo testPanelInfo = wxAuiPaneInfo(defaultInfo);
    testPanelInfo.Caption(wxT("Test Panel (not event based)"));
    testPanelInfo.Right();

    TelemetryPanel *telemetryPanel = new TelemetryPanel(frame, m_eventHub);
    wxAuiPaneInfo telemetryPanelInfo = wxAuiPaneInfo(defaultInfo);
    telemetryPanelInfo.Center();

    // add the panels
    frame->addPanel(depthPanel, depthPanelInfo);
    frame->addPanel(depthRatePanel, depthRatePanelInfo);
    frame->addPanel(positionPanel, positionPanelInfo);
    frame->addPanel(velocityPanel, velocityPanelInfo);
    frame->addPanel(testPanel, testPanelInfo);
    frame->addPanel(telemetryPanel, telemetryPanelInfo);

    // show it
    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

PlotFrame::PlotFrame(const wxString& title, const wxPoint& pos,
                     const wxSize& size) :
    wxFrame(0, -1, title, pos, size)
{
    // use wxAUI to manage the window
    m_mgr.SetManagedWindow(this);

    // Set up the menus
    m_menuFile = new wxMenu();
    m_menuFile->Append(ID_Quit, _("E&xit"));

    m_menuBar = new wxMenuBar();
    m_menuBar->Append(m_menuFile, _("&File"));

    SetMenuBar(m_menuBar);

    // update the window manager
    m_mgr.Update();
}

PlotFrame::~PlotFrame()
{
    m_mgr.UnInit();
}

void PlotFrame::onQuit(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.UnInit();
    Destroy();
    Close(true);
}

void PlotFrame::addPanel(wxWindow *panel, wxAuiPaneInfo& info)
{
    m_mgr.AddPane(panel, info);
    m_mgr.Update();
}
