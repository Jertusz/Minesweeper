//
// Created by JS on 09.12.2019.
//
#include <stdlib.h>
#include <iostream>
using namespace std;

struct field {
    int value;
    bool discovered;
};

field map[10][10];

bool generate_map ()
{
    for (int x = 0; x<10; x++)
        for (int y = 0; y<10; y++)
        {
            map[x][y].value = 0;
            map[x][y].discovered = false;
        }
    return true;
}

void place_mine(int poz_x, int poz_y);
void generate_mines ()
{
    int poz_x, poz_y;
    int quantity = 10;


    while (quantity>0)
    {
        poz_x = rand()%10;
        poz_y = rand()%10;

        if (map[poz_x][poz_y].value!=9)
        {
            place_mine(poz_x,poz_y);
            quantity--;
        }
    }
}


void place_mine (int poz_x, int poz_y)
{
    if (map[poz_x][poz_y].value!=9)
    {
        map[poz_x][poz_y].value = 9;

        for (int k = -1; k<2; k++)
            for (int l = -1; l<2; l++)
            {
                if ((poz_x+l)<0 || (poz_y+k)<0 ) continue;
                if ((poz_x+l)>9 || (poz_y+k)>9 ) continue;
                if (map[poz_x+l][poz_y+k].value==9) continue;
                map[poz_x+l][poz_y+k].value += 1;
            }
    }
}

int unveil_field(int x, int y, int lost)
{
    if (x<0 || x>9) return lost;
    if (y<0 || y>9) return lost;
    if (map[x][y].discovered==true) return lost;

    if(map[x][y].value!=9 && map[x][y].discovered==false) {
        map[x][y].discovered = true;
    } else if (map[x][y].value == 9) {
        lost = 0;
        cout << "BOMBA";
    }

    if (map[x][y].value!=0) return lost;

    unveil_field(x - 1, y - 1, lost);
    unveil_field(x - 1, y, lost);
    unveil_field(x - 1, y + 1, lost);
    unveil_field(x + 1, y - 1, lost);
    unveil_field(x + 1, y, lost);
    unveil_field(x + 1, y + 1, lost);
    unveil_field(x, y - 1, lost);
    unveil_field(x, y, lost);
    unveil_field(x, y + 1, lost);
    return lost;
}


int show_map()
{
    system ("cls");
    int win = 0;
    for (int i = 0; i<10; i++)
    {
        for (int j = 0; j<10; j++)
        {
            if (map[j][i].discovered==true)
            {
                if (map[j][i].value==0)
                    cout << " ";
                else
                    cout << map[j][i].value;

            }
            if (map[j][i].discovered==false)
                cout << "#";
                win++;
        }
        cout << endl;
    }
    return win;
}


int main()
{
    generate_map();
    generate_mines();
    show_map();
    int x,y,lost = 1, win = 0;
    while(lost != 0 && win != 10){
        cout << "Wpisz x:";
        cin >> x;
        cout << "Wpisz y:";
        cin >> y;
        lost = unveil_field(x, y, lost);
        win = show_map();
    }
    if(lost == 0) {
        cout << "Trafiles na bombe i przegrales";
    } else if (win == 10){
        cout << "Wygrana";
    }



}
