/*
 * Copyright (c) 2004 by FlashCode <flashcode@flashtux.org>
 * See README for License detail, AUTHORS for developers list.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* weeconfig.c: WeeChat configuration */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>

#include "weechat.h"
#include "weeconfig.h"
#include "command.h"
#include "../irc/irc.h"
#include "../gui/gui.h"


/* config sections */

t_config_section config_sections[CONFIG_NUMBER_SECTIONS] =
{ { CONFIG_SECTION_LOOK, "look" },
  { CONFIG_SECTION_COLORS, "colors" },
  { CONFIG_SECTION_HISTORY, "history" },
  { CONFIG_SECTION_LOG, "log" },
  { CONFIG_SECTION_DCC, "dcc" },
  { CONFIG_SECTION_PROXY, "proxy" },
  { CONFIG_SECTION_ALIAS, "alias" },
  { CONFIG_SECTION_SERVER, "server" }
};

/* config, look & feel section */

int cfg_look_set_title;
int cfg_look_startup_logo;
int cfg_look_startup_version;
char *cfg_look_weechat_slogan;
int cfg_look_color_nicks;
int cfg_look_color_actions;
int cfg_look_remove_colors_from_msgs;
int cfg_look_nicklist;
int cfg_look_nicklist_position;
char *cfg_look_nicklist_position_values[] =
{ "left", "right", "top", "bottom", NULL };
int cfg_look_nicklist_min_size;
int cfg_look_nicklist_max_size;
int cfg_look_nickmode;
int cfg_look_nickmode_empty;
char *cfg_look_no_nickname;
char *cfg_look_completor;
int cfg_look_infobar;
char *cfg_look_infobar_timestamp;
int cfg_look_infobar_delay_highlight;

t_config_option weechat_options_look[] =
{ { "look_set_title", N_("set title for window (terminal for Curses GUI) with name & version"),
    N_("set title for window (terminal for Curses GUI) with name & version"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_set_title, NULL, config_change_title },
  { "look_startup_logo", N_("display WeeChat logo at startup"),
    N_("display WeeChat logo at startup"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_startup_logo, NULL, config_change_noop },
  { "look_startup_version", N_("display WeeChat version at startup"),
    N_("display WeeChat version at startup"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_startup_version, NULL, config_change_noop },
  { "look_weechat_slogan", N_("WeeChat slogan"),
    N_("WeeChat slogan (if empty, slogan is not used)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "the geekest IRC client!", NULL, NULL, &cfg_look_weechat_slogan, config_change_noop },
  { "look_color_nicks", N_("display nick names with different colors"),
    N_("display nick names with different colors"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_color_nicks, NULL, config_change_noop },
  { "look_color_actions", N_("display actions with different colors"),
    N_("display actions with different colors"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_color_actions, NULL, config_change_noop },
  { "look_remove_colors_from_msgs", N_("remove colors from incoming messages"),
    N_("remove colors from incoming messages"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_remove_colors_from_msgs, NULL, config_change_noop },
  { "look_nicklist", N_("display nicklist window"),
    N_("display nicklist window (for channel windows)"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_nicklist, NULL, config_change_buffers },
  { "look_nicklist_position", N_("nicklist position"),
    N_("nicklist position (top, left, right (default), bottom)"),
    OPTION_TYPE_INT_WITH_STRING, 0, 0, 0,
    "right", cfg_look_nicklist_position_values, &cfg_look_nicklist_position, NULL, config_change_buffers },
  { "look_nicklist_min_size", N_("min size for nicklist"),
    N_("min size for nicklist (width or height, depending on look_nicklist_position "
    "(0 = no min size))"),
    OPTION_TYPE_INT, 0, 100, 0,
    NULL, NULL, &cfg_look_nicklist_min_size, NULL, config_change_buffers },
  { "look_nicklist_max_size", N_("max size for nicklist"),
    N_("max size for nicklist (width or height, depending on look_nicklist_position "
    "(0 = no max size; if min == max and > 0, then size is fixed))"),
    OPTION_TYPE_INT, 0, 100, 0,
    NULL, NULL, &cfg_look_nicklist_max_size, NULL, config_change_buffers },
  { "look_no_nickname", N_("text to display instead of nick when not connected"),
    N_("text to display instead of nick when not connected"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "-cmd-", NULL, NULL, &cfg_look_no_nickname, config_change_buffer_content },
  { "look_nickmode", N_("display nick mode ((half)op/voice) before each nick"),
    N_("display nick mode ((half)op/voice) before each nick"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_nickmode, NULL, config_change_buffers },
  { "look_nickmode_empty", N_("display space if nick mode is not (half)op/voice"),
    N_("display space if nick mode is not (half)op/voice"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_FALSE,
    NULL, NULL, &cfg_look_nickmode_empty, NULL, config_change_buffers },
  { "look_nick_completor", N_("the string inserted after nick completion"),
    N_("the string inserted after nick completion"),
    OPTION_TYPE_STRING, 0, 0, 0,
    ":", NULL, NULL, &cfg_look_completor, config_change_noop },
  { "look_infobar", N_("enable info bar"),
    N_("enable info bar"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_look_infobar, NULL, config_change_buffers },
  { "look_infobar_timestamp", N_("timestamp for time in infobar"),
    N_("timestamp for time in infobar"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "%B, %A %d %G - %H:%M", NULL, NULL, &cfg_look_infobar_timestamp, config_change_buffer_content },
  { "look_infobar_delay_highlight", N_("delay (in seconds) for highlight messages in infobar"),
    N_("delay (in seconds) for highlight messages in infobar "
    "(0 = disable highlight notifications in infobar)"),
    OPTION_TYPE_INT, 0, INT_MAX, 7,
    NULL, NULL, &cfg_look_infobar_delay_highlight, NULL, config_change_noop },
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* config, colors section */

int cfg_col_title;
int cfg_col_title_bg;
int cfg_col_chat;
int cfg_col_chat_time;
int cfg_col_chat_time_sep;
int cfg_col_chat_prefix1;
int cfg_col_chat_prefix2;
int cfg_col_chat_nick;
int cfg_col_chat_host;
int cfg_col_chat_channel;
int cfg_col_chat_dark;
int cfg_col_chat_highlight;
int cfg_col_chat_bg;
int cfg_col_status;
int cfg_col_status_delimiters;
int cfg_col_status_data_msg;
int cfg_col_status_data_highlight;
int cfg_col_status_data_other;
int cfg_col_status_more;
int cfg_col_status_bg;
int cfg_col_infobar;
int cfg_col_infobar_highlight;
int cfg_col_infobar_bg;
int cfg_col_input;
int cfg_col_input_channel;
int cfg_col_input_nick;
int cfg_col_input_bg;
int cfg_col_nick;
int cfg_col_nick_op;
int cfg_col_nick_halfop;
int cfg_col_nick_voice;
int cfg_col_nick_sep;
int cfg_col_nick_self;
int cfg_col_nick_private;
int cfg_col_nick_bg;
int cfg_col_dcc_waiting;
int cfg_col_dcc_connecting;
int cfg_col_dcc_active;
int cfg_col_dcc_done;
int cfg_col_dcc_failed;
int cfg_col_dcc_aborted;

t_config_option weechat_options_colors[] =
{ /* title window */
  { "col_title", N_("color for title bar"),
    N_("color for title bar"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_title, NULL, &config_change_color },
  { "col_title_bg", N_("background for title bar"),
    N_("background for title bar"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "blue", NULL, &cfg_col_title_bg, NULL, &config_change_color },
  
  /* chat window */
  { "col_chat", N_("color for chat text"),
    N_("color for chat text"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_chat, NULL, &config_change_color },
  { "col_chat_time", N_("color for time"),
    N_("color for time in chat window"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_chat_time, NULL, &config_change_color },
  { "col_chat_time_sep", N_("color for time separator"),
    N_("color for time separator (chat window)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "brown", NULL, &cfg_col_chat_time_sep, NULL, &config_change_color },
  { "col_chat_prefix1", N_("color for 1st and 3rd char of prefix"),
    N_("color for 1st and 3rd char of prefix"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightcyan", NULL, &cfg_col_chat_prefix1, NULL, &config_change_color },
  { "col_chat_prefix2", N_("color for middle char of prefix"),
    N_("color for middle char of prefix"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_chat_prefix2, NULL, &config_change_color },
  { "col_chat_nick", N_("color for nicks in actions"),
    N_("color for nicks in actions (chat window)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightcyan", NULL, &cfg_col_chat_nick, NULL, &config_change_color },
  { "col_chat_host", N_("color for hostnames"),
    N_("color for hostnames (chat window)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "cyan", NULL, &cfg_col_chat_host, NULL, &config_change_color },
  { "col_chat_channel", N_("color for channel names in actions"),
    N_("color for channel names in actions (chat window)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_chat_channel, NULL, &config_change_color },
  { "col_chat_dark", N_("color for dark separators"),
    N_("color for dark separators (chat window)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "green", NULL, &cfg_col_chat_dark, NULL, &config_change_color },
  { "col_chat_highlight", N_("color for highlighted nick"),
    N_("color for highlighted nick (chat window)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "yellow", NULL, &cfg_col_chat_highlight, NULL, &config_change_color },
  { "col_chat_bg", N_("background for chat"),
    N_("background for chat window"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "default", NULL, &cfg_col_chat_bg, NULL, &config_change_color },
  
  /* status window */
  { "col_status", N_("color for status bar"),
    N_("color for status bar"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_status, NULL, &config_change_color },
  { "col_status_delimiters", N_("color for status bar delimiters"),
    N_("color for status bar delimiters"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "cyan", NULL, &cfg_col_status_delimiters, NULL, &config_change_color },
  { "col_status_data_msg", N_("color for window with new messages"),
    N_("color for window with new messages (status bar)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "yellow", NULL, &cfg_col_status_data_msg, NULL, &config_change_color },
  { "col_status_highlight", N_("color for window with highlight"),
    N_("color for window with highlight (status bar)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightmagenta", NULL, &cfg_col_status_data_highlight, NULL, &config_change_color },
  { "col_status_data_other", N_("color for window with new data (not messages)"),
    N_("color for window with new data (not messages) (status bar)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_status_data_other, NULL, &config_change_color },
  { "col_status_more", N_("color for \"*MORE*\" text"),
    N_("color for window with new data (status bar)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_status_more, NULL, &config_change_color },
  { "col_status_bg", N_("background for status window"),
    N_("background for status window"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "blue", NULL, &cfg_col_status_bg, NULL, &config_change_color },

  /* infobar window */
  { "col_infobar", N_("color for info bar text"),
    N_("color for info bar text"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "black", NULL, &cfg_col_infobar, NULL, &config_change_color },
  { "col_infobar_highlight", N_("color for info bar highlight notification"),
    N_("color for info bar highlight notification"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_infobar_highlight, NULL, &config_change_color },
  { "col_infobar_bg", N_("background for info bar window"),
    N_("background for info bar window"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "cyan", NULL, &cfg_col_infobar_bg, NULL, &config_change_color },
  
  /* input window */
  { "col_input", N_("color for input text"),
    N_("color for input text"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_input, NULL, &config_change_color },
  { "col_input_channel", N_("color for input text (channel name)"),
    N_("color for input text (channel name)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_input_channel, NULL, &config_change_color },
  { "col_input_nick", N_("color for input text (nick name)"),
    N_("color for input text (nick name)"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightgreen", NULL, &cfg_col_input_nick, NULL, &config_change_color },
  { "col_input_bg", N_("background for input window"),
    N_("background for input window"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "default", NULL, &cfg_col_input_bg, NULL, &config_change_color },
  
  /* nick window */
  { "col_nick", N_("color for nicknames"),
    N_("color for nicknames"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_nick, NULL, &config_change_color },
  { "col_nick_op", N_("color for operator symbol"),
    N_("color for operator symbol"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightgreen", NULL, &cfg_col_nick_op, NULL, &config_change_color },
  { "col_nick_halfop", N_("color for half-operator symbol"),
    N_("color for half-operator symbol"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightmagenta", NULL, &cfg_col_nick_halfop, NULL, &config_change_color },
  { "col_nick_voice", N_("color for voice symbol"),
    N_("color for voice symbol"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "yellow", NULL, &cfg_col_nick_voice, NULL, &config_change_color },
  { "col_nick_sep", N_("color for nick separator"),
    N_("color for nick separator"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "blue", NULL, &cfg_col_nick_sep, NULL, &config_change_color },
  { "col_nick_self", N_("color for local nick"),
    N_("color for local nick"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_nick_self, NULL, &config_change_color },
  { "col_nick_private", N_("color for other nick in private window"),
    N_("color for other nick in private window"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "gray", NULL, &cfg_col_nick_private, NULL, &config_change_color },
  { "col_nick_bg", N_("background for nicknames"),
    N_("background for nicknames"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "default", NULL, &cfg_col_nick_bg, NULL, &config_change_color },
  
  /* DCC */
  { "col_dcc_waiting", N_("color for \"waiting\" dcc status"),
    N_("color for \"waiting\" dcc status"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "white", NULL, &cfg_col_dcc_waiting, NULL, &config_change_color },
  { "col_dcc_connecting", N_("color for \"connecting\" dcc status"),
    N_("color for \"connecting\" dcc status"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "yellow", NULL, &cfg_col_dcc_connecting, NULL, &config_change_color },
  { "col_dcc_active", N_("color for \"active\" dcc status"),
    N_("color for \"active\" dcc status"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightblue", NULL, &cfg_col_dcc_active, NULL, &config_change_color },
  { "col_dcc_done", N_("color for \"done\" dcc status"),
    N_("color for \"done\" dcc status"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightgreen", NULL, &cfg_col_dcc_done, NULL, &config_change_color },
  { "col_dcc_failed", N_("color for \"failed\" dcc status"),
    N_("color for \"failed\" dcc status"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightred", NULL, &cfg_col_dcc_failed, NULL, &config_change_color },
  { "col_dcc_aborted", N_("color for \"aborted\" dcc status"),
    N_("color for \"aborted\" dcc status"),
    OPTION_TYPE_COLOR, 0, 0, 0,
    "lightred", NULL, &cfg_col_dcc_aborted, NULL, &config_change_color },
  
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* config, history section */

int cfg_history_max_lines;
int cfg_history_max_commands;

t_config_option weechat_options_history[] =
{ { "history_max_lines", N_("max lines in history (per window)"),
    N_("maximum number of lines in history "
    "for one server/channel/private window (0 = unlimited)"),
    OPTION_TYPE_INT, 0, INT_MAX, 4096,
    NULL, NULL, &cfg_history_max_lines, NULL, NULL },
  { "history_max_commands", N_("max user commands in history"),
    N_("maximum number of user commands in history (0 = unlimited)"),
    OPTION_TYPE_INT, 0, INT_MAX, 100,
    NULL, NULL, &cfg_history_max_commands, NULL, NULL },
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* config, log section */

int cfg_log_auto_channels;
int cfg_log_auto_private;
char *cfg_log_path;
char *cfg_log_name;
char *cfg_log_timestamp;
char *cfg_log_start_string;
char *cfg_log_end_string;

t_config_option weechat_options_log[] =
{ { "log_auto_channels", N_("automatically log channel chats"),
    N_("automatically log channel chats"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_log_auto_channels, NULL, NULL },
  { "log_auto_private", N_("automatically log private chats"),
    N_("automatically log private chats"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_log_auto_private, NULL, NULL },
  { "log_path", N_("path for log files"),
    N_("path for WeeChat log files"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "~/.weechat/logs/", NULL, NULL, &cfg_log_path, NULL },
  { "log_name", N_("name for log files"),
    N_("name for log files (%S == irc server name, "
    "%N == channel name (or nickname if private chat)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "%S,%N.weechatlog", NULL, NULL, &cfg_log_name, NULL },
  { "log_timestamp", N_("timestamp for log"),
    N_("timestamp for log (see man strftime for date/time specifiers)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "~", NULL, NULL, &cfg_log_timestamp, NULL },
  { "log_start_string", N_("start string for log files"),
    N_("text written when starting new log file "
    "(see man strftime for date/time specifiers)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "--- Log started %a %b %d %Y %H:%M:%s", NULL, NULL, &cfg_log_start_string, NULL },
  { "log_end_string", N_("end string for log files"),
    N_("text written when ending log file "
    "(see man strftime for date/time specifiers)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "--- Log ended %a %b %d %Y %H:%M:%s", NULL, NULL, &cfg_log_end_string, NULL },
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* config, dcc section */

int cfg_dcc_auto_accept_files;
int cfg_dcc_auto_accept_chats;
int cfg_dcc_timeout;
int cfg_dcc_blocksize;
char *cfg_dcc_download_path;
char *cfg_dcc_upload_path;
int cfg_dcc_auto_rename;
int cfg_dcc_auto_resume;

t_config_option weechat_options_dcc[] =
{ { "dcc_auto_accept_files", N_("automatically accept dcc files"),
    N_("automatically accept incoming dcc files"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_FALSE,
    NULL, NULL, &cfg_dcc_auto_accept_files, NULL, config_change_noop },
  { "dcc_auto_accept_chats", N_("automatically accept dcc chats"),
    N_("automatically accept dcc chats (use carefully!)"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_dcc_auto_accept_chats, NULL, config_change_noop },
  { "dcc_timeout", N_("timeout for dcc request"),
    N_("timeout for dcc request (in seconds)"),
    OPTION_TYPE_INT, 1, INT_MAX, 300,
    NULL, NULL, &cfg_dcc_timeout, NULL, config_change_noop },
  { "dcc_blocksize", N_("block size for dcc packets"),
    N_("block size for dcc packets in bytes (default: 1024)"),
    OPTION_TYPE_INT, 1024, 102400, 1024,
    NULL, NULL, &cfg_dcc_blocksize, NULL, config_change_noop },
  { "dcc_download_path", N_("path for incoming files with dcc"),
    N_("path for writing incoming files with dcc (default: user home)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "~", NULL, NULL, &cfg_dcc_download_path, config_change_noop },
  { "dcc_upload_path", N_("default path for sending files with dcc"),
    N_("path for reading files when sending thru dcc (when no path is specified)"),
    OPTION_TYPE_STRING, 0, 0, 0, "~",
    NULL, NULL, &cfg_dcc_upload_path, config_change_noop },
  { "dcc_auto_rename", N_("automatically rename dcc files if already exists"),
    N_("rename incoming files if already exists (add '.1', '.2', ...)"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_dcc_auto_rename, NULL, config_change_noop },
  { "dcc_auto_resume", N_("automatically resume aborted transfers"),
    N_("automatically resume dcc transfer if connection with remote host is loosed"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &cfg_dcc_auto_resume, NULL, config_change_noop },
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* config, proxy section */

int cfg_proxy_use;
char *cfg_proxy_address;
int cfg_proxy_port;
char *cfg_proxy_password;

t_config_option weechat_options_proxy[] =
{ { "proxy_use", N_("use proxy"),
    N_("use a proxy server to connect to irc server"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_FALSE,
    NULL, NULL, &cfg_proxy_use, NULL, NULL },
  { "proxy_address", N_("proxy address"),
    N_("proxy server address (IP or hostname)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &cfg_proxy_address, NULL },
  { "proxy_port", N_("port for proxy"),
    N_("port for connecting to proxy server"),
    OPTION_TYPE_INT, 0, 65535, 1080,
    NULL, NULL, &cfg_proxy_port, NULL, NULL },
  { "proxy_password", N_("proxy password"),
    N_("password for proxy server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &cfg_proxy_password, NULL },
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* config, server section */

static t_irc_server cfg_server;

t_config_option weechat_options_server[] =
{ { "server_name", N_("server name"),
    N_("name associated to IRC server (for display only)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.name), NULL },
  { "server_autoconnect", N_("automatically connect to server"),
    N_("automatically connect to server when WeeChat is starting"),
    OPTION_TYPE_BOOLEAN, BOOL_FALSE, BOOL_TRUE, BOOL_TRUE,
    NULL, NULL, &(cfg_server.autoconnect), NULL, NULL },
  { "server_address", N_("server address or hostname"),
    N_("IP address or hostname of IRC server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.address), NULL },
  { "server_port", N_("port for IRC server"),
    N_("port for connecting to server"),
    OPTION_TYPE_INT, 0, 65535, 6667,
    NULL, NULL, &(cfg_server.port), NULL, NULL },
  { "server_password", N_("server password"),
    N_("password for IRC server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.password), NULL },
  { "server_nick1", N_("nickname for server"),
    N_("nickname to use on IRC server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.nick1), NULL },
  { "server_nick2", N_("alternate nickname for server"),
    N_("alternate nickname to use on IRC server (if nickname is already used)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.nick2), NULL },
  { "server_nick3", N_("2nd alternate nickname for server"),
    N_("2nd alternate nickname to use on IRC server (if alternate nickname is already used)"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.nick3), NULL },
  { "server_username", N_("user name for server"),
    N_("user name to use on IRC server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.username), NULL },
  { "server_realname", N_("real name for server"),
    N_("real name to use on IRC server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.realname), NULL },
  { "server_command", N_("first command to run when connected to server"),
    N_("first command to run when connected to server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.command), NULL },
  { "server_autojoin", N_("list of channels to join when connected to server"),
    N_("comma separated list of channels to join when connected to server"),
    OPTION_TYPE_STRING, 0, 0, 0,
    "", NULL, NULL, &(cfg_server.autojoin), NULL },
  { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL }
};

/* all weechat options */

t_config_option *weechat_options[CONFIG_NUMBER_SECTIONS] =
{ weechat_options_look, weechat_options_colors, weechat_options_history,
  weechat_options_log, weechat_options_dcc, weechat_options_proxy,
  NULL, weechat_options_server
};


/*
 * get_pos_array_values: returns position of a string in an array of values
 *                       returns -1 if not found, otherwise position
 */

int
get_pos_array_values (char **array, char *string)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        if (strcasecmp (array[i], string) == 0)
            return i;
        i++;
    }
    /* string not found in array */
    return -1;
}

/*
 * config_get_section: get section name from option pointer
 */

char *
config_get_section (t_config_option *ptr_option)
{
    int i, j;
    
    for (i = 0; i < CONFIG_NUMBER_SECTIONS; i++)
    {
        if ((i != CONFIG_SECTION_ALIAS) && (i != CONFIG_SECTION_SERVER))
        {
            for (j = 0; weechat_options[i][j].option_name; j++)
            {
                /* if option found, return pointer to section name */
                if (ptr_option == &weechat_options[i][j])
                    return config_sections[i].section_name;
            }
        }
    }
    /* option not found */
    return NULL;
}

/*
 * config_change_noop: called when an option is changed by /set command
 *                     and that no special action is needed after that
 */

void
config_change_noop ()
{
    /* do nothing */
}

/*
 * config_change_title: called when title is changed
 */

void
config_change_title ()
{
    gui_set_window_title ();
}

/*
 * config_change_buffers: called when buffers change (for example nicklist)
 */

void
config_change_buffers ()
{
    gui_switch_to_buffer (gui_current_window, gui_current_window->buffer);
    gui_redraw_buffer (gui_current_window->buffer);
}

/*
 * config_change_buffer_content: called when content of a buffer changes
 */

void
config_change_buffer_content ()
{
    gui_redraw_buffer (gui_current_window->buffer);
}

/*
 * config_change_color: called when a color is changed by /set command
 */

void
config_change_color()
{
    gui_init_colors ();
}

/*
 * config_option_set_value: set new value for an option
 *                          return:  0 if success
 *                                  -1 if error (bad value)
 */

int
config_option_set_value (t_config_option *option, char *value)
{
    int int_value;
    
    switch (option->option_type)
    {
        case OPTION_TYPE_BOOLEAN:
            if (strcasecmp (value, "on") == 0)
                *(option->ptr_int) = BOOL_TRUE;
            else if (strcasecmp (value, "off") == 0)
                *(option->ptr_int) = BOOL_FALSE;
            else
                return -1;
            break;
        case OPTION_TYPE_INT:
            int_value = atoi (value);
            if ((int_value < option->min) || (int_value > option->max))
                return -1;
            *(option->ptr_int) = int_value;
            break;
        case OPTION_TYPE_INT_WITH_STRING:
            int_value = get_pos_array_values (option->array_values, value);
            if (int_value < 0)
                return -1;
            *(option->ptr_int) = int_value;
            break;
        case OPTION_TYPE_COLOR:
            if (!gui_assign_color (option->ptr_int, value))
                return -1;
            break;
        case OPTION_TYPE_STRING:
            if (*(option->ptr_string))
                free (*(option->ptr_string));
            *(option->ptr_string) = strdup (value);
            break;
    }
    return 0;
}

/*
 * config_option_search: look for an option and return pointer to this option
 *                       if option is not found, NULL is returned
 */

t_config_option *
config_option_search (char *option_name)
{
    int i, j;
    
    for (i = 0; i < CONFIG_NUMBER_SECTIONS; i++)
    {
        if ((i != CONFIG_SECTION_ALIAS) && (i != CONFIG_SECTION_SERVER))
        {
            for (j = 0; weechat_options[i][j].option_name; j++)
            {
                /* if option found, return pointer */
                if (strcasecmp (weechat_options[i][j].option_name, option_name) == 0)
                    return &weechat_options[i][j];
            }
        }
    }
    /* option not found */
    return NULL;
}

/*
 * config_set_value: set new value for an option (found by name)
 *                   return:  0 if success
 *                           -1 if bad value for option
 *                           -2 if option is not found
 */

int
config_set_value (char *option_name, char *value)
{
    t_config_option *ptr_option;
    
    ptr_option = config_option_search (option_name);
    if (ptr_option)
        return config_option_set_value (ptr_option, value);
    else
        return -2;
}

/*
 * config_allocate_server: allocate a new server
 */

int
config_allocate_server (char *filename, int line_number)
{
    if (!cfg_server.name
        || !cfg_server.address
        || cfg_server.port < 0
        || !cfg_server.nick1
        || !cfg_server.nick2
        || !cfg_server.nick3
        || !cfg_server.username
        || !cfg_server.realname)
    {
        server_free_all ();
        gui_printf (NULL,
                    _("%s %s, line %d: new server, but previous was incomplete\n"),
                    WEECHAT_WARNING, filename, line_number);
        return 0;
        
    }
    if (server_name_already_exists (cfg_server.name))
    {
        server_free_all ();
        gui_printf (NULL,
                    _("%s %s, line %d: server '%s' already exists\n"),
                    WEECHAT_WARNING, filename, line_number, cfg_server.name);
        return 0;
    }
    if (!server_new (cfg_server.name,
        cfg_server.autoconnect, 0, cfg_server.address, cfg_server.port,
        cfg_server.password, cfg_server.nick1, cfg_server.nick2,
        cfg_server.nick3, cfg_server.username, cfg_server.realname,
        cfg_server.command, cfg_server.autojoin))
    {
        server_free_all ();
        gui_printf (NULL,
                    _("%s %s, line %d: unable to create server\n"),
                    WEECHAT_WARNING, filename, line_number);
        return 0;
    }
    
    server_destroy (&cfg_server);
    server_init (&cfg_server);
    
    return 1;
}

/*
 * config_default_values: initialize config variables with default values
 */

void
config_default_values ()
{
    int i, j, int_value;
    
    for (i = 0; i < CONFIG_NUMBER_SECTIONS; i++)
    {
        if ((i != CONFIG_SECTION_ALIAS) && (i != CONFIG_SECTION_SERVER))
        {
            for (j = 0; weechat_options[i][j].option_name; j++)
            {
                switch (weechat_options[i][j].option_type)
                {
                    case OPTION_TYPE_BOOLEAN:
                    case OPTION_TYPE_INT:
                        *weechat_options[i][j].ptr_int =
                            weechat_options[i][j].default_int;
                        break;
                    case OPTION_TYPE_INT_WITH_STRING:
                        int_value = get_pos_array_values (
                            weechat_options[i][j].array_values,
                            weechat_options[i][j].default_string);
                        if (int_value < 0)
                            gui_printf (NULL,
                                        _("%s unable to assign default int with string (\"%s\")\n"),
                                        weechat_options[i][j].default_string);
                        else
                            *weechat_options[i][j].ptr_int =
                                int_value;
                        break;
                    case OPTION_TYPE_COLOR:
                        if (!gui_assign_color (
                            weechat_options[i][j].ptr_int,
                            weechat_options[i][j].default_string))
                            gui_printf (NULL,
                                        _("%s unable to assign default color (\"%s\")\n"),
                                        weechat_options[i][j].default_string);
                        break;
                    case OPTION_TYPE_STRING:
                        *weechat_options[i][j].ptr_string =
                            strdup (weechat_options[i][j].default_string);
                        break;
                }
            }
        }
    }
}

/*
 * config_read: read WeeChat configuration
 *              returns:   0 = successful
 *                        -1 = config file file not found
 *                      < -1 = other error (fatal)
 */

int
config_read ()
{
    int filename_length;
    char *filename;
    FILE *file;
    int section, line_number, i, option_number;
    int server_found;
    char line[1024], *ptr_line, *pos, *pos2;

    filename_length = strlen (weechat_home) + 64;
    filename =
        (char *) malloc (filename_length * sizeof (char));
    if (!filename)
        return -2;
    snprintf (filename, filename_length, "%s%s" WEECHAT_CONFIG_NAME,
              weechat_home, DIR_SEPARATOR);
    if ((file = fopen (filename, "rt")) == NULL)
    {
        gui_printf (NULL, _("%s config file \"%s\" not found.\n"),
                    WEECHAT_WARNING, filename);
        free (filename);
        return -1;
    }
    
    config_default_values ();
    server_init (&cfg_server);
    
    /* read config file */
    section = CONFIG_SECTION_NONE;
    server_found = 0;
    line_number = 0;
    while (!feof (file))
    {
        ptr_line = fgets (line, sizeof (line) - 1, file);
        line_number++;
        if (ptr_line)
        {
            /* skip spaces */
            while (ptr_line[0] == ' ')
                ptr_line++;
            /* not a comment and not an empty line */
            if ((ptr_line[0] != '#') && (ptr_line[0] != '\r')
                && (ptr_line[0] != '\n'))
            {
                /* beginning of section */
                if (ptr_line[0] == '[')
                {
                    pos = strchr (line, ']');
                    if (pos == NULL)
                        gui_printf (NULL,
                                    _("%s %s, line %d: invalid syntax, missing \"]\"\n"),
                                    WEECHAT_WARNING, filename, line_number);
                    else
                    {
                        pos[0] = '\0';
                        pos = ptr_line + 1;
                        section = CONFIG_SECTION_NONE;
                        for (i = 0; config_sections[i].section_name; i++)
                        {
                            if (strcmp (config_sections[i].section_name, pos) == 0)
                            {
                                section = i;
                                break;
                            }
                        }
                        if (section == CONFIG_SECTION_NONE)
                            gui_printf (NULL,
                                        _("%s %s, line %d: unknown section identifier (\"%s\")\n"),
                                        WEECHAT_WARNING, filename, line_number, pos);
                        else
                        {
                            if (server_found)
                            {
                                /* if server already started => create it */
                                config_allocate_server (filename, line_number);
                            }
                            server_found = (section == CONFIG_SECTION_SERVER) ? 1 : 0;
                        }
                    }
                }
                else
                {
                    pos = strchr (line, '=');
                    if (pos == NULL)
                        gui_printf (NULL,
                                    _("%s %s, line %d: invalid syntax, missing \"=\"\n"),
                                    WEECHAT_WARNING, filename, line_number);
                    else
                    {
                        pos[0] = '\0';
                        pos++;
                        pos2 = strchr (pos, '\r');
                        if (pos2 != NULL)
                            pos2[0] = '\0';
                        pos2 = strchr (pos, '\n');
                        if (pos2 != NULL)
                            pos2[0] = '\0';
                        
                        if (section == CONFIG_SECTION_ALIAS)
                        {
                            if (alias_new (line, pos))
                                index_command_new (pos);
                        }
                        else
                        {
                            option_number = -1;
                            for (i = 0;
                                 weechat_options[section][i].option_name; i++)
                            {
                                if (strcmp
                                    (weechat_options[section][i].option_name,
                                     ptr_line) == 0)
                                {
                                    option_number = i;
                                    break;
                                }
                            }
                            if (option_number < 0)
                                gui_printf (NULL,
                                            _("%s %s, line %d: invalid option \"%s\"\n"),
                                            WEECHAT_WARNING, filename, line_number, ptr_line);
                            else
                            {
                                if (config_option_set_value (&weechat_options[section][option_number], pos) < 0)
                                {
                                    switch (weechat_options[section]
                                            [option_number].option_type)
                                    {
                                        case OPTION_TYPE_BOOLEAN:
                                            gui_printf (NULL,
                                                _("%s %s, line %d: invalid value for"
                                                "option '%s'\n"
                                                "Expected: boolean value: "
                                                "'off' or 'on'\n"),
                                                WEECHAT_WARNING, filename,
                                                line_number, ptr_line);
                                            break;
                                        case OPTION_TYPE_INT:
                                            gui_printf (NULL,
                                                        _("%s %s, line %d: invalid value for "
                                                        "option '%s'\n"
                                                        "Expected: integer between %d "
                                                        "and %d\n"),
                                                        WEECHAT_WARNING, filename,
                                                        line_number, ptr_line,
                                                        weechat_options[section][option_number].min,
                                                        weechat_options[section][option_number].max);
                                            break;
                                        case OPTION_TYPE_INT_WITH_STRING:
                                            gui_printf (NULL,
                                                        _("%s %s, line %d: invalid value for "
                                                        "option '%s'\n"
                                                        "Expected: one of these strings: "),
                                                        WEECHAT_WARNING, filename,
                                                        line_number, ptr_line);
                                            i = 0;
                                            while (weechat_options[section][option_number].array_values[i])
                                            {
                                                gui_printf (NULL, "\"%s\" ",
                                                    weechat_options[section][option_number].array_values[i]);
                                                i++;
                                            }
                                            gui_printf (NULL, "\n");
                                            break;
                                        case OPTION_TYPE_COLOR:
                                            gui_printf (NULL,
                                                        _("%s %s, line %d: invalid color "
                                                        "name for option '%s'\n"),
                                                        WEECHAT_WARNING, filename,
                                                        line_number,
                                                        ptr_line);
                                            break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (server_found)
    {       
        if (!config_allocate_server (filename, line_number))
        {
            fclose (file);
            free (filename);
            return -2;
        }
    }
    
    fclose (file);
    free (filename);
    
    return 0;
}


/*
 * config_create_default: create default WeeChat config
 *                        return:  0 if ok
 *                               < 0 if error
 */

int
config_create_default ()
{
    int filename_length;
    char *filename;
    FILE *file;
    int i, j;
    time_t current_time;
    struct passwd *my_passwd;
    char *realname, *pos;

    filename_length = strlen (weechat_home) + 64;
    filename =
        (char *) malloc (filename_length * sizeof (char));
    if (!filename)
        return -2;
    snprintf (filename, filename_length, "%s%s" WEECHAT_CONFIG_NAME,
              weechat_home, DIR_SEPARATOR);
    if ((file = fopen (filename, "wt")) == NULL)
    {
        gui_printf (NULL, _("%s cannot create file \"%s\"\n"),
                    WEECHAT_ERROR, filename);
        free (filename);
        return -1;
    }
    
    printf (_("%s: creating default config file...\n"), PACKAGE_NAME);
    wee_log_printf (_("creating default config file\n"));
    
    current_time = time (NULL);
    fprintf (file, _("#\n# %s configuration file, created by "
             "%s v%s on %s#\n"),
             PACKAGE_NAME, PACKAGE_NAME, PACKAGE_VERSION,
             ctime (&current_time));

    for (i = 0; i < CONFIG_NUMBER_SECTIONS; i++)
    {
        if ((i != CONFIG_SECTION_ALIAS) && (i != CONFIG_SECTION_SERVER))
        {
            fprintf (file, "\n[%s]\n", config_sections[i].section_name);
            if ((i == CONFIG_SECTION_HISTORY) || (i == CONFIG_SECTION_LOG) ||
                (i == CONFIG_SECTION_DCC) || (i == CONFIG_SECTION_PROXY))
                fprintf (file,
                         "# WARNING!!! Options for section \"%s\" are not developed!\n",
                         config_sections[i].section_name);
            for (j = 0; weechat_options[i][j].option_name; j++)
            {
                switch (weechat_options[i][j].option_type)
                {
                    case OPTION_TYPE_BOOLEAN:
                        fprintf (file, "%s=%s\n",
                                 weechat_options[i][j].option_name,
                                 (weechat_options[i][j].default_int) ?
                                 "on" : "off");
                        break;
                    case OPTION_TYPE_INT:
                        fprintf (file, "%s=%d\n",
                                 weechat_options[i][j].option_name,
                                 weechat_options[i][j].default_int);
                        break;
                    case OPTION_TYPE_INT_WITH_STRING:
                    case OPTION_TYPE_COLOR:
                    case OPTION_TYPE_STRING:
                        fprintf (file, "%s=%s\n",
                                 weechat_options[i][j].option_name,
                                 weechat_options[i][j].default_string);
                        break;
                }
            }
        }
    }
    
    /* default aliases */
    /* TODO: remove comments when missing commands will be ok */
    fprintf (file, "\n[alias]\n");
    fprintf (file, "SAY=msg *\n");
    fprintf (file, "BYE=quit\n");
    fprintf (file, "EXIT=quit\n");
    fprintf (file, "SIGNOFF=quit\n");
    fprintf (file, "C=clear\n");
    fprintf (file, "CL=clear\n");
    fprintf (file, "# CHAT=dcc chat\n");
    fprintf (file, "# GET=dcc get\n");
    fprintf (file, "# IG=ignore\n");
    fprintf (file, "J=join\n");
    fprintf (file, "K=kick\n");
    fprintf (file, "# KB=kickban\n");
    fprintf (file, "# KN=knockout\n");
    fprintf (file, "LEAVE=part\n");
    fprintf (file, "M=msg\n");
    fprintf (file, "# MUB=unban *\n");
    fprintf (file, "N=names\n");
    fprintf (file, "Q=query\n");
    fprintf (file, "T=topic\n");
    fprintf (file, "# UB=unban\n");
    fprintf (file, "# UNIG=unignore\n");
    fprintf (file, "W=who\n");
    fprintf (file, "WC=part\n");
    fprintf (file, "WI=whois\n");
    fprintf (file, "WW=whowas\n");
    
    /* default server is freenode */
    fprintf (file, "\n[server]\n");
    fprintf (file, "server_name=freenode\n");
    fprintf (file, "server_autoconnect=on\n");
    fprintf (file, "server_address=irc.freenode.net\n");
    fprintf (file, "server_port=6667\n");
    fprintf (file, "server_password=\n");
    
    /* Get the user's name from /etc/passwd */
    if ((my_passwd = getpwuid (geteuid ())) != NULL)
    {
        fprintf (file, "server_nick1=%s\n", my_passwd->pw_name);
        fprintf (file, "server_nick2=%s1\n", my_passwd->pw_name);
        fprintf (file, "server_nick3=%s2\n", my_passwd->pw_name);
        fprintf (file, "server_username=%s\n", my_passwd->pw_name);
        if ((!my_passwd->pw_gecos)
            || (my_passwd->pw_gecos[0] == '\0')
            || (my_passwd->pw_gecos[0] == ',')
            || (my_passwd->pw_gecos[0] == ' '))
            fprintf (file, "server_realname=%s\n", my_passwd->pw_name);
        else
        {
            realname = strdup (my_passwd->pw_gecos);
            pos = strchr (realname, ',');
            if (pos)
                pos[0] = '\0';
            fprintf (file, "server_realname=%s\n",
                realname);
            if (pos)
                pos[0] = ',';
            free (realname);
        }
    }
    else
    {
        /* default values if /etc/passwd can't be read */
        fprintf (stderr, "%s: %s (%s).",
            WEECHAT_WARNING,
            _("Unable to get user's name"),
            strerror (errno));
        fprintf (file, "server_nick1=weechat1\n");
        fprintf (file, "server_nick2=weechat2\n");
        fprintf (file, "server_nick3=weechat3\n");
        fprintf (file, "server_username=weechat\n");
        fprintf (file, "server_realname=WeeChat default realname\n");
    }
    
    fprintf (file, "server_command=\n");
    fprintf (file, "server_autojoin=\n");
    
    fclose (file);
    free (filename);
    return 0;
}

/*
 * config_write: write WeeChat configurtion
 *               return:  0 if ok
 *                      < 0 if error
 */

int
config_write (char *config_name)
{
    int filename_length;
    char *filename;
    FILE *file;
    int i, j;
    time_t current_time;
    t_irc_server *ptr_server;
    t_weechat_alias *ptr_alias;

    if (config_name)
        filename = strdup (config_name);
    else
    {
        filename_length = strlen (weechat_home) + 64;
        filename =
            (char *) malloc (filename_length * sizeof (char));
        if (!filename)
            return -2;
        snprintf (filename, filename_length, "%s%s" WEECHAT_CONFIG_NAME,
                  weechat_home, DIR_SEPARATOR);
    }
    
    if ((file = fopen (filename, "wt")) == NULL)
    {
        gui_printf (NULL, _("%s cannot create file \"%s\"\n"),
                    WEECHAT_ERROR, filename);
        free (filename);
        return -1;
    }
    
    wee_log_printf (_("saving config to disk\n"));
    
    current_time = time (NULL);
    fprintf (file, _("#\n# %s configuration file, created by "
             "%s v%s on %s#\n"),
             PACKAGE_NAME, PACKAGE_NAME, PACKAGE_VERSION,
             ctime (&current_time));

    for (i = 0; i < CONFIG_NUMBER_SECTIONS; i++)
    {
        if ((i != CONFIG_SECTION_ALIAS) && (i != CONFIG_SECTION_SERVER))
        {
            fprintf (file, "\n[%s]\n", config_sections[i].section_name);
            if ((i == CONFIG_SECTION_LOG) || (i == CONFIG_SECTION_PROXY))
                fprintf (file,
                         "# WARNING!!! Options for section \"%s\" are not developed!\n",
                         config_sections[i].section_name);
            for (j = 0; weechat_options[i][j].option_name; j++)
            {
                switch (weechat_options[i][j].option_type)
                {
                    case OPTION_TYPE_BOOLEAN:
                        fprintf (file, "%s=%s\n",
                                 weechat_options[i][j].option_name,
                                 (weechat_options[i][j].ptr_int &&
                                 *weechat_options[i][j].ptr_int) ? 
                                 "on" : "off");
                        break;
                    case OPTION_TYPE_INT:
                        fprintf (file, "%s=%d\n",
                                 weechat_options[i][j].option_name,
                                 (weechat_options[i][j].ptr_int) ?
                                 *weechat_options[i][j].ptr_int :
                                 weechat_options[i][j].default_int);
                        break;
                    case OPTION_TYPE_INT_WITH_STRING:
                        fprintf (file, "%s=%s\n",
                                 weechat_options[i][j].option_name,
                                 (weechat_options[i][j].ptr_int) ?
                                 weechat_options[i][j].array_values[*weechat_options[i][j].ptr_int] :
                                 weechat_options[i][j].array_values[weechat_options[i][j].default_int]);
                        break;
                    case OPTION_TYPE_COLOR:
                        fprintf (file, "%s=%s\n",
                                 weechat_options[i][j].option_name,
                                 (weechat_options[i][j].ptr_int) ?
                                 gui_get_color_by_value (*weechat_options[i][j].ptr_int) :
                                 weechat_options[i][j].default_string);
                        break;
                    case OPTION_TYPE_STRING:
                        fprintf (file, "%s=%s\n",
                                 weechat_options[i][j].option_name,
                                 (weechat_options[i][j].ptr_string) ?
                                 *weechat_options[i][j].ptr_string :
                                 weechat_options[i][j].default_string);
                        break;
                }
            }
        }
    }
    
    /* alias section */
    fprintf (file, "\n[alias]\n");
    for (ptr_alias = weechat_alias; ptr_alias;
         ptr_alias = ptr_alias->next_alias)
    {
        fprintf (file, "%s=%s\n",
                 ptr_alias->alias_name, ptr_alias->alias_command + 1);
    }
    
    /* server section */
    for (ptr_server = irc_servers; ptr_server;
         ptr_server = ptr_server->next_server)
    {
        if (!ptr_server->command_line)
        {
            fprintf (file, "\n[server]\n");
            fprintf (file, "server_name=%s\n", ptr_server->name);
            fprintf (file, "server_autoconnect=%s\n",
                     (ptr_server->autoconnect) ? "on" : "off");
            fprintf (file, "server_address=%s\n", ptr_server->address);
            fprintf (file, "server_port=%d\n", ptr_server->port);
            fprintf (file, "server_password=%s\n",
                     (ptr_server->password) ? ptr_server->password : "");
            fprintf (file, "server_nick1=%s\n", ptr_server->nick1);
            fprintf (file, "server_nick2=%s\n", ptr_server->nick2);
            fprintf (file, "server_nick3=%s\n", ptr_server->nick3);
            fprintf (file, "server_username=%s\n", ptr_server->username);
            fprintf (file, "server_realname=%s\n", ptr_server->realname);
            fprintf (file, "server_command=%s\n",
                     (ptr_server->command) ? ptr_server->command : "");
            fprintf (file, "server_autojoin=%s\n",
                     (ptr_server->autojoin) ? ptr_server->autojoin : "");
        }
    }
    
    fclose (file);
    free (filename);
    return 0;
}
