#include "array.h"
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    // Check constructors
    Array<char, 10> arr_0;
    Array<int, 10> arr_1;
    Array<char, 10> arr_2('q');
    Array<std::string, 10> arr_3 = {"Hello", "new", "Array"};
    const Array<int, 10> arr_4 = {1};

    std::cout << arr_0 << '\n';
    std::cout << arr_1 << '\n';
    std::cout << arr_2 << '\n';
    std::cout << arr_3 << '\n';
    std::cout << arr_4 << '\n';

    // Check elements access
    std::cout << "\nAT()\n";
    try {
        // .at(index)
        std::cout << "Trying to access element by index 1 in arr_1\n";
        char el = arr_1.at(1);
    }
    catch (std::out_of_range) {
        std::cout << "Out of range for arr_1 by index 1\n";
    }
    std::string el_arr_3 = arr_3.at(2);
    std::cout << "Element by index 2 in arr_3 '" << el_arr_3 << "'\n";

    // operator[]
    std::cout << "\nOPERATOR[]()\n";
    char op_el_0 = arr_0[1];
    std::cout << "Default element for arr_0 is '" << op_el_0 << "'\n";

    char op_el_2 = arr_2[1];
    std::cout << "Default element for arr_2 is '" << op_el_2 << "'\n";

    try {
        std::string op_el_3 = arr_3[10];
    }
    catch (std::length_error) {
        std::cout << "Can't access element by index 10 in arr_3 with len = 10\n";
    }

    // front()
    std::cout << "\nFRONT()\n";
    std::cout << "front element for arr_0 '" << arr_0.front() << "'\n";
    std::cout << "front element for arr_1 '" << arr_1.front() << "'\n";
    std::cout << "front element for arr_2 '" << arr_2.front() << "'\n";
    std::cout << "front element for arr_3 '" << arr_3.front() << "'\n";
    std::cout << "front element for arr_4 '" << arr_4.front() << "'\n";

    // back()
    std::cout << "\nBACK()\n";
    std::cout << "back element for arr_0 '" << arr_0.back() << "'\n";
    std::cout << "back element for arr_1 '" << arr_1.back() << "'\n";
    std::cout << "back element for arr_2 '" << arr_2.back() << "'\n";
    std::cout << "back element for arr_3 '" << arr_3.back() << "'\n";
    std::cout << "back element for arr_4 '" << arr_4.back() << "'\n";

    // Data
    std::cout << "\nDATA()\n";
    std::string *raw_data = arr_3.data();
    std::cout << "Raw data of arr_3: ";
    for (size_t i = 0; i < arr_3.size(); i++)
        std::cout << "'" << raw_data[i] << "' ";
    std::cout << '\n';

    // Fill
    std::cout << "\nFILL()\n";
    char *raw_chars = arr_0.data();
    std::cout << "Raw data of arr_0 befor filling it: ";
    for (size_t i = 0; i < arr_0.size(); i++)
        std::cout << "'" << raw_chars[i] << "' ";
    std::cout << '\n';
    arr_0.fill('a');
    std::cout << "Raw data of arr_0 after filling it: ";
    for (size_t i = 0; i < arr_0.size(); i++)
        std::cout << "'" << raw_chars[i] << "' ";
    std::cout << '\n';

    // Find element
    std::cout << "\nFIND()\n";
    std::cout << "Find element 'q' in arr_0 -> should be false\n";
    long needed = arr_0.find('q');
    if (needed == -1)
        std::cout << "can't find element 'q' in arr_0 [OK]\n";
    else
        std::cout << "somthing went wrong[FALSE]... " << needed << " found\n";

    std::cout << "Find element 'Array' in arr_3 -> should be true\n";
    needed = arr_3.find("Array");
    if (needed == -1)
        std::cout << "can't find element 'Array' in arr_3 [FALSE]\n";
    else
        std::cout << "Found '" << arr_3.at(needed) << "' by index " << needed << '\n';

    return 0;
}
