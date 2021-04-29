#include <bits/stdc++.h>

class grid{
public:
    int stat;
    int can[8];
    int can_num;

    void clear_can()
    {
        can_num = 0;
        for (int i = 0; i < 8; i++)can[i] = 0;
        if(stat == 2 || stat == -2)stat = 0;
    }
};
class board{
public:
    grid grid[8][8];
    int turn;
    int black, white;
    int can_num;
    int di[8] = {1, 0, -1, 0, 1, 1, -1, -1};
    int dj[8] = {0, 1, 0, -1, 1, -1, 1, -1};

    void init()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                grid[i][j].stat = 0;
            }
        }
        
        grid[3][3].stat = -1;
        grid[4][4].stat = -1;
        grid[4][3].stat = 1;
        grid[3][4].stat = 1;

        turn = 1;

        black = 2;
        white = 2;
    }

    int check()
    {
        can_num = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                grid[i][j].clear_can();
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if(grid[i][j].stat == 0 || grid[i][j].stat == 2 || grid[i][j].stat == -2)//空白なら
                {
                    for (int k = 0; k < 8; k++)
                    {
                        int nexti = i + di[k];
                        int nextj = j + dj[k];
                        if(0 > nexti || nexti > 7 || 0 > nextj || nextj > 7)continue;
                        if(grid[nexti][nextj].stat == -turn)
                        {
                            for (int l = 2; l < 8; l++)
                            {
                                int nexti = i + di[k] * l;
                                int nextj = j + dj[k] * l;
                                if(0 > nexti || nexti > 7 || 0 > nextj || nextj > 7)break;
                                if(grid[nexti][nextj].stat == turn)
                                {
                                    grid[i][j].stat = turn * 2;
                                    grid[i][j].can_num += l - 1;
                                    grid[i][j].can[k] += l - 1;
                                    can_num += l - 1;
                                    break;
                                }
                                if(grid[nexti][nextj].stat == 0)break;
                            }
                        }
                    }
                    
                }
            }
        }
        
        return can_num;
    }
    void put()
    {
        while(true)
        {
            int ini, inj, in;
            if(turn == 1)printf("黒の番です\n");
            else printf("白の番です\n");
            printf(">");
            scanf("%d", &in);
            ini = in / 10;
            inj = in % 10;
            if(0 > ini || ini > 7 || 0 > inj || inj > 7)
            {
                printf("正しい入力をしてください。\n");
                continue;
            }
            if(grid[ini][inj].stat == 2 || grid[ini][inj].stat == -2)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j <= grid[ini][inj].can[i]; j++)
                    {
                        grid[ini + di[i] * j][inj + dj[i] * j].stat = turn;
                    }
                    grid[ini][inj].stat = turn;
                }

                if(turn == 1)
                {
                    black += grid[ini][inj].can_num + 1;
                    white -= grid[ini][inj].can_num;
                }
                else
                {
                    black -= grid[ini][inj].can_num;
                    white += grid[ini][inj].can_num + 1;
                }
                
                break;   
            }
            printf("正しい入力をしてください。\n");
        }
        return;
    }
    void print()
    {
        printf("   0 1 2 3 4 5 6 7\n");
        for (int i = 0; i < 8; i++)
        {
            printf("%d0", i);
            for (int j = 0; j < 8; j++)
            {
                switch (grid[i][j].stat)
                {
                    case 0:
                        printf("・");
                    break;
                    case 1:
                        printf("黒");
                    break;
                    case -1:
                        printf("白");
                    break;
                
                    default:
                        printf("＊");
                    break;
                }
            }
            printf("\n");
        }
        printf("黒:%d 白:%d\n", black, white);
    }
    
    void game()
    {
        init();
        while(true)
        {
            check();
            if(can_num == 0)
            {
                turn *= -1;
                check();
                if(can_num == 0)
                {
                    break;
                }
                else
                {
                    printf("置く場所がありません。\n");
                    print();
                    put();
                    turn *= -1;
                }
            }
            else
            {
                print();
                put();
                turn *= -1;
            }
        }
        print();

        if(black > white)printf("黒の勝利！");
        else if(black == white)printf("引き分け!");
        else printf("白の勝利!");
        printf("\n");
    }
};

int main()
{
    board ribarsi;
    ribarsi.game();
}