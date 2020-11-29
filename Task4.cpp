#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <algorithm>


using std::string;
using std::vector;

void threadFunction(vector<int> &team, int l, int r) {
    for (int i = l; i < r - 1; i += 2) {
        if (team[i] < team[i + 1]) {
            team[i] = 0;
        } else {
            team[i + 1] = 0;
        }
    }
}

int input() {
    int n;
    std::cin >> n;
    bool test = true;
    do {
        if (!(test = std::cin.good())) {
            std::cout << "Incorrect input. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!test);
    return n;
}

int main() {
    int n;
    int max_energy;
    do {
        std::cout << "Input a number of monks <= 100:" << std::endl;
        n = input();
    } while (n <= 0 || n > 100);
    do {
        std::cout << "Input max energy value: " << std::endl;
        max_energy = input();
    } while (max_energy <= 0);

    vector<int> team;
    for (size_t i = 0; i < n; ++i) {
        team.push_back(rand() % max_energy + 1);
        std::cout << "Monk " << i << " with energy " << team[i] << std::endl;
    }

    while (n / 2 + n % 2 >= 2) {

#pragma omp parallel
        {
#pragma omp sections
            {
#pragma omp section
                {
                    threadFunction(team, 0, n / 2);
                }
#pragma omp section
                {
                    threadFunction(team, n / 2, n);
                }

            }
        }

        int a = 0;
        team.erase(std::remove(team.begin(), team.end(), a), team.end());
        n = team.size();

    }
    if (team[0] > team[1]) {
        std::cout << "Win monk with energy " << team[0] <<
                  std::endl;
    } else {
        std::cout << "Win monk with energy " << team[1] <<
                  std::endl;
    }

    return 0;
}
