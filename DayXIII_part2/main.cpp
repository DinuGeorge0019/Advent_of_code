#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

// Modulo Inverse taken from: https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
uint64_t modInverse(const uint64_t a, const uint64_t m)
{
    uint64_t m0 = m;
    uint64_t a0 = a;
    uint64_t y = 0;
    int64_t x = 1;

    if (m == 1)
        return 0;

    while (a0 > 1) {
        // q is quotient
        uint64_t q = a0 / m0;
        uint64_t t = m0;

        // m is remainder now, process same as Euclid's algo
        m0 = a0 % m0;
        a0 = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m;

    return x;
}

void part1(istream& inputFile)
{
    size_t bestBusId = 0;
    size_t minWaitTime = numeric_limits<size_t>::max();

    while (!inputFile.eof())
    {
        size_t timestamp;
        inputFile >> timestamp;
        inputFile.ignore();

        string line;
        getline(inputFile, line);
        istringstream ss(line);

        string busIdStr;
        while (getline(ss, busIdStr, ','))
        {
            if (busIdStr != "x")
            {
                istringstream busIdSs(busIdStr);
                size_t busId;
                busIdSs >> busId;

                size_t waitTime = (static_cast<size_t>(timestamp / busId) + 1) * busId - timestamp;
                if (waitTime < minWaitTime)
                {
                    minWaitTime = waitTime;
                    bestBusId = busId;
                }
            }
        }
    }

    std::cout << bestBusId * minWaitTime << endl;
}

void part2(istream& inputFile)
{
    vector<pair<size_t, size_t>> busIds;    // [ (idx, busId), ... ]

    while (!inputFile.eof())
    {
        size_t timestamp;
        inputFile >> timestamp;
        inputFile.ignore();

        string line;
        getline(inputFile, line);
        istringstream ss(line);

        size_t idx = 0;
        string busIdStr;
        while (getline(ss, busIdStr, ','))
        {
            if (busIdStr != "x")
            {
                size_t busId = stoi(busIdStr);

                busIds.emplace_back(idx, busId);
            }

            idx += 1;
        }
    }

    // Solve using the Chinese Remainder Theorem (CRT)
    // https://crypto.stanford.edu/pbc/notes/numbertheory/crt.html

    uint64_t M = accumulate(
        busIds.begin(),
        busIds.end(),
        static_cast<uint64_t>(1),
        [](const auto& p, const auto& e)
        {
            return p * e.second;
        });

    uint64_t timestamp = 0;
    for (const auto& busId : busIds)
    {
        const uint64_t m = static_cast<uint64_t>(busId.second);
        const uint64_t a = (m - busId.first % m) % m;     // remainder
        const uint64_t b = M / m;
        const uint64_t bPrime = modInverse(b, m);

        timestamp += a * b * bPrime;
    }

    timestamp = timestamp % M;

    cout << timestamp << endl;
}


int main()
{

    ifstream inputFile;
    inputFile.open("input.txt");

    cout << "Part 1: " << endl;
    part1(inputFile);

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    std::cout << "Part 2: " << endl;
    part2(inputFile);

    inputFile.close();

    return 0;
}