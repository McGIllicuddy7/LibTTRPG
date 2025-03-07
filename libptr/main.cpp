#include "libptr.hpp"
using namespace utils;
#include <iostream>
#include <string>
class Printable{
    public:
    virtual std::string print() =0;
    virtual ~Printable() {
        std::cout <<"destroyed";
    }
};
class String:public Printable{
    public:
    std::string s;
    String(){
    }
    String(std::string st){
        s = st;
    }
    std::string print(){
        return s;
    }
};
int main(){
    Box<String> bx = Box<String>::create("howdy");
    Box<Printable> bx2 = bx;
    Box<Printable> bx3 = bx2;
    bx->s = "hello";
    Box<String> bx4 = bx3;
    std::cout <<(*bx).print()<<" "<<bx2->print()<<" "<<bx3->print()<<bx4->print()<<"\n";
}