#include <cstdio>
#include <cassert>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;


int jax_hp, fiora_hp;
int d1, d2, d3, d4;
int m;
int fiora_timeline[301];
int jax_timeline[301];
int your_jax_timeline[301];

int sol_jax_hp, sol_fiora_hp, sol_frame;
int your_jax_hp, your_fiora_hp, your_frame;

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r"); // 입력 데이터 파일
    FILE *sol = fopen(argv[2], "r"); // 출력 데이터 파일
    FILE *out = fopen(argv[3], "r"); // 유저의 출력 파일

    fscanf(in, "%d", &jax_hp);
    fscanf(in, "%d", &fiora_hp);

    fscanf(in, "%d", &d1);
    fscanf(in, "%d", &d2);
    fscanf(in, "%d", &d3);
    fscanf(in, "%d", &d4);

    fscanf(in, "%d", &m);
    for (int i = 0; i < m; ++i) {
        int fiora_frame;
        char c_fiora_skill_name[20];
        fscanf(in, "%d", &fiora_frame);
        fscanf(in, "%s", c_fiora_skill_name);

        string fiora_skill_name = c_fiora_skill_name;
        if (fiora_skill_name == "attack") 
            fiora_timeline[fiora_frame + 6] = 1;
        if (fiora_skill_name == "riposte") {
            for (int t = fiora_frame + 1; t <= fiora_frame + 9; ++t)
                fiora_timeline[t] = 2;
            fiora_timeline[fiora_frame + 10] = 3;
        }
    }
    fclose(in);



    int ans; // 출력 ans
    fscanf(sol, "%d", &ans);
    
    int jax_frame;
    while (fscanf(sol, "%d", &jax_frame) != EOF) {
        char c_jax_skill_name[20];
        fscanf(sol, "%s", c_jax_skill_name);
        string jax_skill_name = c_jax_skill_name;
        if (jax_skill_name == "attack")
            jax_timeline[jax_frame + 5] = 1;
        if (jax_skill_name == "counter") {
            fscanf(sol, "%s", c_jax_skill_name); // dummy, attack

            for (int t = jax_frame + 1; t <= jax_frame + 14; ++t)
                jax_timeline[t] = 2;
            jax_timeline[jax_frame + 15] = 3;
        }
    }
    fclose(sol);

    int yourans; // your ans
    fscanf(out, "%d", &yourans);
    // assert(fscanf(out,"%d",&yourans) == 1); // 여기서 에러
    // assert(ans == yourans); // 여기서 에러 난다고?

    int your_jax_frame;
    while (fscanf(out, "%d", &your_jax_frame) != EOF) {
        char c_your_jax_skill_name[20];
        fscanf(out, "%s", c_your_jax_skill_name);
        string your_jax_skill_name = c_your_jax_skill_name; 
        if (your_jax_skill_name == "attack")
            your_jax_timeline[your_jax_frame + 5] = 1;
        if (your_jax_skill_name == "counter") {
            fscanf(out, "%s", c_your_jax_skill_name); // dummy, attack

            for (int t = your_jax_frame + 1; t <= your_jax_frame + 14; ++t)
                your_jax_timeline[t] = 2;
            your_jax_timeline[your_jax_frame + 15] = 3;
        }
    }
    fclose(out);


    sol_jax_hp = jax_hp, sol_fiora_hp = fiora_hp;
    for (sol_frame = 0; sol_frame <= 300; ++sol_frame) {
        if (fiora_timeline[sol_frame] == 2 || jax_timeline[sol_frame] == 2)
            continue;

        if (jax_timeline[sol_frame] == 1)
            sol_fiora_hp -= d1;
        if (jax_timeline[sol_frame] == 3)
            sol_fiora_hp -= d2;
        if (fiora_timeline[sol_frame] == 1)
            sol_jax_hp -= d3;
        if (fiora_timeline[sol_frame] == 3)
            sol_jax_hp -= d4;
        
        sol_jax_hp = max(0, sol_jax_hp);
        sol_fiora_hp = max(0, sol_fiora_hp);

        if (sol_jax_hp > 0 && sol_fiora_hp == 0)
            break;
    }

    your_jax_hp = jax_hp, your_fiora_hp = fiora_hp;
    for (your_frame = 0; your_frame <= 300; ++your_frame) {
        if (fiora_timeline[your_frame] == 2 || your_jax_timeline[your_frame] == 2)
            continue;

        if (your_jax_timeline[your_frame] == 1)
            your_fiora_hp -= d1;
        if (your_jax_timeline[your_frame] == 3)
            your_fiora_hp -= d2;
        if (fiora_timeline[your_frame] == 1)
            your_jax_hp -= d3;
        if (fiora_timeline[your_frame] == 3)
            your_jax_hp -= d4;  

        your_jax_hp = max(0, your_jax_hp);
        your_fiora_hp = max(0, your_fiora_hp);

        if (your_jax_hp > 0 && your_fiora_hp == 0)
            break;          
    }
    
    assert(sol_frame == your_frame);
    assert(sol_jax_hp == your_jax_hp);
    assert(sol_fiora_hp == your_fiora_hp);
    

    return 0;
}