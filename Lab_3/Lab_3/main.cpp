//
//  main.cpp
//  Lab_3
//
//  Created by  Николай Фонов on 29.05.2021.
// <

#include <iostream>
#include "Tree_3.hpp"
#include "tests.hpp"

tree3::tree3<int> Input_Tree3(){
    std::cout << "Choose type of input: 1 - input nodes one by one, 2 - input tree with format '<K>(1)[2]{3}', 3 - input tree with your format" << std::endl;
    int type_of_input;
    std::cin >> type_of_input;
    if (type_of_input == 1){
        
        int number_nodes;
        std::cout << "Enter count of nodes in your tree: ";
        std::cin >> number_nodes;
        std::cout << "Enter 1 node: ";
        int fn;
        std::cin >> fn;
        tree3::tree3<int> tree(fn);
        for (int i = 1; i < number_nodes; i++){
            int data;
            std::cout << "Enter '" << i + 1 << "' node: ";
            std::cin >> data;
            tree.Add(data);
        }
        return tree;
    }
    else if (type_of_input == 3){
        std::string format;
        std::cout << "Enter format (EX: <K>(1)[2]{3} ): ";
        std::cin >> format;
        std::string str;
        std::cout << "Enter string: ";
        std::cin >> str;
        tree3::tree3<int> tree(str, format);
        return tree;
    }
    else if (type_of_input == 2){
        std::string str;
        std::cout << "Enter string: ";
        std::cin >> str;
        tree3::tree3<int> tree = tree3::tree3<int>(str, "<K>(1)[2]{3}");
        return tree;
    }
    else{
        std::cout << "Incorrect number!";
        return Input_Tree3();
    }
}


int main() {
    while (true) {
        std::cout << "MENU" << std::endl;
        std::cout << "1 - Create tree" << std::endl << "2 - Launch tests" << std::endl << "3 - Exit" << std::endl << "Entet nuber: ";
        int menu;
        std::cin >> menu;
        
        if (menu == 1){
            std::cout << "Choose type: 1 - integer, ..." << std::endl << "Entet number: ";
            int number_type;
            std::cin >> number_type;
            
            if (number_type == 1){
                tree3::tree3<int> tree = Input_Tree3();// <0>(<12>)[<15>]{<22>}
                while (true) {
                    
                     
                    
                    //std::cout << tree.ToString("<K>(1)[2]{3}") << std::endl;
                    
                    std::cout << "Choose function:" << std::endl << "1 - Add 1 element" << std::endl << "2 - Find element" << std::endl << "3 - Find depth" << std::endl << "4 - Print tree '(Parant child)'" << std::endl << "5 - Print tree in the format <K>(1)[2]{3}" << std::endl << "0 - Exit to menu" << std::endl << "Entet number: ";
                    int function_type;
                    std::cin >> function_type;
                    
                    if (function_type == 1){
                        std::cout << "Input integer number: " << std::endl;
                        int number;
                        std::cin >> number;
                        tree.Add(number);
                        std::cout << tree.ToString("<K>(1)[2]{3}") << std::endl;
                    }
                    else if (function_type == 2){
                        std::cout << "Entet search number: " << std::endl;
                        int number;
                        std::cin >> number;
                        tree3::tree3<int> ltree = tree.Search(number);
                        if (tree.Search(number) == nullptr){
                            std::cout << "Tree has not this element!" << std::endl;
                        }
                        else{
                            std::cout << "Tree has this element!" << std::endl;
                        }
                    }
                    else if (function_type == 3){
                        std::cout << tree.Depth() << std::endl;
                    }
                    else if (function_type == 4){
                        std::cout << tree.ToStringParantChild() << std::endl;
                    }
                    else if (function_type == 5){
                        std::cout << tree.ToString("<K>(1)[2]{3}") << std::endl;
                    }
                    else if (function_type == 0){
                        break;
                    }
                    else{
                        std::cout << "Incorrect value!" << std::endl;
                    }
                }
                tree.~tree3();
            }
            else{
                std::cout << "Incorrect value!" << std::endl;
            }
        }
        else if (menu == 2){
            std::cout << "TEST MENU: " << std::endl;
            std::cout << "1 - Creation and functions test: " << std::endl << "2 - Add speed test" << std::endl << "3 - Search speed test" << std::endl << "4 - Add speed test for the range" << std::endl << "5 - Search speed test for the range" << std::endl << "0 - Exit" << std::endl << "Enter number: ";
            int test_menu;
            std::cin >> test_menu;
            if (test_menu == 1){
                AllTests();
                std::cout << "All creation and functoins tests passed!" << std::endl;
            }
            else if (test_menu == 2){
                std::cout << "Enter number of operations: ";
                int num = 0;
                std::cin >> num;
                double res = SpeedTestAdd(num);
                std::cout << "Total test time for " << num << " objects: " << res << " sec." << std::endl;
            }
            else if (test_menu == 3){
                std::cout << "Enter number of operations: ";
                int num = 0;
                std::cin >> num;
                double res = SpeedTestSearch(num);
                
                std::cout << "Total test time for " << num << " objects: " << res << " sec." << std::endl;
            }
            else if (test_menu == 4){
                std::cout << "Enter max number of operations: ";
                int max = 0;
                std::cin >> max;
                std::cout << "Enter step of operations: ";
                int step = 0;
                std::cin >> step;
                GraphTestAdd(step, max);
            }
            else if (test_menu == 5){
                std::cout << "Enter max number of operations: ";
                int max = 0;
                std::cin >> max;
                std::cout << "Enter step of operations: ";
                int step = 0;
                std::cin >> step;
                GraphTestSearch(step, max);
            }
            else if (test_menu == 0){
                break;
            }
            else{
                std::cout << "Incorrect value!" << std::endl;
                break;
            }
        }
        else if (menu == 3){
            break;
        }
        else{
            std::cout << "Incorrect value!" << std::endl;
        }
    }
}


    

