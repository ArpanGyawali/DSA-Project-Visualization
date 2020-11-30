#include "../include/Dijkstra.hpp"

bool sptSet[NUM_CELL][NUM_CELL];
vector<pair<int,int> > pathD;

Djks::Djks(void) //: threadD(std::bind(&Djks::dijkstra,this,source_x,source_y,dest_x,dest_y,grid))
{   
    source_x=2;
    source_y=2;
    dest_x=50;
    dest_y=56;   //Origin(2,3)->Goal(50,56)
    for(int i=0;i<NUM_CELL;i++)
        for(int j=0;j<NUM_CELL;j++){
            if(i==0||i==59||j==0||j==59)        //walls
                grid[i][j]=0;
            else
                grid[i][j]=1;
        }
    for(int i=0;i<NUM_CELL;i++)
        for(int j=0;j<NUM_CELL;j++){
            sptSet[i][j]=false;     //dijkstra all unexplored
            filled[i][j]=0;     //all uncolored
            dist[i][j]=FLT_MAX;
        }
    //threadD = new Thread(&Djks::dijkstra,this,source_x,source_y,dest_x,dest_y,grid);
    dist[source_x][source_y]=0.0;
    // bool sptSet[NUM_CELL][NUM_CELL] = { false };
    previous[NUM_CELL][NUM_CELL] = {make_pair(0,0)};     
    min_x=0;
    min_y=0;
    if (!font.loadFromFile("resource/Text.ttf"))
    {
        std::cerr << "Error loading Text.ttf" << std::endl;
    }
    text1.setFont(font);
    text1.setString("FIND PATH");
    text1.setCharacterSize(15);

    // Shapes
    buttonStartD.setSize(Vector2f(200,30));       //button dijkstra
    buttonStartD.setFillColor(Color::Green);
   
    rectangle.setSize(Vector2f(10,10));      //default box :White
    rectangle.setFillColor(Color::White);
    brectangle.setSize(Vector2f(10,10));     //obstacle box: Black
    brectangle.setFillColor(Color::Black);
    grectangle.setSize(Vector2f(10,10));     //Dijkstra path box: Green
    grectangle.setFillColor(Color::Green);
    grectangle.setOutlineThickness(2);
    grectangle.setOutlineColor(Color::Red);
    blueRectangle.setSize(Vector2f(10,10));      //source box: blue
    blueRectangle.setFillColor(Color::Blue);
    blueRectangle.setOutlineThickness(2);
    blueRectangle.setOutlineColor(Color::Black);
    rrectangle.setSize(Vector2f(10,10));         //destination box: red
    rrectangle.setFillColor(Color::Red);
    rrectangle.setOutlineThickness(2);
    rrectangle.setOutlineColor(Color::Red);
    yrectangle.setSize(Vector2f(10,10));
    yrectangle.setFillColor(Color::Yellow);
}

void Djks::findmin(float dist[NUM_CELL][NUM_CELL],int& min_x,int& min_y){
    float mini=FLT_MAX;
    for(int i=0;i<NUM_CELL;i++)
        for(int j=0;j<NUM_CELL;j++)
            if(sptSet[i][j]==false && dist[i][j]<mini){
                mini=dist[i][j];
                min_x=i;
                min_y=j;
            }
}

void Djks::findpath(pair<int,int> previous[NUM_CELL][NUM_CELL],float dist[NUM_CELL][NUM_CELL],int dest_x,int dest_y,int source_x,int source_y){
    int shortest_distance = dist[dest_x][dest_y];
    while(previous[dest_x][dest_y].first!=source_x || previous[dest_x][dest_y].second!=source_y){        // both simultaneously equal to source coordinates
        sf::sleep(milliseconds(10));        //delay shortest pathD
        cout << "Visiting x = " << previous[dest_x][dest_y].first << "  " << "and y = " << previous[dest_x][dest_y].second << endl;
        pathD.push_back(make_pair(previous[dest_x][dest_y].first,previous[dest_x][dest_y].second));
        int save_x=dest_x,save_y=dest_y;
        dest_x=previous[save_x][save_y].first;                  //change the destination
        dest_y=previous[save_x][save_y].second;
    }
    cout<<"\nLength of Dijkstra path is: "<<shortest_distance<<endl;
}

void Djks::dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[NUM_CELL][NUM_CELL]){
    int found=0;
    for(int i=0;i<NUM_CELL && found==0;i++) {
        for(int j=0;j<NUM_CELL && found==0;j++){
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
                    return (0);
                    break;
                case sf::Keyboard::Q:
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
                int row=Y/10;       //Reversed notion of row & column
                int col=X/10;
                if(grid[row][col]==0 && row>0 && row<59 && col>0 && col<59){
                    grid[row][col]=1;
                    cout<<"Cell "<<row<<" , "<<col<<" state is: "<<"1"<<endl;
                }
                else if(grid[row][col]==1 && row>0 && row<59 && col>0 && col<59){
                    grid[row][col]=0;
                    cout<<"Cell "<<row<<" , "<<col<<" state is: "<<"0"<<endl;
                }
                if(X>600 && X<675 && Y>0 && Y<25){
                    threadD.launch();  
                    //dijkstra(source_x, source_y, dest_x, dest_y, grid);                                                             //to improve
                }
            }
        }

        App.clear();
        buttonStartD.setPosition(600,0);
        App.draw(buttonStartD);      //Dijkstra launch
        text1.setPosition(602,5);       //Dijkstra text
        App.draw(text1);

        if(!pathD.empty()){
            for(int i=0;i<int(pathD.size());i++){
                grectangle.setPosition(pathD[i].second*10,pathD[i].first*10);     //Reversed notion of row & column
                App.draw(grectangle);        //final pathD
                filled[pathD[i].first][pathD[i].second]=1;
            }
        }

        blueRectangle.setPosition(source_y*10,source_x*10);
        App.draw(blueRectangle);     //source
        filled[source_x][source_y]=1;
        rrectangle.setPosition(dest_y*10,dest_x*10);
        App.draw(rrectangle);        //destination
        filled[dest_x][dest_y]=1;
        for(int i=0;i<=590 ;i+=10){
            for(int j=0;j<=590;j+=10){
                if(grid[i/10][j/10]==0){
                    brectangle.setOutlineThickness(2);
                    brectangle.setOutlineColor(Color::Red);
                    brectangle.setPosition(j,i);
                    App.draw(brectangle);        //User's obstacle
                }
                if(sptSet[i/10][j/10]==true && filled[i/10][j/10]==0){
                    yrectangle.setOutlineThickness(2);
                    yrectangle.setOutlineColor(Color::Red);
                    yrectangle.setPosition(j,i);
                    App.draw(yrectangle);        // Explored Cells by dijkstra
                }
                if(grid[i/10][j/10]==1 && sptSet[i/10][j/10]==false && filled[i/10][j/10]==0){     //not in dijkstra
                    rectangle.setOutlineThickness(2);
                    rectangle.setOutlineColor(Color::Red);
                    rectangle.setPosition(j,i);
                    App.draw(rectangle);     //default white cells
                }
            }
        }
        App.display();
    }
    return -1;
}