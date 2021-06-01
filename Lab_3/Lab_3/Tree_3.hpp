#ifndef Tree_2_hpp
#define Tree_2_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>

namespace tree3 {
    template<class T>
    struct node3{
        T data = T{};
        node3<T>* parent = nullptr;
        node3<T>* left =  nullptr;
        node3<T>* central =  nullptr;
        node3<T>* right = nullptr;
    };
    
    template<class T>
    class tree3{
    private:
        node3<T>* root = nullptr;
    
    public:
        tree3() = default;
        tree3(const T& data);
        tree3(const node3<T>& other);
        tree3(const node3<T>* const branch);
        tree3(std::string s, const std::string format = "<K>(1)[2]{3}");
        
        node3<T>* GetRoot();
        void Add(node3<T>* tree, const T& data);
        void Add(const T& data); // const
        void AddBranch(node3<T>* tree, node3<T>* branch);
        void AddBranch(node3<T>* branch);
        
        node3<T>* Search(node3<T>* tree, const T& sought);
        node3<T>* Search(const T& sought);
        node3<T>* Search(node3<T>* tree, const T& sought, int (*cmp)(const T&, const T&));
        node3<T>* Search(const T& sought, int (*cmp)(const T&, const T&));
        node3<T>* PathSearch(node3<T>* sourse,std::string path);
        node3<T>* PathSearch(std::string path);
        
        size_t Depth(node3<T>* tree, size_t cnt);
        size_t Depth();
        
        void Delete(node3<T>* tree);
        void DeleteRecursive(node3<T>* tree);
        
        std::string ToString(node3<T>* tree, const std::string format = "<K>(1)[2]{3}");
        std::string ToString(const std::string format);
        std::string ToStringParantChild(const node3<T>* tree);
        std::string ToStringParantChild();
        
        ~tree3();
    };
    
    
    template<class T>
    std::string tree_to_string(const node3<T>* tree, std::string res, const std::string format){
        if (tree == nullptr){
            return res;
        }
        for (size_t i = 0; i < 11; i += 3){
            switch (format[i + 1]) {
                case 'K':
                    res += format[i];
                    res += std::to_string(tree->data);
                    res += format[i + 2];
                    break;
                case '1':
                    if (tree->left != nullptr){
                        res += format[i];
                        res = tree_to_string(tree->left, res, format);
                        res += format[i + 2];
                    }
                    break;
                case '2':
                    if (tree->central != nullptr){
                        res += format[i];
                        res = tree_to_string(tree->central, res, format);
                        res += format[i + 2];
                    }
                    break;
                default:
                    if (tree->right != nullptr){
                        res += format[i];
                        res = tree_to_string(tree->right, res, format);
                        res += format[i + 2];
                    }
                    break;
            }
        }
    return res;
    }

    template<class T>
    std::string tree_to_string_parent_child(const node3<T>* tree, std::string res){
        if (tree == nullptr){
            return res;
        }
        if (tree->left != nullptr){
            res += '(' + std::to_string(tree->data) + ' ' + std::to_string(tree->left->data) + ')' + ' ';
            res = tree_to_string_parent_child(tree->left, res);
        }
        if (tree->central != nullptr){
            res += '(' + std::to_string(tree->data) + ' ' + std::to_string(tree->central->data) + ')' + ' ';
            res = tree_to_string_parent_child(tree->central, res);
        }
        if (tree->right != nullptr){
            res += '(' + std::to_string(tree->data) + ' ' + std::to_string(tree->right->data) + ')' + ' ';
            res = tree_to_string_parent_child(tree->right, res);
        }
        return res;
    }

    template<class T>
    void tree_from_string(std::string s, std::string format, node3<T>* const res){
        if (s.empty()){
            return;
        }
        for (size_t i = 0; i < 11; i += 3){
            if (s[0] != format[i]){
                continue;
            }
            size_t r;
            if (format[i + 1] == 'K'){
                r = s.find_first_of(format[i + 2]);
            }
            else{
                r = s.find_last_of(format[i + 2]);
            }
            std::string new_string = s.substr(1, r - 1);
            std::istringstream stream(new_string);
            switch (format[i + 1]) {
                case 'K':
                    stream >> res->data;
                    break;
                case '1':
                    res->left = new node3<T>;
                    tree_from_string(new_string, format, res->left);
                    break;
                case '2':
                    res->central = new node3<T>;
                    tree_from_string(new_string, format, res->central);
                    break;
                default:
                    res->right = new node3<T>;
                    tree_from_string(new_string, format, res->right);
                    break;
            }
            s = s.substr(r + 1, std::string::npos);
        }
    }
    
    
    template<class T>
    void copy_nodes3(const node3<T>* source, node3<T>* destination, node3<T>* destination_parent = nullptr){
        if (source != nullptr && destination != nullptr){
            destination->data = source->data;
            if (destination_parent != nullptr){
                destination->parent = destination_parent;
            }
            if (source->left != nullptr){
                if (destination->left == nullptr){
                    destination->left = new node3<T>;
                }
                copy_nodes3(source->left, destination->left, destination);
            }
            if (source->central != nullptr){
                if (destination->central == nullptr){
                    destination->central = new node3<T>;
                }
                copy_nodes3(source->central, destination->central, destination);
            }
            if (source->right != nullptr){
                if (destination->right == nullptr){
                    destination->right = new node3<T>;
                }
                copy_nodes3(source->right, destination->right, destination);
            }
        }
    }

    template<class T, class C>
    tree3<C> tree_map(node3<T>* tree, C(*f)(T), tree3<C>& res){
        if (tree == nullptr){
            return res;
        }
        res.Add(f(tree->data));
        if (tree->left != nullptr){
            tree_map(tree->left, f, res);
        }
        if (tree->central != nullptr){
            tree_map(tree->central, f, res);
        }
        if (tree->right != nullptr){
            tree_map(tree->right, f, res);
        }
        return res;
    }

    template <class T>
    tree3<T>::tree3(const T& data){
        root = new node3<T>;
        root->data = data;
    };

    template<class T>
    tree3<T>::tree3(const node3<T>& other){
        if (other.root != nullptr){
            root = new node3<T>;
            copy_nodes3(other.root, root);
        }
    }
    
    template<class T>
    tree3<T>::tree3(const node3<T>* const branch){
        root = new node3<T>;
        copy_nodes3(branch, root);
    }
     
    template<class T>
    tree3<T>::tree3(std::string s, const std::string format){
        std::string f = format;
        f.erase(remove_if(begin(f), end(f), isspace), end(f));
        std::string ERROR = "---";
        if (f.size() != 12){
            throw std::invalid_argument(ERROR);
        }
        if ((f[1] != '1' && f[1] != '2' && f[1] != '3' && f[1] != 'K') ||
            (f[4] != '1' && f[4] != '2' && f[4] != '3' && f[4] != 'K') ||
            (f[7] != '1' && f[7] != '2' && f[7] != '3' && f[7] != 'K') ||
            (f[10] != '1' && f[10] != '2' && f[10] != '3' && f[10] != 'K')){
            throw std::invalid_argument(ERROR);
        }
        std::set<char> m;
        for (int i = 0; i < 12; ++i){
            m.insert(f[i]);
        }
        if (m.size() != 12){
            throw std::invalid_argument(ERROR);
        }
        root = new node3<T>;
        tree_from_string(s, f, root);
    }

    template<class T>
    node3<T>* tree3<T>::GetRoot(){
        return root;
    }

    template<class T>
    void tree3<T>::Add(node3<T>* tree, const T& data){
        
        
        
        if (tree->right != nullptr){
            if (tree->right->data == data){
                return;
            }
        }
        if (tree->central != nullptr){
            if (tree->central->data == data){
                return;
            }
        }
        if (tree->left != nullptr){
            if (tree->left->data == data){
                return;
            }
        }
        
        if (tree->left == nullptr && tree->central == nullptr && tree->right == nullptr){
            tree->central = new node3<T>;
            tree->central->parent = tree;
            tree->central->data = data;
            return;
        }
        
        
        if (tree->right != nullptr && tree->central != nullptr && tree->left != nullptr){
            if (data > tree->right->data){
                Add(tree->right, data);
                return;
            }
            else if (data < tree->left->data){
                Add(tree->left, data);
                return;
            }
            else{
                Add(tree->central, data);
                return;
            }
        }
        
        if (tree->left != nullptr && tree->central == nullptr && tree->right == nullptr){
            tree->central = new node3<T>;
            if (tree->left->data < data){
                tree->central->parent = tree;
                tree->central->data = data;
                return;
            }
            else{
                tree->central->parent = tree->left->parent;
                tree->central->data = tree->left->data;
                tree->left->parent = tree;
                tree->left->data = data;
                return;
            }
        }
        
        if (tree->left == nullptr && tree->central != nullptr && tree->right == nullptr){
            tree->left = new node3<T>;
            if (tree->central->data > data){
                tree->left->parent = tree;
                tree->left->data = data;
                return;
            }
            else{
                tree->left->parent = tree->central->parent;
                tree->left->data = tree->central->data;
                tree->central->parent = tree;
                tree->central->data = data;
                return;
            }
        }
        
        if (tree->left == nullptr && tree->central == nullptr && tree->right != nullptr){
            tree->central = new node3<T>;
            if (tree->right->data > data){
                tree->central->parent = tree;
                tree->central->data = data;
                return;
            }
            else{
                tree->central->parent = tree->right->parent;
                tree->central->data = tree->right->data;
                tree->right->parent = tree;
                tree->right->data = data;
                return;
            }
        }
        
        if (tree->left != nullptr && tree->central != nullptr && tree->right == nullptr){
            tree->right = new node3<T>;
            if (tree->central->data < data){
                tree->right->parent = tree;
                tree->right->data = data;
                return;
            }
            else{
                tree->right->parent = tree->central->parent;
                tree->right->data = tree->central->data;
                if (tree->left->data < data){
                    tree->central->parent = tree;
                    tree->central->data = data;
                    return;
                }
                else{
                    tree->central->parent = tree->left->parent;
                    tree->central->data = tree->left->data;
                    tree->left->parent = tree;
                    tree->left->data = data;
                    return;
                }
            }
        }
        
        if (tree->left == nullptr && tree->central != nullptr && tree->right != nullptr){
            tree->left = new node3<T>;
            if (tree->central->data > data){
                tree->left->parent = tree;
                tree->left->data = data;
                return;
            }
            else{
                tree->left->parent = tree->central->parent;
                tree->left->data = tree->central->data;
                if (tree->right->data > data){
                    tree->central->parent = tree;
                    tree->central->data = data;
                    return;
                }
                else{
                    tree->central->parent = tree->right->parent;
                    tree->central->data = tree->right->data;
                    tree->right->parent = tree;
                    tree->right->data = data;
                    return;
                }
            }
        }
        
        if (tree->left != nullptr && tree->central == nullptr && tree->right != nullptr){
            tree->central = new node3<T>;
            if (tree->left->data > data){
                tree->central->parent = tree->left->parent;
                tree->central->data = tree->left->data;
                tree->left->parent = tree;
                tree->left->data = data;
                return;
            }
            else if (tree->right->data < data){
                tree->central->parent = tree->right->parent;
                tree->central->data = tree->right->data;
                tree->right->parent = tree;
                tree->right->data = data;
                return;
            }
            else{
                tree->central->parent = tree;
                tree->central->data = data;
                return;
            }
        }
    }

    template<class T>
    void tree3<T>::Add(const T& data){
        if(root == nullptr){
            root = new node3<T>;
        }
        Add(root, data);
    }
    
    template<class T>
    void tree3<T>::AddBranch(node3<T>* tree, node3<T>* branch){
        if (branch == nullptr){
            return;
        }
        this->Add(tree, branch->data);
        this->AddBranch(tree, branch->left);
        this->AddBranch(tree, branch->central);
        this->AddBranch(tree, branch->right);
    }

    template<class T>
    void tree3<T>::AddBranch(node3<T>* branch){
        this->AddBranch(root, branch);
    }

    template<class T>
    node3<T>* tree3<T>::Search(node3<T>* tree, const T& sought){
        if (tree != nullptr){
        }
            if (tree->data == sought){
                return tree;
            }
            if (tree->left != nullptr && sought <= tree->left->data){
                return Search(tree->left, sought);
            }
            else if (tree->right != nullptr && sought >= tree->right->data){
                return Search(tree->right, sought);
            }
            else if (tree->central != nullptr){
                return Search(tree->central, sought);
        }
        else{
            return nullptr;
        }
    }

    template<class T>
    node3<T>* tree3<T>::Search(const T& sought){
        return Search(root, sought);
    }

    template<class T>
    node3<T>* tree3<T>::Search(node3<T>* tree, const T& sought, int(*cmp)(const T&, const T&)){
        if (tree != nullptr){
            if (cmp(sought, tree->data) == 0)
                return tree;
            if (cmp(sought, tree->data) < 0)
                return Search(tree->left, sought);
            if (cmp(sought, tree->data) > 0)
                return Search(tree->right, sought);
        }
        return nullptr;
    }

    template<class T>
    node3<T>* tree3<T>::PathSearch(node3<T>* source, std::string path){
        if (path.empty()){
            return source;
        }
        switch (path[0]) {
            case 'l':
                if (source->left == nullptr){
                    return nullptr;
                }
                return PathSearch(source->left, path.substr(1));
            case 'c':
                if (source->central == nullptr){
                    return nullptr;
                }
                return PathSearch(source->central, path.substr(1));
            case 'r':
                if (source->right == nullptr){
                    return nullptr;
                }
                return PathSearch(source->right, path.substr(1));
            default:
                throw std::invalid_argument("Tree3 PathSearch: path must contain only 'lcr' symbols");
        }
    }

    template <class T>
    node3<T>* tree3<T>::PathSearch(std::string path){
        return PathSearch(root, path);
    }

    template<class T>
    size_t tree3<T>::Depth(node3<T>* tree, size_t cnt){
        if (tree == nullptr){
            return cnt;
        }
        return std::max(Depth(tree->left, cnt + 1), std::max(Depth(tree->right, cnt + 1), Depth(tree->central, cnt + 1)));
    }

    template<class T>
    size_t tree3<T>::Depth(){
        return Depth(root, 0);
    }

    template<class T>
    void make_nullptr_to_parent(node3<T>* tree){
        if (tree->parent->central == tree){
            tree->parent->central = nullptr;
        }
        if (tree->parent->left == tree){
            tree->parent->left = nullptr;
        }
        if (tree->parent->right == tree){
            tree->parent->right = nullptr;
        }
    }

    template<class T>
    void tree3<T>::Delete(node3<T>* tree){
        if (tree == nullptr){
            return;
        }
        node3<T>* destination;
        
        if (tree->parent == nullptr){
            destination = root;
        }
        else{
            destination = tree->parent;
        }
        if (tree->parent != nullptr){
            make_nullptr_to_parent(tree);
        }
        
        AddBranch(destination, tree->left);
        AddBranch(destination, tree->central);
        AddBranch(destination, tree->right);
        this->DeleteRecursive(tree);
    }

    template<class T>
    void tree3<T>::DeleteRecursive(node3<T>* tree){
        if (tree != nullptr){
            if (tree->right != nullptr){
                DeleteRecursive(tree->right);
                tree->right = nullptr;
            }
            if (tree->central != nullptr){
                DeleteRecursive(tree->central);
                tree->central = nullptr;
            }
            if (tree->left != nullptr){
                DeleteRecursive(tree->left);
                tree->left = nullptr;
            }
            if (tree->parent != nullptr){
                make_nullptr_to_parent(tree);
            }
        }
    }

    template<class T>
    std::string tree3<T>::ToString(node3<T>* tree, const std::string format){
        std::string f = format;
        f.erase(remove_if(begin(f), end(f), isspace), end(f));
        std::string error_message = "Tree3 ToString: format must have 12 non_space latin symbols, example - '{K}(1)[2]{3}'";
        if (f.size() != 12){
            throw std::invalid_argument(error_message);
        }
        if ((f[1] != '1' && f[1] != '2' && f[1] != '3' && f[1] != 'K') ||
            (f[4] != '1' && f[4] != '2' && f[4] != '3' && f[4] != 'K') ||
            (f[7] != '1' && f[7] != '2' && f[7] != '3' && f[7] != 'K') ||
            (f[10] != '1' && f[10] != '2' && f[10] != '3' && f[10] != 'K')){
            throw std::invalid_argument(error_message);
        }
        return tree_to_string(tree, "", f);
    }

    template<class T>
    std::string tree3<T>::ToString(const std::string format){
        return ToString(root, format);
    }

    template<class T>
    std::string tree3<T>::ToStringParantChild(const node3<T>* tree){
        return tree_to_string_parent_child(tree, "");
    }

    template<class T>
    std::string tree3<T>::ToStringParantChild(){
        return ToStringParantChild(root);
    }

    template<class T>
    tree3<T>::~tree3(){
        this->DeleteRecursive(root);
    }

    template<class T, class C>
    tree3<C> map_tree3(node3<T>* tree, C(*f)(T)){
        if (tree == nullptr){
            tree3<C> res{};
            return res;
        }
        tree3<C> res{f(tree->data)};
        if (tree->left != nullptr){
            tree_map(tree->left, f, res);
        }
        if (tree->central != nullptr){
            tree_map(tree->central, f, res);
        }
        if (tree->right != nullptr){
            tree_map(tree->right, f, res);
        }
        return res;
        
    }

    template<class T, class C>
    tree3<C> map_tree3(tree3<T>* tree, C(*f)(T)){
        return map_tree3(tree->GetRoot(), f);
    }

    template<class T>
    tree3<T> map_tree3(tree3<T>* tree, T(*f)(T)){
        return map_tree3(tree->GetRoot(), f);
    }

    template<class T>
    T reduce_ar(T(*f)(T, T), node3<T>* tree, const T& c){
        if (tree == nullptr){
            return c;
        }
        T res = c;
        res = reduce_ar(f, tree->left, res);
        res = reduce_ar(f, tree->central, res);
        res = reduce_ar(f, tree->right, res);
        return f(tree->data, res);
    }

    template<class T>
    T reduce_al(T(*f)(T, T), node3<T>* tree, const T& c){
        if (tree == nullptr){
            return c;
        }
        T res = c;
        res = reduce_al(f, tree->left, res);
        res = f(tree->data, res);
        res = reduce_al(f, tree->central, res);
        res = reduce_al(f, tree->right, res);
        return res;
    }

    template<class T>
    T reduce_ac(T(*f)(T, T), node3<T>* tree, const T& c){
        if (tree == nullptr){
            return c;
        }
        T res = c;
        res = reduce_ac(f, tree->left, res);
        res = reduce_ac(f, tree->central, res);
        res = f(tree->data, res);
        res = reduce_ac(f, tree->right, res);
        return res;
}



};

#endif /* Tree_2_hpp */
