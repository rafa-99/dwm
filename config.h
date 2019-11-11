/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=11" };
static const char norm_fg[]           = "#a2e9d0";
static const char norm_bg[]           = "#040a33";
static const char norm_border[]       = "#396087";
static const char sel_fg[]            = "#a2e9d0";
static const char sel_bg[]            = "#396087";
static const char sel_border[]        = "#a2e9d0";
static const char urg_fg[]            = "#a2e9d0";
static const char urg_bg[]            = "#c1355d";
static const char urg_border[]        = "#c1355d";
static const char s_base03[]          = "#002b36";
static const char s_base02[]          = "#073642";
static const char s_base01[]          = "#586e75";
static const char s_base00[]          = "#657b83";
static const char s_base0[]           = "#839496";
static const char s_base1[]           = "#93a1a1";
static const char s_base2[]           = "#eee8d5";
static const char s_base3[]           = "#fdf6e3";
static const char *colors[][3]        = {


	/*fg           bg         border                         */
	{ norm_fg,     norm_bg,   norm_border }, // unfocused wins
	{ sel_fg,      sel_bg,    sel_border },  // the focused win
	{ sel_border,  norm_bg,   sel_border  }, // awesome bar
	{ s_base0, s_base03, s_base2 },      /* SchemeNorm dark */
	{ s_base0, s_base02, s_base2 },      /* SchemeSel dark */
	{ s_base00, s_base3, s_base02 },     /* SchemeNorm light */
	{ s_base00, s_base2, s_base02},      /* SchemeSel light */

};

/* tagging */
static const char *tags[] = { "I ", "II ", "III ", "IV ", "V ", "VI ", "VII ", "VIII ", "IV " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
	{ NULL,       NULL },
};

/* key definitions */
#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86MonBrightnessDown 0x1008ff03
#define XF86MonBrightnessUp 0x1008ff02
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run" };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	// Managing Windows
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_k,      setsmfact,      {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,      setsmfact,      {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
	{ MODKEY|ControlMask,	        XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY,                       XK_Up,     moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY,                       XK_Right,  moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY,                       XK_Left,   moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},
	// Managing Tags & Statusbar
 	{ MODKEY,                       XK_h,      viewtoleft,     {0} },
 	{ MODKEY,                       XK_l,      viewtoright,    {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
 	{ MODKEY|ShiftMask,             XK_space,  togglebar,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// Launching Apps
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },//Terminal
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },//Dmenu
	{ MODKEY,                       XK_m,      spawn,          SHCMD("sh ~/.config/scripts/musicselect") },//Music Selector
	{ MODKEY,                       XK_e,      spawn,          SHCMD("sh ~/.config/scripts/glypher") },//Glyph Selector
	{ MODKEY,                       XK_i,      spawn,          SHCMD("sh ~/.config/scripts/quickopen") },//Quick File Opener
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("sh ~/.config/scripts/mounter") },//Drive Mounter
	{ MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("sh ~/.config/scripts/umounter") },//Drive Umounter
	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("sh ~/.config/scripts/output") },//Set Screen Output
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("sh ~/.config/scripts/shutdowntimer") },//Shutdown Timer
	{ MODKEY|ShiftMask,             XK_F9,     spawn,          SHCMD("sh ~/.config/scripts/screenrecord") },//Start Screen Recording
	{ MODKEY|ShiftMask,             XK_F10,    spawn,          SHCMD("killall ffmpeg") },//Stop Recording
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },//Quick FullScreen
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("sh ~/.config/scripts/bluelight") },//Enable Bluelight Filter
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("mpc toggle") },//Music Pause/Play
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("killall mpd") },//Music Quit/Stop
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("mpc prev") },//Music Previous
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("mpc next") },//Music Next
	{ MODKEY,                       XK_w,      spawn,          SHCMD("tabbed surf -e") },//Web-Browser
	{ MODKEY,                       XK_p,      spawn,          SHCMD("system-config-printer") },//Printer/Scanner Manager
	{ MODKEY,                       XK_n,      spawn,          SHCMD("nm-connection-editor") },//Network Manager
	{ MODKEY,                       XK_a,      spawn,          SHCMD("st -e alsamixer") },//Sound Mixer
	{ MODKEY,                       XK_f,      spawn,          SHCMD("st -e vifm") },//File Manager
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("systemctl suspend && slock") },//Suspend and Lock Computer
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("shutdown now") },//Shutdown
	{ 0,                            XK_Print,  spawn,          SHCMD("maim ~/Pictures/Screenshots/screenshot-$(date '+%Y%m%d_%H%M%S').png") },//Screenshot
	{ 0,                            XF86MonBrightnessDown, spawn, SHCMD("sudo brightnessctl set 10%-") },//Decrease Brightness 10%
	{ 0,                            XF86MonBrightnessUp,   spawn, SHCMD("sudo brightnessctl set +10%") },//Increase Brightness 10%
	{ 0,                            XF86AudioMute,         spawn, SHCMD("amixer set Master toggle") },//Mute Volume
	{ 0,                            XF86AudioLowerVolume,  spawn, SHCMD("amixer set Master 5%-") },//Decrease Volume 5%
	{ 0,                            XF86AudioRaiseVolume,  spawn, SHCMD("amixer set Master 5%+") },//Increase Volume 5%
	{ MODKEY,                       XK_z,      schemeToggle,   {0} },
	{ MODKEY|ShiftMask,             XK_z,      schemeCycle,    {0} },
};

/* Left out Keybindings
 * 	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
 * 	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
 * 	{ MODKEY,                       XK_Return, zoom,           {0} },
 * 	{ MODKEY,                       XK_Tab,    view,           {0} },
 * 	{ MODKEY,                       XK_space,  setlayout,      {0} },
 * 	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
 * 	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
 * 	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
 * 	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
 * 	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
 * 	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
 * 	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
 * 	{ MODKEY|ShiftMask,             XK_Left,   tagtoleft,      {0} },
 * 	{ MODKEY|ShiftMask,             XK_Right,  tagtoright,     {0} },
*/

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

