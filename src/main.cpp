#include <cstdint>
#include <tinyxml2.h>
#include <dh_validator.h>
#include <dhutil.h>
#include <iostream>
#include <string>
#include "reader.h"

using namespace tinyxml2;

static std::string path;

static int internal_strcmp(gconstpointer a, gconstpointer b)
{
    return strcmp((const char*)a, (const char*)b);
}

static GList* find_save()
{
#ifdef G_OS_WIN32
    path = g_getenv("APPDATA");
#else
    path = g_get_user_config_dir();
#endif
    path += "/StardewValley/Saves/";
    GList* dir_list = dh_file_list_create(path.c_str());
    GList* vdf_file = g_list_find_custom(dir_list, "steam_autocloud.vdf", internal_strcmp);
    free(vdf_file->data);
    dir_list = g_list_remove(dir_list, vdf_file->data);
    return dir_list;
}

int main()
{
    GList* dir_list = find_save();
    std::cout << "There are " << g_list_length(dir_list) << " saves:" << std::endl;
    for(int i = 0 ; i < g_list_length(dir_list) ; i++)
        std::cout << "[" << i << "] " << (char*)g_list_nth_data(dir_list, i) << std::endl;

    DhUIntValidator* validator = dh_uint_validator_new(0, g_list_length(dir_list) - 1);
    DhArgInfo* arg = dh_arg_info_new();
    dh_arg_info_add_arg(arg, 'q', "quit", "Quit application");
    DhOut* out = dh_out_new();
    GValue ret;
    dh_out_read_and_output(out, "Please enter a number or option: ", "svpv", arg, DH_VALIDATOR(validator), false, &ret);
    if(G_VALUE_HOLDS_UINT64(&ret))
    {
        uint64_t val = g_value_get_uint64(&ret);
        g_object_unref(validator);
        g_object_unref(arg);
        g_object_unref(out);
        path += (char*)g_list_nth_data(dir_list, val);
        path += "/";
        path += (char*)g_list_nth_data(dir_list, val);
        g_list_free_full(dir_list, free);
    }
    else
    {
        g_object_unref(validator);
        g_object_unref(arg);
        g_object_unref(out);
        g_list_free_full(dir_list, free);
        return 0;
    }

    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    XMLNode* node = &doc;

    dh_svpv_output_reader(node);

    return 0;
}
