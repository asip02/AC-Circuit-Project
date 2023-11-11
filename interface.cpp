#include "interface.h"

void interface_tree()
{   
    std::cout<<"What would you like to do?"<<std::endl;
    std::cout<<"Pick from the following options and input the corresponding number:"<<std::endl;
    std::cout<<   "1. Create a Component"  <<std::endl;
    std::cout<<   "2. View Stored Components"  <<std::endl;
    std::cout<<   "3. Delete Stored Components"  <<std::endl;
    std::cout<<   "4. Create a Circuit"  <<std::endl;
    std::cout<<   "5. Edit an Existing Circuit"  <<std::endl;
    std::cout<<   "6. View Stored Circuits"  <<std::endl;
    std::cout<<   "7. EXIT PROGRAM"  <<std::endl;

    char choice;
    std::cin>>choice;
    switch(choice){
        case '1':
            std::cout<<"-------------------------------------"<<std::endl;
            create_component();
            std::cout<<"-------------------------------------"<<std::endl;
            interface_tree();
        break;
        case '2':
            std::cout<<"-------------------------------------"<<std::endl;
            component::showcomponentlibrary();
            std::cout<<"-------------------------------------"<<std::endl;
            interface_tree();
            break;
        case '3':
            std::cout<<"-------------------------------------"<<std::endl;
            delete_component();
            std::cout<<"-------------------------------------"<<std::endl;
            interface_tree();
            break;
        case '4':
            std::cout<<"-------------------------------------"<<std::endl;
            create_circuit();
            std::cout<<"-------------------------------------"<<std::endl;
            interface_tree();
            break;
        case '5':
            std::cout<<"-------------------------------------"<<std::endl;
            edit_circuit_tree();
            std::cout<<"-------------------------------------"<<std::endl;
            interface_tree();
            break;
        case '6':
            std::cout<<"-------------------------------------"<<std::endl;
            view_stored_circuits();
            std::cout<<"-------------------------------------"<<std::endl;
            interface_tree();
            break;
        case '7':
            std::cout<<"Saving Stored Components..."<<std::endl;
            component::writeoutcomponents();
            std::cout<<"bye"<<std::endl;
            system("pause");
            exit(1);
        default:
            std::cout<<"Please Input a valid number"<<std::endl;
            std::cin.clear();
            interface_tree();
    }
}

//--------------------------------------------Option 1---------------------------------------------//
void create_component()
{
        char component_choice = 0;
    std::cout<<"Choose What Component to Create(Input the Corresponding Letter):"<<std::endl;
    std::cout<<"R:Resistor"<<std::endl;
    std::cout<<"C:Capacitor"<<std::endl;
    std::cout<<"L:Inductor"<<std::endl;
    std::cin>>component_choice;

    std::string choice_name;
    std::string choice_units;
    
    if(component_choice != 'R' && component_choice != 'C' && component_choice != 'L'){
        std::cout<<"Invalid Input. Try again"<<std::endl;
        create_component();
    }

    double characteristic_value;
    
    switch(component_choice){
        case 'R':
            std::cout<<"Input Resistance(up to 10^6 Ohms):";
            choice_name = "Resistor";
            choice_units = "Ohms";
            characteristic_value = get_input_double(0, 1e6);
            break;
        case 'C':
            std::cout<<"Input Capacitance(up to 10^-3 Farads):";
            choice_name = "Capacitor";
            choice_units = "F";
            characteristic_value = get_input_double(0, 1e-3);
            break;
        case 'L':
            std::cout<<"Input Inductance(up to 10^-1 Henry):";
            choice_name = "Inductor";
            choice_units = "H";
            characteristic_value = get_input_double(0, 0.1);
            break;
    }


    std::cout<<"Input a label for your component:";
    std::string label = input_label_component();

    std::cout<<"You are creating a "<<choice_name<<" with "<<component_choice<<" = "<<characteristic_value<<" "<<choice_units<< " with Label: "<<label<<std::endl;

    std::cout<<"confirm (Y/N):";
    bool confirmation = yes_or_no();

    if(confirmation == false){
        std::cout<<"Exiting Component Creator"<<std::endl;
    }else{
        switch(component_choice){
            case 'R':
                component::storecomponent(label, std::make_shared<resistor>(resistor(characteristic_value)));
                std::cout<<"Resistor with label:"<<label<<" created"<<std::endl;
                std::cout<<"Exiting Component Creator"<<std::endl;
                break;
            case 'C':
                component::storecomponent(label, std::make_shared<capacitor>(capacitor(characteristic_value, 100)));
                std::cout<<"Capacitor with label:"<<label<<" created"<<std::endl;
                std::cout<<"Exiting Component Creator"<<std::endl;
                break;
            case 'L':
                component::storecomponent(label, std::make_shared<inductor>(inductor(characteristic_value, 100)));
                std::cout<<"Inductor with label:"<<label<<" created"<<std::endl;
                std::cout<<"Exiting Component Creator"<<std::endl;
                break;
        }
    }
}

//--------------------------------------------Option 2---------------------------------------------//
//used a static component member function for this part 
//--------------------------------------------Option 3---------------------------------------------//
void delete_component()
{
    if(component::checkempty()){std::cout<<"No Components Currently Stored"<<std::endl;return;}
    std::cout<<"You Currently have the following Components Stored"<<std::endl;
    component::showcomponentlibrary();

    std::cout<<"Input the Label of the Component you Want to delete:";
    std::string label = check_label_exists_component();
    component::deletecomponent(label);
    std::cout<<"Component "<< label <<" Destroyed"<<std::endl;
    std::cout<<"Would you like to delete more components(Y/N):";
    bool deleting = yes_or_no();
    if(deleting){delete_component();}
}
//--------------------------------------------Option 4---------------------------------------------//
void create_circuit()
{
    std::cout<<"Would you like the Base Circuit to be Series or Parallel?"<<std::endl;
    std::cout<<"1. Series"<<std::endl;
    std::cout<<"2. Parallel"<<std::endl;

    std::string type_string;
    char user_input;
    std::cin>>user_input;

    switch(user_input){
        case '1':
            type_string = "series";
            std::cin.clear();
            break;
        case '2':
            type_string = "parallel";
            std::cin.clear();
            break;
        default:
            std::cout<<"Invalid Input";
            std::cin.clear();
            create_circuit();
    }

    std::cout<<"Input a Signal Frequency(Hz):";
    double input_f = get_input_double();

    std::cout<<"Input a Label for your new Circuit:";
    std::string label = input_label_circuit();

    switch(user_input)
    {
        case '1':
            circuit::savecircuit(label ,std::make_shared<circuit_series>(circuit_series(input_f)));
            std::cout<<"Series Circuit Created"<<std::endl;
            break;
            circuit::savecircuit(label ,std::make_shared<circuit_series>(circuit_series(input_f)));
        case '2':
            circuit::savecircuit(label ,std::make_shared<circuit_parallel>(circuit_parallel(input_f)));
            std::cout<<"Parallel Circuit Created"<<std::endl;
            break;
    }

    std::cout<<"Would you like to add Components to this Circuit(Y/N)?";
    bool addcomponents = yes_or_no();
    if(addcomponents){add_existing_components(circuit::getcircuit(label));}
}
//--------------------------------------------Option 5---------------------------------------------//
void edit_circuit_tree()
{
    if(circuit::checkempty()){std::cout<<"No Circuits Stored."<<std::endl; return;}
    std::cout<<"Pick a Circuit to Edit"<<std::endl;
    circuit::showcircuitlibrary();
    std::cout<<"Type the label of the circuit you'd like to edit:";
    std::string label_input = check_label_exists_circuit();

    std::string circuit_type = circuit::getcircuit(label_input)->getname();

    if(circuit_type == "series"){edit_series_circuit(circuit::getcircuit(label_input));}
   else if(circuit_type == "parallel"){edit_parallel_circuit(circuit::getcircuit(label_input));}
}

void edit_series_circuit(std::shared_ptr<circuit> circ)
{
    std::cout<<"What would you like to do?"<<std::endl;

    std::cout << "1. Add more components in series" <<std::endl;
    std::cout << "2. Add a Nested Circuit" <<std::endl;
    std::cout << "3. Add a parallel branch" <<std::endl;
    std::cout << "4. Update Circuit Frequency" <<std::endl;

    char user_choice;
    std::cin>>user_choice;

    double input_f;
    
    switch(user_choice){
        case '1':
            std::cin.clear();
            std::cout<<"-------------------------------------"<<std::endl;
            add_existing_components(circ);
            std::cout<<"-------------------------------------"<<std::endl;
            break;
        case '2':
            std::cout<<"-------------------------------------"<<std::endl;
            add_nested_circuit(circ);
            break;
            std::cout<<"-------------------------------------"<<std::endl;
        case '3':
            std::cin.clear();
            std::cout<<"-------------------------------------"<<std::endl;
            add_parallel_branch(circ);
            std::cout<<"-------------------------------------"<<std::endl;
            break;
        case '4':
            std::cout<<"-------------------------------------"<<std::endl;
            std::cout<<"Current Frequency:" << circ->getfrequency()<<std::endl;
            std::cout<<"Input New Frequency:";
            input_f = get_input_double();
            circ->setfrequency(input_f);
            std::cout<<"-------------------------------------"<<std::endl;
            break;
        default:
            std::cout<<"Invalid Input. Please Choose one of the options above:";
            std::cin.clear();
            edit_series_circuit(circ);
    }
}

void add_parallel_branch(std::shared_ptr<circuit> circ)
{
    std::vector<std::shared_ptr<component>> temp;
    std::cout<<"Choose Which Components to Add to the New Branch"<< std::endl;
    component::showcomponentlibrary();
    bool adding = true; 
    while(adding){
        std::cout<<"Input Label:"<<std::endl;
        std::string label_input = check_label_exists_component();
        temp.push_back(component::getcomponent(label_input));
        std::cout<<"Would you like to add more components to this branch(Y/N)?";
        adding = yes_or_no();
    }
    circ->addcomponents_parallel(temp);
    std::cout<<"New Branch Added"<<std::endl;
}

void edit_parallel_circuit(std::shared_ptr<circuit> circ)
{
    std::cout<<"What would you like to do?"<<std::endl;

    std::cout << "1. Add a parallel branch" <<std::endl;
    std::cout << "2. Add a Nested Circuit" <<std::endl;
    std::cout << "3. Update Circuit Frequency" <<std::endl;
    char user_choice;
    std::cin>>user_choice;

    double input_f;

    switch(user_choice){
        case '1':
            add_existing_components(circ);
            break;
        case '2':
            add_nested_circuit(circ);
            break;
        case '3':
            std::cout<<"Current Frequency:"<<circ->getfrequency()<<" Hz"<<std::endl;
            std::cout<<"Input New Frequency:";
            input_f = get_input_double();
            circ->setfrequency(input_f);
            break;
        default:
            std::cout<<"Invalid Input. Please Choose one of the options:";
            std::cin.clear();
            edit_parallel_circuit(circ);
            break;
    }
}


void add_existing_components(std::shared_ptr<circuit> circ)
{
    if(component::checkempty()){std::cout<<"No Components Stored"<<std::endl; return;}
    std::cout<<"You have the following Components stored"<<std::endl;
    component::showcomponentlibrary();
    bool adding = true;
    std::vector<std::shared_ptr<component>> input_comps;
    std::string input_label;

    if(circ->getname() == "parallel"){
        std::cout<<"You are editting a Parallel Circuit:"<<std::endl;
        std::cout<<"How many Parallel Branches would you like to add:"<<std::endl;
        double branches = get_input_double();

        for(int i=1;i<=branches;i++){
            std::cout<<"Adding to Branch"<<i<<":"<<std::endl;
            adding = true;
            while(adding){
            std::cout<<"Input Component Label:";
            std::string input_label = check_label_exists_component();
            component::getcomponent(input_label)->setfrequency(circ->getfrequency());
            input_comps.push_back(component::getcomponent(input_label));
            std::cout<<"Would you like to add more components to this Branch(Y/N):";
            adding = yes_or_no();
            }
            circ->addcomponents_series(input_comps);
            input_comps.clear();
        }
    }else if(circ->getname() == "series"){
        std::cout<<"You are editting a Series Circuit:"<<std::endl;
        bool adding = true;
        while(adding){
            std::cout<<"Input Component Label:";
            input_label = check_label_exists_component();
            input_comps.push_back(component::getcomponent(input_label));
            std::cout<<"Would you like to add more components(Y/N):";
            adding = yes_or_no();
        }
        circ->addcomponents_series(input_comps);
    }
}

void add_nested_circuit(std::shared_ptr<circuit> circ)
{
    if(circuit::checkempty()){std::cout<<"You have no Circuits Stored to Add"<<std::endl;return;}
    std::cout<<"You have the following Circuits stored:"<<std::endl;
    circuit::showcircuitlibrary();
    std::cout<<"Input Label:";
    std::string label = check_label_exists_circuit();
    circ->add_subcircuit(circuit::getcircuit(label));
}

//--------------------------------------------Option 6---------------------------------------------//
//used a static class function to view the map

void view_stored_circuits()
{
    if(circuit::checkempty()){std::cout<<"No circuits currently stored"<<std::endl; return;}
    circuit::showcircuitlibrary();

    std::cout<<"Which circuit would you like to display(Input Label):";
    std::string label = check_label_exists_circuit();
    circuit::getcircuit(label)->print_info();
    circuit::getcircuit(label)->print_circuit();
    circuit::getcircuit(label)->print_subcircuit_info();
}


//--------------------------------------------Input Validation---------------------------------------------//
bool yes_or_no()
{
    bool output;
    char choice;
    std::cin>>choice;
    switch (choice){
    case 'Y':
        output = true;
        break;
    case 'N':
        output = false;
        break;
    default:
        std::cout<<"Invalid. Enter Y/N:"<<std::endl;
        std::cin.clear();
        output = yes_or_no();
        break;
    }
    return output;
}

double get_input_double()
{
    std::string temp;
    double output;
    std::cin>>temp;
    try{
        output = std::stod(temp);
        if(output <= 0){
            std::cout<<"Invalid Input. Please enter a positive Double Value"<<std::endl;
            std::cin.clear();
            output = get_input_double();
        }
    } catch(std::invalid_argument) {
        std::cin.clear();
        std::cout<<"Invalid Input. Please enter a Positive Double Value"<<std::endl;
        output = get_input_double();
    }
    std::cin.clear();
    return output;
}

double get_input_double(double limit_l, double limit_u)
{
    std::string temp;
    double output;
    std::cin>>temp;
    try{
        output = std::stod(temp);
        if(output <= limit_l || output > limit_u){
            std::cout<<"Invalid Input. Please enter a positive Double Value between "
            << limit_l<<"and "<< limit_u <<std::endl;
            std::cin.clear();
            output = get_input_double();
        }
    } catch(std::invalid_argument) {
        std::cin.clear();
        std::cout<<"Invalid Input. Please enter a Positive Double Value"<<std::endl;
        output = get_input_double();
    }
    std::cin.clear();
    return output;
}

std::string input_label_component()
{
    std::string input; 
    std::cin>>input;
    bool label_used = component::checklabel_component(input);
    if(label_used){
        std::cout<<"Invalid. Label Already in Use. Input a New Label:"<<std::endl;
        std::cin.clear();
        input = input_label_component();
    }
    return input;
}

std::string check_label_exists_component()
{
    std::string temp;
    std::cin>>temp;
    bool check = component::checklabel_component(temp);
    if(!check){
        std::cout<<"Label Does Not Exist. Try again:";
        std::cin.clear();
        temp = check_label_exists_component();
    }
    return temp;
}

std::string input_label_circuit()
{
    std::string input; 
    std::cin>>input;
    bool label_used = circuit::checklabel_circuit(input);
    if(label_used){
        std::cout<<"Invalid. Label Already in Use. Input a New Label:"<<std::endl;
        std::cin.clear();
        input = input_label_circuit();
    }
    return input;
}

std::string check_label_exists_circuit()
{
        std::string temp;
    std::cin>>temp;
    bool check = circuit::checklabel_circuit(temp);
    if(!check){
        std::cout<<"Label Does Not Exist. Try again:";
        std::cin.clear();
        temp = check_label_exists_circuit();
    }
    return temp;
}

