/*
 * Copyright (C) 2003-2023 Sébastien Helleu <flashcode@flashtux.org>
 * Copyright (C) 2012 Simon Arlott
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

#ifndef WEECHAT_PLUGIN_PLUGIN_SCRIPT_API_H
#define WEECHAT_PLUGIN_PLUGIN_SCRIPT_API_H

#include <time.h>

extern void plugin_script_api_charset_set (struct t_plugin_script *script,
                                           const char *charset);
extern int plugin_script_api_string_match_list (struct t_weechat_plugin *weechat_plugin,
                                                const char *string,
                                                const char *masks,
                                                int case_sensitive);
extern struct t_config_file *plugin_script_api_config_new (struct t_weechat_plugin *weechat_plugin,
                                                           struct t_plugin_script *script,
                                                           const char *name,
                                                           int (*callback_reload)(const void *pointer,
                                                                                  void *data,
                                                                                  struct t_config_file *config_file),
                                                           const char *function,
                                                           const char *data);
extern struct t_config_section *plugin_script_api_config_new_section (struct t_weechat_plugin *weechat_plugin,
                                                                      struct t_plugin_script *script,
                                                                      struct t_config_file *config_file,
                                                                      const char *name,
                                                                      int user_can_add_options,
                                                                      int user_can_delete_options,
                                                                      int (*callback_read)(const void *pointer,
                                                                                           void *data,
                                                                                           struct t_config_file *config_file,
                                                                                           struct t_config_section *section,
                                                                                           const char *option_name,
                                                                                           const char *value),
                                                                      const char *function_read,
                                                                      const char *data_read,
                                                                      int (*callback_write)(const void *pointer,
                                                                                            void *data,
                                                                                            struct t_config_file *config_file,
                                                                                            const char *section_name),
                                                                      const char *function_write,
                                                                      const char *data_write,
                                                                      int (*callback_write_default)(const void *pointer,
                                                                                                    void *data,
                                                                                                    struct t_config_file *config_file,
                                                                                                    const char *section_name),
                                                                      const char *function_write_default,
                                                                      const char *data_write_default,
                                                                      int (*callback_create_option)(const void *pointer,
                                                                                                    void *data,
                                                                                                    struct t_config_file *config_file,
                                                                                                    struct t_config_section *section,
                                                                                                    const char *option_name,
                                                                                                    const char *value),
                                                                      const char *function_create_option,
                                                                      const char *data_create_option,
                                                                      int (*callback_delete_option)(const void *pointer,
                                                                                                    void *data,
                                                                                                    struct t_config_file *config_file,
                                                                                                    struct t_config_section *section,
                                                                                                    struct t_config_option *option),
                                                                      const char *function_delete_option,
                                                                      const char *data_delete_option);
extern struct t_config_option *plugin_script_api_config_new_option (struct t_weechat_plugin *weechat_plugin,
                                                                    struct t_plugin_script *script,
                                                                    struct t_config_file *config_file,
                                                                    struct t_config_section *section,
                                                                    const char *name,
                                                                    const char *type,
                                                                    const char *description,
                                                                    const char *string_values,
                                                                    int min, int max,
                                                                    const char *default_value,
                                                                    const char *value,
                                                                    int null_value_allowed,
                                                                    int (*callback_check_value)(const void *pointer,
                                                                                                void *data,
                                                                                                struct t_config_option *option,
                                                                                                const char *value),
                                                                    const char *function_check_value,
                                                                    const char *data_check_value,
                                                                    void (*callback_change)(const void *pointer,
                                                                                            void *data,
                                                                                            struct t_config_option *option),
                                                                    const char *function_change,
                                                                    const char *data_change,
                                                                    void (*callback_delete)(const void *pointer,
                                                                                            void *data,
                                                                                            struct t_config_option *option),
                                                                    const char *function_delete,
                                                                    const char *data_delete);
extern void plugin_script_api_printf (struct t_weechat_plugin *weechat_plugin,
                                      struct t_plugin_script *script,
                                      struct t_gui_buffer *buffer,
                                      const char *format, ...);
extern void plugin_script_api_printf_date_tags (struct t_weechat_plugin *weechat_plugin,
                                                struct t_plugin_script *script,
                                                struct t_gui_buffer *buffer,
                                                time_t date, const char *tags,
                                                const char *format, ...);
extern void plugin_script_api_printf_y (struct t_weechat_plugin *weechat_plugin,
                                        struct t_plugin_script *script,
                                        struct t_gui_buffer *buffer,
                                        int y, const char *format, ...);
extern void plugin_script_api_printf_y_date_tags (struct t_weechat_plugin *weechat_plugin,
                                                  struct t_plugin_script *script,
                                                  struct t_gui_buffer *buffer,
                                                  int y, time_t date,
                                                  const char *tags,
                                                  const char *format, ...);
extern void plugin_script_api_log_printf (struct t_weechat_plugin *weechat_plugin,
                                          struct t_plugin_script *script,
                                          const char *format, ...);
extern struct t_hook *plugin_script_api_hook_command (struct t_weechat_plugin *weechat_plugin,
                                                      struct t_plugin_script *script,
                                                      const char *command, const char *description,
                                                      const char *args, const char *args_description,
                                                      const char *completion,
                                                      int (*callback)(const void *pointer,
                                                                      void *data,
                                                                      struct t_gui_buffer *buffer,
                                                                      int argc, char **argv,
                                                                      char **argv_eol),
                                                      const char *function,
                                                      const char *data);
extern struct t_hook *plugin_script_api_hook_command_run (struct t_weechat_plugin *weechat_plugin,
                                                          struct t_plugin_script *script,
                                                          const char *command,
                                                          int (*callback)(const void *pointer,
                                                                          void *data,
                                                                          struct t_gui_buffer *buffer,
                                                                          const char *command),
                                                          const char *function,
                                                          const char *data);
extern struct t_hook *plugin_script_api_hook_timer (struct t_weechat_plugin *weechat_plugin,
                                                    struct t_plugin_script *script,
                                                    long interval, int align_second,
                                                    int max_calls,
                                                    int (*callback)(const void *pointer,
                                                                    void *data,
                                                                    int remaining_calls),
                                                    const char *function,
                                                    const char *data);
extern struct t_hook *plugin_script_api_hook_fd (struct t_weechat_plugin *weechat_plugin,
                                                 struct t_plugin_script *script,
                                                 int fd, int flag_read,
                                                 int flag_write, int flag_exception,
                                                 int (*callback)(const void *pointer,
                                                                 void *data,
                                                                 int fd),
                                                 const char *function,
                                                 const char *data);
extern struct t_hook *plugin_script_api_hook_process_hashtable (struct t_weechat_plugin *weechat_plugin,
                                                                struct t_plugin_script *script,
                                                                const char *command,
                                                                struct t_hashtable *options,
                                                                int timeout,
                                                                int (*callback)(const void *pointer,
                                                                                void *data,
                                                                                const char *command,
                                                                                int return_code,
                                                                                const char *out,
                                                                                const char *err),
                                                                const char *function,
                                                                const char *data);
extern struct t_hook *plugin_script_api_hook_process (struct t_weechat_plugin *weechat_plugin,
                                                      struct t_plugin_script *script,
                                                      const char *command,
                                                      int timeout,
                                                      int (*callback)(const void *pointer,
                                                                      void *data,
                                                                      const char *command,
                                                                      int return_code,
                                                                      const char *out,
                                                                      const char *err),
                                                      const char *function,
                                                      const char *data);
extern struct t_hook *plugin_script_api_hook_connect (struct t_weechat_plugin *weechat_plugin,
                                                      struct t_plugin_script *script,
                                                      const char *proxy,
                                                      const char *address,
                                                      int port,
                                                      int ipv6,
                                                      int retry,
                                                      void *gnutls_sess,
                                                      void *gnutls_cb,
                                                      int gnutls_dhkey_size,
                                                      const char *gnutls_priorities,
                                                      const char *local_hostname,
                                                      int (*callback)(const void *pointer,
                                                                      void *data,
                                                                      int status,
                                                                      int gnutls_rc,
                                                                      int sock,
                                                                      const char *error,
                                                                      const char *ip_address),
                                                      const char *function,
                                                      const char *data);
extern struct t_hook *plugin_script_api_hook_line (struct t_weechat_plugin *weechat_plugin,
                                                   struct t_plugin_script *script,
                                                   const char *buffer_type,
                                                   const char *buffer_name,
                                                   const char *tags,
                                                   struct t_hashtable *(*callback)(const void *pointer,
                                                                                   void *data,
                                                                                   struct t_hashtable *line),
                                                   const char *function,
                                                   const char *data);
extern struct t_hook *plugin_script_api_hook_print (struct t_weechat_plugin *weechat_plugin,
                                                    struct t_plugin_script *script,
                                                    struct t_gui_buffer *buffer,
                                                    const char *tags,
                                                    const char *message,
                                                    int strip_colors,
                                                    int (*callback)(const void *pointer,
                                                                    void *data,
                                                                    struct t_gui_buffer *buffer,
                                                                    time_t date,
                                                                    int tags_count,
                                                                    const char **tags,
                                                                    int displayed,
                                                                    int highlight,
                                                                    const char *prefix,
                                                                    const char *message),
                                                    const char *function,
                                                    const char *data);
extern struct t_hook *plugin_script_api_hook_signal (struct t_weechat_plugin *weechat_plugin,
                                                     struct t_plugin_script *script,
                                                     const char *signal,
                                                     int (*callback)(const void *pointer,
                                                                     void *data,
                                                                     const char *signal,
                                                                     const char *type_data,
                                                                     void *signal_data),
                                                     const char *function,
                                                     const char *data);
extern struct t_hook *plugin_script_api_hook_hsignal (struct t_weechat_plugin *weechat_plugin,
                                                      struct t_plugin_script *script,
                                                      const char *signal,
                                                      int (*callback)(const void *pointer,
                                                                      void *data,
                                                                      const char *signal,
                                                                      struct t_hashtable *hashtable),
                                                      const char *function,
                                                      const char *data);
extern struct t_hook *plugin_script_api_hook_config (struct t_weechat_plugin *weechat_plugin,
                                                     struct t_plugin_script *script,
                                                     const char *option,
                                                     int (*callback)(const void *pointer,
                                                                     void *data,
                                                                     const char *option,
                                                                     const char *value),
                                                     const char *function,
                                                     const char *data);
extern struct t_hook *plugin_script_api_hook_completion (struct t_weechat_plugin *weechat_plugin,
                                                         struct t_plugin_script *script,
                                                         const char *completion,
                                                         const char *description,
                                                         int (*callback)(const void *pointer,
                                                                         void *data,
                                                                         const char *completion_item,
                                                                         struct t_gui_buffer *buffer,
                                                                         struct t_gui_completion *completion),
                                                         const char *function,
                                                         const char *data);
extern struct t_hook *plugin_script_api_hook_modifier (struct t_weechat_plugin *weechat_plugin,
                                                       struct t_plugin_script *script,
                                                       const char *modifier,
                                                       char *(*callback)(const void *pointer,
                                                                         void *data,
                                                                         const char *modifier,
                                                                         const char *modifier_data,
                                                                         const char *string),
                                                       const char *function,
                                                       const char *data);
extern struct t_hook *plugin_script_api_hook_info (struct t_weechat_plugin *weechat_plugin,
                                                   struct t_plugin_script *script,
                                                   const char *info_name,
                                                   const char *description,
                                                   const char *args_description,
                                                   char *(*callback)(const void *pointer,
                                                                     void *data,
                                                                     const char *info_name,
                                                                     const char *arguments),
                                                   const char *function,
                                                   const char *data);
extern struct t_hook *plugin_script_api_hook_info_hashtable (struct t_weechat_plugin *weechat_plugin,
                                                             struct t_plugin_script *script,
                                                             const char *info_name,
                                                             const char *description,
                                                             const char *args_description,
                                                             const char *output_description,
                                                             struct t_hashtable *(*callback)(const void *pointer,
                                                                                             void *data,
                                                                                             const char *info_name,
                                                                                             struct t_hashtable *hashtable),
                                                             const char *function,
                                                             const char *data);
extern struct t_hook *plugin_script_api_hook_infolist (struct t_weechat_plugin *weechat_plugin,
                                                       struct t_plugin_script *script,
                                                       const char *infolist_name,
                                                       const char *description,
                                                       const char *pointer_description,
                                                       const char *args_description,
                                                       struct t_infolist *(*callback)(const void *pointer,
                                                                                      void *data,
                                                                                      const char *infolist_name,
                                                                                      void *obj_pointer,
                                                                                      const char *arguments),
                                                       const char *function,
                                                       const char *data);
extern struct t_hook *plugin_script_api_hook_focus (struct t_weechat_plugin *weechat_plugin,
                                                    struct t_plugin_script *script,
                                                    const char *area,
                                                    struct t_hashtable *(*callback)(const void *pointer,
                                                                                    void *data,
                                                                                    struct t_hashtable *info),
                                                    const char *function,
                                                    const char *data);
extern struct t_gui_buffer *plugin_script_api_buffer_new_props (struct t_weechat_plugin *weechat_plugin,
                                                                struct t_plugin_script *script,
                                                                const char *name,
                                                                struct t_hashtable *properties,
                                                                int (*input_callback)(const void *pointer,
                                                                                      void *data,
                                                                                      struct t_gui_buffer *buffer,
                                                                                      const char *input_data),
                                                                const char *function_input,
                                                                const char *data_input,
                                                                int (*close_callback)(const void *pointer,
                                                                                      void *data,
                                                                                      struct t_gui_buffer *buffer),
                                                                const char *function_close,
                                                                const char *data_close);
extern struct t_gui_buffer *plugin_script_api_buffer_new (struct t_weechat_plugin *weechat_plugin,
                                                          struct t_plugin_script *script,
                                                          const char *name,
                                                          int (*input_callback)(const void *pointer,
                                                                                void *data,
                                                                                struct t_gui_buffer *buffer,
                                                                                const char *input_data),
                                                          const char *function_input,
                                                          const char *data_input,
                                                          int (*close_callback)(const void *pointer,
                                                                                void *data,
                                                                                struct t_gui_buffer *buffer),
                                                          const char *function_close,
                                                          const char *data_close);
extern struct t_gui_bar_item *plugin_script_api_bar_item_new (struct t_weechat_plugin *weechat_plugin,
                                                              struct t_plugin_script *script,
                                                              const char *name,
                                                              char *(*build_callback)(const void *pointer,
                                                                                      void *data,
                                                                                      struct t_gui_bar_item *item,
                                                                                      struct t_gui_window *window,
                                                                                      struct t_gui_buffer *buffer,
                                                                                      struct t_hashtable *extra_info),
                                                              const char *function,
                                                              const char *data);
extern int plugin_script_api_command_options (struct t_weechat_plugin *weechat_plugin,
                                              struct t_plugin_script *script,
                                              struct t_gui_buffer *buffer,
                                              const char *command,
                                              struct t_hashtable *options);
extern int plugin_script_api_command (struct t_weechat_plugin *weechat_plugin,
                                      struct t_plugin_script *script,
                                      struct t_gui_buffer *buffer,
                                      const char *command);
extern const char *plugin_script_api_config_get_plugin (struct t_weechat_plugin *weechat_plugin,
                                                        struct t_plugin_script *script,
                                                        const char *option);
extern int plugin_script_api_config_is_set_plugin (struct t_weechat_plugin *weechat_plugin,
                                                   struct t_plugin_script *script,
                                                   const char *option);
extern int plugin_script_api_config_set_plugin (struct t_weechat_plugin *weechat_plugin,
                                                struct t_plugin_script *script,
                                                const char *option, const char *value);
extern void plugin_script_api_config_set_desc_plugin (struct t_weechat_plugin *weechat_plugin,
                                                      struct t_plugin_script *script,
                                                      const char *option,
                                                      const char *description);
extern int plugin_script_api_config_unset_plugin (struct t_weechat_plugin *weechat_plugin,
                                                  struct t_plugin_script *script,
                                                  const char *option);
extern struct t_upgrade_file *plugin_script_api_upgrade_new (struct t_weechat_plugin *weechat_plugin,
                                                             struct t_plugin_script *script,
                                                             const char *filename,
                                                             int (*callback_read)(const void *pointer,
                                                                                  void *data,
                                                                                  struct t_upgrade_file *upgrade_file,
                                                                                  int object_id,
                                                                                  struct t_infolist *infolist),
                                                             const char *function,
                                                             const char *data);

#endif /* WEECHAT_PLUGIN_PLUGIN_SCRIPT_API_H */
