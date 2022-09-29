/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a89a2f8dfa145afbf1c86bf246715c88babebb07 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_register, 0, 0, 7)
	ZEND_ARG_INFO(0, p0)
	ZEND_ARG_INFO(0, p1)
	ZEND_ARG_INFO(0, p2)
	ZEND_ARG_INFO(0, p3)
	ZEND_ARG_INFO(0, p4)
	ZEND_ARG_INFO(0, p5)
	ZEND_ARG_INFO(0, p6)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_plugin_get_name, 0, 0, 1)
	ZEND_ARG_INFO(0, p0)
ZEND_END_ARG_INFO()

#define arginfo_weechat_charset_set arginfo_weechat_plugin_get_name

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_iconv_to_internal, 0, 0, 2)
	ZEND_ARG_INFO(0, p0)
	ZEND_ARG_INFO(0, p1)
ZEND_END_ARG_INFO()

#define arginfo_weechat_iconv_from_internal arginfo_weechat_iconv_to_internal

#define arginfo_weechat_gettext arginfo_weechat_plugin_get_name

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_ngettext, 0, 0, 3)
	ZEND_ARG_INFO(0, p0)
	ZEND_ARG_INFO(0, p1)
	ZEND_ARG_INFO(0, p2)
ZEND_END_ARG_INFO()

#define arginfo_weechat_strlen_screen arginfo_weechat_plugin_get_name

#define arginfo_weechat_string_match arginfo_weechat_ngettext

#define arginfo_weechat_string_match_list arginfo_weechat_ngettext

#define arginfo_weechat_string_has_highlight arginfo_weechat_iconv_to_internal

#define arginfo_weechat_string_has_highlight_regex arginfo_weechat_iconv_to_internal

#define arginfo_weechat_string_mask_to_regex arginfo_weechat_plugin_get_name

#define arginfo_weechat_string_format_size arginfo_weechat_plugin_get_name

#define arginfo_weechat_string_parse_size arginfo_weechat_charset_set

#define arginfo_weechat_string_color_code_size arginfo_weechat_plugin_get_name

#define arginfo_weechat_string_remove_color arginfo_weechat_iconv_to_internal

#define arginfo_weechat_string_is_command_char arginfo_weechat_plugin_get_name

#define arginfo_weechat_string_input_for_buffer arginfo_weechat_plugin_get_name

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_string_eval_expression, 0, 0, 4)
	ZEND_ARG_INFO(0, p0)
	ZEND_ARG_INFO(0, p1)
	ZEND_ARG_INFO(0, p2)
	ZEND_ARG_INFO(0, p3)
ZEND_END_ARG_INFO()

#define arginfo_weechat_string_eval_path_home arginfo_weechat_string_eval_expression

#define arginfo_weechat_mkdir_home arginfo_weechat_iconv_to_internal

#define arginfo_weechat_mkdir arginfo_weechat_iconv_to_internal

#define arginfo_weechat_mkdir_parents arginfo_weechat_iconv_to_internal

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_list_new, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_weechat_list_add arginfo_weechat_string_eval_expression

#define arginfo_weechat_list_search arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_search_pos arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_casesearch arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_casesearch_pos arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_get arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_set arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_next arginfo_weechat_plugin_get_name

#define arginfo_weechat_list_prev arginfo_weechat_plugin_get_name

#define arginfo_weechat_list_string arginfo_weechat_plugin_get_name

#define arginfo_weechat_list_size arginfo_weechat_plugin_get_name

#define arginfo_weechat_list_remove arginfo_weechat_iconv_to_internal

#define arginfo_weechat_list_remove_all arginfo_weechat_plugin_get_name

#define arginfo_weechat_list_free arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_new arginfo_weechat_ngettext

#define arginfo_weechat_config_new_section arginfo_weechat_list_new

#define arginfo_weechat_config_search_section arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_new_option arginfo_weechat_list_new

#define arginfo_weechat_config_search_option arginfo_weechat_ngettext

#define arginfo_weechat_config_string_to_boolean arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_option_reset arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_option_set arginfo_weechat_ngettext

#define arginfo_weechat_config_option_set_null arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_option_unset arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_option_rename arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_option_is_null arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_option_default_is_null arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_boolean arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_boolean_default arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_integer arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_integer_default arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_string arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_string_default arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_color arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_color_default arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_write_option arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_write_line arginfo_weechat_ngettext

#define arginfo_weechat_config_write arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_read arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_reload arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_option_free arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_section_free_options arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_section_free arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_free arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_get arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_get_plugin arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_is_set_plugin arginfo_weechat_plugin_get_name

#define arginfo_weechat_config_set_plugin arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_set_desc_plugin arginfo_weechat_iconv_to_internal

#define arginfo_weechat_config_unset_plugin arginfo_weechat_plugin_get_name

#define arginfo_weechat_key_bind arginfo_weechat_iconv_to_internal

#define arginfo_weechat_key_unbind arginfo_weechat_iconv_to_internal

#define arginfo_weechat_prefix arginfo_weechat_plugin_get_name

#define arginfo_weechat_color arginfo_weechat_plugin_get_name

#define arginfo_weechat_print arginfo_weechat_iconv_to_internal

#define arginfo_weechat_print_date_tags arginfo_weechat_string_eval_expression

#define arginfo_weechat_print_y arginfo_weechat_ngettext

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_print_y_date_tags, 0, 0, 5)
	ZEND_ARG_INFO(0, p0)
	ZEND_ARG_INFO(0, p1)
	ZEND_ARG_INFO(0, p2)
	ZEND_ARG_INFO(0, p3)
	ZEND_ARG_INFO(0, p4)
ZEND_END_ARG_INFO()

#define arginfo_weechat_log_print arginfo_weechat_plugin_get_name

#define arginfo_weechat_hook_command arginfo_weechat_register

#define arginfo_weechat_hook_completion arginfo_weechat_string_eval_expression

#define arginfo_weechat_hook_completion_get_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_hook_completion_list_add arginfo_weechat_string_eval_expression

#define arginfo_weechat_hook_command_run arginfo_weechat_ngettext

#define arginfo_weechat_hook_timer arginfo_weechat_print_y_date_tags

ZEND_BEGIN_ARG_INFO_EX(arginfo_weechat_hook_fd, 0, 0, 6)
	ZEND_ARG_INFO(0, p0)
	ZEND_ARG_INFO(0, p1)
	ZEND_ARG_INFO(0, p2)
	ZEND_ARG_INFO(0, p3)
	ZEND_ARG_INFO(0, p4)
	ZEND_ARG_INFO(0, p5)
ZEND_END_ARG_INFO()

#define arginfo_weechat_hook_process arginfo_weechat_string_eval_expression

#define arginfo_weechat_hook_process_hashtable arginfo_weechat_print_y_date_tags

#define arginfo_weechat_hook_connect arginfo_weechat_list_new

#define arginfo_weechat_hook_line arginfo_weechat_print_y_date_tags

#define arginfo_weechat_hook_print arginfo_weechat_hook_fd

#define arginfo_weechat_hook_signal arginfo_weechat_ngettext

#define arginfo_weechat_hook_signal_send arginfo_weechat_ngettext

#define arginfo_weechat_hook_hsignal arginfo_weechat_ngettext

#define arginfo_weechat_hook_hsignal_send arginfo_weechat_iconv_to_internal

#define arginfo_weechat_hook_config arginfo_weechat_ngettext

#define arginfo_weechat_hook_modifier arginfo_weechat_ngettext

#define arginfo_weechat_hook_modifier_exec arginfo_weechat_ngettext

#define arginfo_weechat_hook_info arginfo_weechat_print_y_date_tags

#define arginfo_weechat_hook_info_hashtable arginfo_weechat_register

#define arginfo_weechat_hook_infolist arginfo_weechat_hook_fd

#define arginfo_weechat_hook_focus arginfo_weechat_ngettext

#define arginfo_weechat_hook_set arginfo_weechat_ngettext

#define arginfo_weechat_unhook arginfo_weechat_plugin_get_name

#define arginfo_weechat_unhook_all arginfo_weechat_plugin_get_name

#define arginfo_weechat_buffer_new arginfo_weechat_print_y_date_tags

#define arginfo_weechat_buffer_new_props arginfo_weechat_hook_fd

#define arginfo_weechat_buffer_search arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_search_main arginfo_weechat_list_new

#define arginfo_weechat_current_buffer arginfo_weechat_list_new

#define arginfo_weechat_buffer_clear arginfo_weechat_plugin_get_name

#define arginfo_weechat_buffer_close arginfo_weechat_plugin_get_name

#define arginfo_weechat_buffer_merge arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_unmerge arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_get_integer arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_get_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_get_pointer arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_set arginfo_weechat_ngettext

#define arginfo_weechat_buffer_string_replace_local_var arginfo_weechat_iconv_to_internal

#define arginfo_weechat_buffer_match_list arginfo_weechat_iconv_to_internal

#define arginfo_weechat_current_window arginfo_weechat_list_new

#define arginfo_weechat_window_search_with_buffer arginfo_weechat_plugin_get_name

#define arginfo_weechat_window_get_integer arginfo_weechat_iconv_to_internal

#define arginfo_weechat_window_get_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_window_get_pointer arginfo_weechat_iconv_to_internal

#define arginfo_weechat_window_set_title arginfo_weechat_plugin_get_name

#define arginfo_weechat_nicklist_add_group arginfo_weechat_print_y_date_tags

#define arginfo_weechat_nicklist_search_group arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_add_nick arginfo_weechat_register

#define arginfo_weechat_nicklist_search_nick arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_remove_group arginfo_weechat_iconv_to_internal

#define arginfo_weechat_nicklist_remove_nick arginfo_weechat_iconv_to_internal

#define arginfo_weechat_nicklist_remove_all arginfo_weechat_plugin_get_name

#define arginfo_weechat_nicklist_group_get_integer arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_group_get_string arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_group_get_pointer arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_group_set arginfo_weechat_string_eval_expression

#define arginfo_weechat_nicklist_nick_get_integer arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_nick_get_string arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_nick_get_pointer arginfo_weechat_ngettext

#define arginfo_weechat_nicklist_nick_set arginfo_weechat_string_eval_expression

#define arginfo_weechat_bar_item_search arginfo_weechat_plugin_get_name

#define arginfo_weechat_bar_item_new arginfo_weechat_ngettext

#define arginfo_weechat_bar_item_update arginfo_weechat_plugin_get_name

#define arginfo_weechat_bar_item_remove arginfo_weechat_plugin_get_name

#define arginfo_weechat_bar_search arginfo_weechat_plugin_get_name

#define arginfo_weechat_bar_new arginfo_weechat_list_new

#define arginfo_weechat_bar_set arginfo_weechat_ngettext

#define arginfo_weechat_bar_update arginfo_weechat_plugin_get_name

#define arginfo_weechat_bar_remove arginfo_weechat_plugin_get_name

#define arginfo_weechat_command arginfo_weechat_iconv_to_internal

#define arginfo_weechat_command_options arginfo_weechat_ngettext

#define arginfo_weechat_completion_new arginfo_weechat_plugin_get_name

#define arginfo_weechat_completion_search arginfo_weechat_string_eval_expression

#define arginfo_weechat_completion_get_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_completion_list_add arginfo_weechat_string_eval_expression

#define arginfo_weechat_completion_free arginfo_weechat_plugin_get_name

#define arginfo_weechat_info_get arginfo_weechat_iconv_to_internal

#define arginfo_weechat_info_get_hashtable arginfo_weechat_iconv_to_internal

#define arginfo_weechat_infolist_new arginfo_weechat_list_new

#define arginfo_weechat_infolist_new_item arginfo_weechat_plugin_get_name

#define arginfo_weechat_infolist_new_var_integer arginfo_weechat_ngettext

#define arginfo_weechat_infolist_new_var_string arginfo_weechat_ngettext

#define arginfo_weechat_infolist_new_var_pointer arginfo_weechat_ngettext

#define arginfo_weechat_infolist_new_var_time arginfo_weechat_ngettext

#define arginfo_weechat_infolist_search_var arginfo_weechat_iconv_to_internal

#define arginfo_weechat_infolist_get arginfo_weechat_ngettext

#define arginfo_weechat_infolist_next arginfo_weechat_plugin_get_name

#define arginfo_weechat_infolist_prev arginfo_weechat_plugin_get_name

#define arginfo_weechat_infolist_reset_item_cursor arginfo_weechat_plugin_get_name

#define arginfo_weechat_infolist_fields arginfo_weechat_plugin_get_name

#define arginfo_weechat_infolist_integer arginfo_weechat_iconv_to_internal

#define arginfo_weechat_infolist_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_infolist_pointer arginfo_weechat_iconv_to_internal

#define arginfo_weechat_infolist_time arginfo_weechat_iconv_to_internal

#define arginfo_weechat_infolist_free arginfo_weechat_plugin_get_name

#define arginfo_weechat_hdata_get arginfo_weechat_plugin_get_name

#define arginfo_weechat_hdata_get_var_offset arginfo_weechat_iconv_to_internal

#define arginfo_weechat_hdata_get_var_type_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_hdata_get_var_array_size arginfo_weechat_ngettext

#define arginfo_weechat_hdata_get_var_array_size_string arginfo_weechat_ngettext

#define arginfo_weechat_hdata_get_var_hdata arginfo_weechat_iconv_to_internal

#define arginfo_weechat_hdata_get_list arginfo_weechat_iconv_to_internal

#define arginfo_weechat_hdata_check_pointer arginfo_weechat_ngettext

#define arginfo_weechat_hdata_move arginfo_weechat_ngettext

#define arginfo_weechat_hdata_search arginfo_weechat_register

#define arginfo_weechat_hdata_char arginfo_weechat_ngettext

#define arginfo_weechat_hdata_integer arginfo_weechat_ngettext

#define arginfo_weechat_hdata_long arginfo_weechat_ngettext

#define arginfo_weechat_hdata_string arginfo_weechat_ngettext

#define arginfo_weechat_hdata_pointer arginfo_weechat_ngettext

#define arginfo_weechat_hdata_time arginfo_weechat_ngettext

#define arginfo_weechat_hdata_hashtable arginfo_weechat_ngettext

#define arginfo_weechat_hdata_compare arginfo_weechat_print_y_date_tags

#define arginfo_weechat_hdata_update arginfo_weechat_ngettext

#define arginfo_weechat_hdata_get_string arginfo_weechat_iconv_to_internal

#define arginfo_weechat_upgrade_new arginfo_weechat_ngettext

#define arginfo_weechat_upgrade_write_object arginfo_weechat_ngettext

#define arginfo_weechat_upgrade_read arginfo_weechat_plugin_get_name

#define arginfo_weechat_upgrade_close arginfo_weechat_plugin_get_name

#define arginfo_forget_class arginfo_weechat_plugin_get_name

#define arginfo_forget_function arginfo_weechat_plugin_get_name
