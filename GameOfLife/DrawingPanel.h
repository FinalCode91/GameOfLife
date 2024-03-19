#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include <vector>


class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoardRef);
	virtual ~DrawingPanel();

	void SetGridSize(int newSize);

protected:
	void OnPaint(wxPaintEvent& event);
	void OnMouseUp(wxMouseEvent& event);

private:
	int gridSize = 15;
	std::vector<std::vector<bool>>& gameBoard;

	wxDECLARE_EVENT_TABLE();
};

#endif

