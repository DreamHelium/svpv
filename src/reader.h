#ifndef DH_SVPV_READER_H
#define DH_SVPV_READER_H

#include <tinyxml2.h>
#include <string>
#include <vector>

std::string dh_svpv_reader_get_type(tinyxml2::XMLNode* node);
std::string dh_svpv_reader_title_string(tinyxml2::XMLNode* node);

std::string dh_svpv_reader_node_string(tinyxml2::XMLNode* node);
std::vector<tinyxml2::XMLNode*> dh_svpv_get_child(tinyxml2::XMLNode* node);
void dh_svpv_output_reader(tinyxml2::XMLNode* node);

#endif /* DH_SVPV_READER_H */
