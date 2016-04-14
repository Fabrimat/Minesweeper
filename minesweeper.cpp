#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

string W,R,G,O,B,P,C,GR,T;

void ClearScreen(){
    cout << string( 100, '\n' );
}

void ResetMap(int map[50][50], bool cover[50][50], int x, int y){
    // Resetting the map
    for (int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            map[i][j] = 0;
            cover[i][j] = true;
        }
    }
    return;
}

void CreateMap(int map[50][50], int x, int y, int bomb, int ExcX, int ExcY){
    // Generating the map
    int PosBombY,PosBombX;

    for (int i=0;i<bomb;i++){
        PosBombY = rand()%y;
        PosBombX = rand()%x;
        if (map[PosBombY][PosBombX] != -1 || PosBombY == ExcY && PosBombX == ExcX){
            map[PosBombY][PosBombX] = -1;
            for (int j=PosBombY-1; j<PosBombY+2; j++){
                for (int k=PosBombX-1; k<PosBombX+2; k++){
                    if (map[j][k] != -1 && j <= y && j >=0 && k <= x && k >=0)
                        map[j][k] = map[j][k]+1;
                }
            }
        }
        else
            i--;
    }

    return;
}

void PrintMap(int map[50][50], bool cover[50][50], int x, int y){
    // Graphics
    cout << C << "     O" << W;
    for (int i=0;i<x-1;i++){
        cout << C << "   O" << W;
    }
    cout << endl << O << "   ╔" << W;
    for (int j=0;j<x-1;j++)
        cout << O << "═══╦" << W;
    cout << O << "═══╗" << W << endl;
    for (int i=0;i<y;i++){

        if (i != 0 && i != y)
            cout << O << "   ╠" << W;
        for (int j=0;j<x-1;j++)
            if (i != 0)
                cout << O << "═══╬" << W;
            if (i > 0)
                cout << O << "═══╣" << W << endl;
            cout << C << " O " << W;
        for (int j=0;j<x;j++){
            if (cover[i][j] == true)
                cout << O << "║ " << GR << "# " << W;
            else{
                if (map[i][j] == -1)
                    cout << O << "║ " << GR << "@ " << W;
                else{
                    if (map[i][j] == 0)
                        cout << O << "║   "  << W;
                    else if (map[i][j] == 1)
                        cout << O << "║ " << B << map[i][j] << " " << W;
                    else if (map[i][j] == 2)
                        cout << O << "║ " << G << map[i][j] << " " << W;
                    else if (map[i][j] == 3)
                        cout << O << "║ " << R << map[i][j] << " " << W;
                    else
                        cout << O << "║ " << P << map[i][j] << " " << W;
                }
            }
        }
        cout << O << "║" << W << endl;
    }
    cout << O << "   ╚" << W;
    for (int j=0;j<x-1;j++)
        cout << O << "═══╩" << W;
    cout << O << "═══╝" << W << endl;
    return;
}

void ZeroClick (int map[50][50], bool cover[50][50], int x, int y, int SelX, int SelY){

    for(int r=0;r<3;r++){ // Test
        for (int i=0; i<x; i++){
            for (int j=0; j<y; j++){
                for (int k=i-1; k<i+2; k++){
                    for (int w=j-1; w<j+2; w++){
                        // cout << k << "\t" << w << "\t" << cover[k][w] << endl;
                        if (map[k][w] == 0 && cover[k][w] == false && k <= y && k >=0 && w <= x && w >=0){
                            cover[i][j] = false;
                        }
                        // else{
                        //     cout << k << "\t" << w << "\t" << cover[k][w] << endl;
                        // }
                    }
                }
            }
        }
    }
    //cin.ignore().get();

    return;
}

int InsertValue(char xOrY, int a){
        int Value;
        do{
            if (xOrY == 'x'){
                cout << "Inserisci X - ";
                cin >> Value;
            }
            if (xOrY == 'y'){
                cout << "Inserisci Y - ";
                cin >> Value;
            }
            if (Value > a+1){
                cout << "Coordinate non valide.\n";
            }
        }
        while(Value > a+1);
        return Value-1;
    }

bool CheckWin(int map[50][50], bool cover[50][50], int x, int y){
    int CountMap = 0;
    int CountCover = 0;
    int i,j;
    for (i=0; i<x; i++){
        for (j=0; j<y; j++){
            if (map[i][j] == -1)
                CountMap++;
            if (cover[i][j] == true)
                CountCover++;
        }
    }
    if (CountMap == CountCover){
        cout << "You win!\n";
        return true;
    }
    else
        return false;
}

int main(){
    int y,x,bomb;
    bool Error = false;
    int Choose;
    char Colors;
    int map[50][50];
    bool cover[50][50];
    int SelX, SelY;
    bool ExitValue = false;
    int PlayCount = 0;

    ClearScreen();

    do {
        cout << "Colori supportati? (y/n) - ";
        cin >> Colors;
    }
    while (Colors != 'y' && Colors != 'n');

    cout << "\n";
    if (Colors == 'y'){
        W = "\033[0m";    // normal
        R = "\033[31m";   // red
        G = "\033[32m";  // green
        O = "\033[33m";   // orange
        B = "\033[34m";   // blue
        P = "\033[35m";   // purple
        C = "\033[36m";   // cyan
        GR = "\033[37m";  // gray
        T = "\033[93m";    // tan
    }
    else if (Colors == 'n'){
        W = "";    // normal
        R = "";   // red
        G = "";  // green
        O = "";   // orange
        B = "";   // blue
        P = "";   // purple
        C = "";   // cyan
        GR = "";  // gray
        T = "";    // tan
    }

    cout << C << "Scegliere la difficolta':\n" << W;
    cout << G << "[1]" << GR << " - " << G << "Principiante\n" << W;
    cout << T << "[2]" << GR << " - " << T << "Intermedio\n" << W;
    cout << R << "[3]" << GR << " - " << R << "Esperto\n" << W;
    cout << O << "[4]" << GR << " - " << O << "Personalizzato\n" << W;

    do{
        cout << C <<"\nInserire il valore" << GR << " - " << C;
        cin >> Choose;
        if (Choose > 4 || Choose < 1)
            cout << R << "Valore non valido.\n\n" << W;
    }
    while (Choose > 4 || Choose < 1);

    switch (Choose) {
        case 1:
            y = 9;
            x = 9;
            bomb = 10;
            break;
        case 2:
            y = 14;
            x = 17;
            bomb = 40;
            break;
        case 3:
            y = 16;
            x = 16;
            bomb = 99;
            break;
        case 4:
            do {
                cout << C << "Inserire la larghezza"<< GR << " - " << C;
                cin >> x;
                cout << C << "Inserire l'altezza"<< GR << " - " << C;
                cin >> y;
                if (x>50 || y>50 || x==0 || y==0){
                    cout << R << "Coordinate non valide (Max 50x50)" << W << endl;
                }
            }
            while (x>50 || y>50 || x==0 || y==0);
            do{
                cout <<  C << "Inserire il numero delle bombe"<< GR << " - " << C;
                cin >> bomb;
                if (bomb > (y*x)-1){
                    cout << R << "Numero bombe non valido." << W << endl;
                }
            }
            while (bomb > y*x);
            break;
        default:
            y = 5;
            x = 5;
            bomb = 5;
            break;
    }

    srand(time(NULL));

    ResetMap(map, cover, x, y);


    do {

        ClearScreen();
        PrintMap(map, cover, x, y);

        SelX = InsertValue('x',x);
        SelY = InsertValue('y',y);

        if (PlayCount == 0)
            CreateMap(map, x, y, bomb, SelX, SelY);

        if (map[SelX][SelY] == 0){
            cover[SelX][SelY] = false;
            ZeroClick(map, cover, x, y, SelX, SelY);
        }
        else if (map[SelX][SelY] == -1){
            cout << "Boom!\n";
            cover[SelX][SelY] = false;
            ExitValue = true;
        }
        else{
            cover[SelX][SelY] = false;
        }

        if (ExitValue == false)
            ExitValue = CheckWin(map, cover, x, y);

        PlayCount++;
    }
    while(ExitValue == false);

    return 0;
}
