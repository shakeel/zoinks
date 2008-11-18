// ========================================================================================
//	TRadio.cpp				 	Copyright (C) 2001-2002 Mike Lockwood. All rights reserved.
// ========================================================================================
/*
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "FWCommon.h"

#include "TRadio.h"
#include "TDrawContext.h"
#include "TPixmap.h"

#include "Pixmaps/RadioOff.xpm"
#include "Pixmaps/RadioOn.xpm"
#include "Pixmaps/RadioOffPressed.xpm"
#include "Pixmaps/RadioOnPressed.xpm"
#include "Pixmaps/RadioOffDisabled.xpm"
#include "Pixmaps/RadioOnDisabled.xpm"

static TPixmap* sOffPixmap = NULL;
static TPixmap* sOnPixmap = NULL;
static TPixmap* sPressedOffPixmap = NULL;
static TPixmap* sPressedOnPixmap = NULL;
static TPixmap* sDisabledOffPixmap = NULL;
static TPixmap* sDisabledOnPixmap = NULL;

TRadio::TRadio(TWindow* parent, const TRect& bounds, const TChar* title, TCommandID commandID)
	:	TWindow(parent, bounds, kChildWindow),
		fTitle(title),
		fCommandID(commandID),
		fOn(false),
		fPressed(false),
		fEnabled(true),
		fTrackingMouse(false)
{
	SetBackColor(kLightGrayColor);

	if (!sOffPixmap)
		sOffPixmap = new TPixmap(RadioOff_xpm);
	if (!sOnPixmap)
		sOnPixmap = new TPixmap(RadioOn_xpm);
	if (!sPressedOffPixmap)
		sPressedOffPixmap = new TPixmap(RadioOffPressed_xpm);
	if (!sPressedOnPixmap)
		sPressedOnPixmap = new TPixmap(RadioOnPressed_xpm);
	if (!sDisabledOffPixmap)
		sDisabledOffPixmap = new TPixmap(RadioOffDisabled_xpm);
	if (!sDisabledOnPixmap)
		sDisabledOnPixmap = new TPixmap(RadioOnDisabled_xpm);
}


TRadio::~TRadio()
{
}


void TRadio::Draw(TRegion* clip)
{
	TDrawContext	context(this, clip);
	
	TPixmap* pixmap = (fEnabled ?
							(fPressed ? (fOn ? sPressedOnPixmap : sPressedOffPixmap) : 
										(fOn ? sOnPixmap : sOffPixmap)) :
							(fOn ? sDisabledOnPixmap : sDisabledOffPixmap));

	ASSERT(pixmap);

	TRect	bounds;
	GetLocalBounds(bounds);

	TRect r(bounds.left, bounds.top, bounds.left + pixmap->GetWidth() + 4, bounds.top + bounds.GetHeight());
	context.EraseRect(r);
	
	context.DrawPixmap(pixmap, TPoint(bounds.left + 2, bounds.top + (bounds.GetHeight() - pixmap->GetHeight()) / 2));

	TRect	textBounds(bounds);
	textBounds.left = r.right;

	context.SetForeColor(fEnabled ? fForeColor : kDarkGrayColor);
	context.DrawTextBox(fTitle, fTitle.GetLength(), textBounds, kTextAlignLeft);
}


void TRadio::DoMouseDown(const TPoint& point, TMouseButton button, TModifierState state)
{
	if (button == kLeftButton && fEnabled)
	{
		fPressed = true;
		fTrackingMouse = true;
		Redraw();
	}
}


void TRadio::DoMouseUp(const TPoint& point, TMouseButton button, TModifierState state)
{
	if (button == kLeftButton && fTrackingMouse)
	{
		bool wasOn = fOn;
		
		fOn = true;
		fPressed = false;
		Redraw();

		fTrackingMouse = false;
		
		if (!wasOn)
			HandleCommand(this, this, fCommandID);	
	}
}


void TRadio::DoMouseMoved(const TPoint& point, TModifierState state)
{
	if (fTrackingMouse)
	{
		TRect bounds;
		GetLocalBounds(bounds);

		if (bounds.Contains(point) != fPressed)
		{
			fPressed = !fPressed;
			Redraw();
		}
	}
}


void TRadio::SetOn(bool on)
{
	if (fOn != on)
	{
		fOn = on;
		if (IsCreated())
			Redraw();
	}
}	


void TRadio::SetEnabled(bool enabled)
{
	if (fEnabled != enabled)
	{
		fEnabled = enabled;
		if (IsCreated())
			Redraw();
	}
}	

