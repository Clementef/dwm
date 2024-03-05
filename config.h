/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 5 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode Nerd Font:size=11.3" };
static const char col_bg[]          = "#282a36"; // bg
static const char col_hl[]          = "#44475a"; // hl
static const char col_fg[]          = "#f8f8f2"; // white
static const char col_comment[]     = "#6272a4"; // red
static const char col_cyan[]        = "#bd93f9"; // purple
static const char *colors[][4]      = {
	/*               fg         bg          border      floating */
	[SchemeNorm] = { col_fg,    col_bg,     col_hl,     col_hl      },
	[SchemeSel]  = { col_fg,    col_hl,     col_cyan,   col_comment },
};

/* tagging */
static const char *tags[] = { "a", "s", "d", "f", "g", "x", "c"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance    title   tags mask   isfloating  monitor */
	{ "Nm-connection-editor",       NULL,       NULL,   0,          1,          -1 },
	{ "Bitwarden",                  NULL,       NULL,   0,          1,          -1 },
	{ "Signal",                     NULL,       NULL,   0,          1,          -1 },
	{ "firefox",                    NULL,  "Library",   0,          1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[M]",      monocle }
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

/*  keybinds */
#include "movestack.c"
const unsigned int gappxinc = 5;
static const Key keys[] = {
	/* modifier                     key        function        argument */
    // select all tags
	{ MODKEY,                       XK_9,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_9,      tag,            {.ui = ~0 } },

    // toggle layout
	{ MODKEY,                       XK_Tab,     setlayout,      {0} },

    // window modes
    { MODKEY,                       XK_t,       togglefloating, {0} },

    // bar
    { MODKEY,                       XK_b,       togglebar,     {0} },
    
    // monitor
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // gaps
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY,                       XK_0,      setgaps,        {.i = GAP_RESET } },
	// { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = -999} },

    // tags
    { MODKEY,                       XK_w,       killclient,     {0} },
    TAGKEYS(                        XK_a,                       0)
    TAGKEYS(                        XK_s,                       1)
    TAGKEYS(                        XK_d,                       2)
    TAGKEYS(                        XK_f,                       3)
    TAGKEYS(                        XK_g,                       4)
    TAGKEYS(                        XK_x,                       5)
    TAGKEYS(                        XK_c,                       6)

    // stack
    { MODKEY,                       XK_j,       focusstack,     {.i = +1} },
    { MODKEY,                       XK_k,       focusstack,     {.i = -1} },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_equal,   setmfact,       {.f = 1.0 + 0.5 } },
    { MODKEY|ShiftMask,             XK_0,       setmfact,       {.f = 1.0 + mfact } },
    {MODKEY|ShiftMask,		        XK_j,       movestack,	    {.i = +1 } },
    {MODKEY|ShiftMask,		        XK_k,       movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,  zoom,           {0} },

    // quit dwm
	{ MODKEY|ShiftMask,             XK_q,       quit,           {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	// { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

