// ========================================================================================
//	TDocument.h		 		   Copyright (C) 2001-2009 Mike Voydanoff. All rights reserved.
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

#ifndef __TDocument__
#define __TDocument__

#include "TWindowContext.h"
#include "TFile.h"

class TDocumentWindow;

class TDocument : public TWindowContext
{
public:
							TDocument(TFile* file);
	virtual					~TDocument();

	virtual void			GetTitle(TString& title) const;

	virtual void			Open(TDocumentWindow* window);
	virtual void			Save();
	virtual void			SaveAs(bool makeCopy);

	virtual void			ReadFromFile(TFile* file);
	virtual void			WriteToFile(TFile* file);
	virtual void			CheckFileModification();
	virtual void			UpdateFileModification();

	virtual void			AddWindow(TTopLevelWindow* window);

	virtual void			SetFile(TFile* file);
	virtual void			SetTitle(const TChar* title);

	virtual bool			AllowClose();

	virtual bool			IsModified() const;
	inline void				SetModified(bool modified) { fModified = modified; }

	virtual void			ShowLine(int line);

	inline const TFile&		GetFile() const { return fFile; }

protected:
	virtual void			DoSetupMenu(TMenu* menu);
	virtual bool			DoCommand(TCommandHandler* sender, TCommandHandler* receiver, TCommandID command);

protected:
	TFile					fFile;
	TString					fTitle;
	bool					fModified;	// if true, we will prompt to save changes
	
	// for automatic file reload support
	TFileTime				fLastModification;
};


#endif // __TDocument__
