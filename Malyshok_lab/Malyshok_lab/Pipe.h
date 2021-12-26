#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Pipe
{
    static int MaxID;
    int id;
    std::string name;
    double length;
    double diameter;
    bool in_process;
public:
    Pipe();
    double getLen() const { return length; }
    double getDia()const { return diameter; }
    static void setMaxID(const int id) { MaxID = id;}
    bool getProc() const { return in_process; }
    static int getMaxID() { return MaxID; }
    std::string getName() const { return name; }
    double getCapacity() const { return  round(10000 * 0.384 * sqrt(pow(double(diameter) / 1000, 5) / length)); }
    int getId() { return id; }
    int in, out;
    void link(int myin, int myout);
    void untie();
    void edit();
    bool linked() const;
    bool CanBeUsed() const;
    void showLink(int id) const;
    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
    friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);
};

