#include <iostream>

int main() {

    //input of the number of tests
    int tests;
    std::cin >> tests;

    for (int i = 0; i < tests; i++) { // for each new test, perform actions

        // data input
        int fighters;
        std::cin >> fighters;
        int commands;
        std::cin >> commands;

        int fighters_in_small_team = fighters / commands; // number of the fighters in small teams
        int fighters_in_big_team = fighters_in_small_team + 1;
        int number_of_big_teams = fighters %
                                  commands; // big team = small team + 1 fighter (from those who need to be distributed one by one to teams)
        int fights = 0;

        for (; commands > number_of_big_teams; commands--) { // fights += (small team vs small team) + (small team vs big team)
            fighters -= fighters_in_small_team;
            fights += fighters_in_small_team * fighters;
        }

        for (; commands > 1; commands--) { // fights += (big team vs big team)
            fighters -= fighters_in_big_team;
            fights += fighters_in_big_team * fighters;
        }

        // output the result
        std::cout << fights << std::endl;
    }

    return 0;
}
