/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "dwmfont:size=11", "Ubuntu Nerd Font:size=11", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "🖥", "🌎", "💲", "👽", "🧠", "🦄", "🌀", "📦", "🎅" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "KeePass2", NULL,	  NULL,	      1 <<8,	    1,           -1 },
	{ "Spotify",  NULL,	  NULL,	      1 <<8,	    0,           -1 },
	{ "firefox",  NULL,	  NULL,	      1 <<1,	    0,           -1 },
{ "jetbrains-idea",   NULL,	  NULL,	      0,	    1,           -1 },
{ "jetbrains-toolbox",NULL,	  NULL,       0,	    1,           -1 },
{ "Brave-browser",    NULL,	  NULL,	      1 <<1,	    0,           -1 },
	{ "Steam",    NULL,  "Friends List",  0,	    1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-c", "-l", "15","-fn", dmenufont, "-nb", "#2e2e2e", "-nf", "#FFFFFF", "-sb", "#49FF49", "-sf", "#1e1e1e", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,  		        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,			XK_q,	   killclient,	   {0} },
	{ MODKEY,			XK_w,	   spawn,	   SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,		XK_w,	   spawn,	   SHCMD("$TERMINAL -e sudo nmtui") },
	{ MODKEY,			XK_r,	   spawn,	   SHCMD("$TERMINAL -e ranger") },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_a,	   spawn,	   SHCMD("$TERMINAL -e pulsemixer ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,			XK_s,	   spawn,	   SHCMD("dmenu_websearch") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      setgaps,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_z,      setgaps,        {.i = +1 } },
	{ MODKEY,			XK_x,	   spawn,	   SHCMD("betterlockscreen -s") },
	{ MODKEY|ShiftMask,		XK_x,	   spawn,	   SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_m,      spawn,          SHCMD("amixer sset Master toggle ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_space,  zoom, 	   {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ ShiftMask,			XK_Print,  spawn,	   SHCMD("maimpick") },
	{ MODKEY,			XK_Insert, spawn,          SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
	{ MODKEY,			XK_F1,	   spawn,	   SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
	{ MODKEY,			XK_F2,	   quit,	   {0} },
	{ MODKEY,			XK_F3,	   spawn,	   SHCMD("displayselect") },
	{ MODKEY,			XK_F4,	   spawn,	   SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo -A zzz") },
	{ MODKEY,			XK_F5,	   spawn,	   SHCMD("redshift -P -O 6500") },
	{ MODKEY,			XK_F6,	   spawn,	   SHCMD("redshift -P -O 4500") },
	{ MODKEY,			XK_F9,	   spawn,	   SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,	   spawn,	   SHCMD("dmenuumount") },
	{ MODKEY,			XK_F11,	   spawn,	   SHCMD("xbacklight -dec 2") },
	{ MODKEY,			XK_F12,	   spawn,	   SHCMD("xbacklight -inc 2") },
	{ MODKEY|ShiftMask,		XK_Escape, spawn,	   SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Close Xorg?\")\" = Yes ] && killall Xorg") },
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,	   SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot computer?\")\" = Yes ] && sudo -A reboot") },
	{ 0, XF86XK_AudioMute,          spawn,                     SHCMD("pactl set-sink-mute 0 toggle ; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		           SHCMD("pactl set-sink-volume 0 +5% ; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		           SHCMD("pactl set-sink-volume 0 -5% ; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioPrev,		spawn,	                   SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,		spawn,		           SHCMD("playerctl next") },
	{ 0, XF86XK_AudioPause,		spawn,		           SHCMD("playerctl pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		           SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioStop,		spawn,		           SHCMD("playerctl stop") },
	{ 0, XF86XK_Launch1,		spawn,		           SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		           SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		           SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		           SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		           SHCMD("xbacklight -dec 2") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,	                   SHCMD("xbacklight -inc 2") },
	{ 0, XF86XK_PowerOff,		spawn,                     SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
	{ 0, XF86XK_Calculator,		spawn,		           SHCMD("$TERMINAL -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		           SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		           SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		           SHCMD("$TERMINAL") },
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

