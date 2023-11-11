#include "components.h"

std::map<std::string, std::shared_ptr<component>> component::component_storage;


//----------------Resistor--------------//

resistor::resistor(double r) // parameterised constructor
{
    resistance = r;
    impedance = calc_impedance();
    frequency = 0;
    name = "Resistor";  
    symbol = 'R';  
}

void resistor::print_info()
{
    std::cout<<"Resistance = "<<resistance<<" Ohms"<<std::endl;
}
//-------------------------Capacitor--------------------//

capacitor::capacitor(double c, double f)
{
    capacitance = c;
    frequency = f;
    impedance = calc_impedance();
    phase_shift = std::arg(impedance);
    name = "Capacitor";
    symbol = 'C';
}

void capacitor::print_info()
{
    char sign = (impedance.imag() >= 0) ? '+':'-';

    std::cout << "Capacitance = " << capacitance << " F" << std::endl;
    std::cout << "Frequency = " << frequency << std::endl;
    std::cout << "Z = " << impedance.real() << sign << abs(impedance.imag())<<" Ohms" << std::endl;
    std::cout << "|Z| = "  << (*this).getimpedance_abs() << " Ohms" << std::endl;  
    std::cout << "Phase Shift = "<<phase_shift<<std::endl;
}

//----------------------------------Inductor-----------------------------------//

inductor::inductor(double l, double f)
{
    inductance = l;
    frequency = f;
    impedance = calc_impedance();
    phase_shift = std::arg<double>(impedance);
    name = "Inductor";
    symbol = 'L';
}

void inductor::print_info()
{
    char sign = (impedance.imag() >= 0) ? '+':'-';

    std::cout << "Inductance = " << inductance << " H" << std::endl;
    std::cout << "Frequency = " << frequency << " Hz" << std::endl;
    std::cout << "Impedance = " << impedance.real() << sign << abs(impedance.imag()) << " Ohms" << std::endl;
    std::cout << "|Impedance| = "  << (*this).getimpedance_abs() << " Ohms" << std::endl;
    std::cout << "Phase Shift = "<<phase_shift<<std::endl;
}


//----------------------------------Map Editting-----------------------------------//


void component::storecomponent(std::string label, std::shared_ptr<component> input_c)
{
    component_storage[label] = input_c;
    std::cout <<"Component created"<<std::endl ;
}


bool component::checklabel_component(std::string label)
{
    //function outputs false if label has not been used yet and true if it has 
    bool output;
    if(component_storage.count(label) == 0){output = false;}
    else{output = true;}
    return output;
}

void component::showcomponentlibrary()
{
    if(component_storage.empty()){std::cout<<"No Components Currently Stored."<<std::endl; return;}
    for(std::map<std::string, std::shared_ptr<component>>::iterator it = component_storage.begin(); it != component_storage.end();it++){
        std::cout<<"------------------------"<<std::endl;
        std::cout << "Label:" << it->first << std::endl;
        std::cout<<"Properties:"<<std::endl;
        it->second->print_info();
        std::cout<<"------------------------"<<std::endl;
    }
}

void component::readincomponents()
{
    std::fstream file;
    file.open("storedcomponents.dat");
    if(!file){std::cout<<"No Previous Components Found"<<std::endl;;return;}
    std::cout<<"Loading Stored Components...."<<std::endl;

    std::string label;
    char symbol;
    double value;
    std::string line;

    while(!file.eof()){
        getline(file, line);
        std::stringstream line_stream(line);
        line_stream >> label;
        line_stream >> symbol;
        line_stream >> value;

        switch(symbol){
            case 'R':
                component_storage[label] = std::make_shared<resistor>(resistor(value));
                break;
            case 'C':
                component_storage[label] = std::make_shared<capacitor>(capacitor(value, 100));
                break;
            case 'L':
                component_storage[label] = std::make_shared<inductor>(inductor(value, 100));
                break;
        }
    }

    file.close();
    if(checkempty()){std::cout<<"No Previous Components Found"<<std::endl;}

}

void component::writeoutcomponents()
{
    std::ofstream file("storedcomponents.dat");

    for(std::map<std::string, std::shared_ptr<component>>::iterator it = component_storage.begin(); it != component_storage.end();it++){
        file << it->first <<" " << it->second->getsym() << " " << it->second->get_characteristic_value() << std::endl;
    }

    file.close();
}