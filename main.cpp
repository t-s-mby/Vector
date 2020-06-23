#include "vector.h"

int main()
{
    Vector<int> vector(2,5);
    std::cout<<vector.back()<<std::endl;
    vector.resize(8,7);
    //std::cout<<vector.back()<<std::endl;
    int * p = vector.data();
    for(size_t i=0; i<vector.size(); i++)
        std::cout<<p[i]<<' ';
    std::cout<<vector.capacity()<<std::endl;
    vector.insert(2,16,8);
    std::cout<<vector.capacity()<<std::endl;
    int * p2 = vector.data();
    for(size_t i=0; i<vector.size(); i++)
        std::cout<<p2[i]<<' ';
}