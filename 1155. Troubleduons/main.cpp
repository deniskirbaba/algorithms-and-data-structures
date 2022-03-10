#include <iostream>

int main() {

    // data input
    int a, b, c, d, e, f, g, h;
    std::cin >> a >> b >> c >> d >> e >> f >> g >> h;

    // annihilation impossibility condition - sum of the groups of adjacent duons aren't equal
    if ((a + h + f + c) != (e + d + g + b)) std::cout << "IMPOSSIBLE";
    else {

        // annihilation adjacent duons while it's possible
        bool annih_condition = true;
        while (annih_condition) {

            // vertex A
            if (a > 0 && b > 0) {
                a -= 1;
                b -= 1;
                std::cout << "AB-" << std::endl;
            }
            else if (a > 0 && d > 0) {
                a -= 1;
                d -= 1;
                std::cout << "AD-" << std::endl;
            }
            else if (a > 0 && e > 0) {
                a -= 1;
                e -= 1;
                std::cout << "AE-" << std::endl;
            }

            // vertex B
            else if (b > 0 && f > 0) {
                b -= 1;
                f -= 1;
                std::cout << "BF-" << std::endl;
            }
            else if (b > 0 && c > 0) {
                b -= 1;
                c -= 1;
                std::cout << "BC-" << std::endl;
            }

            // vertex C
            else if (c > 0 && g > 0) {
                c -= 1;
                g -= 1;
                std::cout << "CG-" << std::endl;
            }
            else if (c > 0 && d > 0) {
                c -= 1;
                d -= 1;
                std::cout << "CD-" << std::endl;
            }

            // vertex D
            else if (d > 0 && h > 0) {
                d -= 1;
                h -= 1;
                std::cout << "DH-" << std::endl;
            }

            // vertex E
            else if (e > 0 && f > 0) {
                e -= 1;
                f -= 1;
                std::cout << "EF-" << std::endl;
            }
            else if (e > 0 && h > 0) {
                e -= 1;
                h -= 1;
                std::cout << "EH-" << std::endl;
            }

            // vertex F
            else if (f > 0 && g > 0) {
                f -= 1;
                g -= 1;
                std::cout << "FG-" << std::endl;
            }

            // vertex G
            else if (g > 0 && h > 0) {
                g -= 1;
                h -= 1;
                std::cout << "GH-" << std::endl;
            }

            // if annihilation adjacent duons is not possible
            else annih_condition = false;
        }

        annih_condition = true;
        // annihilate the opposite vertices of the cube, for this we add duons between them
        while (annih_condition) {

            // vertices A and G
            if (a > 0 && g > 0) {
                std::cout << "EF+" << std::endl;
                e += 1;
                f += 1;
                std::cout << "AE-" << std::endl;
                a -= 1;
                e -= 1;
                std::cout << "FG-" << std::endl;
                f -= 1;
                g -= 1;
            }

            // vertices C and E
            else if (c > 0 && e > 0) {
                std::cout << "BF+" << std::endl;
                b += 1;
                f += 1;
                std::cout << "BC-" << std::endl;
                b -= 1;
                c -= 1;
                std::cout << "EF-" << std::endl;
                b -= 1;
                f -= 1;
            }

            // vertices B and H
            else if (b > 0 && h > 0) {
                std::cout << "EF+" << std::endl;
                e += 1;
                f += 1;
                std::cout << "BF-" << std::endl;
                b -= 1;
                f -= 1;
                std::cout << "EH-" << std::endl;
                e -= 1;
                h -= 1;
            }

            // vertices D and F
            else if (d > 0 && f > 0) {
                std::cout << "EH+" << std::endl;
                e += 1;
                h += 1;
                std::cout << "DH-" << std::endl;
                d -= 1;
                h -= 1;
                std::cout << "EF-" << std::endl;
                e -= 1;
                f -= 1;
            }

            // if annihilation the opposite vertices is not possible
            else annih_condition = false;
        }
    }

    return 0;
}
