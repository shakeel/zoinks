// ========================================================================================
//	TBehavior.cpp			   Copyright (C) 2001-2002 Mike Voydanoff. All rights reserved.
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

#include "TBehavior.h"


TBehavior::TBehavior()
	:	fOwner(NULL),
		fNextBehavior(NULL)
{
}


TBehavior::~TBehavior()
{
}


void TBehavior::SetOwner(TCommandHandler* owner, TBehavior* nextBehavior)
{
	fOwner = owner;
	fNextBehavior = nextBehavior;
}


void TBehavior::DoSetupMenu(TMenu* menu)
{
}


bool TBehavior::DoCommand(TCommandHandler* sender, TCommandHandler* receiver, TCommandID command)
{
	return false;	// not handled
}


bool TBehavior::DoKeyDown(KeySym key, TModifierState state, const char* string)
{
	return false;	// not handled
}


bool TBehavior::DoKeyUp(KeySym key, TModifierState state, const char* string)
{
	return false;	// not handled
}


bool TBehavior::DoMouseDown(const TPoint& point, TMouseButton button, TModifierState state)
{
	return false;	// not handled
}


bool TBehavior::DoMouseUp(const TPoint& point, TMouseButton button, TModifierState state)
{
	return false;	// not handled
}


bool TBehavior::DoMouseMoved(const TPoint& point, TModifierState state)
{
	return false;	// not handled
}


bool TBehavior::DoMouseEnter(const TPoint& point, TModifierState state)
{
	return false;	// not handled
}


bool TBehavior::DoMouseLeave(const TPoint& point, TModifierState state)
{
	return false;	// not handled
}


bool TBehavior::DoScrollWheel(bool down)
{
	return false;	// not handled
}

