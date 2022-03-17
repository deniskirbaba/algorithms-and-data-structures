#include <iostream>
#include <vector>

using namespace std;

// a structure for storing a symbol and its ordinal in a sequence
struct sequenceChar {
    char symbol;
    int id;
};

// comparator for lexical sorting
bool SequenceCharSort(const sequenceChar first, const sequenceChar second) {
    return first.symbol < second.symbol;
}

int main() {

    // word id input
    int n;
    cin >> n;
    n--;

    // array for storing elements (chars) of sequence
    vector<sequenceChar> sequence;

    int len = 0;
    char c;
    // loop reading element to end of line
    while (cin.get(c)) {

        // character input end condition
        if (len > 0 && (c == '\n' or c == '\r')) break;

        // if an " " meets
        else if (isspace(c)) continue;

        // creating and adding element in an array
        sequenceChar newChar = {c, len};
        sequence.push_back(newChar);

        len++;
    }

    // ascending sorting using self-made comparator
    stable_sort(sequence.begin(), sequence.end(), SequenceCharSort);

    int j = n; // starting element of the initial sequence

    // result output
    for (int i = 0; i < len; i++, j = sequence[j].id) cout << sequence[j].symbol;

    return 0;
}