#include "tests.hpp"
#include <assert.h>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

void TestFunctionsTree3(){
    tree3::tree3<int> t1 = tree3::tree3<int>();
    tree3::tree3<int> t2 = tree3::tree3<int>(1);
    tree3::tree3<int> t3 = tree3::tree3<int>(t2);
    std::string s = "<0>(<4>)[<8>]{<12>}";
    tree3::tree3<int> t4 = tree3::tree3<int>(s);
    
    //function
    //Add
    t1.Add(10);
    t1.Add(20);
    t1.Add(30);
    t1.Add(5);
    t1.Add(25);
    t1.Add(45);
    assert(t1.Search(5)->data == 5);
    assert(t1.Search(10)->data == 10);
    assert(t1.Search(20)->data == 20);
    assert(t1.Search(25)->data == 25);
    assert(t1.Search(30)->data == 30);
    assert(t1.Search(45)->data == 45);
    
    std::string str = t4.ToStringParantChild();
    
    //ToString
    assert(t1.ToString("<K>(1)[2]{3}") == "<0>(<10>[<5>])[<20>[<25>]]{<30>[<45>]}");
    assert(t2.ToString("<K>(1)[2]{3}") == "<1>");
    assert(t3.ToString("<K>(1)[2]{3}") == "<1>");
    assert(t4.ToString("<K>(1)[2]{3}") == "<0>(<4>)[<8>]{<12>}");
    
    //ToStringParantChild
    assert(t1.ToStringParantChild() == "(0 10) (10 5) (0 20) (20 25) (0 30) (30 45) ");
    assert(t2.ToStringParantChild() == "");
    assert(t3.ToStringParantChild() == "");
    assert(t4.ToStringParantChild() == "(0 4) (0 8) (0 12) ");
        
    //Search
    assert(t1.Search(10)->data == 10);
    assert(t1.Search(0)->data == 0);
    assert(t1.Search(5)->data == 5);
    assert(t1.Search(20)->data == 20);
    assert(t1.Search(25)->data == 25);
    assert(t1.Search(30)->data == 30);
    assert(t1.Search(45)->data == 45);
    assert(t2.Search(1)->data == 1);
    assert(t3.Search(1)->data == 1);
    assert(t4.Search(0)->data == 0);
    assert(t4.Search(4)->data == 4);
    assert(t4.Search(8)->data == 8);
    assert(t4.Search(12)->data == 12);
    
    //PathSearch
    assert(t1.PathSearch("l")->data == 10);
    assert(t1.PathSearch("c")->data == 20);
    assert(t1.PathSearch("r")->data == 30);
    assert(t1.PathSearch("lc")->data == 5);
    assert(t1.PathSearch("cc")->data == 25);
    assert(t1.PathSearch("rc")->data == 45);
    assert(t4.PathSearch("l")->data == 4);
    assert(t4.PathSearch("c")->data == 8);
    assert(t4.PathSearch("r")->data == 12);
    
    //Depth
    assert(t1.Depth() == 3);
    assert(t2.Depth() == 1);
    assert(t3.Depth() == 1);
    assert(t4.Depth() == 2);
    
    //DeleteRecursive
    t1.DeleteRecursive(t1.PathSearch("l"));
    assert(t1.ToString("<K>(1)[2]{3}") == "<0>[<20>[<25>]]{<30>[<45>]}");
    t1.DeleteRecursive(t1.PathSearch("c"));
    assert(t1.ToString("<K>(1)[2]{3}") == "<0>{<30>[<45>]}");
    t1.DeleteRecursive(t1.PathSearch("r"));
    assert(t1.ToString("<K>(1)[2]{3}") == "<0>");
}

void TestCreationTree3(){
    //creation
    tree3::tree3<int> t1 = tree3::tree3<int>();
    assert(t1.Depth() == 0);
    assert(t1.GetRoot() == nullptr);
    
    tree3::tree3<int> t2 = tree3::tree3<int>(1);
    assert(t2.Depth() == 1);
    assert(t2.GetRoot()->data == 1);
    assert(t2.GetRoot()->left == nullptr);
    assert(t2.GetRoot()->central == nullptr);
    assert(t2.GetRoot()->right == nullptr);
    
    tree3::tree3<int> t3 = tree3::tree3<int>(t2);
    assert(t3.Depth() == 1);
    assert(t3.GetRoot()->data == 1);
    assert(t3.GetRoot()->left == nullptr);
    assert(t3.GetRoot()->central == nullptr);
    assert(t3.GetRoot()->right == nullptr);
    
    std::string s = "<0>(<4>)[<8>]{<12>}";
    tree3::tree3<int> t4 = tree3::tree3<int>(s);
    assert(t4.Depth() == 2);
    assert(t4.GetRoot()->data == 0);
    assert(t4.GetRoot()->left->data == 4);
    assert(t4.GetRoot()->central->data == 8);
    assert(t4.GetRoot()->right->data == 12);
}

int sum_integer(int a, int b){
    return a + b;
}

void TestReduce(){
    tree3::tree3<int> t1(10);
    t1.Add(1);
    t1.Add(4);
    t1.Add(5);
    t1.Add(3);
    t1.Add(2);
    t1.Add(11);
    t1.Add(14);
    t1.Add(6);
    int res;
    res = tree3::reduce_ar(sum_integer, t1.GetRoot(), 1);
    assert(res == 57);
    res = tree3::reduce_al(sum_integer, t1.GetRoot(), 1);
    assert(res == 57);
    res = tree3::reduce_ac(sum_integer, t1.GetRoot(), 1);
    assert(res == 57);
}

int char_to_int(char item){
    return item;
}

void TestMap(){
    tree3::tree3<char> t('a');
    t.Add('g');
    t.Add('r');
    t.Add('p');
    t.Add('s');
    
    tree3::tree3<int> t1 = tree3::map_tree3(&t, char_to_int);
    assert(t.Depth() == 3);
    assert(t.PathSearch("")->data == 97);
    assert(t.PathSearch("l")->data == 103);
    assert(t.PathSearch("c")->data == 112);
    assert(t.PathSearch("r")->data == 114);
    assert(t.PathSearch("rc")->data == 115);
}

void AllTests(){
    TestCreationTree3();
    TestFunctionsTree3();
    TestMap();
    TestReduce();
}


double SpeedTestAdd(size_t num){
    tree3::tree3<int> t{};
    int start = clock();
    int end;
    double res = 0.0;
    for (size_t i = 0; i < num; ++i){
        t.Add(std::rand());
        end = clock();
        if (double(end - start)/CLOCKS_PER_SEC > 0.001){
            res += double(end - start)/CLOCKS_PER_SEC;
            start = clock();
        }
    }
    return res;
}

double SpeedTestSearch(size_t num){
    tree3::tree3<int> t{};
    int *p_darr = new int[num];
    for (size_t i = 0; i < num; ++i){
        int a = std::rand() % 32000 + 1;
        t.Add(a);
        p_darr[i] = a;
    }
    int start = clock();
    int end;
    double res = 0;
    for (size_t i = 0; i < num; ++i){
        t.Search(p_darr[i]);
        end = clock();
        if (double(end - start) / CLOCKS_PER_SEC > 0.001){
            res += double(end - start) / CLOCKS_PER_SEC;
            start = clock();
        }
    }
    return res;
}

void GraphTestAdd(int step, int max){
    std::ofstream file("/Users/nikolajfonov/Desktop/Lab_3/Lab_3/add.txt", std::ofstream::out);
    
    for(int i = step; i < max; i += step){
        file << SpeedTestAdd(i) << std::endl;
    }
    file << "Step: " << step << std::endl;
    file.close();
}

void GraphTestSearch(int step, int max){
    std::ofstream file("/Users/nikolajfonov/Desktop/Lab_3/Lab_3/search.txt", std::ofstream::out);
    
    for(int i = step; i < max; i += step){
        file << SpeedTestSearch(i) << std::endl;
    }
    file << "Step: " << step << std::endl;
    file.close();
}
