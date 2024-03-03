/*File ResEd.hCopyright Apple Computer, Inc. 1984-1990All rights reserved.	Resource editor interface unit for instances of editors and pickers. This should be	included by any C implementation of a resource editor or picker.  The	companion file ResDisp.a.o should be linked with the c module to build	the file for inclusion in ResEdit.	Pickers are given a resource type and should display all of that type in 	the current resfile in a suitable format.	 If the picker is given an open call 	AND there's a compatible editor, it should give birth to the Editor.  The editor	is given a handle to the resource object and it should open up an edit	window for the user.*/#include	<types.h>#include	<quickdraw.h>#include	<lists.h>#include	<controls.h>#include	<windows.h>#include	<events.h>#include	<dialogs.h>#include	<printing.h>/* Standard menus exported by ResEdit */#define	fileMenu		 2#define	newFileItem     1#define	openFileItem	2#define	openSpecialItem 3#define	closeItem   	4#define	saveItem 		5#define	revertItem		6#define	getThisInfoItem 8#define	getInfoItem 	9#define	verifyItem 		10#define	pageSetupItem   12#define	printItem    	13#define	preferencesItem	15#define	quitItem    	17		// Masks for AbleMenu - normally not used directly.#define	newFileMask		0x2#define	openFileMask	0x4#define openSpecialMask	0x8#define	closeMask		0x10#define	saveMask		0x20#define	revertMask		0x40#define	getThisInfoMask 0x100#define	getInfoMask		0x200#define	verifyMask		0x400#define	pageSetupMask	0x1000#define	printMask		0x2000#define	preferencesMask 0x8000#define	quitMask		0x20000#define	disabledMask	0x1	// Mask combinations to be used in calls to AbleMenu.#define	fileNotOpen			disabledMask + newFileMask + openFileMask + openSpecialMask + getInfoMask + verifyMask + pageSetupMask + preferencesMask + quitMask#define	fileNoPrint			fileNotOpen + getThisInfoMask + closeMask + saveMask + revertMask#define	fileAll				fileNoPrint + printMask#define	fileNoSaveOrRevert 	fileNotOpen + getThisInfoMask + closeMask + printMask#define	fileDA				disabledMask + openFileMask + newFileMask + openSpecialMask + getInfoMask + verifyMask + closeMask + quitMask#define	rsrcMenu    			128	#define	rsrcCreateItem			1#define	rsrcOpenItem			2#define	rsrcOpenTemplateItem	3#define	rsrcOpenHexItem			4#define	rsrcRevertItem			6#define	rsrcGetInfoItem			8	#define	rsrcCreateMask			0x2#define	rsrcOpenMask			0x4#define	rsrcOpenTemplateMask	0x8#define	rsrcOpenHexMask			0x10#define	rsrcRevertMask			0x40#define	rsrcGetInfoMask			0x100#define	rsrcDisabledMask		0xFFFFFE01	#define	rsrcDisabled			0xFFFFFE00#define	rsrcRevertOnly			rsrcDisabledMask + rsrcRevertMask#define	rsrcPickerNoSel			rsrcDisabledMask + rsrcCreateMask#define	rsrcFilePicker			rsrcPickerNoSel + rsrcOpenHexMask + rsrcRevertMask + rsrcOpenMask#define	rsrcRsrcPicker			rsrcFilePicker + rsrcOpenTemplateMask + rsrcGetInfoMask#define	rsrcEditor				rsrcDisabledMask + rsrcRevertMask + rsrcGetInfoMask#define	rsrcEditorPicker		rsrcEditor + rsrcOpenMask + rsrcOpenTemplateMask + rsrcOpenHexMask#define	rsrcDITLEd				rsrcEditorPicker - rsrcOpenHexMask + rsrcCreateMask#define	rsrcEditorCreate		rsrcEditor + rsrcCreateMask#define	editMenu			3#define	undoItem			1#define	cutItem 			3#define	copyItem			4#define	pasteItem			5#define	clearItem			6#define	dupItem 			8#define selectAllItem		9#define selectChangedItem	10/* Masks for AbleMenu - normally not used directly. */#define undoMask			0x2#define cutMask				0x8#define editCopyMask		0x10#define pasteMask			0x20#define clearMask			0x40#define duplicateMask		0x100#define selectAllMask		0x200#define selectChangedMask	0x400#define editDisabledMask 	0xFFFFF801/* Mask combinations to be used in calls to AbleMenu. */#define editNone			editDisabledMask - 1#define editClear			editDisabledMask + clearMask#define editCopy			editDisabledMask + editCopyMask#define editPaste			editDisabledMask + pasteMask#define editUndoPasteOnly	editPaste + undoMask#define editDup				editClear + duplicateMask#define editNoDup			editDisabledMask + cutMask + editCopyMask + pasteMask + clearMask /* No dup or undo */#define editNoUndo			editNoDup + duplicateMask#define editUndNoDup		editNoDup + undoMask#define editAll				editNoUndo + undoMask#define editAcc 			editUndNoDup			/* for DAs */#define viewMenu 130			/* Type pickers view menu. */	#define viewByIDItem			1#define viewByNameItem			2#define viewBySizeItem			3#define viewByOrderItem			4#define viewBySpecialItem		5#define viewShowAttributesItem	7	/* Masks for AbleMenu. */#define viewByIDMask			0x2#define viewByNameMask			0x4#define viewBySizeMask			0x8#define viewByOrderMask			0x10#define viewBySpecialMask		0x20#define viewShowAttributesMask	0x40#define viewDisabledMask		0xFFFFFF81	#define viewNoSpecial			viewDisabledMask + viewByIDMask + viewByNameMask + viewBySizeMask + viewByOrderMask#define viewNoAttributes		viewNoSpecial + viewBySpecialMask#define viewAll					viewNoAttributes + viewShowAttributesMask#define fontMenu				144	/* Font menu with menus already added. */#define miscStrings			129		/* Resource ID of STR# resource containing the strings. */#define miscStringsName 	"\pMisc"#define cantLoadSndErrStr	24		/* Snd picker error. */#define	sysStr 				45		/* 'Sys', etc. used by LDEF. *//* Text for selected errors */#define errorStrings		132		/* Resource ID of STR# resource containing the error strings */#define errorStringsName "\pErrors"#define genericErrStr			1	/* Returned by GetErrorText when no specific message available */#define ioErrStr				1#define writeProtectErrStr		2#define diskFullErrStr			3#define fileLockedErrStr		4#define outOfMemoryErrStr		5#define alreadyOpenErrStr		6#define tooManyOpenErrStr		7#define volNotMountedErrStr		8#define resNotFoundErrStr		9#define accessErrStr			10#define resFileNotFoundErrStr	11#define addResFailErrStr		12#define removeResFailErrStr		13#define resAttributesErrStr		14#define resMapErrStr			15	#define fileNotFoundErrStr		16#define eofErrStr				17#define fileBusyStr				18#define cantDecompressStr		19#define arrowCursor -1	/* Used in the call to SetTheCursor to set the arrow cursor. */#define theScrollBar 15					/* Width of a scroll bar. */#define okChoice 1						/* Used for the OK button in dialogs. */	#define noDialog 0						/* Used with EditorWindSetup. */#define noScrap -1						/* Used with GetResEditScrapFile. */	#define alertStringsName "\pAlert strings"#define revertResourceAlertStr 1#define noTemplateAlert 2				/* GNRL editor */#define cantPlayOnThisMachineAlert 3	/* snd picker */#define cantPlaySndAlert 4				/* snd picker *//* Consts for Resource menu string */#define rsrcStrName 		"\pResource menu"#define rsrcCreateStr 		1#define rsrcOpenStr 		2#define rsrcListStr 		3#define rsrcOpenLists 		4#define rsrcOpenEditor 		5#define rsrcOpenEditors 	6#define rsrcOpenHex 		7#define rsrcRevert 			8#define rsrcRevertThese 	9#define rsrcResources 		10#define rsrcRevertRes 		11#define rsrcRevertThis 		12#define rsrcPatCreateStr 	13#define rsrcSICNCreateStr	14#define rsrcDITLCreateStr	15#define rsrcRevertItemStr	16#define rsrcGNRLCreateStr	17#define rsrcOpenTemplate	18#define rsrcOpenPickerByID	19	//	Character code constants#define 	leftArrowKey		0x1c#define 	rightArrowKey		0x1d#define 	upArrowKey			0x1e#define 	downArrowKey		0x1f#define 	tabkey				0x9#define		enterKey			0x03#define		deleteKey			0x08#define		returnKey			0x0d#define		escapeKey			0x1b#define		periodKey			0x2e	typedef unsigned char Str64[65];/* Alert kinds used by the DisplayAlert procedure. */	typedef enum { displayTheAlert, displayStopAlert, displayNoteAlert, displayCautionAlert, 				   displayYNAlert, displayYNCAlert, displayYNCStopAlert, displayCancelDefaultCautionAlert } AlertType;/* Icon kinds used by the ChooseIcon function */	typedef enum { noIcon, normalIcon, reducedIcon, smallIcon,				   onlyICON, onlyICNPound } IconType;	 /* This defines the various types of icons handled by the icon chooser package. 	 	Passing onlyICON in the IconKind parameter of the ChooseIcon function forces the 		IconChooser to not allow reduced ICONs and SICNs. Passing onlyICNPound in 		the IconKind parameter uses ICN# resources instead of ICONs. Passing any	 	other value instructs the IconChooser to support regular ICONs, reduced ICONs, 		and SICNs (like in the MENU editor).		         *//* Kinds of windows that support color in different degrees */	typedef enum { noColor, canColor, requiresColor } ColorType;/* This structure is used by the GetQuickDrawVars procedure. */	typedef struct  {		long 	randSeed;		BitMap 	screenBits;		Cursor 	arrow;		Pattern dkGray;		Pattern ltGray;		Pattern gray;		Pattern black;		Pattern white;		GrafPtr thePort;	} QuickDrawVars;	typedef	QuickDrawVars	*pQuickDrawVars;		typedef enum {textOnlyPicker, graphical1DPicker, graphical2DPicker} PickerType;		/* window types used to set the windowType field of the ParentHandle */	typedef enum {typePickerWindow, resourcePickerWindow, 				  folderInfoWindow, fileInfoWindow, resourceInfoWindow,				  editorWindow, floatingWindow} PossibleWindowTypes;	typedef	struct ParentRec	*ParentPtr;	typedef	ParentPtr			*ParentHandle;	typedef	struct ParentRec {		ParentHandle		father;		Str255				name;			/* Max 255 characters */		WindowPeek			wind;		Boolean				rebuild;		/* Flag set to indicate that window should be rebuilt  */		Boolean				resWasntLoaded;	/* TRUE if the resource should be released when the window is closed. */		unsigned char		windowType;		ResType				theResType;		/* Type of the resource being picked or edited. */		short				theResFile;		/* The home resfile of the window. */		short				codeResID;		/* Resource ID of the RSSC resource containing the picker or editor. */		Handle				theResToEdit;	} ParentRec;	/* ViewTypes to be used with the viewBy item in the PickRec */	typedef enum {viewById, viewByName, viewBySize, viewByOrder, viewBySpecial} ViewTypes;/* Standard picker record */	typedef struct PickRec {		ParentHandle		father;			/* Back ptr to dad 			*/		Str255				fName;			/* Max 255 characters. 		*/		 		WindowPtr			wind;			/* Picker window 		*/		Boolean				rebuild;		/* Flag set to indicate that window should be rebuilt  */		Boolean				spare1;			/* Not used here */		unsigned char		windowType;		ResType				theResType;		/* Type of the resource being picked or edited. */		short				theResFile;		/* The home resfile of the window. */		short				codeResID;		/* Resource ID of the RSSC resource containing the picker or editor. */		Handle				spare2;			/* Not used here */		ResType				rType;			/* Type for this picker 	*/		long				rSize;			/* size of a null resource 	*/		short				minWindowWidth;	/* Use when the window is grown. */		short				minWindowHeight;		ListHandle			instances;		/* List of instances 		*/		short				nInsts;			/* Number of instances 		*/		unsigned char		viewBy;			/* Current view type		*/		Boolean				showAttributes;	/* Show attrs in window?	*/		ResType				ldefType;		/* Which LDEF to use		*/		MenuHandle			theViewMenu;	/* The picker view menu		*/		long				viewMenuMask;	/* Which items are enabled?	*/		Cell				cellSize;		/* Size for special view.	*/		Str255				optionCreateStr;/* Create item menu text when the option key is pressed. */	} PickRec;		typedef	PickRec	*PickPtr;	typedef	PickPtr	*PickHandle;	typedef struct FloatingWindowRec {		ParentHandle		father;			/* Back ptr to dad 			*/		Str255				name;			/* Max 255 characters. 		*/		 		WindowPtr			wind;			/* Floating window 		*/		Boolean				rebuild;		/* Flag set to indicate that window should be rebuilt  */		Boolean				visible;		/* Is the window hidden temporarily? */		unsigned char		windowType;		ResType				theResType;		/* Type of the resource being picked or edited. */		short				theResFile;		/* The home resfile of the window. */		short				codeResID;		/* Resource ID of the RSSC resource containing the picker or editor. */		WindowPtr			ownerWindow;	/* Which window owns this floating window? */	} FloatingWindowRec;	typedef FloatingWindowRec *FloatingWindowPtr;	typedef FloatingWindowPtr *FloatingWindowHandle;	typedef pascal void (*DrawResProcPtr) (Rect *lRect, Handle theIcon);/* Window Utilities */pascal Boolean		AlreadyOpen (StringPtr windowTitle, StringPtr windowName, ParentHandle parent);pascal WindowPtr	EditorWindSetup (short dlogID, ColorType colorKind, short width, short height, StringPtr windowTitle, 									 StringPtr windowName, Boolean addFrom, short windowKind, ParentHandle parent);pascal WindowPtr	FloatingWindowSetup (short WINDID, FloatingWindowHandle fw,							   			 ParentHandle owner, Point where);pascal void			GetWindowTitle (StringPtr windowTitle, StringPtr windowName, Boolean addFrom,									ParentHandle parent);pascal WindowPtr	PickerWindSetup (ColorType colorKind, Boolean showTheWindow, short width, short height, 									 StringPtr windowTitle, short windowKind, ParentHandle parent);pascal void			SetETitle(Handle h, StringPtr str);pascal WindowPtr	WindAlloc(void);pascal void			WindReturn(WindowPtr w);/* Extended Resource Manager */pascal Boolean		REAddNewRes(short resFile, Handle hNew, ResType t, short idNew, const Str255 s);pascal void			REAddResource(short resFile, Handle theResource,								  ResType theType, short theID, const Str255 name);pascal short		REBeautifulUnique1ID(short resFile, ResType WhichType);pascal short		RECount1Resources(short resFile, ResType theType);pascal short		RECount1Types (short resFile);pascal Handle		REGet1IndResource(short resFile, ResType theType, short index);pascal void			REGet1IndType(short resFile, ResType *theType, short index);pascal Handle		REGet1NamedResource(short resFile, ResType theType, const Str255 name);pascal Handle		REGet1Resource(short resFile, ResType theType, short theID);pascal Handle		REGet1ResourceSpecial (short resFile, ResType theType, short ID, 										   Boolean *wasLoaded, short *error);pascal Handle		RENewUniqueRes(short resFile, long s, ResType t);pascal void			RERemoveAnyResource (short resFile, Handle theRes);pascal Boolean		RevertThisResource (ParentHandle parent, Handle theRes);/* Routines used by pickers. */pascal short		DefaultListCellSize(void);pascal Boolean		DoPickBirth(ColorType colorKind, Boolean buildList, PickerType which,								short pickerResId, PickHandle pick);pascal void			DrawLDEF (short message, Boolean lSelect, const Rect *lRect, Handle theRes,							  short id, StringPtr title, short maxH, short maxV, 							  DrawResProcPtr DrawResource, ListHandle lh);pascal void			GrowMyWindow (short minWidth, short minHeight, WindowPtr windPtr, ListHandle lh);pascal void			PickEvent(EventRecord *evt, PickHandle pick);pascal void			PickInfoUp(short oldID, short newID, PickHandle pick);pascal void			PickMenu(short menu, short item, PickHandle pick);pascal short		PickStdHeight(void);pascal short		PickStdWidth(void);/* Routines used by editors. */pascal Boolean		CloseNoSave(void);pascal Boolean		NeedToRevert (WindowPtr myWindow, Handle theRes);pascal void			NoDoubleClickHere(void);pascal void			SetResChanged(Handle h);pascal Boolean		WasItLoaded(void);/* These routines are used to start pickers and editors.*/pascal void			GiveEBirth(Handle resHandle, PickHandle pick);pascal void			GiveSubEBirth(Handle resHandle, PickHandle pick);pascal void			GiveThisEBirth(Handle resHandle, PickHandle pick, ResType openThisType);/* These routines are used to feed events and menu calls to the appropriate picker or editor. */pascal void 		CallDoEvent (EventRecord *evt, WindowPtr theWindow);pascal void			CallInfoUpdate(short oldID, short newID, long object, short id);pascal void 		PassEvent (EventRecord *evt, ParentHandle parent);pascal void 		PassMenu(short menu, short item, ParentHandle parent);/* Miscellaneous utilities */pascal void			Abort(void);pascal void			AbleMenu(short menu, long enable);pascal void			BubbleUp(Handle);pascal void			CenterDialog (ResType theType, short dialog);pascal Boolean		CheckError(short err, short msgID);pascal Boolean		ChooseIcon(ParentHandle parent, short *IconResID, IconType *IconKind,								short dialogID);pascal Boolean		ColorAvailable(Boolean needColorQD);pascal void			ConcatStr(StringPtr str1, StringPtr str2);pascal short		DisplayAlert(AlertType which, short id);pascal Boolean		DisplaySTRAlert(AlertType which, const Str255 STRName, short STRIndex);pascal void			DrawMBarLater(Boolean forceItNow);pascal WindowPtr	FindOwnerWindow (Handle theRes);pascal void			FixHand(long s, Handle h);pascal void			FlashDialogItem (DialogPtr dp, short item);pascal void			FrameDialogItem (DialogPtr dp, short item);pascal void			GetNamedStr(short index, const Str255 name, StringPtr str);pascal pQuickDrawVars GetQuickDrawVars(void);pascal Rect			GetScreenRect(Boolean roomForIcons, WindowPtr wind);pascal void			GetStr(short index, short resID, StringPtr str);pascal Boolean		HandleCheck(Handle h, short msgID);pascal void			MetaKeys(Boolean *cmd, Boolean *shift, Boolean *opt);pascal Handle		PrintSetup(void);		/* Return type is actually THPrint */pascal void			PrintWindow (PicHandle toPrint);pascal short		ResEdID(void);pascal void			SetTheCursor (short whichCursor);pascal void			ShowInfo(Handle h, ParentHandle parent);pascal Boolean		StandardFilter(DialogPtr theDialog, EventRecord *theEvent, short *itemHit);pascal void			TypeToString(ResType t, StringPtr s);pascal void			UseAppRes(void); pascal Boolean		WasAborted(void);/* Popup Menus */pascal Boolean		ColorPalettePopupSelect(WindowPtr whichWindow, Rect *itemBox,						  	RGBColor *whichColor, Boolean CQDishere, Boolean useColorPicker );pascal void			DeinstallColorPalettePopup(WindowPtr whichWindow, Boolean CQDishere);pascal void			DoPopup(DialogPtr whichDialog, short promptDialogItem,							 short popupDialogItem, short *menuItem, MenuHandle whichMenu);pascal void			DrawColorPopup(WindowPtr whichWindow, Rect *itemBox,						  		   RGBColor *whichColor, Boolean CQDishere);pascal void			DrawPopup(DialogPtr whichDialog, short whichDialogItem,							   short whichMenuItem, MenuHandle whichMenu);pascal void			InstallColorPalettePopup(WindowPtr whichWindow, Boolean CQDishere,											 Boolean isActive);	/* Routines that are used internally within ResEdit and may be useful in other	circumstances. */	pascal short		BuildType(ResType t, ListHandle lh);pascal Boolean		CompressedResource(Handle theResource);pascal void			DoKeyScan(EventRecord *evt, short offset, ListHandle lh);pascal Handle		DupPick(Handle h, Cell c, PickHandle pick);pascal void			GetErrorText (short error, StringPtr errorText);pascal short		GetResEditScrapFile(void);pascal Boolean		GetType(Boolean templatesOnly, StringPtr s);pascal ResType		MapResourceType (Boolean editor, Handle theRes, ResType origResType);pascal Boolean		PlaySyncSound(short which, Handle sndHandle);pascal short		ResEditRes(void) =					{0x3eB8, 0x0900};	/* move.w	CurApRefNum,(sp) */pascal void			ResourceIDHasChanged (ParentHandle parent, ResType theType, short theOldId, short theNewId);pascal Boolean		RestoreRemovedResources (PickHandle pick);pascal void			ScrapCopy(ResType theType, Handle *h);pascal void			ScrapEmpty(void);pascal void			SendRebuildToPicker (ResType theType, ParentHandle parent);pascal void			SendRebuildToPickerAndFile (ResType theType, ParentHandle parent) ;pascal short		SysResFile(void);pascal ListHandle	WindList(WindowPtr w, short nAcross, Point cSize, short drawProc);pascal void			WindOrigin(WindowPtr w, ParentHandle parent);pascal void			WritePreferences (ResType prefType, short prefId, const Str255 prefName, Handle prefHandle);