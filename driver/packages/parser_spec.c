#include "spec.h"

void parse_init();
void parse_refresh();
mixed parse_sentence(string, void | int);
void parse_add_rule(string, string);
void parse_add_synonym(string, string, void | string);
string parse_dump();
mixed parse_my_rules(object, string, void | int);
