#include <iostream>
#include <dlfcn.h> // Linux


typedef float (*PiWallisFunc)(int K);
typedef float (*PiLeibnizFunc)(int K);


int main() {

    void* handle2 = dlopen("./lib2.so", RTLD_LAZY);

    PiWallisFunc PiWallis = (PiWallisFunc)dlsym(handle2, "PiWallis");
    PiLeibnizFunc PiLeibniz = (PiLeibnizFunc)dlsym(handle2, "PiLeibniz");

    int choice;
    int x;
    std::cin >> choice;

    if (choice == 1) {
        std::cin >> x;
        std::cout << "Ответ: " << PiWallis(x) << std::endl;

    } else if (choice == 2) {
        std::cin >> x;
        std::cout << "Ответ: " << PiLeibniz(x) << std::endl;
    }

    dlclose(handle2);

    return 0;
}


// g++ -shared -o lib2.so lib2.cpp
// g++ dynamic.cpp -o dynamic -ldl
// 1 
// 100