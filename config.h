/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=11" };
static const char norm_fg[]         = "#a2e9d0";
static const char norm_bg[]         = "#040a33";
static const char norm_border[]     = "#396087";
static const char sel_fg[]          = "#a2e9d0";
static const char sel_bg[]          = "#396087";
static const char sel_border[]      = "#a2e9d0";
static const char urg_fg[]          = "#a2e9d0";
static const char urg_bg[]          = "#c1355d";
static const char urg_border[]      = "#c1355d";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg,     norm_bg,   norm_border },   // Unfocused Windows
	[SchemeSel]  = { sel_fg,      sel_bg,    sel_border },    // Focused Windows
	[SchemeHid]  = { sel_border,    norm_bg,   sel_border  }, // Awesome Bar
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
 	{ "HHH",      grid },
 	{ "[D]",      deck },
};

/* key definitions */
#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86MonBrightnessDown 0x1008ff03
#define XF86MonBrightnessUp 0x1008ff02
#define ALTKEY Mod1Mask
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
static const char *dmenucmd[] = { "dmenu_run", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* Managing Windows */
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_p,      incnmaster,     {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ALTKEY,                XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ALTKEY,                XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ALTKEY,                XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ALTKEY,                XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ALTKEY,                XK_5,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ALTKEY,                XK_6,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ALTKEY,                XK_7,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ALTKEY,                XK_8,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ALTKEY,                XK_9,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY,                       XK_Up,     moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY,                       XK_Right,  moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY,                       XK_Left,   moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},
	/* Managing Tags and Status Bar */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/* Launching Apps */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          SHCMD("$TERMINAL") },//Terminal
	{ MODKEY,                       XK_m,      spawn,          SHCMD("musicselect") },//Music Selector
	{ MODKEY,                       XK_e,      spawn,          SHCMD("glypher") },//Glyph Selector
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("mounter") },//Drive Mounter
	{ MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("umounter") },//Drive Umounter
	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("monitor") },//Set Screen Output
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("shutdowntimer") },//Shutdown Timer
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("formatter") },//Drive Formatter
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("bluelight") },//Enable Bluelight Filter
	{ MODKEY,                       XK_F7,     spawn,          SHCMD("screenrecord") },//Start Screen Recording
	{ MODKEY,                       XK_F8,     spawn,          SHCMD("killall ffmpeg") },//Stop Recording
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("mpc toggle") },//Music Pause/Play
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("killall mpd") },//Music Quit/Stop
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("mpc prev") },//Music Previous
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("mpc next") },//Music Next
	{ MODKEY,                       XK_w,      spawn,          SHCMD("tabbed surf -e") },//Web-Browser
	{ MODKEY,                       XK_p,      spawn,          SHCMD("system-config-printer") },//Printer/Scanner Manager
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("$TERMINAL -e ncmpcpp") },//Open Music Player
	{ MODKEY,                       XK_n,      spawn,          SHCMD("$TERMINAL -e nmtui") },//Network Manager
	{ MODKEY,                       XK_a,      spawn,          SHCMD("$TERMINAL -e alsamixer") },//Sound Mixer
	{ MODKEY,                       XK_f,      spawn,          SHCMD("$TERMINAL -e vifm") },//File Manager
//	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("systemctl suspend && slock") },//Suspend and Lock Computer
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("sudo poweroff") },//Shutdown
	{ 0,                            XK_Print,  spawn,          SHCMD("scrot ~/Pictures/Screenshots/screenshot-$(date '+%Y%m%d_%H%M%S').png") },//Screenshot
//	{ 0,                            XF86MonBrightnessDown, spawn, SHCMD("sudo brightnessctl set 10%-") },//Decrease Brightness 10%
//	{ 0,                            XF86MonBrightnessUp,   spawn, SHCMD("sudo brightnessctl set +10%") },//Increase Brightness 10%
	{ 0,                            XF86AudioMute,         spawn, SHCMD("amixer set Master toggle") },//Mute Volume
	{ 0,                            XF86AudioLowerVolume,  spawn, SHCMD("amixer set Master 5%-") },//Decrease Volume 5%
	{ 0,                            XF86AudioRaiseVolume,  spawn, SHCMD("amixer set Master 5%+") },//Increase Volume 5%
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("$TERM") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

