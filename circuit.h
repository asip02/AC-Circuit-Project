#ifndef CIRCUIT_H
#define CIRCUIT_H


#include "components.h"

class circuit
{
    protected:
    std::string name;
    std::complex<double> impedance;
    double frequency;
    double phase_shift;
    std::vector<std::shared_ptr<circuit>> sub_circuits;

    static std::map<std::string, std::shared_ptr<circuit>> circuit_storage;
    
    public:
    //access functions 
    virtual std::complex<double> getimpedance() const{return impedance;}
    virtual double getimpedance_abs() const{return std::abs(impedance);}
    virtual double getphase() const{return phase_shift;}
    virtual double getfrequency(){return frequency;}
    virtual void setfrequency(double f);
    virtual std::string getname(){return name;}
    virtual int getlength(){return static_cast<int>(sub_circuits.size());}

    //Pure Virtual Functions
    virtual void add_subcircuit(std::shared_ptr<circuit> circ) = 0;
    virtual void addcomponents_series(std::vector<std::shared_ptr<component>> input_vec) = 0;
    virtual void addcomponents_parallel(std::vector<std::shared_ptr<component>> input_vec) = 0;
    virtual std::complex<double> calc_impedance() = 0;
    virtual void print_info() = 0;
    virtual void print_circuit() = 0;
    virtual void print_subcircuit_info() = 0;

    //map editting functions 
    static bool checkempty(){return circuit_storage.empty();}
    static bool checklabel_circuit(std::string label);
    static void savecircuit(std::string label, std::shared_ptr<circuit> input_c);
    static std::shared_ptr<circuit> getcircuit(std::string label){return circuit::circuit_storage[label];}
    static void showcircuitlibrary();
};


class circuit_series : public circuit
{
    private:
    std::vector<std::shared_ptr<circuit>> parallel_branches;
    public:
    circuit_series(double input_f){frequency = input_f; name = "series";} 

    std::complex<double> calc_impedance();
    void add_subcircuit(std::shared_ptr<circuit> circ);
    void addcomponents_series(std::vector<std::shared_ptr<component>> input_vec);
    void addcomponents_parallel(std::vector<std::shared_ptr<component>> input_vec);
    void print_info();
    void print_circuit();
    void print_subcircuit_info();
};

class circuit_parallel : public circuit
{
    public:
    circuit_parallel(double input_f){frequency = input_f; name = "parallel";}

    std::complex<double> calc_impedance();

    void add_subcircuit(std::shared_ptr<circuit> circ);
    void addcomponents_series(std::vector<std::shared_ptr<component>> input_vec);
    void addcomponents_parallel(std::vector<std::shared_ptr<component>> input_vec);
    void print_info();
    void print_circuit();
    void print_subcircuit_info();
};


class circuit_single : public circuit
{
    private:
    std::shared_ptr<component> base_component;
    public:
    //constructors
    circuit_single() = default;
    circuit_single(std::shared_ptr<component> base){base_component = base;}
    std::complex<double> calc_impedance(){impedance = base_component->getimpedance(); return impedance;}

    void setfrequency(double f){base_component->setfrequency(f);};
    void add_subcircuit(std::shared_ptr<circuit> circ){return;}
    void addcomponents_series(std::vector<std::shared_ptr<component>> input_vec){return;}
    void addcomponents_parallel(std::vector<std::shared_ptr<component>> input_vec){return;}
    void print_info(){base_component->print_info();}
    void print_subcircuit_info(){
        std::cout <<base_component->getsym()<<std::endl;
        std::cout<<"----------"<<std::endl;
        base_component->print_info();}
    void print_circuit(){std::cout<<"--"<<base_component->getsym() << "--";}
};

#endif