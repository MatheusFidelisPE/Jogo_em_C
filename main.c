#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define max_life 10
#define max_balas 10


const int screenWidth = 900;
const int screenHeigth = 680;

const float tam_width = 25;
const float tam_height = 20;

const int Zero_eixo_x = 30;
const int Zero_eixo_y = 30;

const float deslocamento_y = 10;
const float deslocamento_x = 10;

typedef struct
{
    Vector2 p;
    bool pegou;
    Texture2D image;
    Rectangle ret;
}Tmunicao;

typedef struct
{
    Vector2 position;
    bool existe;
}Tbalas;
typedef struct
{
    Rectangle dimen;
    bool vivo;
    float deslocamentox;
    float deslocamentoy;
    Texture2D imagem;
}Tinimigo;
typedef struct
{
    Rectangle dimen;
    Texture2D imagem;

}Tobstaculos;
typedef struct
{
    Rectangle dimen;
    Texture2D imagem;
    bool chave;
    int tipo;
    bool aberto;
}Tbaus;
typedef struct
{
    Vector2 position;
    float radius;
    int colision;
    int life;
    bool chave_verdadeira;

    bool fim;
    Tbalas balas[50];
}Tbola;
typedef struct
{
    Rectangle dimen;
    Texture2D imagem;
}Tporta;
typedef struct
{
    Vector2 position;
    bool existe;
    float deslocamento_x;
    float deslocamento_y;
}Tbala;
int main()
{
    clock_t t = clock();

    srand(time(NULL));
    Tbola bola;
    Tporta porta_saida;

    porta_saida.dimen.x = 839;
    porta_saida.dimen.y = 18;
    porta_saida.dimen.width = 50;
    porta_saida.dimen.height = 46;


    //Definindo a posição inicial do personagem e definindos limites superior e lateral esquerdo.
    int position_initial_x = 40, position_initial_y = 50;
    bola.position = (Vector2){position_initial_x,position_initial_y};
    bola.radius = 2;
    bola.chave_verdadeira = false;
    bola.life = 5;
    bola.fim = false;

    //Tbala balas[max_balas];
    int figura_desce = 0, figura_direita = 0, figura_esquerda = 0, figura_sobe = 0;
    int direcao;


    Vector2 positions_municao_mapa[] =  {   {698,525},
                                            {843,156},
                                            {407,293},
                                            {262,617}};
    int qte_municao = sizeof(positions_municao_mapa)/8;
    Tmunicao item_municao_mapa[qte_municao];
    InitWindow(screenWidth, screenHeigth, "Labirinto Mortal");
    Vector2 positions[] = { {65,108},
                            {65,154},
                            {66,198},
                            {163,197},
                            {66,336},
                            {114,336},
                            {115,107},
                            {309,107},
                            {308,200},
                            {309,247},
                            {308,292},
                            {18,476},
                            {65,475},
                            {113,522},
                            {307,475},
                            {359,476},
                            {260,522},
                            {405,523},
                            {357,568},
                            {405,198},
                            {746,523},
                            {795,523},
                            {697,568},
                            {794,613},
                            {843,522},
                            {794,202},
                            {744,292},
                            {745,154},
                            {744,108},
                            {453,198},
                            {503,199},
                            {502,244},
                            {503,292},
                            {503,336},
                            {453,428},
                            {503,429},
                            {258,430},
                            {503,613},
                            {599,62},
                            {453,17},
                            {599,152},
                            {358,107},
                            {648,336},
                            {648,384},
                            {744,430},
                            {210,613},
                            {549,523},
                            {601,523},
                            {795,430},
                            {599,198},
                            {794,290},
                            {357,61},
                            {258,17},
                            {112,16},
                            {503,152},
                            {308,384},
                            {161,271},
                            {66,380},
                            {600,290},
                            {841,337},
                            {112,568},
                            {597,569},
                            {211,337},
                            {794,17}};

    Vector2 positions_baus[] =  {{64,523},
                                {115,156},
                                {841,200},
                                {358,526},
                                {840,613},
                                {453,248},
                                {18,524},
                                {673,248},
                                {553,434},
                                {745,20},
                                {405,18}};

     Vector2 positions_inim[] = {   {552,65},
                                    {177,430},
                                    {310,19},
                                    {648,246},
                                    {699,384},
                                    {406,570},
                                    {262,292},
                                    {357,433},
                                    {357,155},
                                    {598,616},
                                    {747,201},
                                    {162,431},
                                    {308,17},
                                    {864,114},
                                    {67,247}};
     int qte_inimigos = sizeof(positions_inim)/8;
     int baus[] = {1,1,2,2,2,3,3,3,1,2,3,2};
    //1-chave
    //2-monstro
    //3-vida

    //Leitura de imagens
    int tam = sizeof(positions)/8;
    int tam_bau = sizeof(positions_baus)/8;
    Tobstaculos obstaculos[tam];
    Tbaus bau[tam_bau];

    Texture2D textura = LoadTexture("900x682.png");

    Texture2D desce0 = LoadTexture("./personagem/desce1.png");
    Texture2D desce1 = LoadTexture("./personagem/desce2.png");
    Texture2D desce2 = LoadTexture("./personagem/desce3.png");
    Texture2D desce3 = LoadTexture("./personagem/desce4.png");

    Texture2D direita1 = LoadTexture("./personagem/direita1.png");
    Texture2D direita2 = LoadTexture("./personagem/direita2.png");
    Texture2D direita3 = LoadTexture("./personagem/direita3.png");
    Texture2D direita4 = LoadTexture("./personagem/direita4.png");

    Texture2D esquerda1 = LoadTexture("./personagem/esquerda1.png");
    Texture2D esquerda2 = LoadTexture("./personagem/esquerda2.png");
    Texture2D esquerda3 = LoadTexture("./personagem/esquerda3.png");
    Texture2D esquerda4 = LoadTexture("./personagem/esquerda4.png");
    //leitura
    Texture2D sobe1 = LoadTexture("./personagem/sobe1.png");
    Texture2D sobe2 = LoadTexture("./personagem/sobe2.png");
    Texture2D sobe3 = LoadTexture("./personagem/sobe3.png");
    Texture2D sobe4 = LoadTexture("./personagem/sobe4.png");
    //leitura monstro mapa
    Texture2D monstro_mapa = LoadTexture("./monstros/monstromapa.png");
    Texture2D monstro_mapa2 = LoadTexture("./monstros/monstromapa2.png");
    //Leitura de imagens correspondentes a munição, bomba e efeitos de explosões.
    Texture2D explosao[4] = {LoadTexture("./bomba/explosao1.png"),
                            LoadTexture("./bomba/explosao2.png"),
                            LoadTexture("./bomba/explosao3.png"),
                            LoadTexture("./bomba/explosao4.png")};
    Texture2D bala = LoadTexture("./bomba/bomba.png");


    Texture2D municao_mapa_image = LoadTexture("./bomba/municao.png");


    porta_saida.imagem = LoadTexture("porta.png");

    Texture2D vida = LoadTexture("vida.png");




    SetTargetFPS(10);


    //Construção de paredes

    for(int contador  = 0; contador < tam; contador++)
    {
        obstaculos[contador].dimen = (Rectangle){positions[contador].x-6,positions[contador].y-8,60.0,48.0};
        obstaculos[contador].imagem = LoadTexture("obstaculo.png");
    }

    //carregando baus
    int aleatorio;
    bool chave_true = true;
     for(int contador  = 0; contador < tam_bau; contador++)
    {
        bau[contador].dimen = (Rectangle){positions_baus[contador].x-6,positions_baus[contador].y-6,49.0,48.0};
        bau[contador].imagem = LoadTexture("baufechado.png");
        bau[contador].tipo = 0;
        bau[contador].chave = false;
        bau[contador].aberto = false;
    }
    //Carregando baus - colocando determinado item no baú.
    for(int contador  = 0; contador < tam_bau; contador++)
    {
        int vazio = 0;
        while(vazio == 0)
        {
            aleatorio = rand()%12;
            if(bau[aleatorio].tipo == 0)
            {
                bau[aleatorio].tipo = baus[contador];
                vazio = 1;
            }
        }
    }
    while(chave_true)
    {
        aleatorio = rand() % 8;
        if(bau[aleatorio].tipo == 1)
        {
            chave_true = false;
            bau[aleatorio].chave = true;
        }
    }

    Tinimigo inimigos[qte_inimigos];

    for(int contador = 0; contador < qte_inimigos; contador++)
    {
        inimigos[contador].dimen = (Rectangle){positions_inim[contador].x,positions_inim[contador].y, tam_width, tam_height};
        inimigos[contador].vivo = true;
        if(contador%2 == 0)
        {
            inimigos[contador].deslocamentox = 6;
            inimigos[contador].deslocamentoy = 0;
            inimigos[contador].imagem = monstro_mapa;
        }
        else
        {
            inimigos[contador].deslocamentox = 0;
            inimigos[contador].deslocamentoy = 6;
           inimigos[contador].imagem = monstro_mapa2;
        }
    }
    //Inicializando balas.
    for(int contagem  = 0; contagem < 50; contagem++)
    {
        bola.balas[contagem].existe = false;

    }

    for(int contador = 0; contador < qte_municao; contador++)
    {
        item_municao_mapa[contador].image = municao_mapa_image;
        item_municao_mapa[contador].p = positions_municao_mapa[contador];
        item_municao_mapa[contador].pegou = false;
        item_municao_mapa[contador].ret = (Rectangle){positions_municao_mapa[contador].x,positions_municao_mapa[contador].y,40,40};
    }

    int contagem = 0, contador = 0, contagem1, atirada = 0;
    bola.colision = 0;

    char qte_balas_impressao[15];
    //Inicio jogo.
    int x = 20, y = 5;
    int qte_balas = 6, indice = 0, bala_disparada, balas_no_jogo = 0, balas_que_eu_tive_acesso = 10, qte_inimigos_mortos = 0, a = 0;
    t = clock();
    while(!WindowShouldClose())
    {
        SetTargetFPS(10);
        x = 170;

        qte_inimigos_mortos = 0;
        BeginDrawing();
        {

            ClearBackground(WHITE);
            DrawTexture(textura,0,0,WHITE);

            for(contagem = 0; contagem < tam; contagem++)
            {
                DrawTexture(obstaculos[contagem].imagem,positions[contagem].x,positions[contagem].y, WHITE);
            }
            for(contagem = 0; contagem < tam_bau;contagem++)
            {
                DrawTexture(bau[contagem].imagem, positions_baus[contagem].x, positions_baus[contagem].y, WHITE);
            }

           for(contagem  = 0; contagem < 50; contagem++)
            {
                if(bola.balas[contagem].existe == true)
                {

                    balas_no_jogo++;

                    DrawTexture(bala,bola.balas[contagem].position.x, bola.balas[contagem].position.y,WHITE);
                   // DrawCircle(bola.balas[contagem].position.x,bola.balas[contagem].position.y,14,WHITE);
                }
            }
            //inimigos
             for(contagem = 0; contagem < qte_municao; contagem++)
            {
                if(item_municao_mapa[contagem].pegou == false)
                {
                    DrawTexture(item_municao_mapa[contagem].image,item_municao_mapa[contagem].p.x+5,item_municao_mapa[contagem].p.y-5,WHITE);
                    //DrawCircle(item_municao_mapa[contagem].p.x, item_municao_mapa[contagem].p.x, 25,GREEN);
                }
            }
            for(contagem = 0; contagem < qte_inimigos; contagem++)
            {

                DrawTexture(inimigos[contagem].imagem,inimigos[contagem].dimen.x,inimigos[contagem].dimen.y,RAYWHITE);
                //DrawRectangleRec(inimigos[contagem].dimen,WHITE);
            }


            DrawTexture(porta_saida.imagem,porta_saida.dimen.x, porta_saida.dimen.y, WHITE);


            //Impressão da imagem correta
            if(direcao == 1){
            if(figura_desce == 0)DrawTexture(desce0,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_desce == 1)DrawTexture(desce1,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_desce == 2)DrawTexture(desce2,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_desce == 3){
                    DrawTexture(desce3,bola.position.x-10, bola.position.y-35,WHITE);
                    figura_desce = 0;
                }
            }
            if(direcao == 2){
            if(figura_direita == 0)DrawTexture(direita1,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_direita == 1)DrawTexture(direita2,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_direita == 2)DrawTexture(direita3,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_direita == 3){
                    DrawTexture(direita4,bola.position.x-10, bola.position.y-35,WHITE);
                    figura_direita = 0;
                }
            }
             if(direcao == 3){
            if(figura_esquerda == 0)DrawTexture(esquerda1,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_esquerda == 1)DrawTexture(esquerda2,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_esquerda == 2)DrawTexture(esquerda3,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_esquerda == 3){
                    DrawTexture(esquerda4,bola.position.x-10, bola.position.y-35,WHITE);
                    figura_direita = 0;
                }
            }
             if(direcao == 4){
            if(figura_sobe == 0)DrawTexture(sobe1,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_sobe == 1)DrawTexture(sobe2,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_sobe == 2)DrawTexture(sobe3,bola.position.x-10, bola.position.y-40,WHITE);
            else if(figura_sobe == 3){
                    DrawTexture(sobe4,bola.position.x-10, bola.position.y-35,WHITE);
                    figura_sobe = 0;
                }
             }

            //Impressão de vida e qte de munição
            y = (39*5) - bola.life*39;
            DrawTextureRec(vida,(Rectangle){0,y,vida.width,39},(Vector2){20,2},WHITE);
            x+=350;
            sprintf(qte_balas_impressao,"Ammunition: %d",balas_que_eu_tive_acesso-atirada);
            DrawText(qte_balas_impressao,x,18,20,WHITE);
        }
        EndDrawing();
        //colisão  player com obstaculos
       for(contador  = 0; contador < tam; contador++)
        {
            if(CheckCollisionCircleRec(bola.position,bola.radius,obstaculos[contador].dimen))
            {
                switch(direcao)
                {
                    //down
                case 1:
                    bola.position.y = obstaculos[contador].dimen.y - 5;

                    break;
                    //right
                case 2:
                    bola.position.x = obstaculos[contador].dimen.x - 5;
                    break;
                    //left
                case 3:
                    bola.position.x = obstaculos[contador].dimen.x+obstaculos[contador].dimen.width + 5;
                    break;
                    //up
                case 4:
                    bola.position.y = obstaculos[contador].dimen.y+obstaculos[contador].dimen.height + 5;
                    break;
                }
            }

        }


       //checando colisão Player --> baú
        for(contador  = 0; contador < tam_bau; contador++)
        {
            if(CheckCollisionCircleRec(bola.position,bola.radius,bau[contador].dimen))
            {
               if(IsKeyDown(KEY_SPACE) && bau[contador].tipo == 1 && bau[contador].aberto == false)
               {
                   if(bau[contador].chave)
                   {
                       bola.chave_verdadeira = true;

                   }
                   bau[contador].imagem = LoadTexture("bauaberto.png");
                   BeginDrawing();

                        ClearBackground(RAYWHITE);
                        DrawTexture(LoadTexture("baucomchave.png"),0,0,RAYWHITE);

                        //Substituir por uma figura do baú aberto.


                   EndDrawing();
                   sleep(5);
                   bau[contador].aberto = true;
               }
               else if(IsKeyDown(KEY_SPACE) && bau[contador].tipo == 2 && bau[contador].aberto == false)
               {
                   bola.life -= 1;
                   bau[contador].aberto = true;
                   bau[contador].imagem = LoadTexture("bauaberto.png");
                    BeginDrawing();
                        //ClearBackground(RAYWHITE);
                        DrawTexture(LoadTexture("./monstros/monstrosfundo.png"),0,0,WHITE);
                    EndDrawing();
                    sleep(3);
                    if(bola.life==0)
                        {
                            BeginDrawing();
                                ClearBackground(RAYWHITE);
                                DrawText("GAME OVER!",screenWidth/2 - 270,screenHeigth/2 - 20, 80, BLACK);
                            EndDrawing();

                        }
               }
               else if(IsKeyDown(KEY_SPACE) && bau[contador].tipo == 3 && bau[contador].aberto == false)
               {
                   bau[contador].aberto = true;
                   if(bola.life < 5) bola.life++;
                   bau[contador].imagem = LoadTexture("bauaberto.png");

                   BeginDrawing();
                        ClearBackground(RAYWHITE);
                        DrawTexture(LoadTexture("bau_vida.png"),0,0,WHITE);
                   EndDrawing();
                   sleep(3);

               }

            }
        }
        //Colisão player -> munição
        for(contador = 0; contador < qte_municao; contador++)
        {
            if(CheckCollisionCircleRec(bola.position,bola.radius,item_municao_mapa[contador].ret))
            {
                if(item_municao_mapa[contador].pegou == false)
                {
                    balas_que_eu_tive_acesso+=3;
                    item_municao_mapa[contador].pegou = true;
                }
            }
        }
        // checando colisão porta
        if(CheckCollisionCircleRec(bola.position,bola.radius,(Rectangle){porta_saida.dimen.x,porta_saida.dimen.y,porta_saida.dimen.width,porta_saida.dimen.height+15}))
        {
            bola.position.y = porta_saida.dimen.y+porta_saida.dimen.height+15;
            if(bola.chave_verdadeira && IsKeyDown(KEY_SPACE))
            {

                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText("FIM DE FASE!",screenWidth/2 - 270,screenHeigth/2 - 20, 80, BLACK);

                EndDrawing();
                bola.fim = true;
                sleep(3);
            }
            else if(IsKeyDown(KEY_SPACE))
            {
                bola.position.y = porta_saida.dimen.y+porta_saida.dimen.height+16;
                 BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText("CHAVE ERRADA!",screenWidth/2 - 270,screenHeigth/2 - 20, 80, BLACK);

                EndDrawing();
                sleep(3);
            }


        }

            //movimentação sem colisões.
            if (IsKeyDown(KEY_LEFT)&& bola.position.x <= position_initial_x)bola.position.x = position_initial_x;
            else if(IsKeyDown(KEY_LEFT))
            {


                    direcao = 3;
                    bola.position.x -= deslocamento_x;
                    if(figura_esquerda == 3)
                        {
                            figura_esquerda = 0;
                        }
                    else
                        {
                            figura_esquerda++;
                        }
                    bola.colision = 0;
                    bola.radius = 2;

            }
            else if(IsKeyDown(KEY_RIGHT) && bola.position.x >= screenWidth-45) bola.position.x = bola.position.x;
            else if(IsKeyDown(KEY_RIGHT)){


                        direcao = 2;
                        bola.position.x += deslocamento_x;
                         if(figura_direita == 3)
                            {
                                figura_direita = 0;
                            }
                        else
                            {
                                figura_direita++;
                            }
                        bola.colision = 0;
                        bola.radius = 2;


            }
            else if (IsKeyDown(KEY_DOWN)&& bola.position.y >= screenHeigth-50)bola.position.y = bola.position.y;
            else if(IsKeyDown(KEY_DOWN))
            {

                    direcao = 1;
                    bola.position.y += deslocamento_y;
                    if(figura_desce == 3)
                    {
                        figura_desce = 0;
                    }
                    else
                    {
                        figura_desce++;
                    }
                    bola.colision = 0;
                    bola.radius = 2;




            }
            else if(IsKeyDown(KEY_UP) && bola.position.y <= position_initial_y ) bola.position.x = bola.position.x;
            else if(IsKeyDown(KEY_UP))
            {

                direcao = 4;
                bola.position.y  -= deslocamento_y;
                if(figura_sobe == 3)
                {
                    figura_sobe = 0;
                }
                else
                {
                    figura_sobe++;
                }
                bola.colision = 0;
                bola.radius = 2;
              }
            if(IsKeyDown(KEY_ENTER)) printf("%f -- %f", bola.position.x,bola.position.y);

            // colisão monstro bordas
        for(contagem = 0; contagem < qte_inimigos; contagem++)
        {
            if(inimigos[contagem].dimen.x <= Zero_eixo_x)
            {
               aleatorio = rand() % 3;
               if(aleatorio == 0)
               {
                    inimigos[contagem].dimen.x =  Zero_eixo_x+1;
                    inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
                    inimigos[contagem].deslocamentox *= -1;
               }
               else if(aleatorio == 1)
               {
                    inimigos[contagem].dimen.x =  Zero_eixo_x+1;
                    inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
                    inimigos[contagem].deslocamentox = 0;
                    inimigos[contagem].deslocamentoy = 10;
               }
               else if(aleatorio == 2)
               {
                    inimigos[contagem].dimen.x =  Zero_eixo_x+1;
                    inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
                    inimigos[contagem].deslocamentox = 0;
                    inimigos[contagem].deslocamentoy = -10;
               }
            }
            if(inimigos[contagem].dimen.x >= screenWidth - 40)
            {
                aleatorio = rand() % 3;
               if(aleatorio == 0)
               {
                    inimigos[contagem].dimen.x =  screenWidth-41;
                    inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
                    inimigos[contagem].deslocamentox *= -1;
               }
               else if(aleatorio == 1)
               {
                    inimigos[contagem].dimen.x =  screenWidth-41;
                    inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
                    inimigos[contagem].deslocamentox = 0;
                    inimigos[contagem].deslocamentoy = 10;
               }
               else if(aleatorio == 2)
               {
                    inimigos[contagem].dimen.x =  screenWidth-41;
                    inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
                    inimigos[contagem].deslocamentox = 0;
                    inimigos[contagem].deslocamentoy = -10;
               }
            }
            if(inimigos[contagem].dimen.y >= screenHeigth-40)
            {
                aleatorio = rand() % 3;

                if(aleatorio == 0)
                {
                        inimigos[contagem].dimen.y = screenHeigth - 41;
                        inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                        inimigos[contagem].deslocamentoy *= -1;
                }
                else if(aleatorio == 1)
                {
                    inimigos[contagem].dimen.y = screenHeigth - 41;
                    inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                    inimigos[contagem].deslocamentox = 10;
                    inimigos[contagem].deslocamentoy = 0;
                }
                else if(aleatorio == 2)
                {
                    inimigos[contagem].dimen.y = screenHeigth - 41;
                    inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                    inimigos[contagem].deslocamentox = -10;
                    inimigos[contagem].deslocamentoy = 0;
                }

            }
            if(inimigos[contagem].dimen.y <= Zero_eixo_y)
            {

                aleatorio = rand() % 3;

                if(aleatorio == 0)
                {
                        inimigos[contagem].dimen.y = Zero_eixo_y + 1;
                        inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                        inimigos[contagem].deslocamentoy *= -1;
                }
                else if(aleatorio == 1)
                {
                    inimigos[contagem].dimen.y = Zero_eixo_y + 1;
                    inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                    inimigos[contagem].deslocamentox = 10;
                    inimigos[contagem].deslocamentoy = 0;
                }
                else if(aleatorio == 2)
                {
                    inimigos[contagem].dimen.y = Zero_eixo_y+1;
                    inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                    inimigos[contagem].deslocamentox = -10;
                    inimigos[contagem].deslocamentoy = 0;
                }
            }
            else
            {
                inimigos[contagem].dimen.x += inimigos[contagem].deslocamentox;
                inimigos[contagem].dimen.y += inimigos[contagem].deslocamentoy;
            }
        }
        //colisão monstros com objetos do mapa.
        for(contagem = 0; contagem < tam; contagem++)
        {

            for(contagem1  = 0; contagem1 < qte_inimigos; contagem1++)
            {

                    //colisão monstro player.
                    if(CheckCollisionCircleRec(bola.position,bola.radius*3,(Rectangle){inimigos[contagem1].dimen.x-2,inimigos[contagem1].dimen.y-10,inimigos[contagem1].dimen.width+25,inimigos[contagem1].dimen.height+20}))
                    {
                        if(inimigos[contagem1].vivo == true)
                        {
                            bola.life--;
                            inimigos[contagem1].vivo = false;
                            inimigos[contagem1].dimen = (Rectangle){0};
                            inimigos[contagem1].imagem = LoadTexture("nada.png");

                        }
                        if(bola.life==0)
                        {
                            BeginDrawing();
                                ClearBackground(RAYWHITE);
                                DrawText("GAME OVER!",screenWidth/2 - 270,screenHeigth/2 - 20, 80, BLACK);

                            EndDrawing();
                            sleep(3);

                        }
                    }
                    //colisão monstros baús.
                    if(contagem < tam_bau && CheckCollisionRecs(inimigos[contagem1].dimen,bau[contagem].dimen))
                    {
                        //deslocamento esquerda --> direita
                       if(inimigos[contagem1].deslocamentox>0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.x =  bau[contagem].dimen.x - (tam_width+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.x =  bau[contagem].dimen.x - (tam_width+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.x =  bau[contagem].dimen.x - (tam_width+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = -10;
                           }
                       }
                       //deslocamento direita --> esquerda
                       else if(inimigos[contagem1].deslocamentox<0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.x =  bau[contagem].dimen.x + (60+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.x =  bau[contagem].dimen.x + (60+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.x =  bau[contagem].dimen.x + (60+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = -10;
                           }
                       }
                       //deslocamento cima --> baixo
                       else if(inimigos[contagem1].deslocamentoy>0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.y =  bau[contagem].dimen.y - (tam_height+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.y =  bau[contagem].dimen.y - (tam_height+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;

                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.y =  bau[contagem].dimen.y - (tam_height+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = -10;
                           }
                       }
                       //deslocamento baixo --> cima
                       else if(inimigos[contagem1].deslocamentoy<0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.y =  bau[contagem].dimen.y + (48+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.y =  bau[contagem].dimen.y + (48+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;

                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.y =  bau[contagem].dimen.y + (48+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = -10;
                           }
                       }
                    }
                    //Colisão monstros  paredes.
                    if(CheckCollisionRecs(obstaculos[contagem].dimen,inimigos[contagem1].dimen))
                    {
                        //deslocamento esquerda --> direita
                       if(inimigos[contagem1].deslocamentox>0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.x =  obstaculos[contagem].dimen.x - (tam_width+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.x =  obstaculos[contagem].dimen.x - (tam_width+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.x =  obstaculos[contagem].dimen.x - (tam_width+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = -10;
                           }
                       }
                       //deslocamento direita --> esquerda
                       else if(inimigos[contagem1].deslocamentox<0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.x =  obstaculos[contagem].dimen.x + (60+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.x =  obstaculos[contagem].dimen.x + (60+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.x =  obstaculos[contagem].dimen.x + (60+1);
                                inimigos[contagem1].dimen.y += inimigos[contagem1].deslocamentoy;
                                inimigos[contagem1].deslocamentox = 0;
                                inimigos[contagem1].deslocamentoy = -10;
                           }
                       }
                       //deslocamento cima --> baixo
                       else if(inimigos[contagem1].deslocamentoy>0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.y =  obstaculos[contagem].dimen.y - (tam_height+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.y =  obstaculos[contagem].dimen.y - (tam_height+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;

                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.y =  obstaculos[contagem].dimen.y - (tam_height+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = -10;
                           }
                       }
                       //deslocamento baixo --> cima
                       else if(inimigos[contagem1].deslocamentoy<0)
                       {
                           aleatorio = rand()%3;
                           if(aleatorio == 0)
                           {
                                inimigos[contagem1].dimen.y =  obstaculos[contagem].dimen.y + (48+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy *= -1;
                           }
                           else if(aleatorio == 1)
                           {
                                inimigos[contagem1].dimen.y =  obstaculos[contagem].dimen.y + (48+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;

                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = 10;
                           }
                           else if(aleatorio == 2)
                           {
                                inimigos[contagem1].dimen.y =  obstaculos[contagem].dimen.y + (48+1);
                                inimigos[contagem1].dimen.x += inimigos[contagem1].deslocamentox;
                                inimigos[contagem1].deslocamentoy = 0;
                                inimigos[contagem1].deslocamentox = -10;
                           }
                       }

                    }

                    //colisão monstro bomba
                    if( contagem < atirada && CheckCollisionCircleRec((Vector2){bola.balas[contagem].position.x+16,bola.balas[contagem].position.y+16},14,inimigos[contagem1].dimen))
                    {
                        if(bola.balas[contagem].existe && inimigos[contagem1].vivo == true)
                        {
                            BeginDrawing();
                                DrawTexture(inimigos[contagem1].imagem,bola.balas[contagem].position.x,bola.balas[contagem].position.y,WHITE);
                                DrawTexture(LoadTexture("nada.png"),bola.balas[contagem].position.x,bola.balas[contagem].position.y,WHITE);
                            EndDrawing();

                            bola.balas[contagem].existe = false;
                            inimigos[contagem1].vivo = false;
                            inimigos[contagem1].dimen = (Rectangle){0};
                            inimigos[contagem1].imagem = LoadTexture("nada.png");

                            SetTargetFPS(5);

                            BeginDrawing();
                            for(contador = 0; contador < 4; contador++)
                            {

                                    DrawTexture(explosao[contador],bola.balas[contagem].position.x,bola.balas[contagem].position.y,WHITE);
                                    DrawTexture(LoadTexture("nada.png"),bola.balas[contagem].position.x,bola.balas[contagem].position.y,WHITE);
                            }
                            EndDrawing();

                        }
                    }
                    //colisão porta inimigo
                    if(CheckCollisionRecs(porta_saida.dimen,inimigos[contagem1].dimen))
                    {
                        inimigos[contagem1].dimen.y = porta_saida.dimen.y + porta_saida.dimen.height+1;
                        inimigos[contagem1].dimen.x = screenWidth-40;
                    }
                }
            }
         //terminando o jogo
         if(bola.life <= 0 || bola.fim)
         {
                    sleep(2);
                    break;
                }
         //bala
         if(IsKeyPressed(KEY_G))
         {
             if(atirada == balas_que_eu_tive_acesso)
             {

             }
             else
             {
                bola.balas[atirada].existe = true;
                bola.balas[atirada].position = (Vector2) {bola.position.x-15, bola.position.y-15};
                atirada++;
             }
         }
         for(contagem = 0; contagem < qte_inimigos; contagem++)
         {
             if(inimigos[contagem].vivo == false)
             {
                 qte_inimigos_mortos++;

             }
         }
         if(qte_inimigos_mortos == 4 )
         {
             for(contagem = 0; contagem < qte_inimigos; contagem++)
             {
                 if(inimigos[contagem].vivo == false)
                 {
                     if(contagem%2 == 0)
                     {
                            inimigos[contagem].imagem = monstro_mapa;
                     }
                     else
                     {
                            inimigos[contagem].imagem = monstro_mapa2;
                     }

                     inimigos[contagem].dimen = (Rectangle){positions_inim[contador].x,positions_inim[contador].y, tam_width, tam_height};
                     inimigos[contagem].vivo = true;
                }
             }
         }
    }
    t = clock() - t;
    printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000)));

    CloseWindow();
    return 0;


}


