#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(NULL));

    string filename[301];
    for (int i = 1; i <= 300; ++i) {
        filename[i] = to_string(i) + ".in";
    }

    for (int i = 1; i <= 300; ++i) {
        if (access(filename[i].c_str(), 0) != -1)
            cout << i << ' ' << "존재\n";
        else {
            cout << i << ' ' << "없음\n";
            ofstream HzWriteFile(filename[i]);


            int hp1, hp2;
            hp1 = rand() % 300 + 1;
            hp2 = rand() % 300 + 1;
            cout << hp1 << ' ' << hp2 << '\n';
            HzWriteFile << hp1 << ' ' << hp2 << '\n';

            int d1, d2, d3, d4;
            d1 = rand() % (300 - i) + 1;
            d2 = rand() % (300 - i) + 1;
            d3 = rand() % (300 - i) + 1;
            d4 = rand() % (300 - i) + 1;

            cout << d1 << ' ' << d2 << ' ' << d3 << ' ' << d4 << '\n';
            HzWriteFile << d1 << ' ' << d2 << ' ' << d3 << ' ' << d4 << '\n';


            vector<tuple<int, string>> v;
            int before = 0;
            while (before <= 300) {
                int frame = rand() % 20 + before;
                if (frame > 300) break;
                string s;
                int type = rand() % 2;
                if (type == 0) {
                    s = "attack";
                    before = frame + 7;
                }
                else {
                    s = "riposte";
                    before = frame + 11;
                }
                v.push_back({frame, s});
            }

            HzWriteFile << v.size() << '\n';
            for (auto [frame, type] : v) {
                cout << frame << ' ' << type << '\n';
                HzWriteFile << frame << ' ' << type << '\n';
            }

            HzWriteFile.close();
        }
    }
}