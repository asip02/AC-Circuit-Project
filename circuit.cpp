#include "circuit.h"


std::map<std::string, std::shared_ptr<circuit>> circuit::circuit_storage;

//--------------------Base-----------------------//
void circuit::setfrequency(double f)
{
    frequency = f;
    for(auto sub_circ : sub_circuits){
        sub_circ->setfrequency(f);
    }
}

//--------------------Series-----------------------//

std::complex<double> circuit_series::calc_impedance()
{
    std::complex<double> output(0,0);
    if(sub_circuits.empty()){return output;}
    for(auto circ : sub_circuits){output += circ->calc_impedance();}
    //If parallel branches have been added to a base series the impedance calculation is accordingly modified
    if(!parallel_branches.empty()){
        output = pow(output, -1);
        for(auto circ:parallel_branches){
            output += pow(circ->calc_impedance(), -1);
        }
        output = pow(output,-1);
    }
    impedance = output;
    return output;
}

void circuit_series::add_subcircuit(std::shared_ptr<circuit> circ)
{
    circ->setfrequency(frequency);
    sub_circuits.push_back(circ); 
    impedance = calc_impedance();
    phase_shift = std::arg(impedance);
}

void circuit_series::addcomponents_series(std::vector<std::shared_ptr<component>> input_vec)
{
    for(std::shared_ptr<component> comp : input_vec){
        comp->setfrequency(frequency);
        sub_circuits.push_back(std::make_shared<circuit_single>(circuit_single(comp)));
    }

    impedance = calc_impedance();
    phase_shift = std::arg(impedance);
}

void circuit_series::addcomponents_parallel(std::vector<std::shared_ptr<component>> input_vec)
{
    std::shared_ptr<circuit_parallel> temp = std::make_shared<circuit_parallel>(circuit_parallel(frequency));
    temp->addcomponents_series(input_vec);
    parallel_branches.push_back(temp);
    impedance = calc_impedance();
    phase_shift = std::arg(impedance);
}

void circuit_series::print_info()
{
    std::cout << "Series Circuit:"<<std::endl;
    impedance = calc_impedance();
    phase_shift = std::arg(impedance);
    std::cout << "Z:" << impedance<<" Ohms " << "|Z|:"<< getimpedance_abs()<< " Ohms"<< std::endl; 
    std::cout << "Frequency:"<<frequency<< " Hz Phase Shift:"<<phase_shift<<std::endl; 

}

void circuit_series::print_circuit()
{
    if(!parallel_branches.empty()){
        for(int i=0;i< parallel_branches.size();i++){
            std::cout<<"Branch:" << i+1<<std::endl;
            parallel_branches[i]->print_circuit();
        }
    }
    
    std::cout<<"|";
    for(auto circ:sub_circuits){
        circ->print_circuit();
    }
    std::cout<<"|"<<std::endl;

}

void circuit_series::print_subcircuit_info()
{
    if(!parallel_branches.empty()){
        for(auto branch:parallel_branches){
            branch->print_subcircuit_info();
        }
    }
    for(auto circ:sub_circuits){
        circ->print_subcircuit_info();
    }
}

//--------------------Parallel-----------------------//

std::complex<double> circuit_parallel::calc_impedance()
{
    std::complex<double> sum(0,0);
    if(sub_circuits.empty()){return sum;}
    for(auto circ : sub_circuits){sum += pow(circ->calc_impedance(),-1);}
    return pow(sum,-1);
}

void circuit_parallel::add_subcircuit(std::shared_ptr<circuit> circ)
{
    circ->setfrequency(frequency);
    sub_circuits.push_back(circ); 
    impedance = calc_impedance();
}

void circuit_parallel::addcomponents_series(std::vector<std::shared_ptr<component>> input_vec)
{
    std::shared_ptr<circuit_series> temp = std::make_shared<circuit_series>(circuit_series(frequency));
    temp->addcomponents_series(input_vec);
    sub_circuits.push_back(temp);
    impedance = calc_impedance();
}

void circuit_parallel::addcomponents_parallel(std::vector<std::shared_ptr<component>> input_vec)
{
    for(std::shared_ptr<component> comp : input_vec){
        comp->setfrequency(frequency);
        sub_circuits.push_back(std::make_shared<circuit_single>(comp));
    }
    impedance = calc_impedance();
}

void circuit_parallel::print_info()
{
    std::cout << "Parallel Circuit:"<<std::endl;
    impedance = calc_impedance();
    phase_shift = std::arg(impedance);
    std::cout << "Z:" << impedance<<" Ohms " << "|Z|:"<< getimpedance_abs()<< " Ohms Frequency:"<<frequency<< " Hz Phase Shift:"<<phase_shift<<std::endl;
}

void circuit_parallel::print_circuit()
{
    for(int i=0;i<sub_circuits.size();i++){
        std::cout<<"Branch " << (i+1)<<":"<<std::endl;
        sub_circuits[i]->print_circuit();
        std::cout<<"----------------"<<std::endl;     
    }

    for(int i=0;i<sub_circuits.size();i++){
        std::cout<<"Components on Branch "<<i+1<<std::endl;
        sub_circuits[i]->print_info();
    }


}

void circuit_parallel::print_subcircuit_info()
{
    for(auto circ:sub_circuits){
        circ->print_subcircuit_info();
    }
}

//--------------------Map Editting-----------------------//

bool circuit::checklabel_circuit(std::string label)
{
    //function outputs false if label has not been used yet and true if it has 
    bool output;
    if(circuit_storage.count(label) == 0){output = false;}
    else{output = true;}
    return output;
}

void circuit::savecircuit(std::string label, std::shared_ptr<circuit> input_c)
{
    circuit_storage[label] = input_c;
}

void circuit::showcircuitlibrary()
{
    for(std::map<std::string, std::shared_ptr<circuit>>::iterator it = circuit_storage.begin(); it != circuit_storage.end();it++){
        std::cout<<"------------------------"<<std::endl;
        std::cout<<"Label:" << it->first <<" Type:" << it->second->getname()<<std::endl;
        std::cout<<"Frequency:" << it->second->getfrequency()<< " Hz   |Z|:" << it->second->getimpedance_abs()<<" Ohms"<<std::endl;
        std::cout<<"------------------------"<<std::endl;
    }

}