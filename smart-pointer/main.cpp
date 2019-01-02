#include <iostream> 
#include <memory>
#include <vector> 
#include <string> 
#include "share_ptr_example.h" 

void a_example(){
    std::shared_ptr<std::string> pNico(new std::string("nico"));
    std::shared_ptr<std::string> pJutta(new std::string("jutta"));

    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "JJ");

    std::vector<std::shared_ptr<std::string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);

    for (const auto& ptr : whoMadeCoffee) { 
        std::cout<< *ptr << "    ";
    } 
    std::cout<<std::endl;

    *pNico = "Nicolai";

    for (auto& ptr : whoMadeCoffee) { 
        std::cout<< *ptr << "    ";
    } 
    std::cout<<std::endl;

    
    std::cout<< "use_count: " << whoMadeCoffee[0].use_count() << std::endl;
    std::cout<< "use_count: " << pJutta.use_count() << std::endl;
    std::cout<< "use_count: " << whoMadeCoffee[2].use_count() << std::endl;
    std::cout<< "use_count: " << pNico.use_count() << std::endl;
    
    std::shared_ptr<std::string> pAAA(new std::string("nico"),
                                 [](std::string* p) {
                                    std::cout<< "delete: " << p << "," << *p <<std::endl;
                                    delete p;
                                 });

    pAAA = nullptr;
    std::cout<< "hello, world" <<std::endl;
}

int main (int argc, char* argv[])
{
    a_example();
    test_shared_ptr();
    test_weak_ptr();
    test_unique_ptr();
    return 0;//0 means OK
}

