#include <iostream>
#include <string>
#include <set>

using namespace std;

std::set<std::string> cadenas;
int main()
{    
    string componentes;
    string problema;
    for (int i = 0; i < 3; i++)
    {
        getline(std::cin, componentes);
        cadenas.insert(componentes);
    }   
    getline(std::cin, problema);

    // problema = "abbcabcddacbdcaaac";
    
    return 0;
}