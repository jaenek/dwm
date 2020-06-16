/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 2;        /* border pixel of windows */
static const unsigned int snap        = 32;       /* snap pixel */
static const int swallowfloating    = 0;          /* 1 means swallow floating windows by default */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const char buttonbar[]         = "✖";
static const char *fonts[]            = { "monospace:size=10" };
#include "/home/jaenek/.cache/wal/colors-wal-dwm.h"

/* tagging */
static const char *tags[] = { "I", "II", "III"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance title        tags mask isfloating iscentered isterminal noswallow monitor */
	{ "KeePassXC", NULL,    NULL,        0,        1,         0,         0,         0,        -1 },
	{ NULL,        NULL,    "float",     0,        1,         0,         0,         0,        -1 },
	{ NULL,        NULL,    "vimwiki",   0,        1,         1,         0,         0,        -1 },
	{ NULL,        NULL,    "st",        0,        0,         0,         1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for shell commands */
#define SH(cmd) { "sh", "-c", cmd, NULL }

/* helper for media control */
#define MPC(cmd) { .v = (const char*[]){ "mpc", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = SH("dmenu_run -i");
static const char *darktheme[]      = SH("the");
static const char *lighttheme[]     = SH("the -l");
static const char *mount[]          = SH("mnt");
static const char *umount[]         = SH("umnt");
static const char *unicodemenu[]    = SH("uni");
static const char *plumber[]        = SH("cabl");
static const char *shutdownmenu[]   = SH("sdn");
static const char *twitch[]         = SH("twitch");
static const char *torrent[]        = SH("tpb");
static const char *terminal[]       = SH("$TERMINAL");
static const char *samedir[]        = SH("samedir");
static const char *corner[]         = SH("cnr");
static const char *showclip[]       = SH("showclip");
static const char *browser[]        = SH("$BROWSER");
static const char *filebrowser[]    = SH("$TERMINAL -e $FILE");
static const char *vimwiki[]        = SH("$TERMINAL -T vimwiki -e nvim -c VimwikiIndex");
static const char *htop[]           = SH("$TERMINAL -e htop");
static const char *pulsemixer[]     = SH("$TERMINAL -T pulsemixer -e pulsemixer");
static const char *keepassxc[]      = SH("keepassxc");
static const char *projectm[]       = SH("projectM-pulseaudio");
static const char *ncmpcpp[]        = SH("$TERMINAL -e ncmpcpp");
static const char *newsboat[]       = SH("$TERMINAL -e newsboat");
static const char *youtubesearch[]  = SH("yts");
static const char *screenshot[]     = SH("scr");
static const char *upgrade[]        = SH("$TERMINAL -T upgrade -e upg");
static const char *volup[]          = SH("vol 5%+ && sts");
static const char *voldown[]        = SH("vol 5%- && sts");
static const char *mute[]           = SH("vol toggle && sts");
static const char *pauseall[]       = SH("mpc pause && pauseall && sts");

#include "movestack.c"

static Key keys[] = {
	/* dwm/window bindings */
	/* modifier         key        function        argument */
	{ MODKEY,           XK_F2,     quit,           {0} },
	{ MODKEY,           XK_F5,     spawn,          {.v = darktheme } },
	{ MODKEY|ShiftMask, XK_F5,     spawn,          {.v = lighttheme } },
	{ MODKEY,           XK_Down,   focusstack,     {.i = +1} },
	{ MODKEY,           XK_Up,     focusstack,     {.i = -1} },
	{ MODKEY|ShiftMask, XK_Down,   movestack,      {.i = +1} },
	{ MODKEY|ShiftMask, XK_Up,     movestack,      {.i = -1} },
	{ MODKEY,           XK_Left,   zoom,           {.i = +1} },
	{ MODKEY,           XK_Right,  zoom,           {.i = -1} },
	{ MODKEY|ShiftMask, XK_Left,   setmfact,       {.f = -0.025} },
	{ MODKEY|ShiftMask, XK_Right,  setmfact,       {.f = +0.025} },
	{ MODKEY|ShiftMask, XK_x,      spawn,          {.v = shutdownmenu } },
	{ MODKEY,           XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask, XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask, XK_y,      incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask, XK_o,      incnmaster,     {.i = -1} },
	{ MODKEY,           XK_j,      focusstack,     {.i = +1} },
	{ MODKEY,           XK_k,      focusstack,     {.i = -1} },
	{ MODKEY|ShiftMask, XK_j,      movestack,      {.i = +1} },
	{ MODKEY|ShiftMask, XK_k,      movestack,      {.i = -1} },
	{ MODKEY,           XK_h,      zoom,           {.i = +1} },
	{ MODKEY,           XK_l,      zoom,           {.i = -1} },
	{ MODKEY|ShiftMask, XK_h,      setmfact,       {.f = -0.025} },
	{ MODKEY|ShiftMask, XK_l,      setmfact,       {.f = +0.025} },
	{ MODKEY,           XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask, XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask, XK_b,      togglebar,      {0} },
	{ MODKEY,           XK_Tab,    cyclelayout,    {.i = +1} },
	{ MODKEY|ShiftMask, XK_Tab,	   setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask, XK_space,  setlayout,      {0} },
	/* program bindings */
	/* modifier         key        function        argument */
	{ MODKEY,           XK_F9,     spawn,          {.v = mount } },
	{ MODKEY,           XK_F10,    spawn,          {.v = umount } },
	{ MODKEY,           XK_Return, spawn,          {.v = terminal } },
	{ MODKEY|ShiftMask, XK_Return, spawn,          {.v = samedir } },
	{ MODKEY,           XK_Insert, spawn,          {.v = showclip } },
	{ MODKEY,           XK_grave,  spawn,          {.v = unicodemenu } },
	{ MODKEY,           XK_w,      spawn,          {.v = browser } },
	{ MODKEY,           XK_f,      spawn,          {.v = filebrowser } },
	{ MODKEY,           XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,           XK_t,      spawn,          {.v = twitch } },
	{ MODKEY|ShiftMask, XK_t,      spawn,          {.v = torrent } },
	{ MODKEY,           XK_y,      spawn,          {.v = vimwiki } },
	{ MODKEY,           XK_i,      spawn,          {.v = htop } },
	{ MODKEY,           XK_a,      spawn,          {.v = pulsemixer } },
	{ MODKEY,           XK_c,      spawn,          {.v = plumber } },
	{ MODKEY|ShiftMask, XK_c,      spawn,          {.v = corner } },
	{ MODKEY,           XK_v,      spawn,          {.v = keepassxc } },
	{ MODKEY|ShiftMask, XK_v,      spawn,          {.v = projectm } },
	{ MODKEY,           XK_m,      spawn,          {.v = ncmpcpp } },
	{ MODKEY,           XK_n,      spawn,          {.v = newsboat } },
	{ MODKEY|ShiftMask, XK_n,      spawn,          {.v = youtubesearch } },
	/* media bindings */
	/* modifier         key        function        argument */
	{ 0,                XK_Print,  spawn,          {.v = screenshot } },
	{ MODKEY,           XK_minus,  spawn,          {.v = voldown } },
	{ MODKEY,           XK_equal,  spawn,          {.v = volup } },
	{ MODKEY|ShiftMask, XK_m,      spawn,          {.v = mute } },
	{ MODKEY,           XK_comma,  spawn,          MPC("prev") },
	{ MODKEY|ShiftMask, XK_comma,  spawn,          MPC("replay") },
	{ MODKEY,           XK_period, spawn,          MPC("next") },
	{ MODKEY|ShiftMask, XK_period, spawn,          MPC("next") },
	{ MODKEY,           XK_p,      spawn,          MPC("toggle") },
	{ MODKEY|ShiftMask, XK_p,      spawn,          {.v = pauseall } },
	/* tag bindings */
	TAGKEYS(            XK_1,                      0)
	TAGKEYS(            XK_2,                      1)
	TAGKEYS(            XK_3,                      2)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                 event mask button          function        argument */
	{ ClkButton,     0,      Button1,   spawn,          {.v = shutdownmenu } },
	{ ClkLtSymbol,   0,      Button1,   cyclelayout,    {.i = +1} },
	{ ClkLtSymbol,   0,      Button3,   cyclelayout,    {.i = -1} },
	{ ClkWinTitle,   0,      Button2,   zoom,           {0} },
	{ ClkStatusText, 0,      Button2,   spawn,          {.v = upgrade } },
	{ ClkClientWin,  MODKEY, Button1,   movemouse,      {0} },
	{ ClkClientWin,  MODKEY, Button2,   spawn,          {.v = plumber } },
	{ ClkClientWin,  MODKEY, Button3,   resizemouse,    {0} },
	{ ClkTagBar,     0,      Button1,   view,           {0} },
	{ ClkTagBar,     0,      Button3,   toggleview,     {0} },
	{ ClkTagBar,     MODKEY, Button1,   tag,            {0} },
	{ ClkTagBar,     MODKEY, Button3,   toggletag,      {0} },
};
