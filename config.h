/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int startwithgaps      = 1;        /* 0 means gaps are not used by default */
static const unsigned int gappx     = 20;       /* gap size between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int statusrpad         = 6;        /* right padding of bar status text in px */
static const int statuslpad         = 6;        /* left padding of bar status text in px */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#ff0000";

#ifdef USE_PYWAL_COLORS
#include "colors-wal-dwm.h"
#else
static const char *colors[][3]      = {
 	/*               fg         bg         border   */
 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeUrg]  = { col_gray4, col_cyan,  col_red   }},
};
#endif

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */
static const int decorhints     = 1;    /* 1 means to respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
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
static const char *dmenucmd[]     = { "dmenu_run",
#ifdef USE_PYWAL_COLORS
	"-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg,   "-nf", norm_fg,   "-sb", sel_bg,   "-sf", sel_fg, NULL };
#else
	"-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
#endif
static const char *dmenudruncmd[] = { "dmenu_drun",
#ifdef USE_PYWAL_COLORS
	"-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg,   "-nf", norm_fg,   "-sb", sel_bg,   "-sf", sel_fg, NULL };
#else
	"-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
#endif
static const char *termcmd[]      = { "kitty", NULL };
static const char *helpcmd[]      = { "kitty", "less", "/usr/share/dwm/help.md", NULL };

static Key keys[] = {
	/* modifier                     key        function         argument */
	// Spawn keybinds
	{ MODKEY,                       XK_d,      spawn,           {.v = dmenucmd     } },  // dmenu
	{ MODKEY,                       XK_a,      spawn,           {.v = dmenudruncmd } },  // dmenu_drun
	{ MODKEY,                       XK_t,      spawn,           {.v = termcmd      } },  // terminal

	// Show help
	{ MODKEY|Mod1Mask,              XK_h,      spawn,           {.v = helpcmd } },

	// Change focus
	{ MODKEY,                       XK_j,      focusstack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,      {.i = -1 } },

	// Rotate stack
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,     {.i = -1 } },

	// Move the focused client to the master area
	// The previous client in the master area is pushed on the stack
	{ MODKEY|ShiftMask,             XK_z,      zoom,            {0} },

	// Change factor of master area
	{ MODKEY|ControlMask,           XK_h,      setmfact,        {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,        {.f = +0.05} },
	
	// Change number of clients in the master area
	{ MODKEY|ControlMask,           XK_i,      incnmaster,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_d,      incnmaster,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_0,      incnmaster,      {.i =  0 } },

	// Change factor of clients
	{ MODKEY|ControlMask,           XK_j,      setcfact,        {.f = +0.25 } },
	{ MODKEY|ControlMask,           XK_k,      setcfact,        {.f = -0.25 } },
	{ MODKEY|ControlMask,           XK_o,      setcfact,        {.f =  0.0  } },

	// Change gap size
	{ MODKEY,                       XK_minus,  setgaps,         {.i = -5 } },
	{ MODKEY,                       XK_plus,   setgaps,         {.i = +5 } },
	{ MODKEY,                       XK_0,      setgaps,         {.i = GAP_RESET } },

	// Kill the current client
	{ MODKEY,                       XK_q,      killclient,      {0} },
	
	// Toggle floating for one single window
	{ MODKEY,                       XK_space,  togglefloating,  {0} },

	// Set client fullscreen state
	{ MODKEY,                       XK_F11,    focusfullscreen, {0} },

	// Change window layout
	{ MODKEY|Mod1Mask,              XK_t,      setlayout,       {.v = &layouts[0]} }, // Tiling
	{ MODKEY|Mod1Mask,              XK_f,      setlayout,       {.v = &layouts[1]} }, // No layout / Floating
	{ MODKEY|Mod1Mask,              XK_m,      setlayout,       {.v = &layouts[2]} }, // Monocle

	// Workspaces
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	TAGKEYS(                        XK_8,                       7)
	TAGKEYS(                        XK_9,                       8)

	// Quit dwm
	{ MODKEY|ShiftMask,             XK_e,      quit,            {.i = 0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,            {.i = 1} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

