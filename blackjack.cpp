#include "raylib.h"
#include <iostream>
#include <cstring>
using namespace std;

int t,a;

int generare()
{
    int minim=2;
    int maxim=11;
    return GetRandomValue(minim, maxim);
}

int carterandom()
{
    int minim=1;
    int maxim=4;
    return GetRandomValue(minim, maxim);
}

struct carti{
    int valcarte[20];
    int simbol[20];
    int as[20];
    int manadealer[20];
    int asdealer[20]; 
} n;

void pregenerare()
{
    for(int i=0; i<20; i++)
        n.simbol[i]=carterandom();
}

int main() {
    t=0;
    int scor=0;
    int ace=0;
    bool bust = false;
    bool play=true;
    bool over=false;
    int dealerace=0;
    SetRandomSeed(time(NULL));

    pregenerare();
    n.manadealer[0]=generare();
    int dealer=n.manadealer[0];

    const int screenWidth = 1440;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Blackjack Simplu");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        if(scor>21&& ace==0) {
            DrawText("Ati Pierdut", 500, 360, 80, RED);
            over=true;
            play=false;
        }
        else if(dealer>21 && dealerace==0){
            DrawText("Ati Castigat!", 500, 360, 80, GREEN);
            over=true;
            play=false;
        }
         else if((dealer<=21 && scor<=dealer) && play==false) {
            DrawText("Ati Pierdut", 500, 360, 80, RED);
            over=true;
            play=false;
        }
         else   if(scor==21) play=false;
        // Logica dealer
        if(!play && !over){
            for(int i=1; i<20 && dealer <= scor; i++){
                if(n.manadealer[i] == 0){
                    n.manadealer[i] = generare();
                    dealer += n.manadealer[i];
                    if(n.manadealer[i]==11) {
                        n.asdealer[i]=1;
                        dealerace=1;
                    }
                    if(dealer > scor || dealer == 21){
                        over = true;
                        break;
                    }
                    if(dealer>21 && dealerace==1)
                    {
                        int ok=0;
                        for(int i=0; i<20; i++)
                        if(n.manadealer[i]==11) {
                            n.manadealer[i]=1;
                            dealer=dealer-10;
                            ok=1;
                            break;
                        }
                        else if(ok==0) dealerace=0;
                    }
                }
            }
        }
        DrawText("Scor Dealer:", 120, 270, 30, BLACK);
        char scordealer[4];
        scordealer[0]='0'+dealer/10;
        scordealer[1]='0'+dealer%10;
        scordealer[2]='\0';
        DrawText(scordealer,330, 270,30, BLACK);

        // Desenare carti dealer
        DrawRectangle(220, 100, 100, 150, LIGHTGRAY);
        for(int i=0;i<20;i++){
            if(n.manadealer[i] == 0) break;
            DrawRectangle(100 + i*120, 100, 100, 150, LIGHTGRAY);
            char z[3];
            if(n.manadealer[i]==11 || n.manadealer[i]==1)
                DrawText("A", 140 + i*120, 150, 50, BLACK);
            else{
                if(n.simbol[i]==1) strcpy(z,"10");
                else{
                    if(n.simbol[i]==2) z[0]='J';
                    if(n.simbol[i]==3) z[0]='Q';
                    if(n.simbol[i]==4) z[0]='K';
                    z[1]='\0';
                }
                if(n.manadealer[i]<10){ z[0]='0'+n.manadealer[i]; z[1]='\0'; }
                DrawText(z, 140 + i*120, 150, 50, BLACK);
            }
        }

        if(play) DrawText("?", 260, 150, 50, BLACK);

        // Player
        if(!bust){
            if(IsKeyPressed(KEY_H) && play){
                n.valcarte[t]=generare();
                t++;
            }
            if(IsKeyPressed(KEY_S)) play=false;

            scor=0; ace=0;
            for(int i=0; i<t; i++){
                scor += n.valcarte[i];
                if(n.valcarte[i]==11){ n.as[i]=1; ace=1; }
            }

            if(scor>21 && ace==0) bust=true;
            else if(scor>21 && ace==1){
                for(int i=0;i<t;i++)
                    if(n.as[i]==1){ n.as[i]=0; n.valcarte[i]=1; break; }
            }
        }

        // Carti player
        for(int i=0;i<t;i++){
            DrawRectangle(100 + i*120, 500, 100, 150, LIGHTGRAY);
            char p[3];
            if(n.valcarte[i]==11 || n.valcarte[i]==1)
                DrawText("A", 140 + i*120, 550, 50, BLACK);
            else{
                if(n.simbol[i]==1) strcpy(p,"10");
                else{
                    if(n.simbol[i]==2) p[0]='J';
                    if(n.simbol[i]==3) p[0]='Q';
                    if(n.simbol[i]==4) p[0]='K';
                    p[1]='\0';
                }
                if(n.valcarte[i]<10){ p[0]='0'+n.valcarte[i]; p[1]='\0'; }
                DrawText(p, 140 + i*120, 550, 50, BLACK);
            }
        }
        DrawText("Scor:", 120, 450, 30, BLACK);
        char scordisplay[4];
        scordisplay[0]='0'+scor/10;
        scordisplay[1]='0'+scor%10;
        scordisplay[2]='\0';
        DrawText(scordisplay,250,450,30, BLACK);

        EndDrawing();
        
        if(IsKeyPressed(KEY_ESCAPE)) break;
    }

    CloseWindow();
    return 0;
} 