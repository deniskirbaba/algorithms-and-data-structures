#include <iostream>
#include <vector>

using namespace std;

int main() {

    // reading number of pulled out balls
    int n;
    cin >> n;

    // array for balls
    vector<int> balls(n);

    // buffer
    int currentBall;

    // previous ball
    int prevBall = 0;

    // reading and checking for cheating
    for (int i = 0; i < n; i++) {

        cin >> currentBall;

        // adding elements in array
        if (currentBall > prevBall) {
            for (int j = prevBall + 1; j <= currentBall - 1; j++) balls.push_back(j);
            prevBall = currentBall;
        }

        // delete last element
        else if (currentBall == balls.back()) balls.pop_back();

        // cheater if current ball less that last
        else {

            // answer output
            cout << "Cheater" << endl;

            return 0;
        }
    }

    // answer output
    cout << "Not a proof" << endl;

    return 0;
}