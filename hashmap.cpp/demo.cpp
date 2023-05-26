#include "hashmap.cpp"
#include <iostream>
#include <string>

int main() {
    Hashmap<std::string, std::string> *hashmap = new Hashmap<std::string, std::string>(2);
    std::cout << "size: " << hashmap->size() << std::endl;
    std::cout << "put apple pingguo: " << hashmap->put("apple", "pingguo") << std::endl;
    std::cout << "put banana xiangjiao: " << hashmap->put("banana", "xiangjiao") << std::endl;
    std::cout << "put orange chengzi: " << hashmap->put("orange", "chengzi") << std::endl;
    std::cout << "size: " << hashmap->size() << std::endl;
    std::cout << "get apple: " << hashmap->get("apple") << std::endl;
    std::cout << "get banana: " << hashmap->get("banana") << std::endl;
    std::cout << "get orange: " << hashmap->get("orange") << std::endl;
    std::cout << "remove apple: " << hashmap->remove("apple") << std::endl;
    std::cout << "size: " << hashmap->size() << std::endl;
    std::cout << "get apple: ";
    try {
        std::string value = hashmap->get("apple");
        std::cout << value << std::endl;
    } catch (const char *msg) {
        std::cout << "caught exeption: " << msg << std::endl;
    }
    std::cout << "get banana: " << hashmap->get("banana") << std::endl;
    return 0;
}

/*
output:
size: 0
put apple pingguo: 1
put banana xiangjiao: 1
put orange chengzi: 3
size: 3
get apple: pingguo
get banana: xiangjiao
get orange: chengzi
remove apple: 1
size: 2
get apple: caught exeption: key not found
get banana: xiangjiao
*/