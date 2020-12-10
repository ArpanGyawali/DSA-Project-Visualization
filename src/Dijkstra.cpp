#include "../include/Dijkstra.hpp"

bool sptSet[NUM_ROW][NUM_COLS];
vector<pair<int, int> > pathD;


Djks::Djks(void) 
{
    srand(time(0));
    src_x = 1 + rand() % 20;
    src_y = 2 + rand() % 12;
    dest_x = 1 + rand() % 20;
    dest_y = 26 + rand() % 12; 
    reset();
    // shortest_distance = 0;
    if (!font.loadFromFile("resource/Mono.ttf"))
    {
        std::cerr << "Error loading HeadText.ttf" << std::endl;
    }
    if (!font1.loadFromFile("resource/Texturina.ttf"))
    {
        std::cerr << "Error loading Text.ttf" << std::endl;
    }
    text.setFont(font);
    text.setString("DIJKSTRA");
    text.setCharacterSize(42);
    text.setFillColor(Color::Red);
    text1.setFont(font1);
    text1.setString("FIND PATH |");
    text1.setCharacterSize(25);
    text1.setFillColor(Color::Red);
    text2.setFont(font1);
    text2.setString("RESET");
    text2.setCharacterSize(25);
    text2.setFillColor(Color::Red);
    text3.setFont(font);
    text3.setCharacterSize(23);
    text3.setString("00");
    text3.setFillColor(Color::Red);

    // Shapes
    buttonLaunch.setSize(Vector2f(200, 35));      
    buttonLaunch.setFillColor(Color::Transparent);
    buttonLaunch.setOutlineThickness(1);
    buttonLaunch.setOutlineColor(Color::Red);
    buttonReset.setSize(Vector2f(200, 35));
    buttonReset.setFillColor(Color::Transparent);
    buttonReset.setOutlineThickness(1);
    buttonReset.setOutlineColor(Color::Red);

    rectangle.setSize(Vector2f(20, 20));      
    rectangle.setFillColor(Color::Transparent);
    obsRectangle.setSize(Vector2f(20, 20));     
    obsRectangle.setFillColor(Color::White);
    pathRectangle.setSize(Vector2f(20, 20));     
    pathRectangle.setFillColor(Color::Black);
    pathRectangle.setOutlineThickness(1);
    pathRectangle.setOutlineColor(Color::Red);
    srcRectangle.setSize(Vector2f(20, 20));      
    srcRectangle.setFillColor(Color(255, 69, 0));
    srcRectangle.setOutlineThickness(1);
    srcRectangle.setOutlineColor(Color::Black);
    destRectangle.setSize(Vector2f(20, 20));       
    destRectangle.setFillColor(Color::Red);
    destRectangle.setOutlineThickness(1);
    destRectangle.setOutlineColor(Color::Red);
    findRectangle.setSize(Vector2f(20, 20));
    findRectangle.setFillColor(Color(250, 128, 114));
}

void Djks::reset() {
    for (int i = 0; i < shortest_distance - 1; i++) {
        pathD.pop_back();
    }
    // srand(time(0));
    // src_x=1+rand()%20;
    // src_y=2+rand()%12;
    // dest_x=1+rand()%20;
    // dest_y=26+rand()%12;   
    for (int i = 0; i < NUM_ROW; i++)
        for (int j = 0; j < NUM_COLS; j++) {
            if ((i == 0 && j < 15 && j>25) || i == 29 || j == 0 || j == 39 || (i == 7 && j > 14 && j < 26) || (j == 14 && i < 8) || (j == 25 && i < 8))        //walls
                obstacle[i][j] = 0;
            else
                obstacle[i][j] = 1;
        }
    for (int i = 0; i < NUM_ROW; i++)
        for (int j = 0; j < NUM_COLS; j++) {
            sptSet[i][j] = false;     
            dist[i][j] = FLT_MAX;
            if (i > 7 || j > 25 || j < 14)
                coloured[i][j] = 0;   
            else
                coloured[i][j] = 1;
        }
    dist[src_x][src_y] = 0.0;
    previous[NUM_ROW][NUM_COLS] = { make_pair(0,0) };
    min_x = 0;
    min_y = 0;
    text3.setString("00");
}

void Djks::findMinimum(float dist[NUM_ROW][NUM_COLS], int& min_x, int& min_y) {
    float mini = FLT_MAX;
    for (int i = 0; i < NUM_ROW; i++)
        for (int j = 0; j < NUM_COLS; j++)
            if (sptSet[i][j] == false && dist[i][j] < mini) {
                mini = dist[i][j];
                min_x = i;
                min_y = j;
            }
}

void Djks::pathFinder(pair<int, int> previous[NUM_ROW][NUM_COLS], float dist[NUM_ROW][NUM_COLS], int dest_x, int dest_y, int src_x, int src_y) {
    shortest_distance = dist[dest_x][dest_y];
    while (previous[dest_x][dest_y].first != src_x || previous[dest_x][dest_y].second != src_y) {        
        sf::sleep(milliseconds(10));       
        pathD.push_back(make_pair(previous[dest_x][dest_y].first, previous[dest_x][dest_y].second));
        int save_x = dest_x, save_y = dest_y;
        dest_x = previous[save_x][save_y].first;                
        dest_y = previous[save_x][save_y].second;
    }
    text3.setString(std::to_string(shortest_distance));
}

void Djks::dijkstra(int src_x, int src_y, int dest_x, int dest_y, int obstacle[NUM_ROW][NUM_COLS]) {
    int found = 0;
    for (int i = 0; i < NUM_ROW && found == 0; i++) {
        for (int j = 0; j < NUM_COLS && found == 0; j++) {
            findMinimum(dist, min_x, min_y);                  
            sptSet[min_x][min_y] = true;
            if (sptSet[dest_x][dest_y] == true) {
                found = 1;
                break;
            }
            sf::sleep(milliseconds(1));    
            int possibleX[] = { 0, 0, 1, -1, 1, -1, -1, 1 };
            int possibleY[] = { 1, -1, 0, 0, 1, 1, -1, -1 };

            for (int i = 0; i < 8; ++i) {
                int newRow = min_x + possibleX[i];
                int newCol = min_y + possibleY[i];
                if (obstacle[newRow][newCol] == 1 && sptSet[newRow][newCol] == false && dist[newRow][newCol] > dist[min_x][min_y] + 1.0) {
                    dist[newRow][newCol] = dist[min_x][min_y] + 1.0;
                    previous[newRow][newCol] = make_pair(min_x, min_y);
                }
            }
        }
    }

    pathFinder(previous, dist, dest_x, dest_y, src_x, src_y);
}

int Djks::Run(RenderWindow& App)
{
    Texture Texture;
    Sprite Sprite;
    SoundBuffer buffer1,buffer2,buffer3;

    if (!buffer1.loadFromFile("resource/GUI_Select_31_1.wav")) {
        std::cout << "Error!" << std::endl;
    }

    if (!buffer2.loadFromFile("resource/ninja_Hattori.wav")) {
        std::cout << "Error!" << std::endl;
    }

    if (!buffer3.loadFromFile("resource/GUI_Select_01_1.wav")) {
        std::cout << "Error!" << std::endl;
    }

    Sound sound1,sound2,sound3;
    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound3.setBuffer(buffer3);

    if (!Texture.loadFromFile("resource/red.jpg"))
    {
        std::cerr << "Error loading back.jpg" << std::endl;
    }
    Sprite.setTexture(Texture);
    //Sprite.setColor(sf::Color(255, 255, 255, 0.5));
    Thread threadD(std::bind(&Djks::dijkstra, this, src_x, src_y, dest_x, dest_y, obstacle));
    Event event;
    bool Running = true;

    while (Running)
    {
        //Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            //Key pressed
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    threadD.terminate();
                    reset();
                    return (0);
                    break;
                case sf::Keyboard::Q:
                    threadD.terminate();
                    return (-1);
                    break;
                default:
                    break;
                }
            }

            if (event.type == Event::MouseMoved) {
                int X = event.mouseMove.x;
                int Y = event.mouseMove.y;
                if (X > 305 && X < 498 && Y>69 && Y < 103) {
                    text1.setFillColor(Color::White);
                }
                else
                    text1.setFillColor(Color::Red);

                if (X > 305 && X < 498 && Y>105 && Y < 135) {
                    text2.setFillColor(Color::White);
                }
                else
                    text2.setFillColor(Color::Red);
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                int row = Y / 20;       //Reversed notion of row & column
                int col = X / 20;
                // if (count == 0 && row>0 && row<29 && col>0 && col<29){
                //     src_x = row;
                //     src_y = col;
                //     count++;
                // }
                // else if(count == 1 && row>0 && row<29 && col>0 && col<29){
                //     dest_x = row;
                //     dest_y = col;
                //     count++;
                // }
                if (obstacle[row][col] == 0 && row > 0 && row < 29 && col>0 && col < 39) {
                    if (row > 7 || col > 25 || col < 14) {
                        //sound1.play();
                        obstacle[row][col] = 1;
                    }
                }
                else if (obstacle[row][col] == 1 && row > 0 && row < 29 && col>0 && col < 39) {
                    if (row > 7 || col > 25 || col < 14) {
                        sound1.play();
                        obstacle[row][col] = 0;
                    }
                }
                if (X > 300 && X < 500 && Y>70 && Y < 105) {
                    sound3.play();
                    sound2.play();
                    threadD.launch();
                    //dijkstra(src_x, src_y, dest_x, dest_y, obstacle);                                                         
                }
                if (X > 300 && X < 500 && Y>105 && Y < 140) {
                    sound3.play();
                    threadD.terminate();
                    reset();
                }
            }
        }

        App.clear();
        buttonLaunch.setPosition(300, 70);
        buttonReset.setPosition(300, 105);
        text.setPosition(305, 10);      
        text1.setPosition(305, 73);
        text2.setPosition(360, 108);
        text3.setPosition(466, 73);
        App.draw(Sprite);
        App.draw(buttonLaunch);      
        App.draw(buttonReset);
        App.draw(text);
        App.draw(text1);
        App.draw(text2);
        App.draw(text3);

        if (!pathD.empty()) {
            for (int i = 0; i<int(pathD.size()); i++) {
                pathRectangle.setPosition(pathD[i].second * 20, pathD[i].first * 20);   
                App.draw(pathRectangle);      
                coloured[pathD[i].first][pathD[i].second] = 1;
            }
        }

        srcRectangle.setPosition(src_y * 20, src_x * 20);
        App.draw(srcRectangle);   
        coloured[src_x][src_y] = 1;
        destRectangle.setPosition(dest_y * 20, dest_x * 20);
        App.draw(destRectangle);    
        coloured[dest_x][dest_y] = 1;
        for (int i = 0; i <= 580; i += 20) {
            for (int j = 0; j <= 780; j += 20) {
                if (obstacle[i / 20][j / 20] == 0) {
                    obsRectangle.setOutlineThickness(1);
                    obsRectangle.setOutlineColor(Color::Red);
                    obsRectangle.setPosition(j, i);
                    App.draw(obsRectangle);       
                }
                if (sptSet[i / 20][j / 20] == true && coloured[i / 20][j / 20] == 0) {
                    findRectangle.setOutlineThickness(1);
                    findRectangle.setOutlineColor(Color::Red);
                    findRectangle.setPosition(j, i);
                    App.draw(findRectangle);       
                }
                if (obstacle[i / 20][j / 20] == 1 && sptSet[i / 20][j / 20] == false && coloured[i / 20][j / 20] == 0) {
                    rectangle.setOutlineThickness(1);
                    rectangle.setOutlineColor(Color(250, 128, 114));
                    rectangle.setPosition(j, i);
                    App.draw(rectangle);     
                }
            }
        }
        App.display();
    }
    return -1;
}