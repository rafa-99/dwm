/* See LICENSE file for copyright and license details. */

#include "colors.h"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "FiraCode Nerd Font:size=14" };
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_border }, // Unfocused Windows
	[SchemeSel]  = { sel_fg,  sel_bg,  sel_border  }, // Focused Windows
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal  noswallow  monitor */
	{ NULL,       NULL,       NULL,       0,            False,       0,          0,         -1 },
	{ "st",       NULL,       NULL,       0,            False,       1,          -1,        -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

//#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define ALTKEY Mod1Mask
#define CTRLKEY ControlMask
#define SHIFTKEY ShiftMask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* Managing Windows */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|CTRLKEY,               XK_p,      incnmaster,     {.i = +1 } },
	{ MODKEY|CTRLKEY,               XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|CTRLKEY,               XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|CTRLKEY,               XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|SHIFTKEY,              XK_q,      killclient,     {0} },
	{ MODKEY|SHIFTKEY,              XK_x,      quit,           {0} },
	{ MODKEY|SHIFTKEY,              XK_r,      quit,           {1} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|CTRLKEY,               XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|CTRLKEY,               XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|CTRLKEY,               XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|CTRLKEY,               XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },

	/* Managing Gaps */
	{ MODKEY|ALTKEY,                XK_period, incrgaps,       {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_comma,  incrgaps,       {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_t,      togglegaps,     {0} },
	{ MODKEY|ALTKEY,                XK_d,      defaultgaps,    {0} },

	/* Managing Tags and Status Bar */
	{ MODKEY,                       XK_h,      viewtoleft,     {0} },
	{ MODKEY,                       XK_l,      viewtoright,    {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|SHIFTKEY,              XK_h,      tagtoleft,      {0} },
	{ MODKEY|SHIFTKEY,              XK_l,      tagtoright,     {0} },
	{ MODKEY|SHIFTKEY,              XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|SHIFTKEY,              XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|SHIFTKEY,              XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* Managing Layouts */
	{ MODKEY|ALTKEY,                XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ALTKEY,                XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ALTKEY,                XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ALTKEY,                XK_space,  togglefloating, {0} },

	/* Regular Apps */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run -i") },//dmenu
	{ MODKEY,                       XK_Return, spawn,          SHCMD("$TERMINAL") },//Terminal
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },//Web-Browser
	{ MODKEY,                       XK_f,      spawn,          SHCMD("$TERMINAL -e $FILE") },//File Manager
	{ MODKEY,                       XK_n,      spawn,          SHCMD("$TERMINAL -e $NEWS") },//News Manager
	{ MODKEY|SHIFTKEY,              XK_d,      spawn,          SHCMD("$TERMINAL -e $DOCS") },//Dotfiles Documentation

	/* Scripts */
	{ MODKEY,                       XK_s,      spawn,          SHCMD("search") },//Quick Web Search
	{ MODKEY,                       XK_e,      spawn,          SHCMD("glypher") },//Glyph Selector
	{ MODKEY|SHIFTKEY,              XK_o,      spawn,          SHCMD("monitor") },//Set Screen Output
	{ MODKEY,                       XK_m,      spawn,          SHCMD("musicselect") },//Music Selector
	{ MODKEY|SHIFTKEY,              XK_c,      spawn,          SHCMD("powermenu") },//Power Menu
	{ MODKEY,                       XK_p,      spawn,          SHCMD("screenshot") },//Screenshot Tool Script
	{ MODKEY|SHIFTKEY,              XK_p,      spawn,          SHCMD("passmenu") },//Opens PassMenu Password Manager
	{ MODKEY|SHIFTKEY,              XK_s,      spawn,          SHCMD("screenkeys") },//Enable Screenkeys
	{ MODKEY,                       XK_v,      spawn,          SHCMD("yt") },//Youtube
	{ MODKEY,                       XK_t,      spawn,          SHCMD("switchLayout") },//Switches Between Keyboard Layouts

	/* Quick Actions */
	{ MODKEY,                       XK_F1,     spawn,          SHCMD("mixer t") },//Toggle Mute
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("mixer -") },//Decrease Volume by 5%
	{ MODKEY,                       XK_F3,     spawn,          SHCMD("mixer +") },//Increase Volume by 5%
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("mixer m") },//Toggle Mic Mute
	{ MODKEY,                       XK_F5,     spawn,          SHCMD("doas light -U 5") },//Decrease Brightness by 5%
	{ MODKEY,                       XK_F6,     spawn,          SHCMD("doas light -A 5") },//Increase Brightness by 5%
	{ MODKEY,                       XK_F7,     spawn,          SHCMD("bluelight") },//Toggle Bluelight Filter
	{ MODKEY,                       XK_F8,     spawn,          SHCMD("screenrecord") },//Screen Recording Script
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("mpc toggle") },//Music Pause/Play
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("killall mpd") },//Music Quit/Stop
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("mpc prev") },//Music Previous
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("mpc next") },//Music Next
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
