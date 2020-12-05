#include "../include/Dijkstra.hpp"

bool sptSet[NUM_ROW][NUM_COLS];
vector<pair<int,int> > pathD;

Djks::Djks(void) //: threadD(std::bind(&Djks::dijkstra,this,source_x,source_y,dest_x,dest_y,grid))
{   
    srand(time(0));
    source_x=1+rand()%20;
    source_y=2+rand()%12;
    dest_x=1+rand()%20;
    dest_y=26+rand()%12;   //Origin(2,3)->Goal(50,56)
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
    buttonStartD.setSize(Vector2f(200,35));       //button dijkstra
    buttonStartD.setFillColor(Color::Transparent);
    buttonStartD.setOutlineThickness(1);
    buttonStartD.setOutlineColor(Color::Red);
    buttonReset.setSize(Vector2f(200,35));
    buttonReset.setFillColor(Color::Transparent);
    buttonReset.setOutlineThickness(1);
    buttonReset.setOutlineColor(Color::Red);
   
    rectangle.setSize(Vector2f(20,20));      //default box :White
    rectangle.setFillColor(Color::Transparent);
    brectangle.setSize(Vector2f(20,20));     //obstacle box: Black
    brectangle.setFillColor(Color::White);
    grectangle.setSize(Vector2f(20,20));     //Dijkstra path box: Green
    grectangle.setFillColor(Color::Black);
    grectangle.setOutlineThickness(1);
    grectangle.setOutlineColor(Color::Red);
    blueRectangle.setSize(Vector2f(20,20));      //source box: cyan
    blueRectangle.setFillColor(Color(255,69,0));
    blueRectangle.setOutlineThickness(1);
    blueRectangle.setOutlineColor(Color::Black);
    rrectangle.setSize(Vector2f(20,20));         //destination box: red
    rrectangle.setFillColor(Color::Red);
    rrectangle.setOutlineThickness(1);
    rrectangle.setOutlineColor(Color::Red);
    yrectangle.setSize(Vector2f(20,20));
    yrectangle.setFillColor(Color(250,128,114));
}

void Djks::reset(){
    for (int i = 0;i<shortest_distance-1;i++){
        pathD.pop_back();
    }
    // srand(time(0));
    // source_x=1+rand()%20;
    // source_y=2+rand()%12;
    // dest_x=1+rand()%20;
    // dest_y=26+rand()%12;   //Origin(2,3)->Goal(50,56)
    for(int i=0;i<NUM_ROW;i++)
        for(int j=0;j<NUM_COLS;j++){
            if((i==0 && j<15 && j>25)||i==29||j==0||j==39||(i==7 && j>14 && j<26)||(j==14 && i<8)||(j==25 && i<8))        //walls
                grid[i][j]=0;
            else
                grid[i][j]=1;
        }
    for(int i=0;i<NUM_ROW;i++)
        for(int j=0;j<NUM_COLS;j++){
            sptSet[i][j]=false;     //dijkstra all unexplored
            dist[i][j]=FLT_MAX;
            if(i>7 || j>25 || j<14)
                filled[i][j]=0;   //all uncolored  
            else
                filled[i][j]=1;
        }
    dist[source_x][source_y]=0.0;
    previous[NUM_ROW][NUM_COLS] = {make_pair(0,0)};     
    min_x=0;
    min_y=0;
    text3.setString("00");
}

void Djks::findmin(float dist[NUM_ROW][NUM_COLS],int& min_x,int& min_y){
    float mini=FLT_MAX;
    for(int i=0;i<NUM_ROW;i++)
        for(int j=0;j<NUM_COLS;j++)
            if(sptSet[i][j]==false && dist[i][j]<mini){
                mini=dist[i][j];
                min_x=i;
                min_y=j;
            }
}

void Djks::findpath(pair<int,int> previous[NUM_ROW][NUM_COLS],float dist[NUM_ROW][NUM_COLS],int dest_x,int dest_y,int source_x,int source_y){
    shortest_distance = dist[dest_x][dest_y];
    while(previous[dest_x][dest_y].first!=source_x || previous[dest_x][dest_y].second!=source_y){        // both simultaneously equal to source coordinates
        sf::sleep(milliseconds(10));        //delay shortest pathD
        pathD.push_back(make_pair(previous[dest_x][dest_y].first,previous[dest_x][dest_y].second));
        int save_x=dest_x,save_y=dest_y;
        dest_x=previous[save_x][save_y].first;                  //change the destination
        dest_y=previous[save_x][save_y].second;
    }
    text3.setString(std::to_string(shortest_distance));
}

void Djks::dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[NUM_ROW][NUM_COLS]){
    int found=0;
    for(int i=0;i<NUM_ROW && found==0;i++) {
        for(int j=0;j<NUM_COLS && found==0;j++){
            findmin(dist,min_x,min_y);                  //pass by reference
            sptSet[min_x][min_y]=true;
            if(sptSet[dest_x][dest_y]==true){
                found=1;
                break;
            }
            sf::sleep(milliseconds(1));        //delay exploration
            int possibleX[] = {0, 0, 1, -1, 1, -1, -1, 1};
            int possibleY[] = {1, -1, 0, 0, 1, 1, -1, -1};

            for(int i = 0; i < 8; ++i) {
                int newRow = min_x + possibleX[i];
                int newCol = min_y + possibleY[i];
                if(grid[newRow][newCol]==1 && sptSet[newRow][newCol]==false && dist[newRow][newCol]>dist[min_x][min_y]+1.0){
                    dist[newRow][newCol]=dist[min_x][min_y]+1.0;
                    previous[newRow][newCol]=make_pair(min_x,min_y);
                }
            }
        }
    }
        
    findpath(previous,dist,dest_x,dest_y,source_x,source_y);
}

int Djks::Run(RenderWindow &App)
{   
    Texture Texture;
    Sprite Sprite;
    if (!Texture.loadFromFile("resource/red.jpg"))
    {
        std::cerr << "Error loading back.jpg" << std::endl;
    }
    Sprite.setTexture(Texture);
    //Sprite.setColor(sf::Color(255, 255, 255, 0.5));
    Thread threadD(std::bind(&Djks::dijkstra,this,source_x,source_y,dest_x,dest_y,grid));
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
            if(event.type==Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left)
            {
                int X=event.mouseButton.x;
                int Y=event.mouseButton.y;
                int row=Y/20;       //Reversed notion of row & column
                int col=X/20;
                // if (count == 0 && row>0 && row<29 && col>0 && col<29){
                //     source_x = row;
                //     source_y = col;
                //     count++;
                // }
                // else if(count == 1 && row>0 && row<29 && col>0 && col<29){
                //     dest_x = row;
                //     dest_y = col;
                //     count++;
                // }
                if(grid[row][col]==0 && row>0 && row<29 && col>0 && col<39){
                    if(row>7 || col>25 || col<14){
                        grid[row][col]=1;
                    }
                }
                else if(grid[row][col]==1 && row>0 && row<29 && col>0 && col<39){
                    if(row>7 || col>25 || col<14){
                        grid[row][col]=0;
                    }
                }
                if(X>300 && X<500 && Y>70 && Y<105){
                    threadD.launch();  
                    //dijkstra(source_x, source_y, dest_x, dest_y, grid);                                                             //to improve
                }
                if(X>300 && X<500 && Y>105 && Y<140){
                    threadD.terminate();
                    reset();
                }
            }
        }

        App.clear();
        buttonStartD.setPosition(300,70);
        buttonReset.setPosition(300,105);
        text.setPosition(305,10);       //Dijkstra text
        text1.setPosition(305,73);
        text2.setPosition(360,108);
        text3.setPosition(466,73);
        App.draw(Sprite);
        App.draw(buttonStartD);      //Dijkstra launch
        App.draw(buttonReset);
        App.draw(text);
        App.draw(text1);
        App.draw(text2);
        App.draw(text3);

        if(!pathD.empty()){
            for(int i=0;i<int(pathD.size());i++){
                grectangle.setPosition(pathD[i].second*20,pathD[i].first*20);     //Reversed notion of row & column
                App.draw(grectangle);        //final pathD
                filled[pathD[i].first][pathD[i].second]=1;
            }
        }

        blueRectangle.setPosition(source_y*20,source_x*20);
        App.draw(blueRectangle);     //source
        filled[source_x][source_y]=1;
        rrectangle.setPosition(dest_y*20,dest_x*20);
        App.draw(rrectangle);        //destination
        filled[dest_x][dest_y]=1;
        for(int i=0;i<=580 ;i+=20){
            for(int j=0;j<=780;j+=20){
                if(grid[i/20][j/20]==0){
                    brectangle.setOutlineThickness(1);
                    brectangle.setOutlineColor(Color::Red);
                    brectangle.setPosition(j,i);
                    App.draw(brectangle);        //User's obstacle
                }
                if(sptSet[i/20][j/20]==true && filled[i/20][j/20]==0){
                    yrectangle.setOutlineThickness(1);
                    yrectangle.setOutlineColor(Color::Red);
                    yrectangle.setPosition(j,i);
                    App.draw(yrectangle);        // Explored Cells by dijkstra
                }
                if(grid[i/20][j/20]==1 && sptSet[i/20][j/20]==false && filled[i/20][j/20]==0){     
                    rectangle.setOutlineThickness(1);
                    rectangle.setOutlineColor(Color(250,128,114));
                    rectangle.setPosition(j,i);
                    App.draw(rectangle);     //default white cells
                }
            }
        }
        App.display();
    }
    return -1;
}