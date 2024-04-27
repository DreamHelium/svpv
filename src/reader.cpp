#include "reader.h"
#include <dh_validator.h>
#include <tinyxml2.h>
#include <iostream>

std::string dh_svpv_reader_get_type(tinyxml2::XMLNode* node)
{
    /* determine node type */
    std::string node_type;
    if(node->ToComment())
        node_type = "comment";
    else if (node->ToDeclaration())
        node_type = "declaration";
    else if (node->ToDocument())
        node_type = "document";
    else if (node->ToElement())
        node_type = "element";
    else if (node->ToText())
        node_type = "text";
    else node_type = "unknown";
    return node_type;
}

std::string dh_svpv_reader_title_string(tinyxml2::XMLNode* node)
{
    if(!node)
        return std::string("Not a valid node!");
    else
    {
        std::string value = node->Value() == nullptr ? "null" : node->Value();
        std::string node_type = dh_svpv_reader_get_type(node);
        std::string ret = "The node type [" + node_type + "] has value \"" + value + "\".";
        return ret;
    }
}

std::string dh_svpv_reader_node_string(tinyxml2::XMLNode* node)
{
    if(!node)
        return "???";
    else
    {
        std::string value = node->Value() == nullptr ? "null" : node->Value();
        std::string ret = "[" + dh_svpv_reader_get_type(node) + "] " + value;
        return ret;
    }
}

std::vector<tinyxml2::XMLNode*> dh_svpv_get_child(tinyxml2::XMLNode* node)
{
    std::vector<tinyxml2::XMLNode*> list;
    if(!node || node->NoChildren())
        return list;

    tinyxml2::XMLNode* child = node->FirstChild();
    while(child)
    {
        list.push_back(child);
        child = child->NextSibling();
    }
    return list;
}

void dh_svpv_output_reader(tinyxml2::XMLNode* node)
{
    while(true)
    {
        std::system("clear");
        std::cout << dh_svpv_reader_title_string(node) << std::endl;
        std::vector<tinyxml2::XMLNode*> list = dh_svpv_get_child(node);

        std::cout << std::endl;
        std::cout << "The child has value:\n";
        int i = 0;
        for(tinyxml2::XMLNode* node : list)
        {
            std::cout << "[" << i << "] " << dh_svpv_reader_node_string(node) << std::endl;
            i++;
        }
        std::cout << std::endl;

        DhIntValidator* validator = dh_int_validator_new(0, list.size()-1);
        DhArgInfo* arg = dh_arg_info_new();
        dh_arg_info_add_arg(arg, 'p', "parent", "To parent node.");
        dh_arg_info_add_arg(arg, 'q', "quit", "Quit application");

        DhOut* out = dh_out_new();
        GValue val;
        dh_out_read_and_output(out, "Please enter a number or an option: ", "", arg, DH_VALIDATOR(validator), false, &val);
        if(G_VALUE_HOLDS_INT64(&val))
            node = list[g_value_get_int64(&val)];
        else if(G_VALUE_HOLDS_CHAR(&val))
        {
            char val_c = g_value_get_schar(&val);
            if(val_c == 'p')
            {
                if(node->Parent())
                    node = node->Parent();
            }
            else
            {
                g_object_unref(out);
                g_object_unref(validator);
                g_object_unref(arg);
                break;
            }
        }
        g_object_unref(out);
        g_object_unref(validator);
        g_object_unref(arg);
    }
}
