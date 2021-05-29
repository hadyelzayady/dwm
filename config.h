/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static unsigned int borderpx  = 5;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static unsigned int gappih    = 5;       /* horiz inner gap between windows */
static unsigned int gappiv    = 5;       /* vert inner gap between windows */
static unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-t", "spterm", "-o", "window.columns=120","window.lines=50", NULL };
const char *spcmd2[] = {TERMINAL, "-t", "spcalc", "-o","window.columns=50", "window.lines=20", "-e", "wcalc", NULL };
const char *spcmd3[] = {TERMINAL, "-t", "spnotes", "-o", "window.columns=50","window.lines=20", "-e", "notetaker", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",    spcmd2},
	{"spnotes",    spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ TERMCLASS,   NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      NULL,    "spterm",       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      NULL,    "spcalc",       	    SPTAG(1),     1,           1,         0,        -1 },
	{ NULL,      NULL,    "spnotes",       	    SPTAG(2),     1,           1,         0,        -1 },
	{ "youtube-music-desktop-app",NULL,NULL,   1 << 8,          0,           0,		  0,		-1 },
	{ "Notion","notion"      ,NULL,            1 << 7,         0,           0,		  0,		-1 },

    // Floating windows
	{ NULL,      NULL,    "pulsemixer",       	0,            1,           0,         0,        -1 },
	{ NULL,      NULL,    "nmtui-float",       	0,            1,           0,         0,        -1 },
	{ NULL,      NULL,    "calcurse-float",       	0,            1,           0,         0,        -1 },
	{ "todoist-nativefier-409272",      "todoist-nativefier-409272", NULL,       	2,            1,           0,         0,        -1 },
	{ "copyq",     NULL,       NULL,            0,            1,           0,         0,        -1 },
	{ "scrcpy",     NULL,       NULL,            0,            1,           0,         0,        -1 },
	{ "firefox", "Places", "Library",           0,            1,           0,         0,        -1 },
	{ "firefox","Toolkit", "Picture-in-Picture",0,            1,           0,         0,        -1 },
	{ "firefox","Toolkit", "Picture-in-Picture",0,            1,           0,         0,        -1 },
	{ NULL,       NULL,  "WhatsApp for Linux"  ,0,            1,           0,         0,        -1 },

	//xdownloadmanager floating windows in the browser
	{ "java-lang-Thread","java-lang-Thread"," ",0,            1,           0,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ "###",	gaplessgrid },			/* grid layout */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "dwm.color0",		STRING,	&normbordercolor },
		{ "dwm.color8",		STRING,	&selbordercolor },
		{ "dwm.color0",		STRING,	&normbgcolor },
		{ "dwm.color4",		STRING,	&normfgcolor },
		{ "dwm.color0",		STRING,	&selfgcolor },
		{ "dwm.color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("") }, */
	// { MODKEY,			XK_grave,	spawn,	SHCMD("dmenuunicode") },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	// { MODKEY,           XK_u,      focusurgent,    {0} },
	// hide window
	{ MODKEY,			XK_grave,		tag,            {.ui = 1 << 12}  },
	//restore window
	{ MODKEY|ShiftMask,			XK_grave,		toggleview,            {.ui =  1 << 12}  },

	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_c,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY,		  XK_m,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	// { MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} }, [> centeredmaster <]
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */

	{ MODKEY,		XK_g,		setlayout,	{.v = &layouts[9]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_i,		incnmaster,     {.i = +1 } },
	{ MODKEY,		XK_d,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_backslash,		view,		{0} },
  { MODKEY,			XK_a,		togglegaps,	{0} },
  { MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,			XK_s,		togglesticky,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
  { MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	// { MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	// { MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	// { MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	// { MODKEY|ShiftMask,		XK_semicolon,	shifttag,	{ .i = 1 } },
	{ MODKEY|ShiftMask,			XK_apostrophe,	togglescratch,	{.ui = 1} },
	{ MODKEY|ShiftMask,			XK_n,	togglescratch,	{.ui = 2} },
	/* { MODKEY|ShiftMask,		XK_apostrophe,	spawn,		SHCMD("") }, */
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 0} },

	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,			XK_b,		togglebar,	{0} },
	/* { MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("") }, */

	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

	// jump and move between/to monitors
	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },
	//same with down and up arrow to it will be more convenient with multi monitor where both monitors are up and down
	{ MODKEY,			XK_Up,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Up,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Down,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Down,	tagmon,		{.i = +1 } },
	// same but with l,h
	{ MODKEY|AltMask,			XK_h,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask|AltMask,		XK_h,	tagmon,		{.i = -1 } },
	{ MODKEY|AltMask,			XK_l,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask|AltMask,		XK_l,	tagmon,		{.i = +1 } },
	// same but with j,k
	{ MODKEY|AltMask,			XK_k,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask|AltMask,		XK_k,	tagmon,		{.i = -1 } },
	{ MODKEY|AltMask,			XK_j,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask|AltMask,		XK_j,	tagmon,		{.i = +1 } },
	// { MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	// { MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	// { MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	// { MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },


	///// move and resize floating windows
	//move
	{ MODKEY|ControlMask,					XK_j,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY|ControlMask,					XK_k,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY|ControlMask,					XK_l,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY|ControlMask,					XK_h,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
	//move with arrow keys
	{ MODKEY|ControlMask,					XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY|ControlMask,					XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY|ControlMask,					XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY|ControlMask,					XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
	//resize
	{ MODKEY|ControlMask|ShiftMask,			XK_j,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ControlMask|ShiftMask,			XK_k,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ControlMask|ShiftMask,			XK_l,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ControlMask|ShiftMask,			XK_h,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},
	// { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	// { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	// { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	// { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/repos/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};
