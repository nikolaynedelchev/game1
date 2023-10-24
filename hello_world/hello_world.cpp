#include <dd.h>
#include "resource_loader.h"

dd::engine engine;
using namespace std;

namespace DimankaSpace
{
    struct Rect
    {
        int x;
        int y;
        int width;
        int height;
    };

    void PrintTermsOfConditions()
    {
        dd::println("Terms of Conditions .. Frogger");
        dd::println("Use this software on your ....");
        dd::println("Copyrights");
    }
};


namespace TatiNames
{
    struct Rect
    {
        int width;
        int height;
    };
};




struct Person
{
    int age = 0;
    string name = "";
    int height = 0;
    int weight = 0;
    void Print()
    {
        dd::println("-----");
        dd::println("Name: {}", name);
        dd::println("Age: {}", age);
        dd::println("Height: {}", height);
        dd::println("Weight: {}", weight);
    }
};



void PrintPerson(Person person)
{
    dd::println("-----");
    dd::println("Name: {}", person.name);
    dd::println("Age: {}", person.age);
    dd::println("Height: {}", person.height);
    dd::println("Weight: {}", person.weight);
}

bool IsTeenager(Person person)
{
    if (person.age >= 13 && person.age <= 19)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    dd::println("======= PROGRAM START =======");

    DimankaSpace::PrintTermsOfConditions();

    Person dimana;
    dimana.name = "Dimana Dimitrova";
    dimana.age = 15;
    dimana.height = 167;
    dimana.weight = 59;
    PrintPerson(dimana);

    Person tati;
    tati.name = "Nikolay Nedelchev";
    tati.age = 44;
    tati.height = 180;
    tati.weight = 95;
    PrintPerson(tati);

    dimana.Print();

    int i = 5;
    if (i == 5)
    {
        dd::println("Hello World, i is equal to five!, {}", dimana.name);
        DimankaSpace::PrintTermsOfConditions();
    }
    else if(i == 6)
    {
        dd::println("Hello World, i is equal to six!, {}", dimana.height);
    }
    else
    {
        dd::println("Hello World, i is not equal to five neither six!, {}", dimana.weight);
    }

    if (IsTeenager(tati))
    {
        dd::println("{} is not allowed because he/she is a teenager, she is {} years old", dimana.name, dimana.age);
    }
    else
    {
        dd::println("Poor old {}, he is {} years old", tati.name, tati.age);
    }

    dd::println("======= PROGRAM END =======");
    return 0;
}
