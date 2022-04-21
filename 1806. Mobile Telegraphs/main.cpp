#include <iostream>
#include <vector>

using namespace std;

// struct that represents the soldier's telegraph
// it contains id, telegraph number and array of the available contacts with transmission time
struct telegraphNumber {
    int id;
    int number[10];
    vector<vector<int>> contacts; // contacts[0] - contact id, contacts[1] - transmission time
};

// a function that returns the time of transmission of a message from one fighter to another,
// if the transmission is not possible, return 0
int getTransmissionTime(const vector <vector<int>>& contacts, int id) {
    for (vector<int> contact : contacts) {
        if (contact[0] == id) return contact[1];
    }
    return 0;
}

int main() {

    // input number of soldiers
    int n;
    cin >> n;

    // input times of transmission of a message from one telegraph to another
    // with the length of the common prefix of their numbers equal to zero, one, two, ..., nine
    int time[10];
    for (int & i : time) cin >> i;

    // dynamic array that contains telegraphs numbers
    vector<telegraphNumber> soldierBook(n);

    // fill the soldiers telegraphs numbers array
    uint64_t buffer;
    for (int i = 0; i < n; i++) {
        cin >> buffer;

        // write to array number by one digit
        for (int j = 9; j > -1; j--) {
            soldierBook[i].number[j] = buffer % 10;
            buffer /= 10;
        }
        soldierBook[i].id = i;

        if (soldierBook.size() == 1) continue;

        // fill the contacts
        int mismatchCounter;
        vector<int> mismatchPositions;
        int transmissionSpeed;
        for (int j = 0; j < soldierBook.size(); j++) {
            // counting the mismatches and calculation of message transmission time depending on number prefix
            mismatchCounter = 0;
            mismatchPositions.clear();
            bool firstMismatch = true;
            for (int k = 0; k < 10; k++) {
                if (soldierBook[i].number[k] != soldierBook[j].number[k]) {
                    if (firstMismatch) {
                        transmissionSpeed = time[k];
                        firstMismatch = false;
                    }
                    mismatchCounter += 1;
                    mismatchPositions.push_back(k);
                }
            }
            // condition for sending a message
            if (mismatchCounter == 1 || ((mismatchCounter == 2) &&
                                         (soldierBook[i].number[mismatchPositions[0]] == soldierBook[j].number[mismatchPositions[1]]) &&
                                         (soldierBook[i].number[mismatchPositions[1]] == soldierBook[j].number[mismatchPositions[0]]))) {
                soldierBook[j].contacts.push_back({i, transmissionSpeed});
                soldierBook[i].contacts.push_back({j, transmissionSpeed});
            }
        }
    }

    // Dijkstra's algorithm

    vector <int> minDistances(n);
    vector <int> visitedVertices(n);
    int minIndex;
    int minWeight;
    int temp;

    // initialize vertices and distances
    for (int i = 0; i < n; i++)
    {
        minDistances[i] = 10000;
        visitedVertices[i] = 1;
    }
    minDistances[0] = 0; // initial vertex

    do {
        minIndex = 10000;
        minWeight = 10000;
        for (int i = 0; i < n; i++)
        { // if vertex isn't visited and its weight less than minWeight
            if ((visitedVertices[i] == 1) && (minDistances[i] < minWeight))
            { // rewrite values
                minWeight = minDistances[i];
                minIndex = i;
            }
        }
        // add found minWeight to the current vertex weight and compare with current minWeight of vertex
        if (minIndex != 10000)
        {
            for (int i = 0; i < n; i++)
            {
                if (getTransmissionTime(soldierBook[minIndex].contacts, i) > 0)
                {
                    temp = minWeight + getTransmissionTime(soldierBook[minIndex].contacts, i);
                    if (temp < minDistances[i])
                    {
                        minDistances[i] = temp;
                    }
                }
            }
            visitedVertices[minIndex] = 0;
        }
    } while (minIndex < 10000);

    /*
    // output soldier book info
    cout << '\n' << '\n';
    for (int i = 0; i < n; i++) {
        cout << "id: " << soldierBook[i].id << '\n';

        cout << "number: ";
        for (int j : soldierBook[i].number) {
            cout << j;
        }
        cout << '\n';

        cout << "contacts: ";
        for (vector<int> contact : soldierBook[i].contacts) {
            cout << "{id: " << contact[0] << ", time: " << contact[1] << "} ";
        }

        cout << '\n' << '\n';
    }
    */

    // finding the transmission path
    if (minDistances[n-1] != 10000) {
        vector <int> ver(n); // array of visited vertices
        int end = n - 1; // index of the final vertex
        ver[0] = end + 1; // starting element - final vertex
        int k = 1; // index of the prev vertex
        int weight = minDistances[end]; // weight of the final vertex

        while (end != 0) // until reach the final vertex
        {
            for (int i = 0; i < n; i++) // looking through all vertices
                if (getTransmissionTime(soldierBook[i].contacts, end) != 0) // if connection is exists
                {
                    int temp = weight - getTransmissionTime(soldierBook[i].contacts, end); // define the weight from prev vertex
                    if (temp == minDistances[i]) // if weight is equal with calculated, it means that from this peak there was a transition
                    {
                        weight = temp; // save new weight
                        end = i;       // save prev vertex
                        ver[k] = i + 1;
                        k++;
                    }
                }
        }

        // output result
        cout << minDistances[n-1] << '\n'; // min transmission time
        cout << ver.size() << '\n'; // the number of fighters who will participate in its delivery
        // path output (starting vertex is at the end of an array of k elements)
        for (int i = k - 1; i >= 0; i--) cout << ver[i] << ' ';
    }
    else cout << -1;

    return 0;
}
