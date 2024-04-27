#include <tinyxml2.h>
#include <dh_validator.h>
#include <iostream>
#include "reader.h"

using namespace tinyxml2;

static void print_infomation(void* node)
{

}

static void reader(XMLNode* node)
{

}

int main()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("test.xml");
    XMLNode* node = &doc;

    dh_svpv_output_reader(node);

    return 0;
}
