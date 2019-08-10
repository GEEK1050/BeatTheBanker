/*

    FILE's NAME : game.c
    ROLE        : contains the game function
    AUTHOR      : KARM BAHRI | karim-bahri-18@outlook.fr
    DATE        : 17/07/2019






*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fmod.h>
#include "management.h"
#include "consts.h"
#include "menu.h"
#include "game.h"


    /*-----------------------------------------------------------------------------------*/

        void game(SDL_Surface *screen , FMOD_SYSTEM *system , FMOD_CHANNELGROUP *channelgroup )
                {
                    /*-------------------------DECLARATIONS-------------------------*/

                   // TTF_Font *font = NULL;
                    SDL_Surface *peopleOn[24] = {NULL} , *peopleOff[24] = {NULL} , *boxeOff[24] = {NULL} , *boxeOn[24] = {NULL} , *boxesNumberSurface[24] = {NULL};
                    SDL_Surface *background1 = NULL , *background2 = NULL , *table = NULL;
                    SDL_Event event;
                    SDL_Rect boxesPos[12][2] , peoplePos[12][2] , posBackground , posTable , posNumber;
                    SDL_Color color = { 0 , 0 , 255 };
                    SDL_bool running = SDL_TRUE;
                    int *boxNumber = NULL;

                    /*-------------------------DECLARATIONS-------------------------*/


                        /*-------------------------INITIALISATION-------------------------*/


                       // font = TTF_OpenFont("arial.ttf",16);

                     //   if(font == NULL)
                       //     SDL_ExitWithError(TTF,"Initialization error of TTF FONT");

                        peopleSurface_Create(peopleOn,peopleOff,24);


                        background1 = IMG_Load("sprites/gameBackground1.png");

                            if(background1 == NULL)
                                SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");

                        background2 = IMG_Load("sprites/gameBackground2.png");

                            if(background2 == NULL)
                                SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");


                        table = IMG_Load("sprites/table.png");

                            if(table == NULL)
                                SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");

                        set_position(&posBackground,0,0);
                        set_position(&posTable,95,555);
                        set_position(&posNumber,5,35);
                        peoplePos_Create(peoplePos,12);
                        boxesPos_Create(boxesPos,12);
                        boxNumber = generateNumber_Boxes(24);
                        CreateNumberSurface_box(boxesNumberSurface,NULL,color,boxNumber,24);
                        boxesSurface_Create(boxeOn,boxeOff,boxesNumberSurface,&posNumber,24);


                        /*-------------------------INITIALISATION-------------------------*/


                /*------------------------------------------------------------------------------------*/


                        while(running)
                                {
                                    SDL_PollEvent(&event);

                                        switch(event.type)
                                            {
                                                case SDL_QUIT:
                                                    running = SDL_FALSE;
                                                        break;


                                            }

                                        SDL_BlitSurface(background1,NULL,screen,&posBackground);
                                        SDL_BlitSurface(background2,NULL,screen,&posBackground);
                                        SDL_BlitSurface(table,NULL,screen,&posTable);
                                        blitSurfaces(screen,peopleOff,peoplePos,12);
                                        blitSurfaces(screen,boxeOff,boxesPos,12);
                                        boxChoice(screen,boxeOn,peopleOn,boxesPos,peoplePos,&event);
                                        SDL_Flip(screen);
                                }

                /*------------------------------------------------------------------------------------*/




                        /*------------------------------MEMORIE RELEASE------------------------------*/

                                free(boxNumber);
                                peopleSurface_Release(peopleOn,peopleOff,24);
                                //TTF_CloseFont(font);
                                SDL_FreeSurface(boxeOff);
                                SDL_FreeSurface(background1);
                                SDL_FreeSurface(background2);

                        /*------------------------------MEMORIE RELEASE------------------------------*/


                }




    /*-----------------------------------------------------------------------------------*/

        void boxesSurface_Create(SDL_Surface *boxesOnSurface[] , SDL_Surface *boxesOffSurface[] , SDL_Surface *numberSurface[] , SDL_Rect *posNumber , int nb)
                            {
                                for( int i = 0 ; i < nb ; i++)
                                            {
                                                boxesOffSurface[i] = IMG_Load("sprites/boxes/1.png");

                                                    if(boxesOffSurface[i] == NULL)
                                                            SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");

                                                boxesOnSurface[i] =  IMG_Load("sprites/boxes/2.png");

                                                    if(boxesOnSurface[i] == NULL)
                                                            SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");


                                               SDL_BlitSurface(numberSurface[i],NULL,boxesOffSurface[i],posNumber);
                                               SDL_BlitSurface(numberSurface[i],NULL,boxesOnSurface[i],posNumber);

                                            }


                            }

     /*-----------------------------------------------------------------------------------*/

      void peopleSurface_Create(SDL_Surface *peopleOn[] , SDL_Surface *peopleOff[] , int nb)
                                    {
                                        char txt[20] = {NULL};

                                            for( int i = 0 ; i < nb ; i++)
                                                    {
                                                        sprintf(txt,"sprites/people/%dOn.png",i + 1);
                                                        peopleOn[i] = IMG_Load(txt);

                                                            if(peopleOn == NULL)
                                                                    SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");


                                                        sprintf(txt,"sprites/people/%dOff.png",i + 1);
                                                        peopleOff[i] = IMG_Load(txt);

                                                            if(peopleOff == NULL)
                                                                    SDL_ExitWithError(IMG,"Initialization error of SDL_Surface");
                                                    }

                                    }


     /*-----------------------------------------------------------------------------------*/


     void peopleSurface_Release(SDL_Surface *peopleOn[] , SDL_Surface *peopleOff[] , int nb)

            {
                for( int i = 0 ; i < nb ; i++)
                        {
                            SDL_FreeSurface(peopleOn[i]);
                            SDL_FreeSurface(peopleOff[i]);
                        }

            }


     /*-----------------------------------------------------------------------------------*/

   void boxesPos_Create(SDL_Rect boxesPos[][2] , int nb)
                {
                    int X = 18 , Y1 = 119 , Y2 = 447;
                    for(int i = 0 ; i < nb ; i++)
                        {
                            set_position(&boxesPos[i][0],X,Y1);
                            set_position(&boxesPos[i][1],X,Y2);
                            X += 84;
                        }

                }


     /*-----------------------------------------------------------------------------------*/

     void peoplePos_Create(SDL_Rect peoplePos[][2] , int nb)
                {
                    int X = 66 , Y1 = 53 , Y2 = 380;

                    set_position(&peoplePos[0][0],10,Y1);
                    set_position(&peoplePos[0][1],10,Y2);

                        for( int i = 1 ; i < nb ; i++ )
                                    {
                                        set_position(&peoplePos[i][0],X,Y1);
                                        set_position(&peoplePos[i][1],X,Y2);
                                        X += 83;
                                    }


                }


     /*-----------------------------------------------------------------------------------*/

   void blitSurfaces(SDL_Surface *screen , SDL_Surface *Surfaces[] , SDL_Rect pos[][2] , int nb)
                {
                    int k = 0;

                            for(int j = 0 ; j < 2 ; j++)
                                for(int i = 0 ; i < nb ; i++)
                                {
                                SDL_BlitSurface(Surfaces[k],NULL,screen,&pos[i][j]);
                                k++;
                                }
                }
    /*-----------------------------------------------------------------------------------*/

   boxIndex boxChoice(SDL_Surface *screen , SDL_Surface *boxeOn[] , SDL_Surface *peopleOn[] , SDL_Rect boxesPos[][2] , SDL_Rect peoplePos[][2] , SDL_Event *event)
                    {

                        boxIndex index;
                        int i = 0;

                        /*--------------------------------------------------------------------------*/
                                       //if(Boxes_TestCollision(boxesPos,event,58,60,MOTION,&index))
                                       if(Boxes_TestEvent(event,MOTION,&index))
                                        {
                                            i = ( index.Y * 12 ) + index.X ;
                                            SDL_BlitSurface(peopleOn[i],NULL,screen,&peoplePos[index.X][index.Y]);
                                            SDL_BlitSurface(boxeOn[i],NULL,screen,&boxesPos[index.X][index.Y]);

                                        }


                    }

     /*-----------------------------------------------------------------------------------*/


     SDL_Surface **resizeSurface_box(SDL_Surface *boxes[] , int width , int height , const int nb)
                            {
                               for(int i = 0 ; i < nb ; i++)
                                     boxes[i]->w = width , boxes[i]->h = height;

                                    return boxes;

                            }

     /*-----------------------------------------------------------------------------------*/

     void CreateNumberSurface_box(SDL_Surface *boxesNumber_Surface[] , TTF_Font *font , SDL_Color color , int boxesNumbers[] , const int nb)

                            {
                                char txt[20] = { 0 };

                                /*-------------------------------------*/

                                  /*  numberBackground = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF ,25,22,32,0,0,0,0);

                                        if(numberBackground == NULL)
                                            SDL_ExitWithError(SDL,"Initialization error of SDL_Surface");

                                   //SDL_FillRect(numberBackground,NULL,SDL_MapRGB(numberBackground->format,0,255,255));*/

                                /*-------------------------------------*/

                                for(int i = 0 ; i < nb ; i++)
                                    {
                                        sprintf(txt,"sprites/boxes/numbers/%d.png",boxesNumbers[i]);

                                        //numberBackground = TTF_RenderText_Solid(font,txt,color);
                                         //TTF_SetFontStyle(font,TTF_STYLE_BOLD);
                                        boxesNumber_Surface[i] = IMG_Load(txt);


                                                if(boxesNumber_Surface[i] == NULL)
                                                    SDL_ExitWithError(IMG,"Initialization error of SDL_Surface.");
                                    }

                            }


       /*-----------------------------------------------------------------------------------*/

    int *generateNumber_Boxes( int numb)
                                    {
                                        int tmp = 0 , r = 0;
                                        srand(time(NULL));

                                        int *boxesNumber = malloc(numb * sizeof(int));

                                            if(boxesNumber == NULL)
                                                SDL_ExitWithError(FMOD,"ERROR OF ARRAY ALLOCATION !");

                                          /*--------------INISIALISATION--------------*/
                                            for(int i = 0 ; i < numb ; i++)
                                                    boxesNumber[i] = i + 1;
                                          /*--------------INISIALISATION--------------*/

                                            for(int i = 0 ; i < numb ; i++)
                                                        {
                                                            r = rand() % 23 + 1;
                                                            /*---------PERMUTATION---------*/
                                                            tmp = boxesNumber[i];
                                                            boxesNumber[i] = boxesNumber[r];
                                                            boxesNumber[r] = tmp;
                                                            /*---------PERMUTATION---------*/


                                                        }

                                          return boxesNumber;
                                    }



