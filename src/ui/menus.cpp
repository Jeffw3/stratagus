//   ___________		     _________		      _____  __
//   \_	  _____/______   ____   ____ \_   ___ \____________ _/ ____\/  |_
//    |    __) \_  __ \_/ __ \_/ __ \/    \  \/\_  __ \__  \\   __\\   __\ 
//    |     \   |  | \/\  ___/\  ___/\     \____|  | \// __ \|  |   |  |
//    \___  /   |__|    \___  >\___  >\______  /|__|  (____  /__|   |__|
//	  \/		    \/	   \/	     \/		   \/
//  ______________________                           ______________________
//			  T H E   W A R   B E G I N S
//	   FreeCraft - A free fantasy real time strategy game engine
//
/**@name menus.c	-	The menu buttons. */
//
//	(c) Copyright 1999-2002 by Andreas Arens
//
//	FreeCraft is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published
//	by the Free Software Foundation; only version 2 of the License.
//
//	FreeCraft is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	$Id$

//@{

/*----------------------------------------------------------------------------
--	Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef _MSC_VER
#include <unistd.h>
#else
#ifndef _WIN32_WCE
#include <io.h>
#define F_OK 4
#endif
#endif

#include "freecraft.h"
#include "video.h"
#include "player.h"
#include "font.h"
#include "tileset.h"
#include "map.h"
#include "interface.h"
#include "menus.h"
#include "cursor.h"
#include "pud.h"
#include "iolib.h"
#include "network.h"
#include "netconnect.h"
#include "settings.h"
#include "ui.h"
#include "campaign.h"
#include "sound_server.h"
#include "sound.h"
#include "ccl.h"

#if defined(USE_SDLCD) || defined(USE_SDLA)
#include "SDL.h"
#endif

#ifdef USE_LIBCDA
#include "libcda.h"
#endif

/*----------------------------------------------------------------------------
--	Prototypes for local functions
----------------------------------------------------------------------------*/

local void EndMenu(void);

/*----------------------------------------------------------------------------
--	Prototypes for action handlers and helper functions
----------------------------------------------------------------------------*/

local void GameMenuSave(void);
local void GameMenuLoad(void);
local void GameMenuEnd(void);
local void GameMenuExit(void);
local void GameMenuReturn(void);
local void GameGlobalOptionsMenu(void);
local void GameShowCredits(void);
local void GameMenuObjectives(void);
local void GameMenuEndScenario(void);
local void GameOptions(void);

local void HelpMenu(void);
local void KeystrokeHelpMenu(void);
local void ShowTipsMenu(void);
local void InitTips(Menuitem *mi);
local void TipsMenuEnd(void);
local void SetTips(Menuitem *mi);
local void ShowNextTip();

local void SetMasterPower(Menuitem *mi);
local void SetMusicPower(Menuitem *mi);
local void SetCdPower(Menuitem *mi);
local void SetFogOfWar(Menuitem *mi);
local void SetCdModeAll(Menuitem *mi);
local void SetCdModeRandom(Menuitem *mi);

local void EndScenarioRestart(void);
local void EndScenarioSurrender(void);
local void EndScenarioQuitMenu(void);

local void PrgStartInit(Menuitem *mi);		// master init
local void StartMenusSetBackground(Menuitem *mi);
local void NameLineDrawFunc(Menuitem *mi);
local void EnterNameAction(Menuitem *mi, int key);
local void EnterNameCancel(void);
local void EnterServerIPAction(Menuitem *mi, int key);
local void EnterServerIPCancel(void);

local void JoinNetGameMenu(void);
local void CreateNetGameMenu(void);

local void SinglePlayerGameMenu(void);
local void MultiPlayerGameMenu(void);
local void CampaignGameMenu(void);
local void ScenSelectMenu(void);

local void CampaignMenu1(void);
local void CampaignMenu2(void);
local void CampaignMenu3(void);
local void CampaignMenu4(void);
local void SelectCampaignMenu(void);

local void ScenSelectLBExit(Menuitem *mi);
local void ScenSelectLBInit(Menuitem *mi);
local unsigned char *ScenSelectLBRetrieve(Menuitem *mi, int i);
local void ScenSelectLBAction(Menuitem *mi, int i);
local void ScenSelectTPMSAction(Menuitem *mi, int i);
local void ScenSelectVSAction(Menuitem *mi, int i);
local void ScenSelectVSKeystrokeHelpAction(Menuitem *mi, int i);
local void ScenSelectHSGameSpeedAction(Menuitem *mi, int i);
local void ScenSelectHSMouseScrollAction(Menuitem *mi, int i);
local void ScenSelectHSKeyboardScrollAction(Menuitem *mi, int i);
local void ScenSelectHSMasterVolumeAction(Menuitem *mi, int i);
local void ScenSelectHSMusicVolumeAction(Menuitem *mi, int i);
local void ScenSelectHSCdVolumeAction(Menuitem *mi, int i);
local void ScenSelectFolder(void);
local void ScenSelectInit(Menuitem *mi);	// master init
local void ScenSelectOk(void);
local void ScenSelectCancel(void);

local void GameSetupInit(Menuitem *mi);		// master init
local void GameDrawFunc(Menuitem *mi);

local void GameRCSAction(Menuitem *mi, int i);
local void GameRESAction(Menuitem *mi, int i);
local void GameUNSAction(Menuitem *mi, int i);
local void GameTSSAction(Menuitem *mi, int i);

local void GameCancel(void);

local void CustomGameStart(void);
local void CustomGameOPSAction(Menuitem *mi, int i);

local void MultiClientReady(void);
local void MultiClientNotReady(void);
local void MultiClientGemAction(Menuitem *mi);
local void MultiClientCancel(void);
local void MultiClientRCSAction(Menuitem *mi, int i);

local void MultiGameStart(void);
local void MultiGameCancel(void);
local void MultiGameSetupInit(Menuitem *mi);	// master init
local void MultiGameSetupExit(Menuitem *mi);	// master exit
local void MultiGameDrawFunc(Menuitem *mi);
local void MultiGameFWSAction(Menuitem *mi, int i);
local void MultiGamePTSAction(Menuitem *mi, int o);
local void NetMultiPlayerDrawFunc(Menuitem *mi);
local void MultiGamePlayerSelectorsUpdate(int initial);
local void MultiScenSelectMenu(void);

local void MultiGameClientInit(Menuitem *mi);	// master init
local void MultiGameClientDrawFunc(Menuitem *mi);
local void MultiClientUpdate(int initial);

local void NetConnectingCancel(void);
local void TerminateNetConnect(void);

/*----------------------------------------------------------------------------
--	Variables
----------------------------------------------------------------------------*/

    /// Name, Version, Copyright
extern char NameLine[];
extern int NetStateMsgCnt;	/// Number of consecutive msgs of same type sent

local EventCallback callbacks;

// FIXME: Johns: this must be all be configured from ccl some time.

    /// private struct which specifies the buttons gfx
local struct {
	/// resource filename one for each race
    const char*	File[PlayerMaxRaces];
	/// Width of button
    int		Width, Height;
	/// sprite : FILLED
    Graphic*	Sprite;
} MenuButtonGfx
#ifndef laterUSE_CCL
= {
    { "ui/buttons 1.png" ,"ui/buttons 2.png" },
    300, 7632,

    NULL
}
#endif
    ;

/**
**	The currently processed menu
*/
global int CurrentMenu = -1;

/**
**	Other client and server selection state for Multiplayer clients
*/
global ServerSetup ServerSetupState, LocalSetupState;

local int MenuButtonUnderCursor = -1;
local int MenuButtonCurSel = -1;

/**
**	Text describing the Network Server IP
*/
local char NetworkServerText[64];

/**
**	Text tries
*/
local char NetworkTriesText[32];

/**
**	Offsets from top and left, used for different resolutions
*/
local int OffsetX = 0;
local int OffsetY = 0;

/**
**	The background picture used by start menues
*/
local Graphic* Menusbgnd;

/**
**	Items for the Game Menu
**
**	@todo FIXME: Configure with CCL.
*/
local Menuitem GameMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Game Menu", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 16, 40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Save (~<F11~>)", 106, 27, MBUTTON_GM_HALF, GameMenuSave, KeyCodeF11} } },
    { MI_TYPE_BUTTON, 16 + 12 + 106, 40, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "Load (~<F12~>)", 106, 27, MBUTTON_GM_HALF, GameMenuLoad, KeyCodeF12} } },
    { MI_TYPE_BUTTON, 16, 40 + 36, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Options (~<F5~>)", 224, 27, MBUTTON_GM_FULL, GameOptions, KeyCodeF5} } },
    { MI_TYPE_BUTTON, 16, 40 + 36 + 36, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Help (~<F1~>)", 224, 27, MBUTTON_GM_FULL, HelpMenu, KeyCodeF1} } },
    { MI_TYPE_BUTTON, 16, 40 + 36 + 36 + 36, 0, LargeFont, NULL, NULL,
	{ button:{ "Scenario ~!Objectives", 224, 27, MBUTTON_GM_FULL, GameMenuObjectives, 'o'} } },
    { MI_TYPE_BUTTON, 16, 40 + 36 + 36 + 36 + 36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!End Scenario", 224, 27, MBUTTON_GM_FULL, GameMenuEndScenario, 'e'} } },
    { MI_TYPE_BUTTON, 16, 288-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Return to Game (~<Esc~>)", 224, 27, MBUTTON_GM_FULL, GameMenuReturn, '\033'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Victory Menu
**	@todo FIXME: Configure with CCL.
*/
local Menuitem VictoryMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Congratulations!", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 144, 32, 0, LargeFont, NULL, NULL,
	{ text:{ "You are victorious!", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 32, 90, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!Victory", 224, 27, MBUTTON_GM_FULL, GameMenuEnd, 'v'} } },
    { MI_TYPE_BUTTON, 32, 56, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "Save Game (~<F11~>)", 224, 27, MBUTTON_GM_FULL, NULL, KeyCodeF11} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Lost Menu
**	@todo FIXME: Configure with CCL.
*/
local Menuitem LostMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "You failed to", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 144, 32, 0, LargeFont, NULL, NULL,
	{ text:{ "achieve victory!", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 32, 90, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 224, 27, MBUTTON_GM_FULL, GameMenuEnd, 'o'} } },
#else
    { 0 }
#endif
};

local Menuitem TipsMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, LargeFont, InitTips, NULL,
	{ text:{ "Freecraft Tips", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_GEM, 14, 256-75, 0, GameFont, NULL, NULL,
	{ gem:{ MI_GSTATE_CHECKED, 18, 18, MBUTTON_GEM_SQUARE, SetTips} } },
    { MI_TYPE_TEXT, 14+22, 256-75+4, 0, GameFont, NULL, NULL,
	{ text:{ "Show tips at startup", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_BUTTON, 14, 256-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!Next Tip", 106, 27, MBUTTON_GM_HALF, ShowNextTip, 'n'} } },
    { MI_TYPE_BUTTON, 168, 256-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!Close", 106, 27, MBUTTON_GM_HALF, TipsMenuEnd, 'c'} } },
    { MI_TYPE_TEXT, 14, 35+16*0, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*1, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*2, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*3, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*4, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*5, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*6, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 14, 35+16*7, 0, GameFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_LALIGN} } },
#else
    { 0 }
#endif
};

local Menuitem ObjectivesMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Objectives", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 14, 38+21*0, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*1, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*2, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*3, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*4, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*5, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*6, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*7, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_TEXT, 14, 38+21*8, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, 0} } },
    { MI_TYPE_BUTTON, 16, 288-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 224, 27, MBUTTON_GM_FULL, EndMenu, 'o'} } },
#else
    { 0 }
#endif
};

local Menuitem EndScenarioMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "End Scenario", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*0, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Restart Scenario", 224, 27, MBUTTON_GM_FULL, EndScenarioRestart, 'r'} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*1, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Surrender", 224, 27, MBUTTON_GM_FULL, EndScenarioSurrender, 's'} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*2, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Quit to Menu", 224, 27, MBUTTON_GM_FULL, EndScenarioQuitMenu, 'q'} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*3, 0, LargeFont, NULL, NULL,
	{ button:{ "E~!xit Program", 224, 27, MBUTTON_GM_FULL, GameMenuExit, 'x'} } },
    { MI_TYPE_BUTTON, 16, 288-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Previous (~!E~!s~!c)", 224, 27, MBUTTON_GM_FULL, EndMenu, '\033'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the SelectScen Menu
*/
local unsigned char *ssmtoptions[] = {
    // "All scenarios (cm+pud)",
    "Freecraft scenario (cm)",
    "Foreign scenario (pud)"
    // FIXME: what is about levels in zips?
};

local unsigned char *ssmsoptions[] = {
    "Any size",
    "32 x 32",
    "64 x 64",
    "96 x 96",
    "128 x 128",
    "256 x 256",
    "512 x 512",
    "1024 x 1024",
    // FIXME: We support bigger sizes
};

local int GuiGameStarted;

local char ScenSelectPath[1024];		/// Scenario selector path
local char ScenSelectDisplayPath[1024];		/// Displayed selector path
local char ScenSelectFileName[128];		/// Scenario selector name
global char ScenSelectFullPath[1024];		/// Scenario selector path+name

global MapInfo *ScenSelectPudInfo;		/// Selected pud info

/**
**	Scenario selection menu.
**
**	@todo FIXME: Configure with CCL.
*/
local Menuitem ScenSelectMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 176, 8, 0, LargeFont, ScenSelectInit, NULL,
	{ text:{ "Select scenario", MI_TFLAGS_CENTERED} } },

    { MI_TYPE_LISTBOX, 24, 140, 0, GameFont, ScenSelectLBInit, ScenSelectLBExit,
	{ listbox:{ NULL, 288, 6*18, MBUTTON_PULLDOWN, ScenSelectLBAction, 0, 0, 0, 0, 6, 0,
		    (void *)ScenSelectLBRetrieve, ScenSelectOk} } },
    { MI_TYPE_VSLIDER, 312, 140, 0, 0, NULL, NULL,
	{ vslider:{ 0, 18, 6*18, ScenSelectVSAction, -1, 0, 0, 0, ScenSelectOk} } },

    { MI_TYPE_BUTTON, 48, 318, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "OK", 106, 27, MBUTTON_GM_HALF, ScenSelectOk, 0} } },
    { MI_TYPE_BUTTON, 198, 318, 0, LargeFont, NULL, NULL,
	{ button:{ "Cancel", 106, 27, MBUTTON_GM_HALF, ScenSelectCancel, 0} } },

    { MI_TYPE_TEXT, 132, 40, 0, LargeFont, NULL, NULL,
	{ text:{ "Type:", MI_TFLAGS_RALIGN} } },
    { MI_TYPE_PULLDOWN, 140, 40, 0, GameFont, NULL, NULL,
	{ pulldown:{ ssmtoptions, 192, 20, MBUTTON_PULLDOWN, ScenSelectTPMSAction, 2, 1, 1, 0, 0} } },
    { MI_TYPE_TEXT, 132, 80, 0, LargeFont, NULL, NULL,
	{ text:{ "Map size:", MI_TFLAGS_RALIGN} } },
    { MI_TYPE_PULLDOWN, 140, 80, 0, GameFont, NULL, NULL,
	{ pulldown:{ ssmsoptions, 192, 20, MBUTTON_PULLDOWN, ScenSelectTPMSAction, 8, 0, 0, 0, 0} } },
    { MI_TYPE_BUTTON, 22, 112, 0, GameFont, NULL, NULL,
	{ button:{ NULL, 36, 24, MBUTTON_FOLDER, ScenSelectFolder, 0} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Program Start Menu
*/
local Menuitem PrgStartMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_DRAWFUNC, 0, 0, 0, GameFont, PrgStartInit, NULL,
	{ drawfunc:{ NameLineDrawFunc } } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 0, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Single Player Game", 224, 27,
	    MBUTTON_GM_FULL, SinglePlayerGameMenu, 's'} } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 1, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Multi Player Game", 224, 27,
	    MBUTTON_GM_FULL, MultiPlayerGameMenu, 'm'} } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 2, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Campaign Game", 224, 27,
	    MBUTTON_GM_FULL, CampaignGameMenu, 'c'} } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 3, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "~!Load Game", 224, 27,
	    MBUTTON_GM_FULL, GameMenuLoad, 'l'} } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 4, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "~!Options", 224, 27,
	    MBUTTON_GM_FULL, GameGlobalOptionsMenu, 'o'} } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 5, 0, LargeFont, NULL, NULL,
	{ button:{ "S~!how Credits", 224, 27,
	    MBUTTON_GM_FULL, GameShowCredits, 'h'} } },
    { MI_TYPE_BUTTON, 208, 180 + 36 * 6, 0, LargeFont, NULL, NULL,
	{ button:{ "E~!xit Program", 224, 27,
	    MBUTTON_GM_FULL, GameMenuExit, 'x'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Custom Game Setup Menu
*/
local unsigned char *rcsoptions[] = {
    "Human",
    "Orc",
    "Map Default",
    // FIXME: we support more and other race names
};

local unsigned char *resoptions[] = {
    "Map Default",
    "Low",
    "Medium",
    "High",
};

local unsigned char *unsoptions[] = {
    "Map Default",
    "One Peasant Only",
    // FIXME: we support more and other unit names
};

// FIXME: Must load this from some place.
local unsigned char *tssoptions[] = {
    "Map Default",
    "Forest",
    "Winter",
    "Wasteland",
    "Orc Swamp",	// hmm. need flag if XPN-GFX is present! - tmp-hack in InitMenus()..
			// FIXME: Some time later _all_ tilesets should be a dynamic (ccl-defineable) resource..
};

local unsigned char *cgopsoptions[] = {
    "Map Default",
    "1 Opponent",
    "2 Opponents",
    "3 Opponents",
    "4 Opponents",
    "5 Opponents",
    "6 Opponents",
    "7 Opponents",
    // FIXME: We support upto 15 opponents
};

local unsigned char *mgfwsoptions[] = {
    "On",
    "Off",
};

local unsigned char *mgptsoptions[] = {
    "Available",
    "Computer",
    "Closed",
};

/**
**	Single player custom game menu.
*/
local Menuitem CustomGameMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_DRAWFUNC, 0, 0, 0, GameFont, GameSetupInit, NULL,
	{ drawfunc:{ GameDrawFunc } } },
    { MI_TYPE_TEXT, 640/2+12, 192, 0, LargeFont, NULL, NULL,
	{ text:{ "~<Single Player Game Setup~>", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 640-224-16, 360, 0, LargeFont, NULL, NULL,
	{ button:{ "S~!elect Scenario", 224, 27, MBUTTON_GM_FULL, ScenSelectMenu, 'e'} } },
    { MI_TYPE_BUTTON, 640-224-16, 360+36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Start Game", 224, 27, MBUTTON_GM_FULL, CustomGameStart, 's'} } },
    { MI_TYPE_BUTTON, 640-224-16, 360+36+36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel Game", 224, 27, MBUTTON_GM_FULL, GameCancel, 'c'} } },
    { MI_TYPE_TEXT, 40, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Your Race:~>", 0} } },
    { MI_TYPE_PULLDOWN, 40, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ rcsoptions, 152, 20, MBUTTON_PULLDOWN, GameRCSAction, 3, 2, 2, 0, 0} } },
    { MI_TYPE_TEXT, 220, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Resources:~>", 0} } },
    { MI_TYPE_PULLDOWN, 220, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ resoptions, 152, 20, MBUTTON_PULLDOWN, GameRESAction, 4, 0, 0, 0, 0} } },
    { MI_TYPE_TEXT, 640-224-16, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Units:~>", 0} } },
    { MI_TYPE_PULLDOWN, 640-224-16, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ unsoptions, 190, 20, MBUTTON_PULLDOWN, GameUNSAction, 2, 0, 0, 0, 0} } },
    { MI_TYPE_TEXT, 40, 10+300-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Opponents:~>", 0} } },
    { MI_TYPE_PULLDOWN, 40, 10+300, 0, GameFont, NULL, NULL,
	{ pulldown:{ cgopsoptions, 152, 20, MBUTTON_PULLDOWN, CustomGameOPSAction, 8, 0, 0, 0, 0} } },
    { MI_TYPE_TEXT, 220, 10+300-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Map Tileset:~>", 0} } },
    { MI_TYPE_PULLDOWN, 220, 10+300, 0, GameFont, NULL, NULL,
	{ pulldown:{ tssoptions, 152, 20, MBUTTON_PULLDOWN, GameTSSAction, 5, 0, 0, 0, 0} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Enter Name Menu
*/
local Menuitem EnterNameMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, GameFont, NULL, NULL,
	{ text:{ "Enter your name:", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_INPUT, 40, 38, 0, GameFont, NULL, NULL,
	{ input:{ NULL, 212, 20, MBUTTON_PULLDOWN, EnterNameAction, 0, 0} } },
    { MI_TYPE_BUTTON, 24, 80, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 106, 27, MBUTTON_GM_HALF, EndMenu, 'o'} } },
    { MI_TYPE_BUTTON, 154, 80, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel", 106, 27, MBUTTON_GM_HALF, EnterNameCancel, 'c'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Enter Server Menu
*/
local Menuitem EnterServerIPMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, GameFont, NULL, NULL,
	{ text:{ "Enter server IP-address:", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_INPUT, 40, 38, 0, GameFont, NULL, NULL,
	{ input:{ NULL, 212, 20, MBUTTON_PULLDOWN, EnterServerIPAction, 0, 0} } },
    { MI_TYPE_BUTTON, 24, 80, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 106, 27, MBUTTON_GM_HALF, EndMenu, 'o'} } },
    { MI_TYPE_BUTTON, 154, 80, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel", 106, 27, MBUTTON_GM_HALF, EnterServerIPCancel, 'c'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Net Create Join Menu
*/
local Menuitem NetCreateJoinMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_BUTTON, 208, 320, 0, LargeFont, NULL/*StartMenusSetBackground*/, NULL,
	{ button:{ "~!Join Game", 224, 27, MBUTTON_GM_FULL, JoinNetGameMenu, 'j'} } },
    { MI_TYPE_BUTTON, 208, 320 + 36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Create Game", 224, 27, MBUTTON_GM_FULL, CreateNetGameMenu, 'c'} } },
    { MI_TYPE_BUTTON, 208, 320 + 36 + 36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Previous Menu", 224, 27, MBUTTON_GM_FULL, EndMenu, 'p'} } },
#else
    { 0 }
#endif
};


/**
**	Items for the Net Multiplayer Setup Menu
*/
local Menuitem NetMultiButtonStorage[] = {
#ifdef __GNUC__
    { MI_TYPE_PULLDOWN, 40, 32, 0, GameFont, NULL, NULL,
	{ pulldown:{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN,
	    MultiGamePTSAction, 3, 0, 0, 0, 0} } },
    { MI_TYPE_DRAWFUNC, 40, 32, 0, GameFont, NULL, NULL,
	{ drawfunc:{ NetMultiPlayerDrawFunc } } },
#else
    { 0 }
#endif
};

/**
**	Multi player custom game menu (server side).
*/
local Menuitem NetMultiSetupMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_DRAWFUNC, 0, 0, 0, GameFont, MultiGameSetupInit, NULL,
	{ drawfunc:{ MultiGameDrawFunc } } },
    { MI_TYPE_TEXT, 640/2+12, 8, 0, LargeFont, NULL, NULL,
	{ text:{ "~<Multi Player Setup~>", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 640-224-16, 360, 0, LargeFont, NULL, NULL,
	{ button:{ "S~!elect Scenario", 224, 27, MBUTTON_GM_FULL, MultiScenSelectMenu, 'e'} } },
    { MI_TYPE_BUTTON, 640-224-16, 360+36, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "~!Start Game", 224, 27, MBUTTON_GM_FULL, MultiGameStart, 's'} } },
    { MI_TYPE_BUTTON, 640-224-16, 360+36+36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel Game", 224, 27, MBUTTON_GM_FULL, MultiGameCancel, 'c'} } },

    // 8+7 player slots (content here is overwritten!)
#define SERVER_PLAYER_STATE	5
    { MI_TYPE_PULLDOWN, 40, 32+22*0, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*1, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*2, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*3, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*4, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*5, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*6, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*7, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*0, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*1, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*2, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*3, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*4, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*5, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*6, 0, GameFont, NULL, NULL,
	{ pulldown:
	{ mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },

    { MI_TYPE_TEXT, 40, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Your Race:~>", 0} } },
    { MI_TYPE_PULLDOWN, 40, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ rcsoptions, 152, 20, MBUTTON_PULLDOWN, GameRCSAction,
	3, 2, 2, 0, 0} } },
    { MI_TYPE_TEXT, 220, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Resources:~>", 0} } },
    { MI_TYPE_PULLDOWN, 220, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ resoptions, 152, 20, MBUTTON_PULLDOWN, GameRESAction,
	4, 0, 0, 0, 0} } },
    { MI_TYPE_TEXT, 640-224-16, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Units:~>", 0} } },
    { MI_TYPE_PULLDOWN, 640-224-16, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ unsoptions, 190, 20, MBUTTON_PULLDOWN, GameUNSAction,
	2, 0, 0, 0, 0} } },
    { MI_TYPE_TEXT, 40, 10+300-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Fog of War:~>", 0} } },
    { MI_TYPE_PULLDOWN, 40, 10+300, 0, GameFont, NULL, NULL,
	{ pulldown:{ mgfwsoptions, 152, 20, MBUTTON_PULLDOWN,
	MultiGameFWSAction, 2, 0, 0, 0, 0} } },
    { MI_TYPE_TEXT, 220, 10+300-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Map Tileset:~>", 0} } },
    { MI_TYPE_PULLDOWN, 220, 10+300, 0, GameFont, NULL, NULL,
	{ pulldown:{ tssoptions, 152, 20, MBUTTON_PULLDOWN, GameTSSAction,
	5, 0, 0, 0, 0} } },

    // 7+7 player ready buttons
#define SERVER_PLAYER_READY	30
    { MI_TYPE_GEM, 10, 32+22*1, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 10, 32+22*2, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 10, 32+22*3, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 10, 32+22*4, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 10, 32+22*5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 10, 32+22*6, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 10, 32+22*7, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },

    { MI_TYPE_GEM, 330, 32+22*0, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 330, 32+22*1, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 330, 32+22*2, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 330, 32+22*3, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 330, 32+22*4, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 330, 32+22*5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    { MI_TYPE_GEM, 330, 32+22*6, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },
    // FIXME: Slot 15 is reserved for neutral computer
    //{ MI_TYPE_GEM, 330, 32+22*7, 0, LargeFont, NULL, NULL,
    //	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_SQUARE, NULL} } },

    // 7+7 player lag buttons
#define SERVER_PLAYER_LAG	44
    { MI_TYPE_GEM, 218, 32+22*1, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 218, 32+22*2, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 218, 32+22*3, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 218, 32+22*4, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 218, 32+22*5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 218, 32+22*6, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 218, 32+22*7, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },

    { MI_TYPE_GEM, 538, 32+22*0, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 538, 32+22*1, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 538, 32+22*2, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 538, 32+22*3, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 538, 32+22*4, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 538, 32+22*5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    { MI_TYPE_GEM, 538, 32+22*6, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
    // FIXME: Slot 15 is reserved for neutral computer
    //{ MI_TYPE_GEM, 538, 32+22*7, 0, LargeFont, NULL, NULL,
    //	{ gem:{ MI_GSTATE_PASSIVE, 18, 18, MBUTTON_GEM_ROUND, NULL} } },
#else
    { 0 }
#endif
};

/**
**	Multi player client game menu.
*/
local Menuitem NetMultiClientMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_DRAWFUNC, 0, 0, 0, GameFont, MultiGameClientInit, NULL,
	{ drawfunc:{ MultiGameClientDrawFunc } } },

    { MI_TYPE_TEXT, 640/2+12, 8, 0, LargeFont, NULL, NULL,
	{ text:{ "~<Multi Player Game~>", MI_TFLAGS_CENTERED} } },

    { MI_TYPE_BUTTON, 640-224-16, 360, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Ready", 224, 27, MBUTTON_GM_FULL, MultiClientReady, 'r'} } },
    { MI_TYPE_BUTTON, 640-224-16, 360+36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Not Ready", 224, 27, MBUTTON_GM_FULL, MultiClientNotReady, 'n'} } },

    { MI_TYPE_BUTTON, 640-224-16, 360+36+36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel Game", 224, 27, MBUTTON_GM_FULL, MultiClientCancel, 'c'} } },

    // 8+7 player slots
#define CLIENT_PLAYER_STATE	5
    { MI_TYPE_PULLDOWN, 40, 32, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*2, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*3, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*4, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*5, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*6, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 40, 32+22*7, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*2, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*3, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*4, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*5, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },
    { MI_TYPE_PULLDOWN, 360, 32+22*6, 0, GameFont, NULL, NULL,
	{ pulldown:{
	mgptsoptions, 172, 20, MBUTTON_PULLDOWN, NULL, 3, 0, 0, 0, 0} } },

    { MI_TYPE_TEXT, 40, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Your Race:~>", 0} } },
#define CLIENT_RACE	21
    { MI_TYPE_PULLDOWN, 40, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ rcsoptions, 152, 20, MBUTTON_PULLDOWN,
	    MultiClientRCSAction, 3, 2, 2, 0, 0} } },
    { MI_TYPE_TEXT, 220, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Resources:~>", 0} } },
#define CLIENT_RESOURCE	23
    { MI_TYPE_PULLDOWN, 220, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ resoptions, 152, 20, MBUTTON_PULLDOWN,
	    GameRESAction, 4, 0, 0, 0, MI_PSTATE_PASSIVE} } },
    { MI_TYPE_TEXT, 640-224-16, 10+240-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Units:~>", 0} } },
#define CLIENT_UNITS	25
    { MI_TYPE_PULLDOWN, 640-224-16, 10+240, 0, GameFont, NULL, NULL,
	{ pulldown:{ unsoptions, 190, 20, MBUTTON_PULLDOWN,
	    GameUNSAction, 2, 0, 0, 0, MI_PSTATE_PASSIVE} } },
    { MI_TYPE_TEXT, 40, 10+300-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Fog of War:~>", 0} } },
#define CLIENT_FOG_OF_WAR	27
    { MI_TYPE_PULLDOWN, 40, 10+300, 0, GameFont, NULL, NULL,
	{ pulldown:{ mgfwsoptions, 152, 20, MBUTTON_PULLDOWN,
	    MultiGameFWSAction, 2, 0, 0, 0, MI_PSTATE_PASSIVE} } },
    { MI_TYPE_TEXT, 220, 10+300-20, 0, GameFont, NULL, NULL,
	{ text:{ "~<Map Tileset:~>", 0} } },
#define CLIENT_TILESET	29
    { MI_TYPE_PULLDOWN, 220, 10+300, 0, GameFont, NULL, NULL,
	{ pulldown:{ tssoptions, 152, 20, MBUTTON_PULLDOWN,
	    GameTSSAction, 5, 0, 0, 0, MI_PSTATE_PASSIVE} } },

    // 7+7 player state buttons
#define CLIENT_PLAYER_READY	30
    { MI_TYPE_GEM, 10, 32+22*1, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 10, 32+22*2, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 10, 32+22*3, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 10, 32+22*4, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 10, 32+22*5, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 10, 32+22*6, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 10, 32+22*7, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*0, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*1, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*2, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*3, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*4, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*5, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    { MI_TYPE_GEM, 330, 32+22*6, 0, LargeFont, NULL, NULL,
	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
    //{ MI_TYPE_GEM, 330, 32+22*7, 0, LargeFont, NULL, NULL,
    //	{ gem:{ 0, 18, 18, MBUTTON_GEM_SQUARE, MultiClientGemAction} } },
#else
    { 0 }
#endif
};

local Menuitem NetErrorMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Error:", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 144, 38, 0, LargeFont, NULL, NULL,
	{ text:{ NULL, MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 92, 80, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 106, 27, MBUTTON_GM_HALF, EndMenu, 'o'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Connecting Network Menu
*/
local Menuitem ConnectingMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 144, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Connecting to server", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 144, 32, 0, LargeFont, NULL, NULL,
	{ text:{ NetworkServerText, MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 144, 53, 0, LargeFont, NULL, NULL,
	{ text:{ NetworkTriesText , MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 32, 90, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel", 224, 27, MBUTTON_GM_FULL, NetConnectingCancel, 'c'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Campaign Select Menu
*/
local Menuitem CampaignSelectMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_BUTTON, 208, 212 + 36 * 0, 0, LargeFont, NULL, NULL,
	{ button:{ NULL, 224, 27, MBUTTON_GM_FULL, CampaignMenu1, 'a'} } },
    { MI_TYPE_BUTTON, 208, 212 + 36 * 1, 0, LargeFont, NULL, NULL,
	{ button:{ NULL, 224, 27, MBUTTON_GM_FULL, CampaignMenu2, 'm'} } },
    { MI_TYPE_BUTTON, 208, 212 + 36 * 2, 0, LargeFont, NULL, NULL,
	{ button:{ NULL, 224, 27, MBUTTON_GM_FULL, CampaignMenu3, 'l'} } },
    { MI_TYPE_BUTTON, 208, 212 + 36 * 3, 0, LargeFont, NULL, NULL,
	{ button:{ NULL, 224, 27, MBUTTON_GM_FULL, CampaignMenu4, 'y'} } },
    { MI_TYPE_BUTTON, 208, 212 + 36 * 4, MenuButtonDisabled, LargeFont, NULL,
	NULL, { button:{ "~!Select Campaign", 224, 27, MBUTTON_GM_FULL,
		SelectCampaignMenu, 's'} } },
    { MI_TYPE_BUTTON, 208, 212 + 36 * 5, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Previous Menu", 224, 27, MBUTTON_GM_FULL, EndMenu, 'p'} } },
#else
    { 0 }
#endif
};

/**
**	Items for the Campaign Continue Menu
*/
local Menuitem CampaignContMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_BUTTON, 508, 320 + 36 + 36 + 36, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Continue", 106, 27, MBUTTON_GM_HALF, EndMenu, 'c'} } },
#else
    { 0 }
#endif
};

local Menuitem SoundOptionsMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 176, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Sound Options", MI_TFLAGS_CENTERED} } },

    { MI_TYPE_TEXT, 16, 36*1, 0, GameFont, NULL, NULL,
	{ text:{ "Master Volume", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_HSLIDER, 32, 36*1.5, 0, 0, NULL, NULL,
        { hslider:{ 0, 11*18, 18, ScenSelectHSMasterVolumeAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_TEXT, 44, 36*2 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "min", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 218, 36*2 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "max", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_GEM, 240, 36*1.5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_UNCHECKED, 18, 18, MBUTTON_GEM_SQUARE, SetMasterPower} } },
    { MI_TYPE_TEXT, 266, 36*1.5 + 2, 0, GameFont, NULL, NULL,
	{ text:{ "Enabled", MI_TFLAGS_LALIGN} } },

    { MI_TYPE_TEXT, 16, 36*3, 0, GameFont, NULL, NULL,
	{ text:{ "Music Volume", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_HSLIDER, 32, 36*3.5, 0, 0, NULL, NULL,
        { hslider:{ 0, 11*18, 18, ScenSelectHSMusicVolumeAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_TEXT, 44, 36*4 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "min", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 218, 36*4 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "max", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_GEM, 240, 36*3.5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_UNCHECKED, 18, 18, MBUTTON_GEM_SQUARE, SetMusicPower} } },
    { MI_TYPE_TEXT, 266, 36*3.5 + 2, 0, GameFont, NULL, NULL,
	{ text:{ "Enabled", MI_TFLAGS_LALIGN} } },

    { MI_TYPE_TEXT, 16, 36*5, 0, GameFont, NULL, NULL,
	{ text:{ "CD Volume", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_HSLIDER, 32, 36*5.5, 0, 0, NULL, NULL,
        { hslider:{ 0, 11*18, 18, ScenSelectHSCdVolumeAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_TEXT, 44, 36*6 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "min", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 218, 36*6 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "max", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_GEM, 240, 36*5.5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_UNCHECKED, 18, 18, MBUTTON_GEM_SQUARE, SetCdPower} } },
    { MI_TYPE_TEXT, 266, 36*5.5 + 2, 0, GameFont, NULL, NULL,
	{ text:{ "Enabled", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_GEM, 32, 36*6.5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_UNCHECKED, 18, 18, MBUTTON_GEM_ROUND, SetCdModeAll} } },
    { MI_TYPE_TEXT, 58, 36*6.5 + 2, 0, GameFont, NULL, NULL,
	{ text:{ "All Tracks", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_GEM, 154, 36*6.5, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_UNCHECKED, 18, 18, MBUTTON_GEM_ROUND, SetCdModeRandom} } },
    { MI_TYPE_TEXT, 180, 36*6.5 + 2, 0, GameFont, NULL, NULL,
	{ text:{ "Random Tracks", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_BUTTON, 176 - (106 / 2), 352 - 11 - 27, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 106, 27, MBUTTON_GM_HALF, EndMenu, 'o'} } },
#else
    { 0 }
#endif
};

local Menuitem PreferencesMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Preferences", MI_TFLAGS_CENTERED} } },

    { MI_TYPE_GEM, 16, 36*1, 0, LargeFont, NULL, NULL,
	{ gem:{ MI_GSTATE_UNCHECKED, 18, 18, MBUTTON_GEM_SQUARE, SetFogOfWar} } },
    { MI_TYPE_TEXT, 46, 36*1 + 2, 0, GameFont, NULL, NULL,
	{ text:{ "Fog of War Enabled", MI_TFLAGS_LALIGN} } },

    { MI_TYPE_BUTTON, 128 - (106 / 2), 245, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 106, 27, MBUTTON_GM_HALF, EndMenu, 'o'} } },
#else
    { 0 }
#endif
};

local Menuitem SpeedSettingsMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Speed Settings", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_TEXT, 16, 36*1, 0, GameFont, NULL, NULL,
	{ text:{ "Game Speed", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_HSLIDER, 32, 36*1.5, 0, 0, NULL, NULL,
        { hslider:{ 0, 11*18, 18, ScenSelectHSGameSpeedAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_TEXT, 34, 36*2 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "slow", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 230, 36*2 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "fast", MI_TFLAGS_RALIGN} } },
    { MI_TYPE_TEXT, 16, 36*3, 0, GameFont, NULL, NULL,
	{ text:{ "Mouse Scroll", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_HSLIDER, 32, 36*3.5, 0, 0, NULL, NULL,
        { hslider:{ 0, 11*18, 18, ScenSelectHSMouseScrollAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_TEXT, 34, 36*4 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "off", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 230, 36*4 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "fast", MI_TFLAGS_RALIGN} } },
    { MI_TYPE_TEXT, 16, 36*5, 0, GameFont, NULL, NULL,
	{ text:{ "Keyboard Scroll", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_HSLIDER, 32, 36*5.5, 0, 0, NULL, NULL,
        { hslider:{ 0, 11*18, 18, ScenSelectHSKeyboardScrollAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_TEXT, 34, 36*6 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "off", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 230, 36*6 + 6, 0, SmallFont, NULL, NULL,
	{ text:{ "fast", MI_TFLAGS_RALIGN} } },
    { MI_TYPE_BUTTON, 128 - (106 / 2), 245, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "~!OK", 106, 27, MBUTTON_GM_HALF, EndMenu, 'o'} } },
#else
    { 0 }
#endif
};

local Menuitem GameOptionsMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Game Options", MI_TFLAGS_CENTERED} } },
#ifdef WITH_SOUND
    { MI_TYPE_BUTTON, 16, 40 + 36*0, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Sound (~!F~!7)", 224, 27, MBUTTON_GM_FULL, SoundOptions, KeyCodeF7} } },
#else
    { MI_TYPE_BUTTON, 16, 40 + 36*0, MenuButtonDisabled, LargeFont, NULL, NULL,
	{ button:{ "Sound (~!F~!7)", 224, 27, MBUTTON_GM_FULL, SoundOptions, KeyCodeF7} } },
#endif
    { MI_TYPE_BUTTON, 16, 40 + 36*1, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Speeds (~!F~!8)", 224, 27, MBUTTON_GM_FULL, SpeedSettings, KeyCodeF8} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*2, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Preferences (~!F~!9)", 224, 27, MBUTTON_GM_FULL, Preferences, KeyCodeF9} } },
    { MI_TYPE_BUTTON, 128 - (224 / 2), 245, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Previous (~!E~!s~!c)", 224, 27, MBUTTON_GM_FULL, EndMenu, '\033'} } },
#else
    { 0 }
#endif
};

local Menuitem HelpMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 128, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Help Menu", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*0, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Keystroke ~!Help", 224, 27, MBUTTON_GM_FULL, KeystrokeHelpMenu, 'h'} } },
    { MI_TYPE_BUTTON, 16, 40 + 36*1, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Freecraft ~!Tips", 224, 27, MBUTTON_GM_FULL, ShowTipsMenu, 't'} } },
    { MI_TYPE_BUTTON, 128 - (224 / 2), 288-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Previous (~!E~!s~!c)", 224, 27, MBUTTON_GM_FULL, EndMenu, '\033'} } },
#else
    { 0 }
#endif
};

local Menuitem KeystrokeHelpMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 352/2, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Keystroke Help Menu", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_VSLIDER, 352 - 18 - 16, 40+20, 0, 0, NULL, NULL,
	{ vslider:{ 0, 18, 12*18, ScenSelectVSKeystrokeHelpAction, -1, 0, 0, 0, NULL} } },
    { MI_TYPE_BUTTON, 352/2 - (224 / 2), 352-40, MenuButtonSelected, LargeFont, NULL, NULL,
	{ button:{ "Previous (~!E~!s~!c)", 224, 27, MBUTTON_GM_FULL, EndMenu, '\033'} } },
    { MI_TYPE_TEXT, 16, 40+20, 0, GameFont, NULL, NULL,
	{ text:{ "Alt-F  - toggle full screen", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*2, 0, GameFont, NULL, NULL,
	{ text:{ "Ctrl-S - mute sound", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*3, 0, GameFont, NULL, NULL,
	{ text:{ "Alt-Q  - quit to main menu", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*4, 0, GameFont, NULL, NULL,
	{ text:{ "+      - increase game speed", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*5, 0, GameFont, NULL, NULL,
	{ text:{ "-      - decrease game speed", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*6, 0, GameFont, NULL, NULL,
	{ text:{ "Ctrl-P - pause game", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*7, 0, GameFont, NULL, NULL,
	{ text:{ "Alt-G  - toggle grab mouse", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*8, 0, GameFont, NULL, NULL,
	{ text:{ "Alt-X  - quit game", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*9, 0, GameFont, NULL, NULL,
	{ text:{ "Alt-B  - toggle expand map", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*10, 0, GameFont, NULL, NULL,
	{ text:{ "ENTER  - write a message", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*11, 0, GameFont, NULL, NULL,
	{ text:{ "TAB    - hide/unhide terrain", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*12, 0, GameFont, NULL, NULL,
	{ text:{ "Alt-I  - find idle peon", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*13, 0, GameFont, NULL, NULL,
	{ text:{ "F10    - game menu", MI_TFLAGS_LALIGN} } },
    { MI_TYPE_TEXT, 16, 40+20*14, 0, GameFont, NULL, NULL,
	{ text:{ "F5     - game options", MI_TFLAGS_LALIGN} } },


#else
    { 0 }
#endif
};

local Menuitem SaveGameMenuItems[] = {
#ifdef __GNUC__
    { MI_TYPE_TEXT, 384/2, 11, 0, LargeFont, NULL, NULL,
	{ text:{ "Save Game", MI_TFLAGS_CENTERED} } },
    { MI_TYPE_INPUT, 16, 11+36*1, 0, SmallFont, NULL, NULL,
	{ input:{ "test123", 384-16-16, 16, MI_TFLAGS_CENTERED, NULL, 7, 33} } },
    { MI_TYPE_LISTBOX, 16, 11+36*1.5, 0, GameFont, ScenSelectLBInit, ScenSelectLBExit,
	{ listbox:{ NULL, 384-16-16-16, 7*18, MBUTTON_PULLDOWN, ScenSelectLBAction, 0, 0, 0, 0, 7, 0,
		    (void *)ScenSelectLBRetrieve, ScenSelectOk} } },
    { MI_TYPE_VSLIDER, 384-16-16, 11+36*1.5, 0, 0, NULL, NULL,
	{ vslider:{ 0, 18, 7*18, ScenSelectVSAction, -1, 0, 0, 0, ScenSelectOk} } },
    { MI_TYPE_BUTTON, 384/3 - 106 - 10, 256-16-27, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Save", 106, 27, MBUTTON_GM_HALF, EndMenu, 's'} } },
    { MI_TYPE_BUTTON, 2*384/3 - 106 - 10, 256-16-27, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Delete", 106, 27, MBUTTON_GM_HALF, EndMenu, 'd'} } },
    { MI_TYPE_BUTTON, 3*384/3 - 106 - 10, 256-16-27, 0, LargeFont, NULL, NULL,
	{ button:{ "~!Cancel", 106, 27, MBUTTON_GM_HALF, EndMenu, 'c'} } },

#else
    { 0 }
#endif
};

/**
**	FIXME: Ari please look, this is now in TheUI.
*/
enum {
    ImageNone,
    ImagePanel1,	// 256 x 288
    ImagePanel2,	// 288 x 256
    ImagePanel3,	// 384 x 256
    ImagePanel4,	// 288 x 128
    ImagePanel5,	// 352 x 352
};

/**
**	Menus
*/
global Menu Menus[] = {
    {
	// Game Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	7, 8,
	GameMenuItems,
	NULL,
    },
    {
	// Victory Menu
	176+(14*TileSizeX-288)/2,
	16+(14*TileSizeY-128)/2,
	288, 128,
	ImagePanel4,
	2, 4,
	VictoryMenuItems,
	NULL,
    },
    {
	// Lost Menu
	176+(14*TileSizeX-288)/2,
	16+(14*TileSizeY-128)/2,
	288, 128,
	ImagePanel4,
	2, 3,
	LostMenuItems,
	NULL,
    },
    {
	// SelectScen Menu
	(640-352)/2,
	(480-352)/2,
	352, 352,
	ImagePanel5,
	4, 10,
	ScenSelectMenuItems,
	NULL,
    },
    {
	// PrgStart Menu
	0,
	0,
	640, 480,
	ImageNone,
	1, 8,
	PrgStartMenuItems,
	NULL,
    },
    {
	// CustomGame Menu
	0,
	0,
	640, 480,
	ImageNone,
	3, 15,
	CustomGameMenuItems,
	NULL,
    },
    {
	// Enter Name Menu
	(640-288)/2,
	260,
	288, 128,
	ImagePanel4,
	2, 4,
	EnterNameMenuItems,
	NULL,
    },
    {
	// Net Create Join Menu
	0,
	0,
	640, 480,
	ImageNone,
	2, 3,
	NetCreateJoinMenuItems,
	NULL,
    },
    {
	// Multi Player Setup Menu
	0,
	0,
	640, 480,
	ImageNone,
	3, 58,
	NetMultiSetupMenuItems,
	NULL,
    },
    {
	// Enter Server Menu
	(640-288)/2,
	260,
	288, 128,
	ImagePanel4,
	3, 4,
	EnterServerIPMenuItems,
	NULL,
    },
    {
	// Multi Player Client Menu
	0,
	0,
	640, 480,
	ImageNone,
	4, 44,
	NetMultiClientMenuItems,		// FIXME: unfinished
	TerminateNetConnect,
    },
    {
	// Connecting Menu
	(640-288)/2,
	260,
	288, 128,
	ImagePanel4,
	2, 4,
	ConnectingMenuItems,
	TerminateNetConnect,
    },
    {
	// Campaign Select Menu
	0,
	0,
	640, 480,
	ImageNone,
	0, 6,
	CampaignSelectMenuItems,
	NULL,
    },
    {
	// Campaign Continue Menu
	0,
	0,
	640, 480,
	ImageNone,
	0, 1,
	CampaignContMenuItems,
	NULL,
    },
    {
	// Objectives Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	10, 11,
	ObjectivesMenuItems,
	NULL,
    },
    {
	// End Scenario Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	5, 6,
	EndScenarioMenuItems,
	NULL,
    },
    {
	// Sound Options Menu
	176+(14*TileSizeX-352)/2,
	16+(14*TileSizeY-352)/2,
	352, 352,
	ImagePanel5,
	24, 24,
	SoundOptionsMenuItems,
	NULL,
    },
    {
	// Preferences Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	4, 4,
	PreferencesMenuItems,
	NULL,
    },
    {
	// Speed Settings Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	14, 14,
	SpeedSettingsMenuItems,
	NULL,
    },
    {
	// Game Options Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	4, 5,
	GameOptionsMenuItems,
	NULL,
    },
    {
	// Net Errors Menu
	(640-288)/2,
	260,
	288, 128,
	ImagePanel4,
	2, 3,
	NetErrorMenuItems,
	NULL,
    },
    {
	// Tips Menu
	176+(14*TileSizeX-288)/2,
	16+(14*TileSizeY-256)/2,
	288, 256,
	ImagePanel2,
	4, 13,
	TipsMenuItems,
	NULL,
    },
    {
	// Help Menu
	176+(14*TileSizeX-256)/2,
	16+(14*TileSizeY-288)/2,
	256, 288,
	ImagePanel1,
	4, 4,
	HelpMenuItems,
	NULL,
    },
    {
	// Keystroke Help Menu
	176+(14*TileSizeX-352)/2,
	16+(14*TileSizeY-352)/2,
	352, 352,
	ImagePanel5,
	17, 17,
	KeystrokeHelpMenuItems,
	NULL,
    },
    {
	// Save Menu
	176+(14*TileSizeX-384)/2,
	16+(14*TileSizeY-256)/2,
	384, 256,
	ImagePanel3,
	7, 7,
	SaveGameMenuItems,
	NULL,
    },

};

/*----------------------------------------------------------------------------
--	Functions
----------------------------------------------------------------------------*/

/**
**	Draw menu button 'button' on x,y
**
**	@param button	Button identifier
**	@param flags	State of Button (clicked, mouse over...)
**	@param w	Button width (for border)
**	@param h	Button height (for border)
**	@param x	X display position
**	@param y	Y display position
**	@param font	font number for text
**	@param text	text to print on button
*/
global void DrawMenuButton(MenuButtonId button,unsigned flags,unsigned w,unsigned h,unsigned x,unsigned y,
	const int font,const unsigned char *text)
{
    MenuButtonId rb;
    int s, nc, rc;

    GetDefaultTextColors(&nc, &rc);
    if (flags&MenuButtonDisabled) {
	rb = button - 1;
	s = 0;
	SetDefaultTextColors(FontGrey,FontGrey);
    } else if (flags&MenuButtonClicked) {
	rb = button + 1;
	s = 2;
	SetDefaultTextColors(rc,rc);
    } else {
	rb = button;
	s = 0;
	if (flags&MenuButtonActive) {
	    SetDefaultTextColors(rc,rc);
	}
    }
    if (rb < MenuButtonGfx.Sprite->NumFrames) {
	VideoDraw(MenuButtonGfx.Sprite, rb, x, y);
    } else {
	if (rb < button) {
	    VideoDrawRectangleClip(ColorGray,x+1,y+1,w-2,h-2);
	    VideoDrawRectangleClip(ColorGray,x+2,y+2,w-4,h-4);
	} else {
	    // FIXME: Temp-workaround for missing folder button in non-expansion gfx
	    VideoDrawRectangleClip(ColorYellow,x+1,y+1,w-2,h-2);
	    VideoDrawRectangleClip(ColorYellow,x+2,y+2,w-4,h-4);
	}
    }
    if (text) {
	if (button != MBUTTON_FOLDER) {
	    VideoDrawTextCentered(s+x+w/2,s+y+(font == GameFont ? 4 : 7),font,text);
	} else {
	    SetDefaultTextColors(nc,rc);
	    VideoDrawText(x+44,y+6,font,text);
	}
    }
    if (flags&MenuButtonSelected) {
	if (flags&MenuButtonDisabled) {
	    VideoDrawRectangleClip(ColorGray,x,y,w-1,h);
	} else {
	    VideoDrawRectangleClip(ColorYellow,x,y,w-1,h);
	}
    }
    SetDefaultTextColors(nc,rc);
}

/**
**	Draw pulldown 'button' on menu mx, my
**
**	@param mi	menuitem pointer
**	@param mx	menu X display position (offset)
**	@param my	menu Y display position (offset)
*/
local void DrawPulldown(Menuitem *mi, unsigned mx, unsigned my)
{
    int i, nc, rc;
    char *text;
    unsigned flags = mi->flags;
    MenuButtonId rb = mi->d.pulldown.button;
    unsigned w, h, x, y, oh;
    x = mx+mi->xofs;
    y = my+mi->yofs;
    w = mi->d.pulldown.xsize;
    oh = h = mi->d.pulldown.ysize - 2;

    GetDefaultTextColors(&nc, &rc);
    if (flags&MenuButtonClicked) {
	y -= mi->d.pulldown.curopt * h;
	i = mi->d.pulldown.noptions;
	h *= i;
	while (i--) {
	    PushClipping();
	    SetClipping(0,0,x+w,VideoHeight-1);
	    VideoDrawClip(MenuButtonGfx.Sprite, rb, x-1, y-1 + oh*i);
	    PopClipping();
	    text = mi->d.pulldown.options[i];
	    if (text) {
		if (i == mi->d.pulldown.cursel)
		    SetDefaultTextColors(rc,rc);
		else
		    SetDefaultTextColors(nc,rc);
		VideoDrawText(x+2,y+2 + oh*i ,mi->font,text);
	    }
	}
	w += 2;
    } else {
	h = mi->d.pulldown.ysize;
	y = my+mi->yofs;
	if (flags&MenuButtonDisabled) {
	    rb--;
	    SetDefaultTextColors(FontGrey,FontGrey);
	} else {
	    if (flags&MenuButtonActive) {
		SetDefaultTextColors(rc,rc);
	    }
	}

	PushClipping();
	if (!(mi->d.pulldown.state & MI_PSTATE_PASSIVE)) {
	    SetClipping(0,0,x+w-20,VideoHeight-1);
	} else {
	    SetClipping(0,0,x+w-1,VideoHeight-1);
	}
	VideoDrawClip(MenuButtonGfx.Sprite, rb, x-1, y-1);
	PopClipping();
	if (!(mi->d.pulldown.state & MI_PSTATE_PASSIVE)) {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_DOWN_ARROW + rb - MBUTTON_PULLDOWN, x-1 + w-20, y-2);
	}
	text = mi->d.pulldown.options[mi->d.pulldown.curopt];
	if (text) {
	    VideoDrawText(x+2,y+2,mi->font,text);
	}
    }
    if (flags&MenuButtonSelected) {
	if (flags&MenuButtonDisabled) {
	    VideoDrawRectangleClip(ColorGray,x-2,y-2,w,h);
	} else {
	    VideoDrawRectangleClip(ColorYellow,x-2,y-2,w,h);
	}
    }
    SetDefaultTextColors(nc,rc);
}

/**
**	Draw listbox 'button' on menu mx, my
**
**	@param mi	menuitem pointer
**	@param mx	menu X display position (offset)
**	@param my	menu Y display position (offset)
*/
local void DrawListbox(Menuitem *mi, unsigned mx, unsigned my)
{
    int i, s, nc, rc;
    char *text;
    MenuButtonId rb = mi->d.listbox.button;
    unsigned flags = mi->flags;
    unsigned w, h, x, y;
    w = mi->d.listbox.xsize;
    h = mi->d.listbox.ysize;
    x = mx+mi->xofs;
    y = my+mi->yofs;

    GetDefaultTextColors(&nc, &rc);

    if (flags&MenuButtonDisabled) {
	rb--;
    }
    i = mi->d.listbox.nlines;
    s = mi->d.listbox.startline;
    while (i--) {
	PushClipping();
	SetClipping(0,0,x+w,VideoHeight-1);
	VideoDrawClip(MenuButtonGfx.Sprite, rb, x-1, y-1 + 18*i);
	PopClipping();
	if (!(flags&MenuButtonDisabled)) {
	    if (i < mi->d.listbox.noptions) {
		SetDefaultTextColors(nc,rc);
		text = (*mi->d.listbox.retrieveopt)(mi, i + s);
		if (text) {
		    if (i == mi->d.listbox.curopt)
			SetDefaultTextColors(rc,rc);
		    else
			SetDefaultTextColors(nc,rc);
		    VideoDrawText(x+2,y+2 + 18*i ,mi->font,text);
		}
	    }
	}
    }

    if (flags&MenuButtonSelected) {
	if (flags&MenuButtonDisabled) {
	    VideoDrawRectangleClip(ColorGray,x-2,y-2,w+1,h+2);
	} else {
	    VideoDrawRectangleClip(ColorYellow,x-2,y-2,w+1,h+2);
	}
    }
    SetDefaultTextColors(nc,rc);
}

/**
**	Draw vslider 'button' on menu mx, my
**
**	@param mi	menuitem pointer
**	@param mx	menu X display position (offset)
**	@param my	menu Y display position (offset)
*/
local void DrawVSlider(Menuitem *mi, unsigned mx, unsigned my)
{
    int p;
    unsigned flags = mi->flags;
    unsigned w, h, x, y;
    w = mi->d.vslider.xsize;
    h = mi->d.vslider.ysize;
    x = mx+mi->xofs;
    y = my+mi->yofs;

    if (flags&MenuButtonDisabled) {
	PushClipping();
	SetClipping(0,0,VideoWidth-1,y + h - 20);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_VCONT - 1, x, y - 2);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_VCONT - 1, x, y + h/2);
	PopClipping();
	VideoDraw(MenuButtonGfx.Sprite, MBUTTON_UP_ARROW - 1, x, y - 2);
	VideoDraw(MenuButtonGfx.Sprite, MBUTTON_DOWN_ARROW - 1, x, y + h - 20);
    } else {
	PushClipping();
	SetClipping(0,0,VideoWidth-1,y + h - 20);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_VCONT, x, y - 2);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_VCONT, x, y + h/2);
	PopClipping();
	if (mi->d.vslider.cflags&MI_CFLAGS_UP) {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_UP_ARROW + 1, x, y - 2);
	} else {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_UP_ARROW, x, y - 2);
	}
	if (mi->d.vslider.cflags&MI_CFLAGS_DOWN) {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_DOWN_ARROW + 1, x, y + h - 20);
	} else {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_DOWN_ARROW, x, y + h - 20);
	}
	p = (mi->d.vslider.percent * (h - 54)) / 100;
	VideoDraw(MenuButtonGfx.Sprite, MBUTTON_S_KNOB, x + 1, y + 18 + p);
    }

    if (flags&MenuButtonSelected) {
	if (flags&MenuButtonDisabled) {
	    VideoDrawRectangleClip(ColorGray,x,y-2,w,h+2);
	} else {
	    VideoDrawRectangleClip(ColorYellow,x,y-2,w,h+2);
	}
    }

}

/**
**	Draw hslider 'button' on menu mx, my
**
**	@param mi	menuitem pointer
**	@param mx	menu X display position (offset)
**	@param my	menu Y display position (offset)
*/
local void DrawHSlider(Menuitem *mi, unsigned mx, unsigned my)
{
    int p;
    unsigned flags = mi->flags;
    unsigned w, h, x, y;
    w = mi->d.hslider.xsize;
    h = mi->d.hslider.ysize;
    x = mx+mi->xofs;
    y = my+mi->yofs;

    if (flags&MenuButtonDisabled) {
	PushClipping();
	SetClipping(0,0,x + w - 20,VideoHeight-1);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_HCONT - 1, x - 2, y);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_HCONT - 1, x + w/2, y);
	PopClipping();
	VideoDraw(MenuButtonGfx.Sprite, MBUTTON_LEFT_ARROW - 1, x - 2, y);
	VideoDraw(MenuButtonGfx.Sprite, MBUTTON_RIGHT_ARROW - 1, x + w - 20, y);
    } else {
	PushClipping();
	SetClipping(0,0,x + w - 20,VideoHeight-1);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_HCONT, x - 2, y);
	VideoDrawClip(MenuButtonGfx.Sprite, MBUTTON_S_HCONT, x + w/2, y);
	PopClipping();
	if (mi->d.hslider.cflags&MI_CFLAGS_LEFT) {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_LEFT_ARROW + 1, x - 2, y);
	} else {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_LEFT_ARROW, x - 2, y);
	}
	if (mi->d.hslider.cflags&MI_CFLAGS_RIGHT) {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_RIGHT_ARROW + 1, x + w - 20, y);
	} else {
	    VideoDraw(MenuButtonGfx.Sprite, MBUTTON_RIGHT_ARROW, x + w - 20, y);
	}
	p = (mi->d.hslider.percent * (w - 54)) / 100;
	VideoDraw(MenuButtonGfx.Sprite, MBUTTON_S_KNOB, x + 18 + p, y + 1);
    }

    if (flags&MenuButtonSelected) {
	if (flags&MenuButtonDisabled) {
	    VideoDrawRectangleClip(ColorGray,x-2,y,w+2,h);
	} else {
	    VideoDrawRectangleClip(ColorYellow,x-2,y,w+2,h);
	}
    }

}

/**
**	Draw gem 'button' on menu mx, my
**
**	@param mi	menuitem pointer
**	@param mx	menu X display position (offset)
**	@param my	menu Y display position (offset)
*/
local void DrawGem(Menuitem *mi, unsigned mx, unsigned my)
{
    unsigned flags = mi->flags;
    MenuButtonId rb = mi->d.gem.button;
    unsigned x, y;

    x = mx+mi->xofs;
    y = my+mi->yofs;
    if ((mi->d.gem.state & MI_GSTATE_INVISIBLE)) {
	return;
    }
    if (flags&MenuButtonDisabled) {
	rb--;
    } else if (flags&MenuButtonClicked) {
	rb++;
    }
    if ((mi->d.gem.state & MI_GSTATE_CHECKED)) {
	rb += 2;
    }
    VideoDraw(MenuButtonGfx.Sprite, rb, x, y);
}

/**
**	Draw input 'button' on menu mx, my
**
**	@param mi	menuitem pointer
**	@param mx	menu X display position (offset)
**	@param my	menu Y display position (offset)
*/
local void DrawInput(Menuitem *mi, unsigned mx, unsigned my)
{
    int nc, rc;
    char *text;
    unsigned flags = mi->flags;
    MenuButtonId rb = mi->d.input.button;
    unsigned w, h, x, y;

    x = mx+mi->xofs;
    y = my+mi->yofs;
    w = mi->d.input.xsize;
    h = mi->d.input.ysize;

    GetDefaultTextColors(&nc, &rc);
    if (flags&MenuButtonDisabled) {
	rb--;
	SetDefaultTextColors(FontGrey,FontGrey);
    }

    PushClipping();
    SetClipping(0,0,x+w,VideoHeight-1);
    VideoDrawClip(MenuButtonGfx.Sprite, rb, x-1, y-1);
    PopClipping();
    text = mi->d.input.buffer;
    if (text) {
	VideoDrawText(x+2,y+2,mi->font,text);
    }
    if (flags&MenuButtonSelected) {
	if (flags&MenuButtonDisabled) {
	    VideoDrawRectangleClip(ColorGray,x-2,y-2,w,h);
	} else {
	    VideoDrawRectangleClip(ColorYellow,x-2,y-2,w,h);
	}
    }
    SetDefaultTextColors(nc,rc);
}


/**
**	Draw a menu.
**
**	@param menu_id	The menu number to display
*/
global void DrawMenu(int menu_id)
{
    int i, n, l;
    Menu *menu;
    Menuitem *mi, *mip;

    MustRedraw &= ~RedrawMenu;
    if (menu_id == -1) {
	return;
    }

    menu = Menus + menu_id;
    switch( menu->image ) {
	case ImagePanel1:
	    VideoDrawSub(TheUI.GameMenuePanel.Graphic,0,0,
		    VideoGraphicWidth(TheUI.GameMenuePanel.Graphic),
		    VideoGraphicHeight(TheUI.GameMenuePanel.Graphic),
		    menu->x,menu->y);
	    break;
	case ImagePanel2:
	    VideoDrawSub(TheUI.Menue1Panel.Graphic,0,0,
		    VideoGraphicWidth(TheUI.Menue1Panel.Graphic),
		    VideoGraphicHeight(TheUI.Menue1Panel.Graphic),
		    menu->x,menu->y);
	    break;
	case ImagePanel3:
	    VideoDrawSub(TheUI.Menue2Panel.Graphic,0,0,
		   VideoGraphicWidth(TheUI.Menue2Panel.Graphic),
		   VideoGraphicHeight(TheUI.Menue2Panel.Graphic),
		   menu->x,menu->y);
	    break;
	case ImagePanel4:
	    VideoDrawSub(TheUI.VictoryPanel.Graphic,0,0,
		   VideoGraphicWidth(TheUI.VictoryPanel.Graphic),
		   VideoGraphicHeight(TheUI.VictoryPanel.Graphic),
		   menu->x,menu->y);
	    break;
	case ImagePanel5:
	    VideoDrawSub(TheUI.ScenarioPanel.Graphic,0,0,
		   VideoGraphicWidth(TheUI.ScenarioPanel.Graphic),
		   VideoGraphicHeight(TheUI.ScenarioPanel.Graphic),
		   menu->x,menu->y);
	default:
	    break;
    }
    n = menu->nitems;
    mi = menu->items;
    mip = NULL;
    for (i = 0; i < n; i++) {
	switch (mi->mitype) {
	    case MI_TYPE_TEXT:
		if (!mi->d.text.text)
		    break;
		if (mi->d.text.tflags&MI_TFLAGS_CENTERED)
		    VideoDrawTextCentered(menu->x+mi->xofs,menu->y+mi->yofs,
			    mi->font,mi->d.text.text);
		else if (mi->d.text.tflags&MI_TFLAGS_RALIGN) {
		    l = VideoTextLength(mi->font,mi->d.text.text);
		    VideoDrawText(menu->x+mi->xofs-l,menu->y+mi->yofs,
			    mi->font,mi->d.text.text);
		} else
		    VideoDrawText(menu->x+mi->xofs,menu->y+mi->yofs,
			    mi->font,mi->d.text.text);
		break;
	    case MI_TYPE_BUTTON:
		DrawMenuButton(mi->d.button.button,mi->flags,
			mi->d.button.xsize,mi->d.button.ysize,
			menu->x+mi->xofs,menu->y+mi->yofs,
			mi->font,mi->d.button.text);
		break;
	    case MI_TYPE_PULLDOWN:
		if (mi->flags&MenuButtonClicked) {
		    mip = mi;	// Delay, due to possible overlaying!
		} else {
		    DrawPulldown(mi,menu->x,menu->y);
		}
		break;
	    case MI_TYPE_LISTBOX:
		DrawListbox(mi,menu->x,menu->y);
		break;
	    case MI_TYPE_VSLIDER:
		DrawVSlider(mi,menu->x,menu->y);
		break;
	    case MI_TYPE_HSLIDER:
		DrawHSlider(mi,menu->x,menu->y);
		break;
	    case MI_TYPE_DRAWFUNC:
		if (mi->d.drawfunc.draw) {
		    (*mi->d.drawfunc.draw)(mi);
		}
		break;
	    case MI_TYPE_INPUT:
		DrawInput(mi,menu->x,menu->y);
		break;
	    case MI_TYPE_GEM:
		DrawGem(mi,menu->x,menu->y);
		break;
	    default:
		break;
	}
	mi++;
    }
    if (mip) {
	DrawPulldown(mip,menu->x,menu->y);
    }

    InvalidateArea(menu->x,menu->y,menu->xsize,menu->ysize);
}

/*----------------------------------------------------------------------------
--	Button action handler and Init/Exit functions
----------------------------------------------------------------------------*/

/**
**	Set start menu backgound and draw it.
*/
local void StartMenusSetBackground(Menuitem *mi __attribute__((unused)))
{
    DestroyCursorBackground();
    if (!Menusbgnd) {
	Menusbgnd = LoadGraphic(MenuBackground);
	VideoSetPalette(Menusbgnd->Pixels);
    }

    // VideoLockScreen();

    // FIXME: bigger window ?
    VideoDrawSubClip(Menusbgnd,0,0,
	Menusbgnd->Width,Menusbgnd->Height,
	(VideoWidth-Menusbgnd->Width)/2,(VideoHeight-Menusbgnd->Height)/2);

    // VideoUnlockScreen();
}

/**
**	Draw the version and copyright at bottom of the screen.
**	Also include now the license.
*/
local void NameLineDrawFunc(Menuitem *mi __attribute__((unused)))
{
    int nc, rc;

    GetDefaultTextColors(&nc, &rc);
    StartMenusSetBackground(mi);
    SetDefaultTextColors(rc, rc);

#ifdef WITH_SOUND
    if( SoundFildes==-1 ) {
	VideoDrawText(16,16,LargeFont,"Sound disabled, please check!");
    }
#endif

    VideoDrawTextCentered(VideoWidth/2, OffsetY + 440, GameFont, NameLine);
    VideoDrawTextCentered(VideoWidth/2, OffsetY + 456, GameFont,
	"Engine distributed under the terms of the GNU General Public License.");
    SetDefaultTextColors(nc, rc);
}

/**
**	Start menu master init.
**
**	@param mi	The menu.
*/
local void PrgStartInit(Menuitem *mi)
{
#ifdef NEW_NETMENUS
    if (NetworkNumInterfaces == 0) {
	mi[2].flags = MenuButtonDisabled;
    } else {
	mi[2].flags = 0;
    }
#else
    mi[2].flags = MenuButtonDisabled;
#endif
}

local void GameMenuReturn(void)
{
    EndMenu();
    MustRedraw &= ~RedrawMenu;
    InterfaceState = IfaceStateNormal;
    ClearStatusLine();
    MarkDrawEntireMap();	//FIXME: some tiles could be left as they were?
    MustRedraw=RedrawEverything;
    GamePaused = 0;
}

local void GameMenuSave(void)
{
    ProcessMenu(MENU_SAVE_GAME, 1);
}

local void GameMenuLoad(void)
{
    LoadAll();	// FIXME: Sample code
}

global void SoundOptions(void)
{
#ifdef WITH_SOUND
    SoundOptionsMenuItems[2].flags = 0;				// master volume slider
    SoundOptionsMenuItems[5].d.gem.state = MI_GSTATE_CHECKED;	// master power
    SoundOptionsMenuItems[8].flags = 0;				// music volume slider
    SoundOptionsMenuItems[11].flags = 0;			// music power
    SoundOptionsMenuItems[11].d.gem.state = MI_GSTATE_CHECKED;
    SoundOptionsMenuItems[14].flags = 0;			// cd volume slider
    SoundOptionsMenuItems[17].d.gem.state = MI_GSTATE_CHECKED;	// cd power
    SoundOptionsMenuItems[19].flags = 0;			// all tracks button
    SoundOptionsMenuItems[19].d.gem.state = MI_GSTATE_UNCHECKED;
    SoundOptionsMenuItems[21].flags = 0;			// random tracks button
    SoundOptionsMenuItems[21].d.gem.state = MI_GSTATE_UNCHECKED;

    // Set master volume checkbox and slider
    if (SoundFildes == -1) {
	SoundOptionsMenuItems[5].d.gem.state = MI_GSTATE_UNCHECKED;
	SoundOptionsMenuItems[2].flags = -1;
	SoundOptionsMenuItems[11].flags = -1;
    }
    SoundOptionsMenuItems[2].d.hslider.percent = (GlobalVolume * 100) / 255;

    // Set music volume checkbox and slider
    if (PlayingMusic != 1 || SoundFildes == -1) {
	SoundOptionsMenuItems[11].d.gem.state = MI_GSTATE_UNCHECKED;
	SoundOptionsMenuItems[8].flags = -1;
    }
    SoundOptionsMenuItems[8].d.hslider.percent = (MusicVolume * 100) / 255;

#if defined(USE_LIBCDA) || defined(USE_SDLCD)
    if (!strcmp(":off", CDMode) || !strcmp(":stopped", CDMode)) {
	SoundOptionsMenuItems[17].d.gem.state = MI_GSTATE_UNCHECKED;
	SoundOptionsMenuItems[14].flags = -1;
	SoundOptionsMenuItems[19].flags = -1;

	SoundOptionsMenuItems[21].flags = -1;
    } else {
#ifdef USE_LIBCDA
	int i = 17;

	cd_get_volume(&i, &i);
	SoundOptionsMenuItems[14].d.hslider.percent = (i * 100) / 255;
#endif
	if (!strcmp(":all", CDMode)) {
	    SoundOptionsMenuItems[19].d.gem.state = MI_GSTATE_CHECKED;
	}
	if (!strcmp(":random", CDMode)) {
	    SoundOptionsMenuItems[21].d.gem.state = MI_GSTATE_CHECKED;
	}
	SoundOptionsMenuItems[11].flags = -1;
    }
#else
    SoundOptionsMenuItems[14].flags = -1;			// cd volume slider
    SoundOptionsMenuItems[17].flags = -1;			// cd power
    SoundOptionsMenuItems[17].d.gem.state = MI_GSTATE_UNCHECKED;
    SoundOptionsMenuItems[19].flags = -1;			// all tracks button
    SoundOptionsMenuItems[21].flags = -1;			// random tracks button
#endif
    ProcessMenu(MENU_SOUND_OPTIONS, 1);
#endif // with sound
}

local void SetMasterPower(Menuitem *mi __attribute__((unused)))
{
#ifdef WITH_SOUND
#ifdef USE_SDLA
    if (SoundFildes != -1) {
	SDL_CloseAudio();
	SoundFildes=-1;
    } else {
	InitSound();
	MapUnitSounds();
	InitSoundServer();
	InitSoundClient();
	SoundOff=0;
    }
#else
    if (SoundFildes != -1) {
        close(SoundFildes);
        SoundFildes=-1;
    } else {
	InitSound();
	MapUnitSounds();
	InitSoundServer();
	InitSoundClient();
	SoundOff=0;
    }
#endif
#endif // with sound
    CurrentMenu=-1;
    SoundOptions();
}

local void SetMusicPower(Menuitem *mi __attribute__((unused)))
{
#ifdef WITH_SOUND
    SCM cb;

    if (PlayingMusic == 1) {
	StopMusic();
    } else {
            if (CallbackMusic) {
                cb = gh_symbol2scm("music-stopped");
                if (!gh_null_p(symbol_boundp(cb, NIL))) {
                    SCM value;

                    value = symbol_value(cb, NIL);
                    if (!gh_null_p(value)) {
                        gh_apply(value, NIL);
                    }
                }
            }
    }
#endif // with sound
    CurrentMenu=-1;
    SoundOptions();
}

local void SetCdPower(Menuitem *mi __attribute__((unused)))
{
#ifdef USE_SDLCD
    // Start Playing CD
    if (!strcmp(":off", CDMode) || !strcmp(":stopped", CDMode)) {
#ifdef USE_WIN32
	SDL_CDResume(CDRom);
#endif
	PlayMusic(":random");
    } else {
    // Stop Playing CD
        SDL_CDPause(CDRom);
	CDMode = ":stopped";
    }
#elif defined(USE_LIBCDA)
    // Start Playing CD
    if (!strcmp(":off", CDMode) || !strcmp(":stopped", CDMode)) {
	PlayMusic(":random");
    } else {
    // Stop Playing CD
        cd_pause();
	CDMode = ":stopped";
    }
#endif
    CurrentMenu=-1;
    SoundOptions();
}

local void SetFogOfWar(Menuitem *mi __attribute__((unused)))
{
    if (!TheMap.NoFogOfWar) {
        TheMap.NoFogOfWar = 1;
        UpdateFogOfWarChange();
        MapUpdateVisible();
    } else {
        TheMap.NoFogOfWar = 0;
        UpdateFogOfWarChange();
        MapUpdateVisible();
    }
}

local void SetCdModeAll(Menuitem *mi __attribute__((unused)))
{
#if defined(USE_LIBCDA) || defined(USE_SDLCD)
    CDMode = ":all";
#endif
    CurrentMenu=-1;
    SoundOptions();

}

local void SetCdModeRandom(Menuitem *mi __attribute__((unused)))
{
#if defined(USE_LIBCDA) || defined(USE_SDLCD)
    CDMode = ":random";
#endif
    CurrentMenu=-1;
    SoundOptions();

}

global void SpeedSettings(void)
{
    int i = 2;

    SpeedSettingsMenuItems[i].d.hslider.percent = ((VideoSyncSpeed - MIN_GAME_SPEED) * 100) / (MAX_GAME_SPEED - MIN_GAME_SPEED);
    if (SpeedSettingsMenuItems[i].d.hslider.percent < 0)
	SpeedSettingsMenuItems[i].d.hslider.percent = 0;
    if (SpeedSettingsMenuItems[i].d.hslider.percent > 100)
	SpeedSettingsMenuItems[i].d.hslider.percent = 100;
    SpeedSettingsMenuItems[i + 4].d.hslider.percent = 100 - (SpeedMouseScroll - 1) * 100 / 10;
    if (TheUI.MouseScroll == 0)
	SpeedSettingsMenuItems[i + 4].d.hslider.percent = 0;
    SpeedSettingsMenuItems[i + 8].d.hslider.percent = 100 - (SpeedKeyScroll - 1) * 100 / 10;
    if (TheUI.KeyScroll == 0)
	SpeedSettingsMenuItems[i + 8].d.hslider.percent = 0;
    ProcessMenu(MENU_SPEED_SETTINGS, 1);
}

global void Preferences(void)
{
    if (!TheMap.NoFogOfWar)
	PreferencesMenuItems[1].d.gem.state = MI_GSTATE_CHECKED;
    else
	PreferencesMenuItems[1].d.gem.state = MI_GSTATE_UNCHECKED;
    ProcessMenu(MENU_PREFERENCES, 1);
}

/**
**	Show the game options.
*/
local void GameOptions(void)
{
    ProcessMenu(MENU_GAME_OPTIONS, 1);
}

/**
**	Show the global options.
*/
local void GameGlobalOptionsMenu(void)
{
    // FIXME: write me
}

/**
**	Show the game credits.
*/
local void GameShowCredits(void)
{
    ShowCredits(&GameCredits);
}

/**
**	Show the End Scenario menu
*/
local void GameMenuEndScenario(void)
{
    ProcessMenu(MENU_END_SCENARIO, 1);
    if( !GameRunning )
	EndMenu();
}

/**
**	Restart the scenario
*/
local void EndScenarioRestart(void)
{
    RestartScenario=1;
    InterfaceState=IfaceStateNormal;
    GameRunning=0;
    EndMenu();
}

/**
**	End the game in defeat
*/
local void EndScenarioSurrender(void)
{
    InterfaceState=IfaceStateNormal;
    GameResult=GameDefeat;
    GameRunning=0;
    EndMenu();
}

/**
**	End the game and return to the menu
*/
local void EndScenarioQuitMenu(void)
{
    QuitToMenu=1;
    InterfaceState=IfaceStateNormal;
    GameRunning=0;
    EndMenu();
}

/**
**	End the running game from menu.
*/
local void GameMenuEnd(void)
{
    InterfaceState=IfaceStateNormal;
    GameRunning=0;
    CursorOn=CursorOnUnknown;
    CurrentMenu=-1;
}

local void KeystrokeHelpMenu(void)
{
    int j;
    int nitems = Menus[MENU_KEYSTROKE_HELP].nitems;

    KeystrokeHelpMenuItems[1].d.hslider.percent = ( (KeystrokeHelpMenuItems[3].yofs - (40+20*1)) / -20 ) * 100 / (nitems - 11 - 3);

    for (j=3; j < nitems ;++j) {
	if ((KeystrokeHelpMenuItems[j].yofs < (40+20*1)) || (KeystrokeHelpMenuItems[j].yofs > (40+20*11)))
	    KeystrokeHelpMenuItems[j].mitype = 0;
	else
	    KeystrokeHelpMenuItems[j].mitype = MI_TYPE_TEXT;
    }
    ProcessMenu(MENU_KEYSTROKE_HELP, 1);
}

local void HelpMenu(void)
{
    ProcessMenu(MENU_HELP, 1);
}

local void ShowTipsMenu(void)
{
    if (ShowTips)
	TipsMenuItems[1].d.gem.state = MI_GSTATE_CHECKED;
    else
	TipsMenuItems[1].d.gem.state = MI_GSTATE_UNCHECKED;

    ProcessMenu(MENU_TIPS, 1);
}

/**
**	Free the tips from the menu
*/
local void FreeTips()
{
    int i;

    for( i=5; i<13; i++ ) {
	if( TipsMenuItems[i].d.text.text ) {
	    free(TipsMenuItems[i].d.text.text);
	    TipsMenuItems[i].d.text.text=NULL;
	}
    }
}

/**
**	Initialize the tips menu
*/
local void InitTips(Menuitem *mi __attribute__((unused)))
{
    int i;
    int line;
    char* p;
    char* s;
    char* str;
    int w;
    int font;
    int l;

    if( ShowTips )
	TipsMenuItems[1].d.gem.state=MI_GSTATE_CHECKED;
    else
	TipsMenuItems[1].d.gem.state=MI_GSTATE_UNCHECKED;

    FreeTips();

    w=Menus[MENU_TIPS].xsize-2*TipsMenuItems[5].xofs;
    font=TipsMenuItems[5].font;
    i=0;
    line=5;

    p=Tips[CurrentTip];
    if( !p )
	return;

    l=0;
    s=str=strdup(p);

    while( line<13 ) {
	char* s1;
	char* space;

	space=NULL;
	for( ;; ) {
	    if( VideoTextLength(font,s)<w ) {
		break;
	    }
	    s1=strrchr(s,' ');
	    if( !s1 ) {
		fprintf(stderr, "line too long: \"%s\"\n", s);
		break;
	    }
	    if( space )
		*space=' ';
	    space=s1;
	    *space='\0';
	}
	TipsMenuItems[line++].d.text.text=strdup(s);
	l+=strlen(s);
	if( !p[l] ) {
	    break;
	}
	++l;
	s=str+l;
    }

    free(str);
}

/**
**	Show tips at startup gem callback
*/
local void SetTips(Menuitem* mi __attribute__((unused)))
{
    if( TipsMenuItems[1].d.gem.state==MI_GSTATE_CHECKED ) {
	ShowTips=1;
    } else {
	ShowTips=0;
    }
}

local void NextTip(void)
{
    CurrentTip++;
    if( Tips[CurrentTip]==NULL )
	CurrentTip=0;
}

/**
**	Cycle through the tips
*/
local void ShowNextTip()
{
    NextTip();
    InitTips(NULL);
}

/**
**	Exit the tips menu
*/
local void TipsMenuEnd(void)
{
    NextTip();
    FreeTips();

    EndMenu();
}

/**
**	Exit the game from menu.
*/
local void GameMenuExit(void)
{
    Exit(0);
}

/**
**
*/
local void SetMenuObjectives()
{
    int i;
    int line;
    char* p;
    char* s;
    char* str;
    int w;
    int font;
    int l;

    w=Menus[MENU_OBJECTIVES].xsize-2*ObjectivesMenuItems[1].xofs;
    font=ObjectivesMenuItems[1].font;
    i=0;
    line=1;

    for( p=GameIntro.Objectives[i]; p; p=GameIntro.Objectives[++i] ) {
	l=0;
	s=str=strdup(p);

	for( ;; ) {
	    char* s1;
	    char* space;

	    space=NULL;
	    for( ;; ) {
		if( VideoTextLength(font,s)<w ) {
		    break;
		}
		s1=strrchr(s,' ');
		if( !s1 ) {
		    fprintf(stderr, "line too long: \"%s\"\n", s);
		    break;
		}
		if( space )
		    *space=' ';
		space=s1;
		*space='\0';
	    }
	    ObjectivesMenuItems[line++].d.text.text=strdup(s);
	    l+=strlen(s);
	    if( !p[l] ) {
		break;
	    }
	    ++l;
	    s=str+l;

	    if( line==Menus[MENU_OBJECTIVES].nitems-1 ) {
		break;
	    }
	}
	free(str);
    }
}

/**
**
*/
local void FreeMenuObjectives()
{
    int i;

    for( i=1;i<Menus[MENU_OBJECTIVES].nitems-1;i++ ) {
	if( ObjectivesMenuItems[i].d.text.text ) {
	    free(ObjectivesMenuItems[i].d.text.text);
	    ObjectivesMenuItems[i].d.text.text=NULL;
	}
    }
}

/**
**
*/
local void GameMenuObjectives(void)
{
    SetMenuObjectives();
    ProcessMenu(MENU_OBJECTIVES, 1);
    FreeMenuObjectives();
}

/**
**	Get pud info from select path+name
*/
local void GetInfoFromSelectPath(void)
{
    int i;

    FreeMapInfo(ScenSelectPudInfo);
    ScenSelectPudInfo = NULL;

    if (ScenSelectPath[0]) {
	i = strlen(ScenSelectPath);
	strcat(ScenSelectPath, "/");
    } else {
	i = 0;
    }
    strcat(ScenSelectPath, ScenSelectFileName);	// Final map name with path
    if (strcasestr(ScenSelectFileName, ".pud")) {
	ScenSelectPudInfo = GetPudInfo(ScenSelectPath);
	strcpy(ScenSelectFullPath, ScenSelectPath);
    } else {
	// FIXME: GetCmInfo();
    }
    ScenSelectPath[i] = '\0';		// Remove appended part
}

/**
**	Enter select scenario menu.
*/
local void ScenSelectMenu(void)
{
    ProcessMenu(MENU_SCEN_SELECT, 1);

    GetInfoFromSelectPath();
}

/**
**	Enter multiplayer select scenario menu.
*/
local void MultiScenSelectMenu(void)
{
    ScenSelectMenu();
    MultiGamePlayerSelectorsUpdate(1);
}

/**
**	Enter single player menu.
*/
local void SinglePlayerGameMenu(void)
{
    DestroyCursorBackground();
    GuiGameStarted = 0;
    ProcessMenu(MENU_CUSTOM_GAME_SETUP, 1);
    if (GuiGameStarted) {
	GameMenuReturn();
    }
}

/**
**	Show the campaign select menu.
**
**	Look which campaigns are available and how they are called.
*/
local void CampaignGameMenu(void)
{
    int i;

    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    Invalidate();

    DebugLevel0Fn("%d campaigns available\n",NumCampaigns);
    IfDebug(
	for( i=0; i<NumCampaigns; ++i ) {
	    DebugLevel0Fn("Campaign %d: %16.16s: %s\n",i,
		Campaigns[i].Ident,
		Campaigns[i].Name);
	}
    );

    //
    //	Setup campaign name.
    //
    for( i=0; i<NumCampaigns && i<4; ++i ) {
	char* s;

	CampaignSelectMenuItems[i].d.button.text=Campaigns[i].Name;
	CampaignSelectMenuItems[i].flags&=~MenuButtonDisabled;

	if( (s=strchr(Campaigns[i].Name,'!')) ) {
	    CampaignSelectMenuItems[i].d.button.hotkey=tolower(s[1]);
	}
    }
    for( ; i<4; ++i ) {
	CampaignSelectMenuItems[i].d.button.text="Not available";
	CampaignSelectMenuItems[i].flags|=MenuButtonDisabled;
    }

    GuiGameStarted = 0;
    ProcessMenu(MENU_CAMPAIGN_SELECT, 1);
    if (GuiGameStarted) {
	GameMenuReturn();
    }

    for( i=0; i<4; ++i ) {
	CampaignSelectMenuItems[i].d.button.text=NULL;
    }
}

/**
**	Start campaign from menu.
**
**	@param number	Number of the compaign.
*/
local void StartCampaignFromMenu(int number)
{
    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    Invalidate();

#if 0
    // JOHNS: this is currently not needed:

    // Any Campaign info should be displayed through a DrawFunc() Item
    // int the CAMPAIN_CONT menu processed below...
    ProcessMenu(MENU_CAMPAIGN_CONT, 1);
    // Set GuiGameStarted = 1 to acctually run a game here...
    // But select and load the map first...
    // See CustomGameStart() for info...
#endif

    PlayCampaign(Campaigns[number].Ident);
    GuiGameStarted = 1;

    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoClearScreen();
    VideoUnlockScreen();
    Invalidate();

    // FIXME: johns othewise crash in UpdateDisplay -> DrawMinimapCursor
    EndMenu();
}

/**
**	Call back for 1st entry of campaign menu.
**
**	@note FIXME: Isn't it possible to have an argument in the menu?
*/
local void CampaignMenu1(void)
{
    StartCampaignFromMenu(0);
}

/**
**	Call back for 2nd entry of campaign menu.
**
**	@note FIXME: Isn't it possible to have an argument in the menu?
*/
local void CampaignMenu2(void)
{
    StartCampaignFromMenu(1);
}

/**
**	Call back for 3rd entry of campaign menu.
**
**	@note FIXME: Isn't it possible to have an argument in the menu?
*/
local void CampaignMenu3(void)
{
    StartCampaignFromMenu(2);
}

/**
**	Call back for 4th entry of campaign menu.
**
**	@note FIXME: Isn't it possible to have an argument in the menu?
*/
local void CampaignMenu4(void)
{
    StartCampaignFromMenu(3);
}

/**
**	Call back for select entry of campaign menu.
*/
local void SelectCampaignMenu(void)
{
    // FIXME: not written
}

/**
**	FIXME: docu.
*/
local void EnterNameCancel(void)
{
    EnterNameMenuItems[1].d.input.nch = 0;
    EndMenu();
}

/**
**	FIXME: docu.
*/
local void EnterNameAction(Menuitem *mi, int key)
{
    if (mi->d.input.nch == 0) {
	mi[1].flags = MenuButtonDisabled;
    } else {
	mi[1].flags &= ~MenuButtonDisabled;
	if (key == 10 || key == 13) {
	    EndMenu();
	}
    }
}

/**
**	Cancel button of enter server ip/name menu pressed.
*/
local void EnterServerIPCancel(void)
{
    EnterServerIPMenuItems[1].d.input.nch = 0;
    EndMenu();
}

/**
**	Input field action of server ip/name.
*/
local void EnterServerIPAction(Menuitem *mi, int key)
{
    if (mi->d.input.nch == 0) {
	mi[1].flags = MenuButtonDisabled;
    } else {
	mi[1].flags &= ~MenuButtonDisabled;
	if (key == 10 || key == 13) {
	    EndMenu();
	}
    }
}

/**
**	Start processing join a network game menu.
*/
local void JoinNetGameMenu(void)
{
    char server_host_buffer[32];

    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    Invalidate();

    //
    //  Prepare enter ip/hostname menu
    //
    if (NetworkArg) {
	strcpy(server_host_buffer, NetworkArg);
    } else {
	server_host_buffer[0] = '\0';
    }
    strcat(server_host_buffer, "~!_");
    EnterServerIPMenuItems[1].d.input.buffer = server_host_buffer;
    EnterServerIPMenuItems[1].d.input.nch = strlen(server_host_buffer) - 3;
    EnterServerIPMenuItems[1].d.input.maxch = 24;
    if (EnterServerIPMenuItems[1].d.input.nch) {
	EnterServerIPMenuItems[2].flags &= ~MenuButtonDisabled;
    } else {
	EnterServerIPMenuItems[2].flags |= MenuButtonDisabled;
    }

    ProcessMenu(MENU_NET_ENTER_SERVER_IP, 1);

    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();

    if (EnterServerIPMenuItems[1].d.input.nch == 0) {
	return;
    }
    // Now finally here is the address
    server_host_buffer[EnterServerIPMenuItems[1].d.input.nch] = 0;
    if (NetworkSetupServerAddress(server_host_buffer, NetworkServerText)) {
	NetErrorMenuItems[1].d.text.text = "Unable to lookup host.";
	ProcessMenu(MENU_NET_ERROR, 1);
	VideoLockScreen();
	StartMenusSetBackground(NULL);
	VideoUnlockScreen();
	return;
    }
    NetworkInitClientConnect();
    if (NetworkArg) {
	free(NetworkArg);
    }
    NetworkArg = strdup(server_host_buffer);

    // Here we really go...
    ProcessMenu(MENU_NET_CONNECTING, 1);
}

/**
**	Cancel button of network connect menu pressed.
*/
local void NetConnectingCancel(void)
{
    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    NetworkExitClientConnect();
    // Trigger TerminateNetConnect() to call us again and end the menu
    NetLocalState = ccs_usercanceled;
    EndMenu();
}

/**
**	Call back from menu loop, if network state has changed.
*/
local void TerminateNetConnect(void)
{
    switch (NetLocalState) {
	case ccs_unreachable:
	    NetErrorMenuItems[1].d.text.text = "Cannot reach server.";
	    ProcessMenu(MENU_NET_ERROR, 1);

	    NetConnectingCancel();
	    return;
	case ccs_nofreeslots:
	    NetErrorMenuItems[1].d.text.text = "Server is full.";
	    ProcessMenu(MENU_NET_ERROR, 1);

	    NetConnectingCancel();
	    return;
	case ccs_serverquits:
	    NetErrorMenuItems[1].d.text.text = "Server gone.";
	    ProcessMenu(MENU_NET_ERROR, 1);

	    NetConnectingCancel();
	    return;
	case ccs_incompatibleengine:
	    NetErrorMenuItems[1].d.text.text = "Incompatible engine version.";
	    ProcessMenu(MENU_NET_ERROR, 1);

	    NetConnectingCancel();
	    return;
	case ccs_incompatiblenetwork:
	    NetErrorMenuItems[1].d.text.text = "Incompatible network version.";
	    ProcessMenu(MENU_NET_ERROR, 1);

	case ccs_usercanceled:
	    NetConnectingCancel();
	    return;
    }

    DebugLevel1Fn("NetLocalState %d\n", NetLocalState);
    NetConnectRunning = 2;
    DestroyCursorBackground();
    GuiGameStarted = 0;
    ProcessMenu(MENU_NET_MULTI_CLIENT, 1);
    if (GuiGameStarted) {
	GameMenuReturn();
    } else {
	NetConnectingCancel();
    }
}

local void CreateNetGameMenu(void)
{
    DestroyCursorBackground();
    GuiGameStarted = 0;
    ProcessMenu(MENU_NET_MULTI_SETUP, 1);
    if (GuiGameStarted) {
	GameMenuReturn();
    }
}

/**
**	Multiplayer game start game button pressed.
*/
local void MultiGameStart(void)
{
    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    Invalidate();

    DebugLevel0Fn("Send start to all clients.\n");

    CustomGameStart();
}

/**
**	Enter multiplayer game menu.
*/
local void MultiPlayerGameMenu(void)
{
    char NameBuf[32];

    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    Invalidate();

    EnterNameMenuItems[1].d.input.buffer = NameBuf;
    strcpy(NameBuf, NetworkName);
    strcat(NameBuf, "~!_");
    EnterNameMenuItems[1].d.input.nch = strlen(NameBuf) - 3;
    EnterNameMenuItems[1].d.input.maxch = 15;
    EnterNameMenuItems[2].flags &= ~MenuButtonDisabled;

    ProcessMenu(MENU_ENTER_NAME, 1);

    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();

    if (EnterNameMenuItems[1].d.input.nch == 0) {
	return;
    }

    NameBuf[EnterNameMenuItems[1].d.input.nch] = 0;	// Now finally here is the name
    memset(NetworkName, 0, 16);
    strcpy(NetworkName, NameBuf);

    GuiGameStarted = 0;
    // Here we really go...
    ProcessMenu(MENU_NET_CREATE_JOIN, 1);

    DebugLevel0Fn("What here?\n");
    if (GuiGameStarted) {
	GameMenuReturn();
    }
}

local void FreeMapInfos(FileList *fl, int n)
{
    int i;

    for (i = 0; i < n; i++) {
	if (fl[i].type && fl[i].xdata) {
	    FreeMapInfo(fl[i].xdata);
	    fl[i].xdata = NULL;
	}
    }
}

/**
**	Initialize the scenario selector menu.
*/
local void ScenSelectInit(Menuitem * mi __attribute__ ((unused)))
{
    DebugCheck(!*ScenSelectPath);
    ScenSelectMenuItems[9].flags =
	*ScenSelectDisplayPath ? 0 : MenuButtonDisabled;
    ScenSelectMenuItems[9].d.button.text = ScenSelectDisplayPath;
    DebugLevel0Fn("Start path: %s\n", ScenSelectPath);
}

local void ScenSelectLBAction(Menuitem *mi, int i)
{
    FileList *fl;

    DebugCheck(i<0);
    if (i < mi->d.listbox.noptions) {
	fl = mi->d.listbox.options;
	if (fl[i].type) {
	    ScenSelectMenuItems[3].d.button.text = "OK";
	} else {
	    ScenSelectMenuItems[3].d.button.text = "Open";
	}
	if (mi->d.listbox.noptions > 5) {
	    mi[1].d.vslider.percent = (i * 100) / (mi->d.listbox.noptions - 1);
	    mi[1].d.hslider.percent = (i * 100) / (mi->d.listbox.noptions - 1);
	}
    }
}

local void ScenSelectLBExit(Menuitem *mi)
{
    FileList *fl;

    if (mi->d.listbox.noptions) {
	fl = mi->d.listbox.options;
	FreeMapInfos(fl, mi->d.listbox.noptions);
	free(fl);
	mi->d.listbox.options = NULL;
	mi->d.listbox.noptions = 0;
	mi[1].flags |= MenuButtonDisabled;
    }
}

#ifndef O_BINARY
#define O_BINARY	0
#endif

local int ScenSelectRDFilter(char *pathbuf, FileList *fl)
{
    MapInfo *info;
    char *suf, *cp, *lcp, *np;
    int p, sz;
    static int szl[] = { -1, 32, 64, 96, 128, 256, 512, 1024 };
#ifdef USE_ZZIPLIB
    ZZIP_FILE *zzf;
#endif

#if 0
    if (ScenSelectMenuItems[6].d.pulldown.curopt == 0) {
	suf = NULL;
	p = -1;
    } else
#endif
    if (ScenSelectMenuItems[6].d.pulldown.curopt == 0) {
	suf = ".cm";
	p = 0;
    } else {
	suf = ".pud";
	p = 1;
    }
    np = strrchr(pathbuf, '/');
    if (np) {
	np++;
    } else {
	np = pathbuf;
    }
    cp = np;
    cp--;
    fl->type = -1;
#ifdef USE_ZZIPLIB
    if ((zzf = zzip_open(pathbuf, O_RDONLY|O_BINARY))) {
	sz = zzip_file_real(zzf);
	zzip_close(zzf);
	if (!sz) {
	    goto usezzf;
	}
    }
#endif
    do {
	lcp = cp++;
	cp = strcasestr(cp, suf);
#if 0
	if( suf ) {
	} else if( !suf && (cp = strcasestr(cp, ".cm")) ) {
	    suf = ".cm";
	    p = 0;
	} else if( !suf && (cp = strcasestr(cp, ".pud")) ) {
	    suf = ".pud";
	    p = 1;
	} else {
	    cp=NULL;
	}
#endif
    } while (cp != NULL);
    if (lcp >= np) {
	cp = lcp + strlen(suf);
#ifdef USE_ZLIB
	if (strcmp(cp, ".gz") == 0) {
	    *cp = 0;
	}
#endif
#ifdef USE_BZ2LIB
	if (strcmp(cp, ".bz2") == 0) {
	    *cp = 0;
	}
#endif
	if (*cp == 0) {
#ifdef USE_ZZIPLIB
usezzf:
#endif
#if 0
	    if( p==-1 ) {
		printf("What now ?\n");
		if (strcasestr(pathbuf, ".pud")) {
		    p=1;
		} else {
		    p=0;
		}
	    }
#endif
	    if (p) {
		if (strcasestr(pathbuf, ".pud")) {
		    info = GetPudInfo(pathbuf);
		    if (info) {
			DebugLevel3Fn("GetPudInfo(%s) : %p\n", pathbuf, info);
			sz = szl[ScenSelectMenuItems[8].d.pulldown.curopt];
			if (sz < 0 || (info->MapWidth == sz && info->MapHeight == sz)) {
			    fl->type = 1;
			    fl->name = strdup(np);
			    fl->xdata = info;
			    return 1;
			} else {
			    FreeMapInfo(info);
			}
		    }
		}
	    } else {
		if (strstr(pathbuf, ".cm")) {
		    // info = GetCmInfo(pathbuf);
		    info = NULL;
		    DebugLevel3Fn("GetCmInfo(%s) : %p\n", pathbuf, info);
		    fl->type = 1;
		    fl->name = strdup(np);
		    fl->xdata = info;
		    return 1;
		}
	    }
	}
    }
    return 0;
}

local void ScenSelectLBInit(Menuitem *mi)
{
    int i;

    ScenSelectLBExit(mi);
    if (ScenSelectMenuItems[6].d.pulldown.curopt == 0) {
	ScenSelectMenuItems[8].flags |= MenuButtonDisabled;
    } else {
	ScenSelectMenuItems[8].flags &= ~MenuButtonDisabled;
    }
    i = mi->d.listbox.noptions = ReadDataDirectory(ScenSelectPath, ScenSelectRDFilter,
						     (FileList **)&(mi->d.listbox.options));
    if (i == 0) {
	ScenSelectMenuItems[3].d.button.text = "OK";
	ScenSelectMenuItems[3].flags |= MenuButtonDisabled;
    } else {
	ScenSelectLBAction(mi, 0);
	ScenSelectMenuItems[3].flags &= ~MenuButtonDisabled;
	if (i > 5) {
	    mi[1].flags &= ~MenuButtonDisabled;
	}
    }
}

local unsigned char *ScenSelectLBRetrieve(Menuitem *mi, int i)
{
    FileList *fl;
    Menu *menu;
    MapInfo *info;
    static char buffer[1024];
    int j, n;

    if (i < mi->d.listbox.noptions) {
	fl = mi->d.listbox.options;
	if (fl[i].type) {
	    if (i - mi->d.listbox.startline == mi->d.listbox.curopt) {
		if ((info = fl[i].xdata)) {
		    menu = Menus + MENU_SCEN_SELECT;
		    if (info->Description) {
			VideoDrawText(menu->x+8,menu->y+254,LargeFont,info->Description);
		    }
		    sprintf(buffer, "%d x %d", info->MapWidth, info->MapHeight);
		    VideoDrawText(menu->x+8,menu->y+254+20,LargeFont,buffer);
		    for (n = j = 0; j < PlayerMax; j++) {
			if (info->PlayerType[j] == PlayerPerson) {
			    n++;
			}
		    }
		    if (n == 1) {
			VideoDrawText(menu->x+8,menu->y+254+40,LargeFont,"1 player");
		    } else {
			sprintf(buffer, "%d players", n);
			VideoDrawText(menu->x+8,menu->y+254+40,LargeFont,buffer);
		    }
		}
	    }
	    strcpy(buffer, "   ");
	} else {
	    strcpy(buffer, "\260 ");
	}
	strcat(buffer, fl[i].name);
	return buffer;
    }
    return NULL;
}

local void ScenSelectTPMSAction(Menuitem *mi, int i __attribute__((unused)))
{
    mi = ScenSelectMenuItems + 1;
    ScenSelectLBInit(mi);
    mi->d.listbox.cursel = -1;
    mi->d.listbox.startline = 0;
    mi->d.listbox.curopt = 0;
    mi[1].d.vslider.percent = 0;
    mi[1].d.hslider.percent = 0;
    MustRedraw |= RedrawMenu;
}

local void ScenSelectVSAction(Menuitem *mi, int i)
{
    int op, d1, d2;

    mi--;
    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.vslider.cflags&MI_CFLAGS_DOWN) {
		if (mi->d.listbox.curopt+mi->d.listbox.startline+1 < mi->d.listbox.noptions) {
		    mi->d.listbox.curopt++;
		    if (mi->d.listbox.curopt >= mi->d.listbox.nlines) {
			mi->d.listbox.curopt--;
			mi->d.listbox.startline++;
		    }
		    MustRedraw |= RedrawMenu;
		}
	    } else if (mi[1].d.vslider.cflags&MI_CFLAGS_UP) {
		if (mi->d.listbox.curopt+mi->d.listbox.startline > 0) {
		    mi->d.listbox.curopt--;
		    if (mi->d.listbox.curopt < 0) {
			mi->d.listbox.curopt++;
			mi->d.listbox.startline--;
		    }
		    MustRedraw |= RedrawMenu;
		}
	    }
	    ScenSelectLBAction(mi, mi->d.listbox.curopt + mi->d.listbox.startline);
	    if (i == 2) {
		mi[1].d.vslider.cflags &= ~(MI_CFLAGS_DOWN|MI_CFLAGS_UP);
	    }
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.vslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.vslider.curper > mi[1].d.vslider.percent) {
		    if (mi->d.listbox.curopt+mi->d.listbox.startline+1 < mi->d.listbox.noptions) {
			for (;;) {
			    op = ((mi->d.listbox.curopt + mi->d.listbox.startline + 1) * 100) /
				 (mi->d.listbox.noptions - 1);
			    d1 = mi[1].d.vslider.curper - mi[1].d.vslider.percent;
			    d2 = op - mi[1].d.vslider.curper;
			    if (d2 >= d1)
				break;
			    mi->d.listbox.curopt++;
			    if (mi->d.listbox.curopt >= mi->d.listbox.nlines) {
				mi->d.listbox.curopt--;
				mi->d.listbox.startline++;
			    }
			    if (mi->d.listbox.curopt+mi->d.listbox.startline+1 == mi->d.listbox.noptions)
				break;
			}
		    }
		} else if (mi[1].d.vslider.curper < mi[1].d.vslider.percent) {
		    if (mi->d.listbox.curopt+mi->d.listbox.startline > 0) {
			for (;;) {
			    op = ((mi->d.listbox.curopt + mi->d.listbox.startline - 1) * 100) /
				     (mi->d.listbox.noptions - 1);
			    d1 = mi[1].d.vslider.percent - mi[1].d.vslider.curper;
			    d2 = mi[1].d.vslider.curper - op;
			    if (d2 >= d1)
				break;
			    mi->d.listbox.curopt--;
			    if (mi->d.listbox.curopt < 0) {
				mi->d.listbox.curopt++;
				mi->d.listbox.startline--;
			    }
			    if (mi->d.listbox.curopt+mi->d.listbox.startline == 0)
				break;
			}
		    }
		}

		DebugCheck(mi->d.listbox.startline < 0);
		DebugCheck(mi->d.listbox.startline+mi->d.listbox.curopt >= mi->d.listbox.noptions);

		ScenSelectLBAction(mi, mi->d.listbox.curopt + mi->d.listbox.startline);
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

local void ScenSelectVSKeystrokeHelpAction(Menuitem *mi, int i)
{
    int j = 3;
    int nitems = Menus[MENU_KEYSTROKE_HELP].nitems;

    mi--;
    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.vslider.cflags&MI_CFLAGS_DOWN &&
	        KeystrokeHelpMenuItems[nitems-1].yofs > (40+20*11)) {
		    for (j=3; j < nitems ;++j) {
			KeystrokeHelpMenuItems[j].yofs -= 20;
			if ((KeystrokeHelpMenuItems[j].yofs < (40+20*1)) ||
			    (KeystrokeHelpMenuItems[j].yofs > (40+20*11)))
			    KeystrokeHelpMenuItems[j].mitype = 0;
			else
			    KeystrokeHelpMenuItems[j].mitype = MI_TYPE_TEXT;
		    }
		    MustRedraw |= RedrawMenu;
	    } else if (mi[1].d.vslider.cflags&MI_CFLAGS_UP &&
	               KeystrokeHelpMenuItems[3].yofs < (40+20*1)) {
		    for (j=3; j < nitems ;++j) {
			KeystrokeHelpMenuItems[j].yofs += 20;
			if ((KeystrokeHelpMenuItems[j].yofs < (40+20*1)) ||
			    (KeystrokeHelpMenuItems[j].yofs > (40+20*11)))
			    KeystrokeHelpMenuItems[j].mitype = 0;
			else
			    KeystrokeHelpMenuItems[j].mitype = MI_TYPE_TEXT;
		    }
		    MustRedraw |= RedrawMenu;
	    }
	    if (i == 2) {
		mi[1].d.vslider.cflags &= ~(MI_CFLAGS_DOWN|MI_CFLAGS_UP);
	    }
	    mi[1].d.vslider.percent = ( (KeystrokeHelpMenuItems[3].yofs - (40+20*1)) / -20 ) * 100 / (nitems - 11 - 3);
	    break;
	case 1:		// mouse - move
	    if ((mi[1].d.vslider.cflags&MI_CFLAGS_KNOB) && (mi[1].flags&MenuButtonClicked)) {
		int ys;
		// ARI: FIXME: No floats please, John!!!
		float f;
		f = (int)((float)mi[1].d.vslider.curper/(100/(nitems-11-3))+.5f) * 100 / (float)(nitems-11-3);
		mi[1].d.vslider.percent = (int)f;
		ys = ((int)(f * (nitems-11-3) + .5f) / 100) * -20 + (40+20*1);
		for (j=3; j < nitems; ++j) {
		    KeystrokeHelpMenuItems[j].yofs = ys + (j-3)*20;
		    if ((KeystrokeHelpMenuItems[j].yofs < (40+20*1)) || (KeystrokeHelpMenuItems[j].yofs > (40+20*11)))
			KeystrokeHelpMenuItems[j].mitype = 0;
		    else
			KeystrokeHelpMenuItems[j].mitype = MI_TYPE_TEXT;
		}
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

local void ScenSelectHSGameSpeedAction(Menuitem *mi, int i)
{
    mi--;

    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_RIGHT) {
		DebugLevel0Fn("Increasing game speed by 10%s\n", "%");
		mi[1].d.hslider.percent += 10;
		if (mi[1].d.hslider.percent > 100)
		    mi[1].d.hslider.percent = 100;
	    } else if (mi[1].d.hslider.cflags&MI_CFLAGS_LEFT) {
		DebugLevel0Fn("Decreasing game speed by 10%s\n", "%");
		mi[1].d.hslider.percent -= 10;
		if (mi[1].d.hslider.percent < 0)
		    mi[1].d.hslider.percent = 0;
	    }
	    if (i == 2) {
		mi[1].d.hslider.cflags &= ~(MI_CFLAGS_RIGHT|MI_CFLAGS_LEFT);
	    }
		VideoSyncSpeed = (mi[1].d.hslider.percent * (MAX_GAME_SPEED - MIN_GAME_SPEED)) / 100 + MIN_GAME_SPEED;
		SetVideoSync();
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.hslider.curper > mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		} else if (mi[1].d.hslider.curper < mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		}
		mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		VideoSyncSpeed = (mi[1].d.hslider.percent * (MAX_GAME_SPEED - MIN_GAME_SPEED)) / 100 + MIN_GAME_SPEED;
		SetVideoSync();
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

local void ScenSelectHSMouseScrollAction(Menuitem *mi, int i)
{
    mi--;

    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_RIGHT) {
		DebugLevel0Fn("Increasing mouse speed\n");
		mi[1].d.hslider.percent += 10;
		if (mi[1].d.hslider.percent > 100)
		    mi[1].d.hslider.percent = 100;
	    } else if (mi[1].d.hslider.cflags&MI_CFLAGS_LEFT) {
		DebugLevel0Fn("Decreasing mouse speed\n");
		mi[1].d.hslider.percent -= 10;
		if (mi[1].d.hslider.percent < 0)
		    mi[1].d.hslider.percent = 0;
	    }
	    if (i == 2) {
		mi[1].d.hslider.cflags &= ~(MI_CFLAGS_RIGHT|MI_CFLAGS_LEFT);
	    }
	    TheUI.MouseScroll = 1;
	    SpeedMouseScroll = 10 - (mi[1].d.hslider.percent * 9) / 100;
	    if (mi[1].d.hslider.percent == 0)
		TheUI.MouseScroll = 0;
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.hslider.curper > mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		} else if (mi[1].d.hslider.curper < mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		}
		mi[1].d.hslider.percent = (mi[1].d.hslider.curper + 6) / 10 * 10;
		TheUI.MouseScroll = 1;
		SpeedMouseScroll = 10 - (mi[1].d.hslider.percent * 9) / 100;
		if (mi[1].d.hslider.percent == 0)
		    TheUI.MouseScroll = 0;
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

local void ScenSelectHSKeyboardScrollAction(Menuitem *mi, int i)
{
    mi--;

    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_RIGHT) {
		DebugLevel0Fn("Increasing keyboard speed\n");
		mi[1].d.hslider.percent += 10;
		if (mi[1].d.hslider.percent > 100)
		    mi[1].d.hslider.percent = 100;
	    } else if (mi[1].d.hslider.cflags&MI_CFLAGS_LEFT) {
		DebugLevel0Fn("Decreasing keyboard speed\n");
		mi[1].d.hslider.percent -= 10;
		if (mi[1].d.hslider.percent < 0)
		    mi[1].d.hslider.percent = 0;
	    }
	    if (i == 2) {
		mi[1].d.hslider.cflags &= ~(MI_CFLAGS_RIGHT|MI_CFLAGS_LEFT);
	    }
	    TheUI.KeyScroll = 1;
	    SpeedKeyScroll = 10 - (mi[1].d.hslider.percent * 9) / 100;
	    if (mi[1].d.hslider.percent == 0)
		TheUI.KeyScroll = 0;
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.hslider.curper > mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		} else if (mi[1].d.hslider.curper < mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		}
		mi[1].d.hslider.percent = (mi[1].d.hslider.curper + 6) / 10 * 10;
		TheUI.KeyScroll = 1;
		SpeedKeyScroll = 10 - (mi[1].d.hslider.percent * 9) / 100;
		if (mi[1].d.hslider.percent == 0)
		    TheUI.KeyScroll = 0;
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

local void ScenSelectHSMasterVolumeAction(Menuitem *mi, int i)
{
    mi--;

    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_RIGHT) {
		DebugLevel0Fn("Increasing master volume\n");
		mi[1].d.hslider.percent += 10;
		if (mi[1].d.hslider.percent > 100)
		    mi[1].d.hslider.percent = 100;
	    } else if (mi[1].d.hslider.cflags&MI_CFLAGS_LEFT) {
		DebugLevel0Fn("Decreasing master volume\n");
		mi[1].d.hslider.percent -= 10;
		if (mi[1].d.hslider.percent < 0)
		    mi[1].d.hslider.percent = 0;
	    }
	    if (i == 2) {
		mi[1].d.hslider.cflags &= ~(MI_CFLAGS_RIGHT|MI_CFLAGS_LEFT);
	    }
	    SetGlobalVolume((mi[1].d.hslider.percent * 255) / 100);
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.hslider.curper > mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		} else if (mi[1].d.hslider.curper < mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		}
		mi[1].d.hslider.percent = (mi[1].d.hslider.curper + 6) / 10 * 10;
		SetGlobalVolume((mi[1].d.hslider.percent * 255) / 100);
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

local void ScenSelectHSMusicVolumeAction(Menuitem *mi, int i)
{
    mi--;

    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_RIGHT) {
		DebugLevel0Fn("Increasing music volume\n");
		mi[1].d.hslider.percent += 10;
		if (mi[1].d.hslider.percent > 100)
		    mi[1].d.hslider.percent = 100;
	    } else if (mi[1].d.hslider.cflags&MI_CFLAGS_LEFT) {
		DebugLevel0Fn("Decreasing music volume\n");
		mi[1].d.hslider.percent -= 10;
		if (mi[1].d.hslider.percent < 0)
		    mi[1].d.hslider.percent = 0;
	    }
	    if (i == 2) {
		mi[1].d.hslider.cflags &= ~(MI_CFLAGS_RIGHT|MI_CFLAGS_LEFT);
	    }
	    SetMusicVolume((mi[1].d.hslider.percent * 255) / 100);
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.hslider.curper > mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		} else if (mi[1].d.hslider.curper < mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		}
		mi[1].d.hslider.percent = (mi[1].d.hslider.curper + 6) / 10 * 10;
		SetMusicVolume((mi[1].d.hslider.percent * 255) / 100);
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}

#ifdef USE_LIBCDA
local void ScenSelectHSCdVolumeAction(Menuitem *mi, int i)
{
    mi--;

    switch (i) {
	case 0:		// click - down
	case 2:		// key - down
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_RIGHT) {
		DebugLevel0Fn("Increasing cd volume\n");
		mi[1].d.hslider.percent += 10;
		if (mi[1].d.hslider.percent > 100)
		    mi[1].d.hslider.percent = 100;
	    } else if (mi[1].d.hslider.cflags&MI_CFLAGS_LEFT) {
		DebugLevel0Fn("Decreasing cd volume\n");
		mi[1].d.hslider.percent -= 10;
		if (mi[1].d.hslider.percent < 0)
		    mi[1].d.hslider.percent = 0;
	    }
	    if (i == 2) {
		mi[1].d.hslider.cflags &= ~(MI_CFLAGS_RIGHT|MI_CFLAGS_LEFT);
	    }
	    cd_set_volume((mi[1].d.hslider.percent * 255) / 100,(mi[1].d.hslider.percent * 255) / 100);
	    break;
	case 1:		// mouse - move
	    if (mi[1].d.hslider.cflags&MI_CFLAGS_KNOB && (mi[1].flags&MenuButtonClicked)) {
		if (mi[1].d.hslider.curper > mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		} else if (mi[1].d.hslider.curper < mi[1].d.hslider.percent) {
		    mi[1].d.hslider.percent = mi[1].d.hslider.curper;
		}
		mi[1].d.hslider.percent = (mi[1].d.hslider.curper + 6) / 10 * 10;
		cd_set_volume((mi[1].d.hslider.percent * 255) / 100,(mi[1].d.hslider.percent * 255) / 100);
		MustRedraw |= RedrawMenu;
	    }
	    break;
	default:
	    break;
    }
}
#else
local void ScenSelectHSCdVolumeAction(Menuitem *mi __attribute__((unused)),
	int i __attribute__((unused)))
{
}
#endif

local void ScenSelectFolder(void)
{
    char *cp;
    Menuitem *mi = ScenSelectMenuItems + 1;

    if (ScenSelectDisplayPath[0]) {
	cp = strrchr(ScenSelectDisplayPath, '/');
	if (cp) {
	    *cp = 0;
	} else {
	    ScenSelectDisplayPath[0] = 0;
	    ScenSelectMenuItems[9].flags |= MenuButtonDisabled;
	    ScenSelectMenuItems[9].d.button.text = NULL;
	}
	cp = strrchr(ScenSelectPath, '/');
	if (cp) {
	    *cp = 0;
	    ScenSelectLBInit(mi);
	    mi->d.listbox.cursel = -1;
	    mi->d.listbox.startline = 0;
	    mi->d.listbox.curopt = 0;
	    mi[1].d.vslider.percent = 0;
	    mi[1].d.hslider.percent = 0;
	    MustRedraw |= RedrawMenu;
	}
    }
}

local void ScenSelectOk(void)
{
    FileList *fl;
    char *cp;
    Menuitem *mi = ScenSelectMenuItems + 1;
    int i = mi->d.listbox.curopt + mi->d.listbox.startline;

    if (i < mi->d.listbox.noptions) {
	fl = mi->d.listbox.options;
	if (fl[i].type == 0) {
	    cp = strrchr(ScenSelectPath, '/');
	    if (!cp || cp[1]) {
		strcat(ScenSelectPath, "/");
	    }
	    strcat(ScenSelectPath, fl[i].name);
	    if (ScenSelectMenuItems[9].flags&MenuButtonDisabled) {
		ScenSelectMenuItems[9].flags &= ~MenuButtonDisabled;
		ScenSelectMenuItems[9].d.button.text = ScenSelectDisplayPath;
	    } else {
		strcat(ScenSelectDisplayPath, "/");
	    }
	    strcat(ScenSelectDisplayPath, fl[i].name);
	    ScenSelectLBInit(mi);
	    mi->d.listbox.cursel = -1;
	    mi->d.listbox.startline = 0;
	    mi->d.listbox.curopt = 0;
	    mi[1].d.vslider.percent = 0;
	    mi[1].d.hslider.percent = 0;
	    MustRedraw |= RedrawMenu;
	} else {
	    strcpy(ScenSelectFileName, fl[i].name);	// Final map name
	    EndMenu();
	}
    }
}

/**
**	Scenario select cancel button.
*/
local void ScenSelectCancel(void)
{
    char* s;

    //
    //  Use last selected map.
    //
    DebugLevel0Fn("Map   path: %s\n", CurrentMapPath);
    strcpy(ScenSelectPath, FreeCraftLibPath);
    if (*ScenSelectPath) {
	strcat(ScenSelectPath, "/");
    }
    strcat(ScenSelectPath, CurrentMapPath);
    if ((s = strrchr(ScenSelectPath, '/'))) {
	strcpy(ScenSelectFileName, s + 1);
	*s = '\0';
    }
    strcpy(ScenSelectDisplayPath, CurrentMapPath);
    if ((s = strrchr(ScenSelectDisplayPath, '/'))) {
	*s = '\0';
    } else {
	*ScenSelectDisplayPath = '\0';
    }

    DebugLevel0Fn("Start path: %s\n", ScenSelectPath);

    EndMenu();
}

local void GameCancel(void)
{
    VideoLockScreen();
    StartMenusSetBackground(NULL);
    VideoUnlockScreen();
    FreeMapInfo(ScenSelectPudInfo);
    ScenSelectPudInfo = NULL;
    EndMenu();
}

/**
**	Custom game start game button pressed.
*/
local void CustomGameStart(void)
{
    int i;
    char *p;

    FreeMapInfo(ScenSelectPudInfo);
    ScenSelectPudInfo = NULL;

    if (ScenSelectPath[0]) {
	strcat(ScenSelectPath, "/");
	strcat(ScenSelectPath, ScenSelectFileName);	// Final map name with path
	p = ScenSelectPath + strlen(FreeCraftLibPath) + 1;
	strcpy(CurrentMapPath, p);
    } else {
	strcpy(CurrentMapPath, ScenSelectFileName);
	strcat(ScenSelectPath, ScenSelectFileName);	// Final map name with path
    }

    for (i = 0; i < MAX_OBJECTIVES; i++) {
	if (GameIntro.Objectives[i]) {
	    free(GameIntro.Objectives[i]);
	    GameIntro.Objectives[i] = NULL;
	}
    }
    GameIntro.Objectives[0] = strdup(DefaultObjective);

    // FIXME: Johns is this here needed? Can the map loaded in create game?
    // ARI: Yes - This switches the menu gfx.. from def. Orc to Human, etc
    InitUnitTypes();
    UpdateStats();
    // ARI: And this finally loads it.
    //  For an alternative Method see network games..
    //  That way it should work finally..
    LoadMap(ScenSelectPath, &TheMap);

    GuiGameStarted = 1;
    EndMenu();
}

/**
**	Single player custom game menu entered.
*/
local void GameSetupInit(Menuitem * mi __attribute__ ((unused)))
{
    char* s;

    //
    //  No old path, setup the default.
    //
    if (!*CurrentMapPath || *CurrentMapPath == '.' || *CurrentMapPath == '/') {
#if 0					// FIXME: as soon as .cm is supported..
	strcpy(CurrentMapPath, "default.cm");
#endif
	strcpy(CurrentMapPath, "default.pud");

    }

    DebugLevel0Fn("Map   path: %s\n", CurrentMapPath);
    strcpy(ScenSelectPath, FreeCraftLibPath);
    if (*ScenSelectPath) {
	strcat(ScenSelectPath, "/");
    }
    strcat(ScenSelectPath, CurrentMapPath);
    if ((s = strrchr(ScenSelectPath, '/'))) {
	strcpy(ScenSelectFileName, s + 1);
	*s = '\0';
    }
    strcpy(ScenSelectDisplayPath, CurrentMapPath);
    if ((s = strrchr(ScenSelectDisplayPath, '/'))) {
	*s = '\0';
    } else {
	*ScenSelectDisplayPath = '\0';
    }
    DebugLevel0Fn("Start path: %s\n", ScenSelectPath);

    GetInfoFromSelectPath();
}

local void GameDrawFunc(Menuitem *mi)
{
    int nc, rc, l;
    char buffer[32];

    GetDefaultTextColors(&nc, &rc);
    StartMenusSetBackground(mi);
    SetDefaultTextColors(rc, rc);
    l = VideoTextLength(GameFont, "Scenario:");
    VideoDrawText(OffsetX + 16, OffsetY + 360, GameFont, "Scenario:");
    VideoDrawText(OffsetX + 16, OffsetY + 360+24 , GameFont, ScenSelectFileName);
    if (ScenSelectPudInfo) {
	if (ScenSelectPudInfo->Description) {
	    VideoDrawText(OffsetX + 16 + l + 8, OffsetY + 360, GameFont, ScenSelectPudInfo->Description);
	}
	sprintf(buffer, " (%d x %d)", ScenSelectPudInfo->MapWidth, ScenSelectPudInfo->MapHeight);
	VideoDrawText(OffsetX + 16+l+8+VideoTextLength(GameFont, ScenSelectFileName), OffsetY + 360+24, GameFont, buffer);
    }
#if 0
    for (n = j = 0; j < PlayerMax; j++) {
	if (info->PlayerType[j] == PlayerPerson) {
	    n++;
	}
    }
    if (n == 1) {
	VideoDrawText(menu->x+8,menu->y+254+40,LargeFont,"1 player");
    } else {
	sprintf(buffer, "%d players", n);
	VideoDrawText(menu->x+8,menu->y+254+40,LargeFont,buffer);
    }
#endif
    SetDefaultTextColors(nc, rc);
}

/**
**	Menu setup race pulldown action.
**
**	@note FIXME: Todo support more and other races.
*/
local void GameRCSAction(Menuitem *mi, int i)
{
    int v[] = { PlayerRaceHuman, PlayerRaceOrc, SettingsPresetMapDefault };

    if (mi->d.pulldown.curopt == i) {
	GameSettings.Presets[0].Race = v[i];
	ServerSetupState.Race[0] = i;
	NetworkServerResyncClients();
    }
}

local void GameRESAction(Menuitem *mi, int i)
{
    int v[] = { SettingsResourcesMapDefault, SettingsResourcesLow,
		SettingsResourcesMedium, SettingsResourcesHigh };

    if (!mi || mi->d.pulldown.curopt == i) {
	GameSettings.Resources = v[i];
	ServerSetupState.ResOpt = i;
	NetworkServerResyncClients();
    }
}

local void GameUNSAction(Menuitem *mi, int i)
{
    if (!mi || mi->d.pulldown.curopt == i) {
	GameSettings.NumUnits = i ? SettingsNumUnits1 : SettingsNumUnitsMapDefault;
	ServerSetupState.UnsOpt = i;
	NetworkServerResyncClients();
    }
}

local void GameTSSAction(Menuitem *mi, int i)
{
    // FIXME: TilesetSummer, ... shouldn't be used, they will be removed.
    int v[] = { SettingsPresetMapDefault, TilesetSummer, TilesetWinter, TilesetWasteland, TilesetSwamp };

    if (!mi || mi->d.pulldown.curopt == i) {
	GameSettings.Terrain = v[i];
	ServerSetupState.TssOpt = i;
	NetworkServerResyncClients();
    }
}

local void CustomGameOPSAction(Menuitem *mi __attribute__((unused)), int i)
{
    GameSettings.Opponents = i ? i : SettingsPresetMapDefault;
}

/**
**	Menu setup fog-of-war pulldown action.
**
**	@note FIXME: Want to support more features. fe. reveal map on start.
*/
local void MultiGameFWSAction(Menuitem *mi, int i)
{
    if (!mi || mi->d.pulldown.curopt == i) {
	FlagRevealMap = i;
	ServerSetupState.FwsOpt = i;
	NetworkServerResyncClients();
    }
}

/**
**	Multiplayer menu player server states.
*/
local void MultiGamePTSAction(Menuitem *mi, int o)
{
    int i;

    i = mi - NetMultiSetupMenuItems - SERVER_PLAYER_STATE;
    // JOHNS: Must this be always true?
    // ARI: NO! think of client menus!
    // DebugCheck( i<0 || i>PlayerMax-1 );

    if (i > 0 && i < PlayerMax-1) {
	if (mi->d.pulldown.curopt == o) {
	    ServerSetupState.CompOpt[i] = o;
	    MultiGamePlayerSelectorsUpdate(3);	// Recalc buttons on server
	    NetworkServerResyncClients();
	}
    }
}

local void MultiGameDrawFunc(Menuitem *mi)
{
    GameDrawFunc(mi);
}

local void MultiGameClientDrawFunc(Menuitem *mi)
{
    // FIXME: do something better
    GameDrawFunc(mi);
}

/**
**	Player selectors have changed.
**	Caution: Called by network events from clients (inital = 2)!
*/
local void MultiGamePlayerSelectorsUpdate(int initial)
{
    int i, h, c;
    int avail, ready;

    //	FIXME: What this has to do:
    //	disable additional buttons - partially done
    //  Notify clients about MAP change: (initial = 1...)

    DebugLevel0Fn("initial = %d\n", initial);

    if (initial == 1) {
	NetMultiSetupMenuItems[SERVER_PLAYER_STATE] = NetMultiButtonStorage[1];
	NetMultiSetupMenuItems[SERVER_PLAYER_STATE].yofs = 32;
    }

    //	Calculate available slots from pudinfo
    for (c = h = i = 0; i < PlayerMax; i++) {
	if (ScenSelectPudInfo->PlayerType[i] == PlayerPerson) {
	    h++;	// available interactive player slots
	}
	if (ScenSelectPudInfo->PlayerType[i] == PlayerComputer) {
	    c++;	// available computer player slots
	}
    }

    //	Tell connect state machines how many interactive players we can have
    NetPlayers = avail = h;

    //	Setup the player menu
    for (ready = i = 1; i < PlayerMax-1; i++) {
	if (initial == 1) {
	    if (i >= h) {
		ServerSetupState.CompOpt[i] = 1;
	    }

	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].flags = 0;
	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_PASSIVE;

	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].flags = 0;
	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].d.gem.state = MI_GSTATE_PASSIVE;

	    // FIXME: don't forget to throw out additional players
	    //	  without available slots here!

	}
	if (Hosts[i].PlyNr) {
	    NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i] = NetMultiButtonStorage[1];

	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].flags = 0;
	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_PASSIVE;
	    if (ServerSetupState.Ready[i]) {
		NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].d.gem.state |= MI_GSTATE_CHECKED;
		++ready;
#if 0
	    } else {
		NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].d.gem.state &= ~MI_GSTATE_CHECKED;
#endif
	    }

	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].flags = 0;
	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].d.gem.state = MI_GSTATE_PASSIVE;
	} else {
	    if (initial < 2 && !(NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].flags&MenuButtonClicked)) {
		// don't allow network and button events to intercept server player's action on pulldown buttons!
		NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i] = NetMultiButtonStorage[0];
		NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].d.pulldown.state = 0;
		NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].d.pulldown.curopt = ServerSetupState.CompOpt[i];
	    }
	    if (i < h && ServerSetupState.CompOpt[i] != 0) {
		avail--;
	    }

	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].flags = MenuButtonDisabled;
	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_INVISIBLE;

	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].flags = MenuButtonDisabled;
	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].d.gem.state = MI_GSTATE_INVISIBLE;
	}

	NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].yofs = 32 + (i&7) * 22;
	if (i > 7) {
	    NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].xofs = 320 + 40;
	}


	if (i >= h) {
	    NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].d.pulldown.state = MI_PSTATE_PASSIVE;

	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].flags = MenuButtonDisabled;
	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_INVISIBLE;

	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].flags = MenuButtonDisabled;
	    NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].d.gem.state = MI_GSTATE_INVISIBLE;
	}

	if (i >= h + c) {
	    NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].d.pulldown.defopt = 2;
	    NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].d.pulldown.curopt = 2;
	    NetMultiSetupMenuItems[SERVER_PLAYER_STATE + i].flags = MenuButtonDisabled;
	}
    }

    //	Check if all players are ready.
    DebugLevel0Fn("READY to START: AVAIL = %d, READY = %d! (NetPlayers = %d)\n", avail, ready, NetPlayers);
    if (ready == avail) {
	NetMultiSetupMenuItems[3].flags = 0;	// enable start game button
    } else {
	NetMultiSetupMenuItems[3].flags = MenuButtonDisabled;	// disable start game button
    }
}

/**
**	Update client network menu.
*/
local void MultiClientUpdate(int initial)
{
    int i, h, c;

    //	Calculate available slots from pudinfo
    for (c = h = i = 0; i < PlayerMax; i++) {
	if (ScenSelectPudInfo->PlayerType[i] == PlayerPerson) {
	    h++;	// available interactive player slots
	}
	if (ScenSelectPudInfo->PlayerType[i] == PlayerComputer) {
	    c++;	// available computer player slots
	}
    }

    if (initial) {
	NetMultiClientMenuItems[CLIENT_PLAYER_STATE] = NetMultiButtonStorage[1];
	NetMultiClientMenuItems[CLIENT_PLAYER_STATE].yofs = 32;
	memset(&ServerSetupState, 0, sizeof(ServerSetup));
	memset(&LocalSetupState, 0, sizeof(ServerSetup));
    }
    for (i = 1; i < PlayerMax - 1; i++) {
	if (Hosts[i].PlyNr) {
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i] =
		NetMultiButtonStorage[1];
	    if (i == NetLocalHostsSlot) {
		NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].d.gem.state = 0;
	    } else {
		NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_PASSIVE;
	    }
	} else {
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i] = NetMultiButtonStorage[0];
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].d.pulldown.state = MI_PSTATE_PASSIVE;
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].d.pulldown.curopt = ServerSetupState.CompOpt[i];
	    NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_INVISIBLE;
	}
	NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].yofs = 32 + (i&7) * 22;
	if (i > 7) {
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].xofs = 320 + 40;
	}

	NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].flags = 0;
	if (ServerSetupState.Ready[i]) {
	    NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].d.gem.state |= MI_GSTATE_CHECKED;
	} else {
	    NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].d.gem.state &= ~MI_GSTATE_CHECKED;
	}

	if (i >= h) {
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].d.pulldown.curopt = ServerSetupState.CompOpt[i];
	}
	if (i >= h + c) {
	    NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].flags = MenuButtonDisabled;
	    NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].d.gem.state = MI_GSTATE_INVISIBLE;
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].d.pulldown.defopt =
			 NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].d.pulldown.curopt = 2;
	    NetMultiClientMenuItems[CLIENT_PLAYER_STATE + i].flags = MenuButtonDisabled;
	}
    }
}

local void MultiGameSetupInit(Menuitem *mi)
{
    GameSetupInit(mi);
    NetworkInitServerConnect();
    memset(&ServerSetupState, 0, sizeof(ServerSetup));
    MultiGamePlayerSelectorsUpdate(1);
}

local void MultiGameSetupExit(Menuitem *mi __attribute__((unused)))
{
    NetworkExitServerConnect();
}

/**
**	Cancel button of server multi player menu pressed.
*/
local void MultiGameCancel(void)
{
    MultiGameSetupExit(NULL);
    NetPlayers = 0;		// Make single player menus work again!
    GameCancel();
}

/**
**	Draw the multi player setup menu.
**
**	@note FIXME: the other buttons aren't updated if the player leaves.
*/
local void NetMultiPlayerDrawFunc(Menuitem *mi)
{
    int i, nc, rc;

    i = mi - NetMultiSetupMenuItems - SERVER_PLAYER_STATE;
    if (i >= 0 && i < PlayerMax - 1) {		// Ugly test to detect server
	if (i > 0) {
	    NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i].flags &=
		~MenuButtonDisabled;
	    // Note: re-disabled in MultiGamePlayerSelectorsUpdate()
	    //		for kicked out clients!!
	    if (ServerSetupState.Ready[i]) {
		NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i]
			.d.gem.state = MI_GSTATE_PASSIVE|MI_GSTATE_CHECKED;
	    } else {
		NetMultiSetupMenuItems[SERVER_PLAYER_READY - 1 + i]
			.d.gem.state = MI_GSTATE_PASSIVE;
	    }
	    if (ServerSetupState.LastFrame[i]+30>FrameCounter) {
		NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].flags &=
		    ~MenuButtonDisabled;
		NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i]
			.d.gem.state = MI_GSTATE_PASSIVE|MI_GSTATE_CHECKED;
	    } else {
		NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i].flags |=
		    MenuButtonDisabled;
		NetMultiSetupMenuItems[SERVER_PLAYER_LAG - 1 + i]
			.d.gem.state = MI_GSTATE_PASSIVE;
	    }

	}
    } else {
	i = mi - NetMultiClientMenuItems - CLIENT_PLAYER_STATE;
	if (i > 0) {
	    NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].flags &=
		~MenuButtonDisabled;
	    if (i == NetLocalHostsSlot) {
		NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].
			d.gem.state &= ~MI_GSTATE_PASSIVE;
	    } else {
		NetMultiClientMenuItems[CLIENT_PLAYER_READY - 1 + i].
			d.gem.state |= MI_GSTATE_PASSIVE;
	    }
	}
    }
    /* FIXME:
	 further changes to implement client menu...
    */

    GetDefaultTextColors(&nc, &rc);
    SetDefaultTextColors(rc, rc);
    DebugLevel3Fn("Hosts[%d].PlyName = %s\n", i, Hosts[i].PlyName);
    VideoDrawText(mi->xofs, mi->yofs, GameFont, Hosts[i].PlyName);

    SetDefaultTextColors(nc, rc);
}

/**
**	Cancel button of multiplayer client menu pressed.
*/
local void MultiClientCancel(void)
{
    NetworkDetachFromServer();
    // GameCancel();
}

local void MultiGameClientInit(Menuitem *mi __attribute__((unused)))
{
    // GameSetupInit(mi);
    MultiClientUpdate(1);
    if (LocalSetupState.Ready[NetLocalHostsSlot]) {
	NetMultiClientMenuItems[2].flags = MenuButtonDisabled;
	NetMultiClientMenuItems[3].flags = 0;
    } else {
	NetMultiClientMenuItems[3].flags = MenuButtonDisabled;
	NetMultiClientMenuItems[2].flags = 0;
    }
}

/**
**	Multiplayer client gem action. Toggles ready flag.
*/
local void MultiClientGemAction(Menuitem *mi __attribute__((unused)))
{
    int i;

    i = mi - NetMultiClientMenuItems - CLIENT_PLAYER_READY + 1;
    DebugLevel3Fn("i = %d, NetLocalHostsSlot = %d\n", i, NetLocalHostsSlot);
    if (i == NetLocalHostsSlot) {
	LocalSetupState.Ready[i] = !LocalSetupState.Ready[i];
	if (LocalSetupState.Ready[i]) {
	    NetMultiClientMenuItems[2].flags = MenuButtonDisabled;
	    NetMultiClientMenuItems[3].flags = 0;
	} else {
	    NetMultiClientMenuItems[3].flags = MenuButtonDisabled;
	    NetMultiClientMenuItems[2].flags = 0;
	}
	MultiClientUpdate(0);
    }
}

local void MultiClientRCSAction(Menuitem *mi, int i)
{
    int v[] = { PlayerRaceHuman, PlayerRaceOrc, SettingsPresetMapDefault };

    if (mi->d.pulldown.curopt == i) {
	LocalSetupState.Race[NetLocalHostsSlot] = i;
	GameSettings.Presets[NetLocalHostsSlot].Race = v[i];
	MultiClientUpdate(0);
    }
}

local void MultiClientReady(void)
{
    NetMultiClientMenuItems[2].flags = MenuButtonDisabled;
    NetMultiClientMenuItems[3].flags = 0;
    LocalSetupState.Ready[NetLocalHostsSlot] = 1;
    MultiClientUpdate(0);
}

local void MultiClientNotReady(void)
{
    NetMultiClientMenuItems[3].flags = MenuButtonDisabled;
    NetMultiClientMenuItems[2].flags = 0;
    LocalSetupState.Ready[NetLocalHostsSlot] = 0;
    MultiClientUpdate(0);
}

/*
 * Callback from Netconnect Loop in Client-Sync State:
 * Compare Local State with Server's information
 * and force Update when changes have occured.
 */
global void NetClientCheckLocalState(void)
{
    if (LocalSetupState.Ready[NetLocalHostsSlot] != ServerSetupState.Ready[NetLocalHostsSlot]) {
	NetLocalState = ccs_changed;
	return;
    }
    if (LocalSetupState.Race[NetLocalHostsSlot] != ServerSetupState.Race[NetLocalHostsSlot]) {
	NetLocalState = ccs_changed;
	return;
    }
    /* ADD HERE */
}

global int NetClientSelectScenario(void)
{
    char *cp;

    FreeMapInfo(ScenSelectPudInfo);
    ScenSelectPudInfo = NULL;

    cp = strrchr(ScenSelectFullPath, '/');
    if (cp) {
	strcpy(ScenSelectFileName, cp + 1);
	*cp = 0;
	strcpy(ScenSelectPath, ScenSelectFullPath);
	*cp = '/';
    } else {
	strcpy(ScenSelectFileName, ScenSelectFullPath);
	ScenSelectPath[0] = 0;
    }

    if (strcasestr(ScenSelectFileName, ".pud")) {
	ScenSelectPudInfo = GetPudInfo(ScenSelectFullPath);
    } else {
	// FIXME: GetCmInfo();
    }
    return ScenSelectPudInfo == NULL;
}

global void NetConnectForceDisplayUpdate(void)
{
    MultiGamePlayerSelectorsUpdate(2);
    MustRedraw |= RedrawMenu;
}

/**
**	Update client menu to follow server menu.
*/
global void NetClientUpdateState(void)
{
#if 0
    // FIXME: Handle RACES -> Not visible! Delayed to final InitConfig msg...
    GameSettings.Presets[0].Race = ServerSetupState.Race[0];
#endif

    GameRESAction(NULL, ServerSetupState.ResOpt);
    NetMultiClientMenuItems[CLIENT_RESOURCE].d.pulldown.curopt =
	ServerSetupState.ResOpt;

    GameUNSAction(NULL, ServerSetupState.UnsOpt);
    NetMultiClientMenuItems[CLIENT_UNITS].d.pulldown.curopt =
	ServerSetupState.UnsOpt;

    MultiGameFWSAction(NULL, ServerSetupState.FwsOpt);
    NetMultiClientMenuItems[CLIENT_FOG_OF_WAR].d.pulldown.curopt =
	ServerSetupState.FwsOpt;

    GameTSSAction(NULL, ServerSetupState.TssOpt);
    NetMultiClientMenuItems[CLIENT_TILESET].d.pulldown.curopt =
	ServerSetupState.TssOpt;

    MultiClientUpdate(0);
    DebugLevel1Fn("MultiClientMenuRedraw\n");

    MustRedraw |= RedrawMenu;
}

/*----------------------------------------------------------------------------
--	Menu operation functions
----------------------------------------------------------------------------*/

/**
**	Handle keys in menu mode.
**
**	@param key	Key scancode.
**	@param keychar	ASCII character code of key.
**
**	@todo FIXME: Should be MenuKeyDown(), and act on _new_ MenuKeyUp() !!!
**      to implement button animation (depress before action)
*/
local void MenuHandleKeyDown(unsigned key,unsigned keychar)
{
    int i, n;
    Menuitem *mi;
    Menu *menu;

    HandleKeyModifiersDown(key,keychar);

    if (CurrentMenu < 0) {
	return;
    }
    menu = Menus + CurrentMenu;

    if (MenuButtonCurSel != -1 && menu->items[MenuButtonCurSel].mitype == MI_TYPE_INPUT) {
	mi = menu->items + MenuButtonCurSel;
	if (!(mi->flags & MenuButtonDisabled)) {
inkey:
#if 0
	    // Key is unsigned
	    if (key < 0) {
		key &= 0xFF;
	    }
#endif
	    if (key >= 0x80 && key < 0x100) {
		// FIXME ARI: ISO->WC2 Translation here!
		key = 0;
	    }
	    switch(key) {
		case '\b': case '\177':
		    if (mi->d.input.nch > 0) {
			strcpy(mi->d.input.buffer + (--mi->d.input.nch), "~!_");
			MustRedraw |= RedrawMenu;
		    }
		    break;
		case 9:
		    goto normkey;
		case 'x':
		case 'X':
		    if( (KeyModifiers&ModifierAlt) ) {
			goto normkey;
		    }
		    /* FALL THROUGH */
		default:
		    if (key >= 32 && key < 0x100) {
			if (mi->d.input.nch < mi->d.input.maxch) {
			    mi->d.input.buffer[mi->d.input.nch++] = keychar;
			    strcpy(mi->d.input.buffer + mi->d.input.nch, "~!_");
			    MustRedraw |= RedrawMenu;
			}
		    }
		    break;
	    }
	    if (mi->d.input.action) {
		(*mi->d.input.action)(mi, key);
	    }
	    return;
	}
    }

normkey:
    if( !(KeyModifiers&ModifierAlt) ) {
	mi = menu->items;
	i = menu->nitems;
	while (i--) {
	    switch (mi->mitype) {
		case MI_TYPE_BUTTON:
		    if (key == mi->d.button.hotkey) {
			if (mi->d.button.handler) {
			    (*mi->d.button.handler)();
			}
			return;
		    }
		default:
		    break;
	    }
	    mi++;
	}
    }
    switch (key) {
	case 10: case 13:			// RETURN
	    if (MenuButtonCurSel != -1) {
		mi = menu->items + MenuButtonCurSel;
		switch (mi->mitype) {
		    case MI_TYPE_BUTTON:
			if (mi->d.button.handler) {
			    (*mi->d.button.handler)();
			}
			return;
		    case MI_TYPE_LISTBOX:
			if (mi->d.listbox.handler) {
			    (*mi->d.listbox.handler)();
			}
			return;
		    case MI_TYPE_VSLIDER:
			if (mi->d.vslider.handler) {
			    (*mi->d.vslider.handler)();
			}
			return;
		    case MI_TYPE_HSLIDER:
			if (mi->d.hslider.handler) {
			    (*mi->d.hslider.handler)();
			}
			return;
		    default:
			break;
		}
	    }
	    break;
	case KeyCodeUp: case KeyCodeDown:
	    if (MenuButtonCurSel != -1) {
		mi = menu->items + MenuButtonCurSel;
		if (!(mi->flags&MenuButtonClicked)) {
		    switch (mi->mitype) {
			case MI_TYPE_PULLDOWN:
			    if (key == KeyCodeDown) {
				if (mi->d.pulldown.curopt + 1 < mi->d.pulldown.noptions)
				    mi->d.pulldown.curopt++;
				else
				    break;
			    } else {
				if (mi->d.pulldown.curopt > 0)
				    mi->d.pulldown.curopt--;
				else
				    break;
			    }
			    MustRedraw |= RedrawMenu;
			    if (mi->d.pulldown.action) {
				(*mi->d.pulldown.action)(mi, mi->d.pulldown.curopt);
			    }
			    break;
			case MI_TYPE_LISTBOX:
			    if (key == KeyCodeDown) {
				if (mi->d.listbox.curopt+mi->d.listbox.startline+1 < mi->d.pulldown.noptions) {
				    mi->d.listbox.curopt++;
				    if (mi->d.listbox.curopt >= mi->d.listbox.nlines) {
					mi->d.listbox.curopt--;
					mi->d.listbox.startline++;
				    }
				} else {
				    break;
				}
			    } else {
				if (mi->d.listbox.curopt+mi->d.listbox.startline > 0) {
				    mi->d.listbox.curopt--;
				    if (mi->d.listbox.curopt < 0) {
					mi->d.listbox.curopt++;
					mi->d.listbox.startline--;
				    }
				} else {
				    break;
				}
			    }
			    if (mi->d.listbox.action) {
				(*mi->d.listbox.action)(mi, mi->d.listbox.curopt + mi->d.listbox.startline);
			    }
			    MustRedraw |= RedrawMenu;
			    break;
			case MI_TYPE_VSLIDER:
			    if (key == KeyCodeDown) {
				mi->d.vslider.cflags |= MI_CFLAGS_DOWN;
			    } else {
				mi->d.vslider.cflags |= MI_CFLAGS_UP;
			    }
			    if (mi->d.vslider.action) {
				(*mi->d.vslider.action)(mi, 2);		// 0 indicates key down
			    }
			    MustRedraw |= RedrawMenu;
			    break;
			default:
			    break;
		    }
		}
	    }
	    break;
	case 9:				// TAB			// FIXME: Add Shift-TAB
	    if (MenuButtonCurSel != -1 && !(menu->items[MenuButtonCurSel].flags&MenuButtonClicked)) {
		n = menu->nitems;
		for (i = 0; i < n; ++i) {
		    mi = menu->items + ((MenuButtonCurSel + i + 1) % n);
		    switch (mi->mitype) {
			case MI_TYPE_PULLDOWN:
			    if ((mi->d.pulldown.state & MI_PSTATE_PASSIVE)) {
				continue;
			    }
			    /* FALL THROUGH */
			case MI_TYPE_BUTTON:
			case MI_TYPE_LISTBOX:
			case MI_TYPE_VSLIDER:
			case MI_TYPE_HSLIDER:
			case MI_TYPE_INPUT:
			    if (mi->flags & MenuButtonDisabled) {
				break;
			    }
			    mi->flags |= MenuButtonSelected;
			    menu->items[MenuButtonCurSel].flags &= ~MenuButtonSelected;
			    MenuButtonCurSel = mi - menu->items;
			    MustRedraw |= RedrawMenu;
			    return;
			default:
			    break;
		    }
		}
	    }
	    break;
	case 'x':
	case 'X':
	    if( (KeyModifiers&ModifierAlt) ) {
		Exit(0);
	    }
	default:
	    mi = menu->items;
	    i = menu->nitems;
	    while (i--) {
		switch (mi->mitype) {
		    case MI_TYPE_INPUT:
			if (!(mi->flags & MenuButtonDisabled)) {
			    menu->items[MenuButtonCurSel].flags &= ~MenuButtonSelected;
			    mi->flags |= MenuButtonSelected;
			    MenuButtonCurSel = mi - menu->items;
			    MustRedraw |= RedrawMenu;
			    goto inkey;
			}
		    default:
			break;
		}
		mi++;
	    }
	    DebugLevel3("Key %d\n",key);
	    return;
    }
    return;
}

/**
**	Handle keys in menu mode.
**
**	@param key	Key scancode.
**	@param keychar	ASCII character code of key.
*/
local void MenuHandleKeyUp(unsigned key,unsigned keychar)
{
    HandleKeyModifiersUp(key,keychar);
}

/**
**	Handle movement of the cursor.
**
**	@param x	Screen X position.
**	@param y	Screen Y position.
*/
local void MenuHandleMouseMove(int x,int y)
{
    int h, w, i, j, n, xs, ys;
    Menuitem *mi;
    Menu *menu = Menus + CurrentMenu;
    int RedrawFlag = 0;

    HandleCursorMove(&x,&y);

    if (CurrentMenu == -1)
	return;

    n = menu->nitems;
    MenuButtonUnderCursor = -1;

    /* check active (popped-up) pulldown first, as it may overlay other menus! */
    mi = menu->items;
    for (i = 0; i < n; ++i) {
	if (!(mi->flags&MenuButtonDisabled)) {
	    if (mi->mitype == MI_TYPE_PULLDOWN && (mi->flags&MenuButtonClicked)) {
		xs = menu->x + mi->xofs;
		ys = menu->y + mi->yofs;
		h = mi->d.pulldown.ysize - 2;
		ys -= mi->d.pulldown.curopt * h;
		if (!(x<xs || x>xs + mi->d.pulldown.xsize || y<ys || y>ys + h*mi->d.pulldown.noptions)) {
		    j = (y - ys) / h;
		    if (j >= 0 && j < mi->d.pulldown.noptions && j != mi->d.pulldown.cursel) {
			mi->d.pulldown.cursel = j;
			RedrawFlag = 1;
			if (mi->d.pulldown.action) {
			    (*mi->d.pulldown.action)(mi, mi->d.pulldown.cursel);
			}
		    }
		}
		MenuButtonUnderCursor = i;
		break;
	    }
	}
	mi++;
    }
    if (MenuButtonUnderCursor == -1) {
	for (i = 0; i < n; ++i) {
	    mi = menu->items + i;
	    if (!(mi->flags&MenuButtonDisabled)) {
		switch (mi->mitype) {
		    case MI_TYPE_GEM:
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x < xs || x > xs + mi->d.gem.xsize || y < ys || y > ys + mi->d.gem.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    continue;
			}
			break;
		    case MI_TYPE_BUTTON:
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x < xs || x > xs + mi->d.button.xsize || y < ys || y > ys + mi->d.button.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    continue;
			}
			break;
		    case MI_TYPE_INPUT:
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x<xs || x>xs + mi->d.input.xsize || y<ys || y>ys + mi->d.input.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    continue;
			}
			break;
		    case MI_TYPE_PULLDOWN:
			if ((mi->d.pulldown.state & MI_PSTATE_PASSIVE)) {
			    continue;
			}
			// Clicked-state already checked above - there can only be one!
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x<xs || x>xs + mi->d.pulldown.xsize || y<ys || y>ys + mi->d.pulldown.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    continue;
			}
			break;
		    case MI_TYPE_LISTBOX:
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x < xs || x > xs + mi->d.listbox.xsize || y < ys || y > ys + mi->d.listbox.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    continue;
			}
			j = (y - ys) / 18;
			if (j != mi->d.listbox.cursel) {
			    mi->d.listbox.cursel = j;	// just store for click
			}
			break;
		    case MI_TYPE_VSLIDER:
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x < xs || x > xs + mi->d.vslider.xsize || y < ys || y > ys + mi->d.vslider.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    mi->d.vslider.cursel = 0;
			    continue;
			}
			j = y - ys;
			mi->d.vslider.cursel = 0;

			if (j < 20) {
			    mi->d.vslider.cursel |= MI_CFLAGS_UP;
			} else if (j > mi->d.vslider.ysize - 20) {
			    mi->d.vslider.cursel |= MI_CFLAGS_DOWN;
			} else {
			    mi->d.vslider.cursel &= ~(MI_CFLAGS_UP|MI_CFLAGS_DOWN);
			    h = (mi->d.vslider.percent * (mi->d.vslider.ysize - 54)) / 100 + 18;
			    if (j > h && j < h + 18) {
				mi->d.vslider.cursel |= MI_CFLAGS_KNOB;
			    } else {
				mi->d.vslider.cursel |= MI_CFLAGS_CONT;
				if (j <= h) {
				    mi->d.vslider.cursel |= MI_CFLAGS_UP;
				} else {
				    mi->d.vslider.cursel |= MI_CFLAGS_DOWN;
				}
			    }
			    j -= 8;
			    if (j < 20) j=20;

			    mi->d.vslider.curper = ((j - 20) * 100) / (mi->d.vslider.ysize - 54);
			    if (mi->d.vslider.curper > 100) {
				mi->d.vslider.curper = 100;
			    }
			}
			if (mi->d.vslider.action) {
			    (*mi->d.vslider.action)(mi, 1);		// 1 indicates move
			}
			break;
		    case MI_TYPE_HSLIDER:
			xs = menu->x + mi->xofs;
			ys = menu->y + mi->yofs;
			if (x < xs || x > xs + mi->d.hslider.xsize || y < ys || y > ys + mi->d.hslider.ysize) {
			    if (!(mi->flags&MenuButtonClicked)) {
				if (mi->flags&MenuButtonActive) {
				    RedrawFlag = 1;
				    mi->flags &= ~MenuButtonActive;
				}
			    }
			    mi->d.hslider.cursel = 0;
			    continue;
			}
			j = x - xs;
			j -= 6;
			if (j < 20) {
			    mi->d.hslider.cursel |= MI_CFLAGS_LEFT;
			} else if (j > mi->d.hslider.xsize - 20) {
			    mi->d.hslider.cursel |= MI_CFLAGS_RIGHT;
			} else {
			    mi->d.hslider.cursel &= ~(MI_CFLAGS_LEFT|MI_CFLAGS_RIGHT);
			    w = (mi->d.hslider.percent * (mi->d.hslider.xsize - 54)) / 100 + 18;
			    mi->d.hslider.curper = ((j - 20) * 100) / (mi->d.hslider.xsize - 54);
			    if (mi->d.hslider.curper > 100) {
				mi->d.hslider.curper = 100;
			    }
			    if (j > w && j < w + 18) {
				mi->d.hslider.cursel |= MI_CFLAGS_KNOB;
			    } else {
				mi->d.hslider.cursel |= MI_CFLAGS_CONT;
				if (j <= w) {
				    mi->d.hslider.cursel |= MI_CFLAGS_LEFT;
				} else {
				    mi->d.hslider.cursel |= MI_CFLAGS_RIGHT;
				}
			    }
			}
			if (mi->d.hslider.action) {
			    (*mi->d.hslider.action)(mi, 1);		// 1 indicates move
			}
			break;
		    default:
			continue;
			// break;
		}
		switch (mi->mitype) {
		    case MI_TYPE_GEM:
			if ((mi->d.gem.state & MI_GSTATE_PASSIVE)) {
			    break;
			}
			/* FALL THROUGH */
		    case MI_TYPE_BUTTON:
		    case MI_TYPE_PULLDOWN:
		    case MI_TYPE_LISTBOX:
		    case MI_TYPE_VSLIDER:
		    case MI_TYPE_HSLIDER:
		    case MI_TYPE_INPUT:
			if (!(mi->flags&MenuButtonActive)) {
			    RedrawFlag = 1;
			    mi->flags |= MenuButtonActive;
			}
			MenuButtonUnderCursor = i;
		    default:
			break;
		}
	    }
	}
    }
    if (RedrawFlag) {
	MustRedraw |= RedrawMenu;
    }
}

/**
**	Called if mouse button pressed down.
**
**	@param b	button code
*/
local void MenuHandleButtonDown(unsigned b __attribute__((unused)))
{
    Menuitem *mi;
    Menu *menu = Menus + CurrentMenu;

    if (CurrentMenu == -1)
	return;

    if (MouseButtons&(LeftButton<<MouseHoldShift))
	return;

    if (MouseButtons&LeftButton) {
	if (MenuButtonUnderCursor != -1) {
	    mi = menu->items + MenuButtonUnderCursor;
	    if (!(mi->flags&MenuButtonClicked)) {
		switch (mi->mitype) {
		    case MI_TYPE_GEM:
		    case MI_TYPE_BUTTON:
		    case MI_TYPE_PULLDOWN:
		    case MI_TYPE_LISTBOX:
		    case MI_TYPE_VSLIDER:
		    case MI_TYPE_HSLIDER:
		    case MI_TYPE_INPUT:
			if (MenuButtonCurSel != -1) {
			    menu->items[MenuButtonCurSel].flags &= ~MenuButtonSelected;
			}
			MenuButtonCurSel = MenuButtonUnderCursor;
			mi->flags |= MenuButtonClicked|MenuButtonSelected;
			MustRedraw |= RedrawMenu;
		    default:
			break;
		}
	    }
	    PlayGameSound(GameSounds.Click.Sound,MaxSampleVolume);
	    switch (mi->mitype) {
		case MI_TYPE_VSLIDER:
		    mi->d.vslider.cflags = mi->d.vslider.cursel;
		    if (mi->d.vslider.action) {
			(*mi->d.vslider.action)(mi, 0);		// 0 indicates down
		    }
		    break;
		case MI_TYPE_HSLIDER:
		    mi->d.hslider.cflags = mi->d.hslider.cursel;
		    if (mi->d.hslider.action) {
			(*mi->d.hslider.action)(mi, 0);		// 0 indicates down
		    }
		    break;
		case MI_TYPE_PULLDOWN:
		    if (mi->d.pulldown.curopt >= 0 &&
					    mi->d.pulldown.curopt < mi->d.pulldown.noptions) {
			mi->d.pulldown.cursel = mi->d.pulldown.curopt;
		    }
		    break;
		case MI_TYPE_LISTBOX:
		    if (mi->d.listbox.cursel != mi->d.listbox.curopt) {
			mi->d.listbox.curopt = mi->d.listbox.cursel;
			if (mi->d.listbox.action) {
			    (*mi->d.listbox.action)(mi, mi->d.listbox.curopt + mi->d.listbox.startline);
			}
		    } else if (mi->d.listbox.handler) {
			// double click support - maybe limit time!
			(*mi->d.listbox.handler)();
		    }
		    break;
		default:
		    break;
	    }
	}
    }
}

/**
**	Called if mouse button released.
**
**	@param b	button code
*/
local void MenuHandleButtonUp(unsigned b)
{
    int i, n;
    Menuitem *mi;
    Menu *menu = Menus + CurrentMenu;
    int RedrawFlag = 0;

    if (CurrentMenu == -1)
	return;

    if ((1<<b) == LeftButton) {
	n = menu->nitems;
	for (i = 0; i < n; ++i) {
	    mi = menu->items + i;
	    switch (mi->mitype) {
		case MI_TYPE_GEM:
		    if (mi->flags&MenuButtonClicked) {
			RedrawFlag = 1;
			mi->flags &= ~MenuButtonClicked;
			if (MenuButtonUnderCursor == i) {
			    MenuButtonUnderCursor = -1;
			    if ((mi->d.gem.state & MI_GSTATE_CHECKED)) {
				mi->d.gem.state &= ~MI_GSTATE_CHECKED;
			    } else {
				mi->d.gem.state |= MI_GSTATE_CHECKED;
			    }
			    if (mi->d.gem.action) {
				(*mi->d.gem.action)(mi);
			    }
			}
		    }
		    break;
		case MI_TYPE_BUTTON:
		    if (mi->flags&MenuButtonClicked) {
			RedrawFlag = 1;
			mi->flags &= ~MenuButtonClicked;
			if (MenuButtonUnderCursor == i) {
			    MenuButtonUnderCursor = -1;
			    if (mi->d.button.handler) {
				(*mi->d.button.handler)();
			    }
			}
		    }
		    break;
		case MI_TYPE_PULLDOWN:
		    if (mi->flags&MenuButtonClicked) {
			RedrawFlag = 1;
			mi->flags &= ~MenuButtonClicked;
			if (MenuButtonUnderCursor == i) {
			    MenuButtonUnderCursor = -1;
			    if (mi->d.pulldown.cursel != mi->d.pulldown.curopt &&
					    mi->d.pulldown.cursel >= 0 &&
					    mi->d.pulldown.cursel < mi->d.pulldown.noptions) {
				mi->d.pulldown.curopt = mi->d.pulldown.cursel;
				if (mi->d.pulldown.action) {
				    (*mi->d.pulldown.action)(mi, mi->d.pulldown.curopt);
				}
			    }
			}
			mi->d.pulldown.cursel = 0;
		    }
		    break;
		case MI_TYPE_LISTBOX:
		    if (mi->flags&MenuButtonClicked) {
			RedrawFlag = 1;
			mi->flags &= ~MenuButtonClicked;
			// MAYBE ADD HERE
		    }
		    break;
		case MI_TYPE_VSLIDER:
		    if (mi->flags&MenuButtonClicked) {
			RedrawFlag = 1;
			mi->flags &= ~MenuButtonClicked;
			mi->d.vslider.cflags = 0;
		    }
		    break;
		case MI_TYPE_HSLIDER:
		    if (mi->flags&MenuButtonClicked) {
			RedrawFlag = 1;
			mi->flags &= ~MenuButtonClicked;
			mi->d.hslider.cflags = 0;
		    }
		    break;
		default:
		    break;
	    }
	}
    }
    if (RedrawFlag) {
	MustRedraw |= RedrawMenu;

	MenuHandleMouseMove(CursorX,CursorY);
    }
}

/**
**	End process menu
**
*/
local void EndMenu(void)
{
    CursorOn = CursorOnUnknown;
    CurrentMenu = -1;

    MustRedraw = RedrawEverything;
    InterfaceState = IfaceStateNormal;
    UpdateDisplay();
    InterfaceState = IfaceStateMenu;
    MustRedraw = RedrawMenu;
}

/**
**	Process a menu.
**
**	@param menu_id	The menu number to process
**	@param loop	Indicates to setup handlers and really 'Process'
**
**	@todo FIXME: This function is called from the event handler!!
*/
global void ProcessMenu(int menu_id, int loop)
{
    int i, oldncr;
    Menu *menu;
    Menuitem *mi;
    int CurrentMenuSave = -1;
    int MenuButtonUnderCursorSave = -1;
    int MenuButtonCurSelSave = -1;

    CancelBuildingMode();

    // Recursion protection:
    if (loop) {
	CurrentMenuSave = CurrentMenu;
	MenuButtonUnderCursorSave = MenuButtonUnderCursor;
	MenuButtonCurSelSave = MenuButtonCurSel;
    }

    InterfaceState = IfaceStateMenu;
    VideoLockScreen();
    HideAnyCursor();
    VideoUnlockScreen();
    DestroyCursorBackground();
    MustRedraw |= RedrawCursor;
    CursorState = CursorStatePoint;
    GameCursor = TheUI.Point.Cursor;
    CurrentMenu = menu_id;
    menu = Menus + CurrentMenu;
    MenuButtonCurSel = -1;
    for (i = 0; i < menu->nitems; ++i) {
	mi = menu->items + i;
	switch (mi->mitype) {
	    case MI_TYPE_BUTTON:
	    case MI_TYPE_PULLDOWN:
	    case MI_TYPE_LISTBOX:
	    case MI_TYPE_VSLIDER:
	    case MI_TYPE_HSLIDER:
	    case MI_TYPE_INPUT:
		mi->flags &= ~(MenuButtonClicked|MenuButtonActive
				|MenuButtonSelected);
		if (i == menu->defsel) {
		    mi->flags |= MenuButtonSelected;
		    MenuButtonCurSel = i;
		}
		break;
	}
	switch (mi->mitype) {
	    case MI_TYPE_PULLDOWN:
		mi->d.pulldown.cursel = 0;
		if (mi->d.pulldown.defopt != -1)
		    mi->d.pulldown.curopt = mi->d.pulldown.defopt;
		break;
	    case MI_TYPE_LISTBOX:
		mi->d.listbox.cursel = -1;
		mi->d.listbox.startline = 0;
		if (mi->d.listbox.defopt != -1)
		    mi->d.listbox.curopt = mi->d.listbox.defopt;
		break;
	    case MI_TYPE_VSLIDER:
		mi->d.vslider.cflags = 0;
		if (mi->d.vslider.defper != -1)
		    mi->d.vslider.percent = mi->d.vslider.defper;
		break;
	    case MI_TYPE_HSLIDER:
		mi->d.hslider.cflags = 0;
		if (mi->d.hslider.defper != -1)
		    mi->d.hslider.percent = mi->d.hslider.defper;
		break;
	    default:
		break;
	}
	if (mi->initfunc) {
	    (*mi->initfunc)(mi);
	}
    }
    MenuButtonUnderCursor = -1;
    if (loop) {
	SetVideoSync();
	MustRedraw = 0;
	MenuHandleMouseMove(CursorX,CursorY);	// This activates buttons as appropriate!
	MustRedraw |= RedrawCursor;
    }


    VideoLockScreen();
    DrawMenu(CurrentMenu);
    VideoUnlockScreen();

    if (loop) {
	while (CurrentMenu != -1) {
	    DebugLevel3("MustRedraw: 0x%08x\n",MustRedraw);
	    if (MustRedraw) {
		UpdateDisplay();
	    }
	    RealizeVideoMemory();
	    oldncr = NetConnectRunning;
	    WaitEventsOneFrame(&callbacks);
	    if (NetConnectRunning == 2) {
		NetworkProcessClientRequest();
		// ARI: FIXME: THIS DOES NOT BELONG HERE!
		if (NetLocalState == ccs_connecting) {
		    sprintf(NetworkTriesText,"Connecting try %d of 60",
			NetStateMsgCnt);
		} else {
		    sprintf(NetworkTriesText,"Connected try %d of 20",
			NetStateMsgCnt);
		}
		MustRedraw |= RedrawMenu;
	    }
	    // stopped by network activity?
	    if (oldncr == 2 && NetConnectRunning == 0) {
		if (menu->netaction) {
		    (*menu->netaction)();
		}
	    }
	}
    }

    for (i = 0; i < menu->nitems; ++i) {
	mi = menu->items + i;
	if (mi->exitfunc) {
	    (*mi->exitfunc)(mi);		// action/destructor
	}
    }

    if (loop) {
	CurrentMenu = CurrentMenuSave;
	MenuButtonUnderCursor = MenuButtonUnderCursorSave;
	MenuButtonCurSel = MenuButtonCurSelSave;
    }

    // FIXME: Johns good point?
    if (Menusbgnd) {
	VideoFree(Menusbgnd);
	Menusbgnd = NULL;
    }
}

/**
**	Move buttons so they're centered on different resolutions
*/
local void MoveButtons()
{
    int menus = sizeof(Menus) / sizeof(Menu);
    int i;

    OffsetX = (VideoWidth - 640) / 2;
    OffsetY = (VideoHeight - 480) / 2;

    for (i=0; i<menus; i++) {
	Menus[i].x += OffsetX;
	Menus[i].y += OffsetY;
    }
}

/**
**	Init Menus for a specific race
**
**	@param race	The Race to set-up for
*/
global void InitMenus(unsigned int race)
{
    static int last_race = -1;
    const char* file;
    char *buf;

    if (last_race == -1 && VideoWidth != 640) {
	MoveButtons();
    }
    if (last_race == -1) {
	callbacks.ButtonPressed=&MenuHandleButtonDown;
	callbacks.ButtonReleased=&MenuHandleButtonUp;
	callbacks.MouseMoved=&MenuHandleMouseMove;
	callbacks.MouseExit=&HandleMouseExit;
	callbacks.KeyPressed=&MenuHandleKeyDown;
	callbacks.KeyReleased=&MenuHandleKeyUp;
	callbacks.NetworkEvent=NetworkEvent;
	callbacks.SoundReady=WriteSound;
    }

    if (race == last_race) {	// same race? already loaded!
	return;
    }
    if (last_race != -1) {	// free previous sprites for different race
	VideoFree(MenuButtonGfx.Sprite);
    }
    last_race = race;
    file = MenuButtonGfx.File[race];
    buf = alloca(strlen(file) + 9 + 1);
    file = strcat(strcpy(buf, "graphics/"), file);
    MenuButtonGfx.Sprite = LoadSprite(file, 300, 144);	// 50/53 images!

    //
    //	Autodetect the swamp tileset 
    //
#ifdef HAVE_EXPANSION
    strcpy(ScenSelectFullPath, FreeCraftLibPath);
    if (ScenSelectFullPath[0]) {
	strcat(ScenSelectFullPath, "/graphics/tilesets/");
    }
    strcat(ScenSelectFullPath, "swamp");
    if (access(ScenSelectFullPath, F_OK) != 0) {
	// ARI FIXME: Hack to disable Expansion Gfx..
	// also shows how to add new tilesets....
	// - FIXME2:
	// With new dynamic tileset configuration this
	// should read what siod-config gave us and
	// build the menu from that..
	CustomGameMenuItems[14].d.pulldown.noptions = 4;
    }
#else
    CustomGameMenuItems[14].d.pulldown.noptions = 4;
#endif
}

/**
**	Exit Menus code (freeing data)
**
**	// FIXME: NOT CALLED YET.....!!!!!
*/
global void ExitMenus(void)
{
    if (Menusbgnd) {
	VideoFree(Menusbgnd);
	Menusbgnd = NULL;
    }
}

//@}
