#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <functional> // Для сортировки в set

using std::cin, std::cout, std::pair, std::string, std::unordered_map, std::map, std::greater, std::set;

struct City {
    string name;
    uint64_t money{};
    int days{}; // days in top
};

struct Person {
    City* city;
    uint64_t money;
};

int main()
{
    City cities[60000];
    Person persons[10000];
    unordered_map<string, Person*> namePerson;
    map<string, City*> nameCity;
    set<pair<uint64_t , City*>, greater<>> topCity; // sorting cities by money

    uint16_t n, m, k, count; cin >> n;
    m, k, count = 0;

    uint64_t money;

    string curPersonName, curCityName;

    for(uint16_t i = 0; i < n; i++) { // cycle reading the names of billionaires, cities and states on day 0
        cin >> curPersonName >> curCityName >> money;
        namePerson[curPersonName] = &persons[i]; // add person
        if(!nameCity[curCityName]) nameCity[curCityName] = &cities[count++]; // if there is no such city yet, add
        persons[i] = (Person){nameCity[curCityName], money}; // fill out the person info
        nameCity[curCityName]->name = curCityName; // add city name
        nameCity[curCityName]->money += money; // sum the money
    }
    for(const auto& city : nameCity) // add cities to the toCity array
        topCity.insert({city.second->money, city.second });

    uint16_t prevDay = 0, day;
    string name, place;
    cin >> m >> k;

    while(true) {
        bool finished = (!(cin >> day >> curPersonName >> place)); // while we can read go ahead
        if(finished) day = m; // to prevent premature exit from the loop

        if(day != prevDay) { // if day continue
            auto top1 = topCity.begin(); // first city at the top now
            auto top2 = top1++; // second city at the top now (if sums are equals)
            if(top1 == topCity.end() or top2->first > top1->first) // if only one day or the first day is superior to the second
                top2->second->days += day - prevDay; // increase the number of days of the top city by the time difference
        }
        if(finished) break; // leave if there are no more cities
        if(!nameCity[place]) { // if there was no such city
            nameCity[place] = &cities[count++]; // add this city
            nameCity[place]->name = place;
        }

        { // updating
            auto nextPlace = nameCity[place]; // city name
            auto person = namePerson[curPersonName]; // person name
            auto prevPlace = person->city;
            auto prevMoney = prevPlace->money;
            { // transferring a person from one city to another
                topCity.erase({prevMoney, prevPlace}); // delete from old
                prevPlace->money -= person->money; // decrease the money
                topCity.insert({prevPlace->money, prevPlace}); // add to the new city
                topCity.erase({nextPlace->money, nextPlace}); // remove the old top city
                nextPlace->money += person->money; // recalculate the money
                topCity.insert({nextPlace->money, nextPlace}); // correct the money of the new city
                person->city = nextPlace; // change the location
                prevDay = day;
            }
        }
    }

    map<string, int> result; // output with sorting

    for (auto& r : topCity) if (r.second->days) // if was at top at least once
        result.insert(make_pair(r.second->name, r.second->days)); // add to the result
    for (auto& o : result) cout << o.first << " " << o.second << "\n"; // output

    return 0;
}