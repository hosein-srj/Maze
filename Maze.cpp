#include <iostream>
#include <conio.h>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
int r=0;

bool promising(int board[4][4], int x, int y)
{
    if(x >= 0 && x < 4 && y >= 0 && y < 4 && board[x][y] != 0)
        return true;
    return false;
}



bool backTrack(int board[4][4], int x, int y, int solveBoard[4][4],int stepSol[100][4][4])
{

    for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
                stepSol[r][i][j]=solveBoard[i][j];
        }
    r++;

    if(x == 3 && y == 3)
    {
        solveBoard[x][y] = 1;
        return true;
    }

    if(promising(board, x, y) == true)
    {
        solveBoard[x][y] = 1;

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
                stepSol[r][i][j]=solveBoard[i][j];
        }
        r++;


        for (int i = 1; i <= board[x][y] && i <4; i++) {

            if (backTrack(board, x, y+i, solveBoard,stepSol) == true)
	            return true;

	        if (backTrack(board, x+i, y, solveBoard,stepSol)  == true)
	            return true;


	    }

        solveBoard[x][y] = 0;
        return false;
    }

    return false;
}



bool solve(int maze[4][4],int solveBoard[4][4],int stepSol[100][4][4])
{

    if(backTrack(maze, 0, 0, solveBoard,stepSol) == false)
    {
        printf("Error");
        return false;
    }

    return true;
}



int main(){


    /*Araye Do bodi moshakhas konande  bon bast ha */

    int board[4][4]= { { 1, 0, 0, 0 },
                       { 1, 1, 1, 1 },
                       { 1, 0, 0, 0 },
                       { 1, 2, 1, 1 }
                     };

    int solveBoard[4][4];

    for(int i=0;i<4;i++){
    	for(int j=0;j<4;j++)
    		solveBoard[i][j]=0;
	}

	int stepsol[100][4][4];

	for(int i=0;i<4;i++){
    	for(int j=0;j<4;j++)
    		for(int k=0;k<100;k++)
                stepsol[k][i][j]=0;
	}


    sf::RenderWindow window(sf::VideoMode(800, 800), "Maze!");
    sf::Texture texture1;
    sf::Sprite sprite1;
    if (!texture1.loadFromFile("Background.jpg")){
        cout << "Error\n";
    }
    sf::Texture texture2;
    sf::Sprite sprite2;
    if (!texture2.loadFromFile("BackgroundStart.jpg")){
        cout << "Error\n";
    }
    sf::Font font;
    if (!font.loadFromFile("CURLZ.TTF"))
        cout << "Error";
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);
    int state=0;
    while (window.isOpen()){

        while(state==0){
            int x1,y1;
            window.clear();
            sf::Text play,welcome;
            play.setString("Start");
            play.setFont(font);
            play.setColor(sf::Color::Red);
            play.setCharacterSize(100);
            play.setPosition(300,330);
            welcome.setString("Welcome To Maze");
            welcome.setFont(font);
            welcome.setColor(sf::Color::Red);
            welcome.setCharacterSize(40);
            welcome.setPosition(250,250);
            sf::Event event3;
            while (window.pollEvent(event3)){
                if (event3.type == sf::Event::Closed)
                    window.close();
                if ( event3.type == sf::Event::MouseMoved ){
                    x1=event3.mouseMove.x;
                    y1=event3.mouseMove.y;
                }
                if(event3.type==sf::Event::MouseButtonPressed){
                    if(event3.mouseButton.button==sf::Mouse::Left){
                        if(x1>300&&x1<500&&y1>330&&y1<430)
                            state=1;
                    }
                }
            }
            if(x1>300&&x1<500&&y1>330&&y1<430){
                play.setStyle(sf::Text::Bold | sf::Text::Underlined );
                play.setColor(sf::Color::Green);
            }
            window.draw(sprite2);
            window.draw(play);
            window.draw(welcome);
            window.display();
        }

        solve(board,solveBoard,stepsol);
        int counter=0;
        cout <<r;
        stepsol[r-1][3][3]=1;
        while(state==1){

            int x1,y1;
            window.clear();
            window.draw(sprite1);
            sf::Text play,welcome;
            play.setString("Start");
            play.setFont(font);
            play.setColor(sf::Color::Red);
            play.setCharacterSize(100);
            play.setPosition(300,330);
            welcome.setString("Welcome To Maze");
            welcome.setFont(font);
            welcome.setColor(sf::Color::Red);
            welcome.setCharacterSize(40);
            welcome.setPosition(250,250);
            sf::Event event3;
            while (window.pollEvent(event3)){
                if (event3.type == sf::Event::Closed)
                    window.close();
            }


            sf::RectangleShape line(sf::Vector2f(60,60));
            sf::Text sharpText;
            sharpText.setString("#");
            sharpText.setFont(font);
            sharpText.setCharacterSize(50);
            sharpText.setColor(sf::Color::Red);
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    line.setPosition(250+65*j,250+i*65);
                    window.draw(line);
                    if(board[i][j]==0){
                        sharpText.setPosition(265+65*j,255+i*65);
                        window.draw(sharpText);
                    }

                }
            }


            sf::RectangleShape square(sf::Vector2f(50,50));
            square.setFillColor(sf::Color::Green);
            square.setPosition(205,205);
            sf::RectangleShape way(sf::Vector2f(50,50));
            way.setFillColor(sf::Color::Cyan);

            if(counter<=r){
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        way.setPosition(255+65*j,255+i*65);
                        if(stepsol[counter][i][j]==1){
                            way.setFillColor(sf::Color::Blue);
                        }
                        if(board[i][j]!=0){
                        window.draw(way);
                    }
                    way.setFillColor(sf::Color::White);

                    }
                }
                counter++;
            }
            if(counter>r)
                counter=r-1;
            Sleep(500);





            window.display();
        }


        window.clear();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(sprite1);
        window.display();
    }
	return 0;
}
