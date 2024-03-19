#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_MENU(10001, MainWindow::OnPlay)
	EVT_MENU(10002, MainWindow::OnPause)
	EVT_MENU(10003, MainWindow::OnNext)
	EVT_MENU(10004, MainWindow::OnTrash)
	EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(200,200))
{
	drawingPanel = new DrawingPanel(this, gameBoard);
	InitializeGrid();

	statusBar = CreateStatusBar();
	UpdateStatusBar();

	timer = new wxTimer(this, wxID_ANY);

	toolBar = CreateToolBar();
	const int playToolId = 10001, pauseToolId = 10002, nextToolId = 10003, trashToolId = 10004;


	toolBar->AddTool(10001, wxT("Play"), wxBitmap(play_xpm), wxT("Start Animation"));
	toolBar->AddTool(10002, wxT("Pause"), wxBitmap(pause_xpm), wxT("Pause Animation"));
	toolBar->AddTool(10003, wxT("Next"), wxBitmap(next_xpm), wxT("Next Generation"));
	toolBar->AddTool(10004, wxT("Trash"), wxBitmap(trash_xpm), wxT("Clear Grid"));

	toolBar->Realize();
	this->Layout();
}

MainWindow::~MainWindow()
{
	delete timer;
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	wxSize newSize = this->GetSize();
	drawingPanel->SetSize(newSize);
	event.Skip();
}

void MainWindow::InitializeGrid()
{
	gameBoard.resize(gridSize, std::vector<bool>(gridSize, false));
	drawingPanel->SetGridSize(gridSize);
	UpdateStatusBar();
}

void MainWindow::UpdateStatusBar()
{
	wxString statusText;
	statusText.Printf(wxT("Generations: %d, Living Cells: %d"), generation, livingCells);
	statusBar->SetStatusText(statusText);
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
	timer->Start(timerInterval);
}

void MainWindow::OnPause(wxCommandEvent& event)
{
	timer->Stop();
}

void MainWindow::OnNext(wxCommandEvent& event)
{
	NextGeneration();
}

void MainWindow::OnTrash(wxCommandEvent& event)
{
	ClearBoard();
}

int MainWindow::CalculateNeighborCount(int row, int col)
{
	int count = 0;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0)
				continue;

			int newRow = row + i;
			int newCol = col + j;

			if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize)
			{
				if (gameBoard[newRow][newCol])
					count++;
			}
		}
	}
	return count;
}

void MainWindow::NextGeneration()
{
	std::vector<std::vector<bool>> sandbox(gridSize, std::vector<bool>(gridSize, false));
	int newLivingCells = 0;

	for (int row = 0; row < gridSize; ++row)
	{
		for (int col = 0; col < gridSize; ++col)
		{
			int livingNeighbors = CalculateNeighborCount(row, col);
			bool willLive = false;

			if (gameBoard[row][col])
			{
				if (livingNeighbors == 2 || livingNeighbors == 3)
				{
					willLive = true;
				}
			}

			sandbox[row][col] = willLive;
			if (willLive)
			{
				++newLivingCells;
			}
		}
	}

	std::swap(gameBoard, sandbox);
	livingCells = newLivingCells;
	++generation;

	UpdateStatusBar();
	drawingPanel->Refresh();
}

void MainWindow::ClearBoard()
{
	for (int row = 0; row < gridSize; ++row)
	{
		for (int col = 0; col < gridSize; ++col)
		{
			gameBoard[row][col] = false;
		}
	}

	livingCells = 0;
	generation = 0;

	UpdateStatusBar();

	drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
	NextGeneration();
}

