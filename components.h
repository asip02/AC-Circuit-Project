#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <complex>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>


//------------------------------------Base Class------------------------------------//

class component
{
    protected:
    std::string name;
    std::complex<double> impedance;
    double frequency;
    double phase_shift;
    char symbol;

    static std::map<std::string, std::shared_ptr<component>> component_storage;
    
    public:
    //Pure virtual functions 
    virtual std::complex<double> calc_impedance() = 0;
    virtual void print_info() = 0;
    virtual double get_characteristic_value() = 0;
    //Access Functions
    virtual std::string getname(){return name;}
    virtual char getsym(){return symbol;}
    virtual std::complex<double> getimpedance() const{return impedance;}
    virtual double getimpedance_abs() const{return std::abs(impedance);}
    virtual double getphase() const{return phase_shift;}
    //Updating Class Members
    virtual void setfrequency(double f){frequency = f; update_class_members();}
    virtual void update_class_members(){impedance = calc_impedance(); phase_shift = std::arg(impedance);}

    //static functions relating to map
    static bool checkempty() {if (component_storage.empty()){return true;}else{return false;}}
    static void storecomponent(std::string label, std::shared_ptr<component> input_c);
    static std::shared_ptr<component> getcomponent(std::string label){return component::component_storage[label];}
    static void showcomponentlibrary();
    static void deletecomponent(std::string label){component_storage.erase(label);};
    static bool checklabel_component(std::string label);
    static void readincomponents();
    static void writeoutcomponents(); //Function to write all the saved components to an external text file 
};

//------------------------------------Resistor------------------------------------//

class resistor : public component
{
    private:
    double resistance;
    public:
    //constructors
    resistor() = default; //default constructor 
    resistor(double r); // parameterised constructor
    //redefining virtual functions
    std::complex<double> calc_impedance(){impedance = std::complex<double>(resistance,0);phase_shift=std::arg(impedance); return impedance;}
    void print_info();
    double get_characteristic_value(){return resistance;}
    //defining class functions
    double getresistance(){return resistance;}

};

//------------------------------------Capacitor------------------------------------//

class capacitor : public component
{
    private:
    double capacitance;
    public:
    //constructors 
    capacitor() = default; //default constructor 
    capacitor(double c, double f); // parameterised constructor 
    //redefining virtual functions
    std::complex<double> calc_impedance(){impedance = std::complex<double>(0,1/(frequency*capacitance));phase_shift=std::arg(impedance);return impedance;}
    void print_info();
    //class functions
    double get_characteristic_value(){return capacitance;}
    double getcapacitance(){return capacitance;}

};

//----------------------------------Inductor-----------------------------------//

class inductor : public component
{
    private:
    double inductance;
    public:
    //constructors 
    inductor() = default; //default constructor
    inductor(double l, double f);//parameterised constructor
    //redefining virtual functions 
    std::complex<double> calc_impedance(){impedance = std::complex<double>(0,frequency*inductance);phase_shift=std::arg(impedance);return impedance;}
    double get_characteristic_value(){return inductance;}
    void print_info();
    //class functions
    double getinductance(){return inductance;}
};

#endif