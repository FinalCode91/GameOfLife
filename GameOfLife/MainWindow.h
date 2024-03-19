#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include <wx/timer.h>
#include "DrawingPanel.h"
#include <vector>

class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title);
	virtual ~MainWindow();

	void OnPlay(wxCommandEvent& event);
	void OnPause(wxCommandEvent& event);
	void OnNext(wxCommandEvent& event);
	void OnTrash(wxCommandEvent& event);
	int CalculateNeighborCount(int row, int col);
	void NextGeneration();
	void ClearBoard();
	void OnTimer(wxTimerEvent& event);

private:
	DrawingPanel* drawingPanel;
	std::vector<std::vector<bool>> gameBoard;
	int gridSize = 15;
	int generation = 0;
	int livingCells = 0;
	wxStatusBar* statusBar;
	wxToolBar* toolBar;
	wxTimer* timer;
	int timerInterval = 50;

	void InitializeGrid();
	void OnSizeChange(wxSizeEvent& event);
	void UpdateStatusBar();
	
	wxDECLARE_EVENT_TABLE();
};

#endif