/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx 	= 0;        /* border pixel of windows */
static const unsigned int snap 		= 32;       /* snap pixel */
static const int showbar 		= 1;        /* 0 means no bar */
static const int topbar 		= 1;        /* 0 means bottom bar */
static const char *fonts[] 		= { "Sans:pixelsize=17:antialias=true:autohint=true" , "Font Awesome:pixelsize=17:antialias=true:autohint=true" };
static const char dmenufont[] 		= "Sans:pixelsize=17:antialias=true:autohint=true";
static const char col_white[] 		= "#ffffff";
static const char col_alt1[] 		= "#f6f5f4";
static const char col_alt2[] 		= "#2e3436";
static const char col_black[] 		= "#000000";
static const char col_accent[] 		= "#3584E4";
static const char *colors[][3] 		= {
	/*		fg		bg		border   */
	[SchemeNorm] = {col_alt2,	col_alt1,	col_alt1 },
	[SchemeSel]  = {col_black,	col_alt1,	col_accent },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact 	= 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster 	= 1;    /* number of clients in master area */
static const int resizehints 	= 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=", 	tile },    /* first entry is default */
	{ "><>", 	NULL },    /* no layout function means floating behavior */
	{ "[M]", 	monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY, 			KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask, 		KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask, 		KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* include all media- and functionkeys */
#include <X11/XF86keysym.h>

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] 	= "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 	= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_alt1, "-nf", col_black, "-sb", col_accent, "-sf", col_white, NULL };
static const char *termcmd[]  	= { "st", NULL };
static const char *browsercmd[] = {"firefox", NULL};

static Key keys[] = {
	/* modifier 			key 				function 		argument */
	{ MODKEY,			XK_p,				spawn, 			{.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_Return, 			spawn, 			{.v = termcmd } },
	{ MODKEY,			XK_w,				spawn, 			{.v = browsercmd } },
	{ MODKEY,			XK_b,				togglebar, 		{0} },
	{ MODKEY,			XK_j,				focusstack, 		{.i = +1 } },
	{ MODKEY,			XK_k,				focusstack, 		{.i = -1 } },
	{ MODKEY,			XK_i,				incnmaster, 		{.i = +1 } },
	{ MODKEY,			XK_d,				incnmaster, 		{.i = -1 } },
	{ MODKEY,			XK_h,				setmfact, 		{.f = -0.05} },
	{ MODKEY,			XK_l,				setmfact, 		{.f = +0.05} },
	{ MODKEY,			XK_Return,			zoom, 			{0} },
	{ MODKEY,			XK_Tab,				view,			{0} },
	{ MODKEY|ShiftMask,		XK_c,				killclient, 		{0} },
	{ MODKEY,			XK_t,				setlayout, 		{.v = &layouts[0]} },
	{ MODKEY,			XK_f,				setlayout, 		{.v = &layouts[1]} },
	{ MODKEY,			XK_m,				setlayout, 		{.v = &layouts[2]} },
	{ MODKEY,			XK_space,			setlayout, 		{0} },
	{ MODKEY|ShiftMask,		XK_space,			togglefloating, 	{0} },
	{ MODKEY,			XK_0,				view, 			{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,				tag, 			{.ui = ~0 } },
	{ MODKEY,			XK_comma,			focusmon, 		{.i = -1 } },
	{ MODKEY,			XK_period,			focusmon, 		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_comma,			tagmon, 		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_period,			tagmon, 		{.i = +1 } },
	TAGKEYS(			XK_1,							0)
	TAGKEYS( 			XK_2,							1)
	TAGKEYS(			XK_3,							2)
	TAGKEYS(			XK_4,							3)
	TAGKEYS(			XK_5,							4)
	TAGKEYS(			XK_6,							5)
	{ MODKEY|ShiftMask, 		XK_q,				quit,			{0} },
	{ 0,				XF86XK_AudioMute,		spawn,			SHCMD("pamixer -t; kill -38 $(pidof dwmblocks)") },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,			SHCMD("pamixer --allow-boost -i 10; kill -38 $(pidof dwmblocks)") },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,			SHCMD("pamixer --allow-boost -d 10; kill -38 $(pidof dwmblocks)") },
	{ ShiftMask,			XF86XK_AudioRaiseVolume,	spawn,			SHCMD("pamixer --allow-boost -i 5; kill -38 $(pidof dwmblocks)") },
	{ ShiftMask,			XF86XK_AudioLowerVolume,	spawn,			SHCMD("pamixer --allow-boost -d 5; kill -38 $(pidof dwmblocks)") },
	{ 0,				XF86XK_MonBrightnessUp,		spawn,			SHCMD("xbacklight -inc 10; kill -37 $(pidof dwmblocks)") },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,			SHCMD("xbacklight -dec 10; kill -37 $(pidof dwmblocks)") },
	{ ControlMask, 			XF86XK_MonBrightnessUp,		spawn,			SHCMD("xbacklight -set 100; kill -37 $(pidof dwmblocks)") },
	{ ControlMask, 			XF86XK_MonBrightnessDown,	spawn,			SHCMD("xbacklight -set 5; kill -37 $(pidof dwmblocks)") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click		event mask		button		function	argument */
	{ ClkLtSymbol,		0,			Button1,	setlayout,	{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,	{.v = &layouts[2]} },
	{ ClkWinTitle,		0,			Button2,	zoom,		{0} },
	{ ClkStatusText,	0,			Button2,	spawn,		{.v = termcmd } },
	{ ClkClientWin,		MODKEY,			Button1,	movemouse,	{0} },
	{ ClkClientWin,		MODKEY,			Button2,	togglefloating,	{0} },
	{ ClkClientWin,		MODKEY|ShiftMask,	Button1,	resizemouse,	{0} },
	{ ClkTagBar,		0,			Button1,	view,		{0} },
	{ ClkTagBar,		0,			Button3,	toggleview,	{0} },
	{ ClkTagBar,		MODKEY,			Button1,	tag,		{0} },
	{ ClkTagBar,		MODKEY,			Button3,	toggletag,	{0} },
};

