/*
 * wee-hook-line.c - WeeChat line hook
 *
 * Copyright (C) 2003-2023 Sébastien Helleu <flashcode@flashtux.org>
 *
 * This file is part of WeeChat, the extensible chat client.
 *
 * WeeChat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WeeChat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WeeChat.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>

#include "../weechat.h"
#include "../wee-arraylist.h"
#include "../wee-hashtable.h"
#include "../wee-hook.h"
#include "../wee-infolist.h"
#include "../wee-log.h"
#include "../wee-string.h"
#include "../../gui/gui-buffer.h"
#include "../../gui/gui-line.h"
#include "../../plugins/plugin.h"


/*
 * Returns description of hook.
 *
 * Note: result must be freed after use.
 */

char *
hook_line_get_description (struct t_hook *hook)
{
    char str_desc[1024];

    snprintf (str_desc, sizeof (str_desc),
              "buffer type: %d, %d buffers, %d tags",
              HOOK_LINE(hook, buffer_type),
              HOOK_LINE(hook, num_buffers),
              HOOK_LINE(hook, tags_count));

    return strdup (str_desc);
}

/*
 * Hooks a line added in a buffer.
 *
 * Returns pointer to new hook, NULL if error.
 */

struct t_hook *
hook_line (struct t_weechat_plugin *plugin, const char *buffer_type,
           const char *buffer_name, const char *tags,
           t_hook_callback_line *callback, const void *callback_pointer,
           void *callback_data)
{
    struct t_hook *new_hook;
    struct t_hook_line *new_hook_line;
    int priority;
    const char *ptr_buffer_type;

    if (!callback)
        return NULL;

    new_hook = malloc (sizeof (*new_hook));
    if (!new_hook)
        return NULL;
    new_hook_line = malloc (sizeof (*new_hook_line));
    if (!new_hook_line)
    {
        free (new_hook);
        return NULL;
    }

    string_get_priority_and_name (buffer_type, &priority, &ptr_buffer_type,
                                  HOOK_PRIORITY_DEFAULT);
    hook_init_data (new_hook, plugin, HOOK_TYPE_LINE, priority,
                    callback_pointer, callback_data);

    new_hook->hook_data = new_hook_line;
    new_hook_line->callback = callback;
    if (!ptr_buffer_type || !ptr_buffer_type[0])
        new_hook_line->buffer_type = GUI_BUFFER_TYPE_DEFAULT;
    else if (strcmp (ptr_buffer_type, "*") == 0)
        new_hook_line->buffer_type = -1;
    else
        new_hook_line->buffer_type = gui_buffer_search_type (ptr_buffer_type);
    new_hook_line->buffers = string_split (
        (buffer_name && buffer_name[0]) ? buffer_name : "*",
        ",",
        NULL,
        WEECHAT_STRING_SPLIT_STRIP_LEFT
        | WEECHAT_STRING_SPLIT_STRIP_RIGHT
        | WEECHAT_STRING_SPLIT_COLLAPSE_SEPS,
        0,
        &new_hook_line->num_buffers);
    new_hook_line->tags_array = string_split_tags (tags,
                                                   &new_hook_line->tags_count);

    hook_add_to_list (new_hook);

    return new_hook;
}

/*
 * Executes a line hook and updates the line data.
 */

struct t_arraylist *
hook_line_exec (struct t_gui_line *line)
{
    struct t_hook *ptr_hook, *next_hook;
    struct t_hashtable *hashtable, *hashtable2;
    struct t_arraylist *buffers;
    struct t_gui_buffer *ptr_buffer;
    char str_value[128], *str_tags, **str_buffers;
    int i, size;

    hashtable = NULL;
    buffers = NULL;
    str_buffers = NULL;

    buffers = arraylist_new (16, 0, 0, NULL, NULL, NULL, NULL);
    if (!buffers)
        goto end;
    arraylist_add (buffers, line->data->buffer);

    if (!weechat_hooks[HOOK_TYPE_LINE])
        goto end;

    str_buffers = string_dyn_alloc (256);
    if (!str_buffers)
        goto end;

    hook_exec_start ();

    ptr_hook = weechat_hooks[HOOK_TYPE_LINE];
    while (ptr_hook)
    {
        next_hook = ptr_hook->next_hook;

        if (!ptr_hook->deleted && !ptr_hook->running
            && ((HOOK_LINE(ptr_hook, buffer_type) == -1)
                || ((int)(line->data->buffer->type) == (HOOK_LINE(ptr_hook, buffer_type))))
            && string_match_list (line->data->buffer->full_name,
                                  (const char **)HOOK_LINE(ptr_hook, buffers),
                                  0)
            && (!HOOK_LINE(ptr_hook, tags_array)
                || gui_line_match_tags (line->data,
                                        HOOK_LINE(ptr_hook, tags_count),
                                        HOOK_LINE(ptr_hook, tags_array))))
        {
            /* create the hashtable that will be sent to callback */
            if (!hashtable)
            {
                hashtable = hashtable_new (32,
                                           WEECHAT_HASHTABLE_STRING,
                                           WEECHAT_HASHTABLE_STRING,
                                           NULL, NULL);
                if (!hashtable)
                    break;
            }
            size = arraylist_size (buffers);
            /* build list of buffer pointers */
            string_dyn_copy (str_buffers, NULL);
            for (i = 0; i < size; i++)
            {
                if (i > 0)
                    string_dyn_concat (str_buffers, ",", -1);
                snprintf (str_value, sizeof (str_value),
                          "0x%lx", (unsigned long)(arraylist_get (buffers, i)));
                string_dyn_concat (str_buffers, str_value, -1);
            }
            HASHTABLE_SET_STR("buffer", *str_buffers);
            /* build list of buffer names */
            string_dyn_copy (str_buffers, NULL);
            for (i = 0; i < size; i++)
            {
                if (i > 0)
                    string_dyn_concat (str_buffers, ",", -1);
                ptr_buffer = (struct t_gui_buffer *)arraylist_get (buffers, i);
                string_dyn_concat (str_buffers, ptr_buffer->full_name, -1);
            }
            HASHTABLE_SET_STR("buffer_name", *str_buffers);
            HASHTABLE_SET_STR("buffer_type",
                              gui_buffer_type_string[line->data->buffer->type]);
            HASHTABLE_SET_INT("y", line->data->y);
            HASHTABLE_SET_TIME("date", line->data->date);
            HASHTABLE_SET_TIME("date_printed", line->data->date_printed);
            HASHTABLE_SET_STR_NOT_NULL("str_time", line->data->str_time);
            HASHTABLE_SET_INT("tags_count", line->data->tags_count);
            str_tags = string_rebuild_split_string (
                (const char **)line->data->tags_array, ",", 0, -1);
            HASHTABLE_SET_STR_NOT_NULL("tags", str_tags);
            if (str_tags)
                free (str_tags);
            HASHTABLE_SET_INT("displayed", line->data->displayed);
            HASHTABLE_SET_INT("notify_level", line->data->notify_level);
            HASHTABLE_SET_INT("highlight", line->data->highlight);
            HASHTABLE_SET_STR_NOT_NULL("prefix", line->data->prefix);
            HASHTABLE_SET_STR_NOT_NULL("message", line->data->message);

            /* run callback */
            ptr_hook->running = 1;
            hashtable2 = (HOOK_LINE(ptr_hook, callback))
                (ptr_hook->callback_pointer,
                 ptr_hook->callback_data,
                 hashtable);
            ptr_hook->running = 0;

            if (hashtable2)
            {
                gui_line_hook_update (line, buffers, hashtable, hashtable2);
                hashtable_free (hashtable2);
                if (!line->data->buffer)
                    break;
            }
        }

        ptr_hook = next_hook;
    }

    hook_exec_end ();

end:
    if (hashtable)
        hashtable_free (hashtable);

    if (str_buffers)
        string_dyn_free (str_buffers, 1);

    if (line->data->buffer && buffers && (arraylist_size (buffers) == 0))
        arraylist_add (buffers, line->data->buffer);

    return buffers;
}

/*
 * Frees data in a line hook.
 */

void
hook_line_free_data (struct t_hook *hook)
{
    if (!hook || !hook->hook_data)
        return;

    if (HOOK_LINE(hook, buffers))
    {
        string_free_split (HOOK_LINE(hook, buffers));
        HOOK_LINE(hook, buffers) = NULL;
    }
    if (HOOK_LINE(hook, tags_array))
    {
        string_free_split_tags (HOOK_LINE(hook, tags_array));
        HOOK_LINE(hook, tags_array) = NULL;
    }

    free (hook->hook_data);
    hook->hook_data = NULL;
}

/*
 * Adds line hook data in the infolist item.
 *
 * Returns:
 *   1: OK
 *   0: error
 */

int
hook_line_add_to_infolist (struct t_infolist_item *item,
                           struct t_hook *hook)
{
    if (!item || !hook || !hook->hook_data)
        return 0;

    if (!infolist_new_var_pointer (item, "callback", HOOK_LINE(hook, callback)))
        return 0;
    if (!infolist_new_var_integer (item, "buffer_type", HOOK_LINE(hook, buffer_type)))
        return 0;
    if (!infolist_new_var_pointer (item, "buffers", HOOK_LINE(hook, buffers)))
        return 0;
    if (!infolist_new_var_integer (item, "num_buffers", HOOK_LINE(hook, num_buffers)))
        return 0;
    if (!infolist_new_var_integer (item, "tags_count", HOOK_LINE(hook, tags_count)))
        return 0;
    if (!infolist_new_var_pointer (item, "tags_array", HOOK_LINE(hook, tags_array)))
        return 0;

    return 1;
}

/*
 * Prints line hook data in WeeChat log file (usually for crash dump).
 */

void
hook_line_print_log (struct t_hook *hook)
{
    int i, j;

    if (!hook || !hook->hook_data)
        return;

    log_printf ("  line data:");
    log_printf ("    callback. . . . . . . : 0x%lx", HOOK_LINE(hook, callback));
    log_printf ("    buffer_type . . . . . : %d", HOOK_LINE(hook, buffer_type));
    log_printf ("    buffers . . . . . . . : 0x%lx", HOOK_LINE(hook, buffers));
    log_printf ("    num_buffers . . . . . : %d", HOOK_LINE(hook, num_buffers));
    for (i = 0; i < HOOK_LINE(hook, num_buffers); i++)
    {
        log_printf ("      buffers[%03d]. . . : '%s'",
                    i, HOOK_LINE(hook, buffers)[i]);
    }
    log_printf ("    tags_count. . . . . . : %d", HOOK_LINE(hook, tags_count));
    log_printf ("    tags_array. . . . . . : 0x%lx", HOOK_LINE(hook, tags_array));
    if (HOOK_LINE(hook, tags_array))
    {
        for (i = 0; i < HOOK_LINE(hook, tags_count); i++)
        {
            for (j = 0; HOOK_LINE(hook, tags_array)[i][j]; j++)
            {
                log_printf ("      tags_array[%03d][%03d]: '%s'",
                            i,
                            j,
                            HOOK_LINE(hook, tags_array)[i][j]);
            }
        }
    }
}
