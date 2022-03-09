#include <iostream>

int main() {

    //input of the number of elements
    int n;
    std::cin >> n;

    int current_sequence = 0; // sum of the elements
    int result_potential = 0; // result value

    for (int i = 0; i < n; i++) // read the element and examine the sequence
    {
        // input element
        int input;
        std::cin >> input;

        current_sequence += input;

        if (current_sequence > result_potential) result_potential = current_sequence; // if the sequence grows, then we increase the value of the possible potential
        if (current_sequence < 0) current_sequence = 0; // if the sequence is less than 0, then it has no meaning
    }

    // result output
    std::cout << result_potential << std::endl;

    return 0;
}