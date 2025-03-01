#include "libstrings.hpp"
#include "libtile.hpp"
#include <experimental/reflect>
struct A{
    int a;
    int b;
};
using meta_S = reflexpr(A);
int main(int argc, const char ** argv){
    
}