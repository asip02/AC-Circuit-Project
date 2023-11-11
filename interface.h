#ifndef INTERFRACE_H
#define INTERFACE_H

#include "circuit.h"

void interface_tree();
//Interface_tree gives user a range of options and the functions relating to these are presented below

//Option 1
void create_component();
//Option 2
//Used Static component Member function for this
//Option 3
void delete_component();
//Option 4
void create_circuit();
//Option 5
void edit_circuit_tree();
void edit_series_circuit(std::shared_ptr<circuit> circ);
void add_parallel_branch(std::shared_ptr<circuit> circ);
void edit_parallel_circuit(std::shared_ptr<circuit> circ);
void add_existing_components(std::shared_ptr<circuit> circ);
void add_nested_circuit(std::shared_ptr<circuit> circ);
//Option 6
void view_stored_circuits();
//Input Validation
bool yes_or_no();
double get_input_double();
double get_input_double(double limit_l, double limit_u);
std::string input_label_component();
std::string check_label_exists_component();
std::string input_label_circuit();
std::string check_label_exists_circuit();






















#endif