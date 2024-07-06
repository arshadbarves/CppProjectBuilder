#include <iostream>

#include "ProjectGenerator.h"

int main(int argc, char *argv[])
{
    std::cout << "Welcome to CPP Project Builder!" << std::endl;

    std::string project_name;
    std::string version;

    std::cout << "Enter the project name: ";
    std::cin >> project_name;
    std::cout << "Enter the project version: ";
    std::cin >> version;

    std::cout
        << "Project Name: " << project_name << std::endl;
    std::cout << "Version: " << version << std::endl;
    try
    {
        CppProjectBuilder::ProjectGenerator generator(project_name, version);
        generator.GenerateProject();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}