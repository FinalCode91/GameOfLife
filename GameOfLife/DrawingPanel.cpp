#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoardRef)
	: wxPanel(parent), gridSize(15), gameBoard(gameBoardRef)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

DrawingPanel::~DrawingPanel()
{

}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();

	wxSize size = this->GetSize();
	int cellWidth = size.GetWidth() / gridSize;
	int cellHeight = size.GetHeight() / gridSize;

	int col = x / cellWidth;
	int row = y / cellHeight;

	if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
	{
		gameBoard[row][col] = !gameBoard[row][col];
		Refresh();
	}
}

void DrawingPanel::SetGridSize(int newSize)
{
	gridSize = newSize;
	Refresh();
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) return;

	context->SetPen(*wxGREEN_PEN);

	wxSize size = this->GetSize();
	double cellWidth = size.GetWidth() / double(gridSize);
	double cellHeight = size.GetHeight() / double(gridSize);

	for (int x = 0; x < gridSize; ++x)
	{
		for (int y = 0; y < gridSize; ++y)
		{
			if (gameBoard[x][y])
			{
				context->SetBrush(*wxLIGHT_GREY_BRUSH);
			}
			else
			{
				context->SetBrush(*wxWHITE_BRUSH);
			}

			context->DrawRectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
		}

	}

	delete context;
}


