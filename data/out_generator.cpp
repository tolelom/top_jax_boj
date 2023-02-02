#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;


int hp1, hp2;
int d1, d2, d3, d4;
int m;

tuple<int, int, int, int> dp[301][301][301][3]; 
int time_table[301];
bool ans = false;

void attack(int jax_hp, int fiora_hp, int remain_skill, int time, queue<tuple<int, int, int, int, int, int, int, int>>& q) {
    int b_time = time, b_jax_hp = jax_hp, b_fiora_hp = fiora_hp, b_remain_skill = remain_skill;
    for (int sub_time = time + 1; sub_time <= time + 5; ++sub_time) {
        if (time_table[sub_time] == 1) 
            jax_hp -= d3;
        if (time_table[sub_time] == 3) 
            jax_hp -= d4;
    }
    
    if (time_table[time + 5] != 2) 
        fiora_hp -= d1;

    jax_hp = max(jax_hp , 0);
    fiora_hp = max(fiora_hp, 0);

    q.push({jax_hp, fiora_hp, remain_skill, time + 6, b_jax_hp, b_fiora_hp, b_remain_skill, b_time});
}

void counter_strike(int jax_hp, int fiora_hp, int remain_skill, int time, queue<tuple<int, int, int, int, int, int, int, int>>& q) {
    int b_time = time, b_jax_hp = jax_hp, b_fiora_hp = fiora_hp, b_remain_skill = remain_skill;
    if (time_table[time + 15] != 2)
        fiora_hp -= d2;

    if (time_table[time + 15] == 1) 
        jax_hp -= d3;
    if (time_table[time + 15] == 3) 
        jax_hp -= d4;
    
    jax_hp = max(jax_hp , 0);
    fiora_hp = max(fiora_hp, 0);
    
    q.push({jax_hp, fiora_hp, remain_skill - 1, time + 16, b_jax_hp, b_fiora_hp, b_remain_skill, b_time});       
}

void pass(int jax_hp, int fiora_hp, int remain_skill, int time, queue<tuple<int, int, int, int, int, int, int, int>>& q) {
    int b_time = time, b_jax_hp = jax_hp, b_fiora_hp = fiora_hp, b_remain_skill = remain_skill;
    if (time_table[time] == 1)
        jax_hp -= d3;
    if (time_table[time] == 3)
        jax_hp -= d4;
    jax_hp = max(jax_hp, 0);

    q.push({jax_hp, fiora_hp, remain_skill, time + 1, b_jax_hp, b_fiora_hp, b_remain_skill, b_time});
}


int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string filename[301];
    string outfile[301];
    for (int i = 1; i < 300; ++i) {
        filename[i] = to_string(i) + ".in";
        outfile[i] = to_string(i) + ".out";
    }
    

    for (int i = 1; i < 300; ++i) {
        if (access(filename[i].c_str(), 0) != -1) {
            cout << i << ' ' << "존재\n";
            
            ifstream HzReadFile(filename[i]);
            ofstream HzWriteFile(outfile[i]);

            for (int i = 0; i < 301; ++i) {
                for (int j = 0; j < 301; ++j) {
                    for (int k = 0; k < 301; ++k) {
                        for (int l = 0; l < 3; ++l) 
                            dp[i][k][j][l] = {0, 0, 0, 0};
                    }
                }
                time_table[i] = 0;
            }
            ans = false;        

            HzReadFile >> hp1 >> hp2;
            HzReadFile >> d1 >> d2 >> d3 >> d4;
            cout << hp1 << ' ' << hp2 << '\n';
            cout << d1 << ' ' << d2 << ' ' << d3 << ' ' << d4 << '\n';

            HzReadFile >> m;
            for (int i = 0; i < m; ++i) {
                int attack_time;
                string type_of_attack;
                HzReadFile >> attack_time >> type_of_attack;

                if (type_of_attack == "attack") {
                    if (attack_time + 6 <= 300)
                        time_table[attack_time + 6] = 1;
                }
                if (type_of_attack == "riposte") {
                    for (int j = attack_time + 1; j <= attack_time + 9; ++j) {
                        if (j > 300) continue;
                        time_table[j] = 2;
                    }
                    if (attack_time + 10 <= 300)
                        time_table[attack_time + 10] = 3;
                }
            }

            queue<tuple<int, int, int, int, int, int, int, int>> q; // jax, fiora, counter strike, time, b_jax, b_fiora, b_couter strike, b_time
            q.push({hp1, hp2, 2, 0, 0, 0, 0, 0}); 

            // bfs
            while (!q.empty()) {
                auto [jax_hp, fiora_hp, remain_skill, cur_time, before_jax_hp, before_fiora_hp, before_remain_skill, before_time] = q.front();
                q.pop();
                
                if (cur_time > 300) { // time out
                    continue;
                }
                
                

                if (dp[cur_time][jax_hp][fiora_hp][remain_skill] != tuple<int, int, int, int>{0, 0, 0, 0})
                    continue;

                dp[cur_time][jax_hp][fiora_hp][remain_skill] = {before_time, before_jax_hp, before_fiora_hp, before_remain_skill};

                if (jax_hp == 0)
                    continue;
                
                if (fiora_hp == 0) 
                    ans = true;


                // attack 
                if (time_table[cur_time + 5] != 2)
                    attack(jax_hp, fiora_hp, remain_skill, cur_time, q);  

                // counter strike
                if (remain_skill > 0) 
                    counter_strike(jax_hp, fiora_hp, remain_skill, cur_time, q);

                // pass
                pass(jax_hp, fiora_hp, remain_skill, cur_time, q);
            }

            if (ans == false)
                HzWriteFile << "NO" << '\n';
            else {
                HzWriteFile << "YES" << '\n';
                deque<tuple<int, string>> ans_vector; // time, skill

                for (int time = 0; time < 300; ++time) {
                    for (int jax_hp = 299; jax_hp >= 0; --jax_hp) {
                        for (int remain_skill = 0; remain_skill < 3; ++remain_skill) {
                            if (dp[time][jax_hp][0][remain_skill] != tuple<int, int, int, int> {0, 0, 0, 0}) {
                                int c_time = time, c_jax_hp = jax_hp, c_fiora_hp = 0, c_remain_skill = remain_skill;
                                while (c_time != 0) {
                                    // cout << c_time << ' ' << c_jax_hp << ' ' << c_fiora_hp << ' ' << c_remain_skill << '\n';
                                    auto [b_time, b_jax_hp, b_fiora_hp, b_remain_skill] = dp[c_time][c_jax_hp][c_fiora_hp][c_remain_skill];
                                    // cout << b_time << ' ' << b_jax_hp << ' ' << b_fiora_hp << ' ' << b_remain_skill << '\n';
                                    if (c_time - b_time == 6) 
                                        ans_vector.push_front({b_time, "attack"});
                                    if (c_time - b_time == 16) 
                                        ans_vector.push_front({b_time, "counter attack"});

                                    c_time = b_time, c_jax_hp = b_jax_hp, c_fiora_hp = b_fiora_hp, c_remain_skill = b_remain_skill;
                                }    
                                goto end;
                            }
                        }
                    }
                }
                end:;

                for (auto [time, attack] : ans_vector) {
                    HzWriteFile << time << ' ' << attack << '\n';
                }
            }

            HzReadFile.close();
            HzWriteFile.close();
        }
        else {
            cout << i << ' ' << "없음\n";
        }
    }
}