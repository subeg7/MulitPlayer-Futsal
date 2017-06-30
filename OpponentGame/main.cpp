//Client Game
//OpponentGame

#include <iostream>
#include<string>
#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<ctime>
#include<cstdlib>

#define FoutLine RRectangle outline(fieldStart,fieldEnd,WHITE,LINE_THICKNESS);
#define FmidLine RRectangle midline(pm1,pm2,WHITE);
#define FDboxs EEllipse(pem1, -88, 88, 130,180,WHITE,LINE_THICKNESS);EEllipse(pem2, 90, -90, 130,180,WHITE,LINE_THICKNESS);
#define Fcenter CCircle(fieldCenter,25,WHITE,LINE_THICKNESS);
#define CREATE_FIELD_LINES FoutLine FmidLine FDboxs Fcenter
#define CREATE_ALL_PLAYERS  lp =0; for(; lp<5; lp++) {tempServerTeam[lp].createPlayer(); clientTeam[lp].createPlayer();}
using namespace std;



const int LINE_THICKNESS = 5;
const int PLAYER_SIZE=37;
SOCKET m_socket;



/*
//forward declarations
class Player{
public:
   Player(Position p,string n, int t );
    Player();
    void setData(Position p,string n, int t);
    void setCurrPos(Position p);
    void setPossessStat(bool s);

    Position getCurrPos();
    string getName();

    void shift(Position newPos);
    void show();


};
*/
class Position {

public:

    int x;
    int y;

    //methods
    Position(int xx, int yy) {
        x = xx;
        y = yy;
    }

    Position() {}


    int getDistanceFrom(Position p) {
        unsigned int dis = sqrt(  pow((this->x-p.x),2)+   pow((this->y-p.y),2) );
        return dis;
    }


    int operator<(Position pp) {
        if(pp.x>this->x || pp.y>this->y)
            return 1;
        else return 0;
    }

    Position operator+(int len) {
        Position temp;
        temp.x = this->x+len;
        temp.y = this->y+len;
        return temp;

    }

    /*Position operator-(Position p)
    {
         Position temp;
        temp.x = unsigned(this->x-p.x);
        temp.y = unsigned(this->y-p.y;

        return temp;
    }*/


    Position shift(int xlen, int ylen) {
        //to shift to origin xlen and yylen must myst be negative
        Position temp;
        temp.x = this->x+xlen;
        temp.y = this->y+ylen;

        return temp;
    }

    /*    Position operator/(int div){
            Position temp;
            temp.x = this->x/div;
            temp.y = this->y/div;

            return temp;
        }*/

    Position midPointFrom(Position p) {
        Position temp;
        int div = 2;
        temp.x = (-this->x+p.x)/div+this->x;
        temp.y =(-this->y+p.y)/div+this->y;

        return temp;
    }

    void showCoor() {
        //////cout<<"\nCo-ordintes:\n";
        ////cout<<"\t x="<<x<<"\t\t y="<<y;
    }

    int getSlopeFrom(Position p) {
        int slope = 0;
    }



};


class Shape {
protected:
    int thickness;
    Position pos;

public:
    void draw(Position p1, Position p2);

};
//int Shape::thickness = 1;

class RRectangle:public Shape {
    Position startPos;
    Position endPos;
public:
    RRectangle(Position p1, Position p2,int color,float thick=-1) {
        startPos = p1;
        endPos = p2;

        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        if(thick>-1) {
            this->thickness = thick;
            rectangle(p1.x,p1.y,p2.x,p2.y);
            rectangle(p1.x+thick,p1.y+thick,p2.x-thick,p2.y-thick);
            floodfill(p1.x+1,p1.y+1,color);


        } else { //fill the entire area

            rectangle(p1.x,p1.y,p2.x,p2.y);
            floodfill(p1.x+1,p1.y+6,color);
        }
    }

    void shiftVertical(int len) {
        this->startPos.y+=len;
        this->endPos.y+=len;

    }
};

/*class LLine: public Shape{
    Shape(Position p, position q,int color, int thick=0){
        setcolor(color);
        line(p.x,p.y,q.x,q.y);
        if(thick!=0){
            this->thickness = thick;

            //line(p.x,p.y,q.x,q.y);
        }

    }
};*/

class CCircle:public Shape {

    Position center;
    int color;
    int thickness;
public:

    int getColor() {
        return color;
    }
    int getthickness() {
        return thickness;
    }

    void setCenter(Position p) {
        center = p;
    }



    CCircle() {
    }
    //copy constructor

    CCircle(Position p,int r, int color, int thick =-1) {
        center = p;
        this-> color = color;
        thickness = thick;


        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        circle(p.x,p.y,r);


        if(thick>-1) {
            circle(p.x,p.y,r+thick);
            //sometimes the circle is ostructed y other colors make 4 points fill
            floodfill(p.x,p.y+r+1,color);//down
            floodfill(p.x,p.y-r-1,color);//up
            floodfill(p.x+r+1,p.y,color);//right
            floodfill(p.x-r-1,p.y,color);//left






        } else { //fill all

            floodfill(p.x+r/2,p.y,color);
            floodfill(p.x-r/2,p.y,color);
        }



    }
    void shift(Position newPos,int thick=0) {

        Position old = center;
        //erase old;


        if(thick >0) {
            CCircle(old, PLAYER_SIZE+thick,GREEN);
            CCircle(newPos, PLAYER_SIZE,getColor(), thick);
        } else
            CCircle(newPos, PLAYER_SIZE,getColor());

        //delay(100);



    }
};



class EEllipse {

public:
    EEllipse( Position p, int sta, int enda, int a, int b, int color, float thick=-1) {
        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        ellipse(p.x, p.y, sta, enda, a, b);
        //this->thickness = thick;
        if(thick>-1) {
            ellipse(p.x, p.y, sta, enda, a+thick, b+thick);
            if(sta<1)
                floodfill(p.x+thick/2+a, p.y, color);
            else {
                // putpixel(p.x-thick/2-a, p.y
//, RED);
                //setcolor(RED);
                //circle(p.x-thick/2-a, p.y,10);

                floodfill(p.x-thick/2-a, p.y,WHITE);
            }
        } else {

            floodfill(p.x +a/2, p.y+b/2,color);
        }


    }


};



class PassLine {
    Position p1, p2;
public:
    PassLine(Position m, Position b, int color,int thick = 0) {
        setcolor(color);

        /*

            int pX, pY;
            int xDif = m.x -b.x;
            Position obst;


             //= m.x>b.x?m.x:b.x

             int xPos = m.x;
            if(m.x>b.x && xDif!=0){
                    ////cout<<"\n MouseXX is Greater";

                int slope = (m.y - b.y)/xDif;
                for(;xPos>=b.x;xPos--){
                    ////cout<<"\nSearching...";
                    pX = b.x+xPos;
                    pY = b.y+ slope*(pX);
                    if(getpixel(pX,pY)==GREEN||getpixel(pX,pY)==WHITE){
                        ////cout<<"\n Color Found";
                        obst.x  =pX;
                        obst.y  = pY;

                        break;
                    }
                }
            }
                else{
                    ////cout<<"\n MOUSEXX might be smaller or xDif might be 0";
                }

                delay(2000);


        /*
            }else if(m.x<b.x && xDif!=0){
                int slope = (m.y - b.y)/xDif;
                for(;lpcnt<=b.x;lpcnt++){
                    pX = b.x+lpcnt;
                    pY = b.y+ slope*(pX);

                    if(getpixel(pX,pY)==GREEN||getpixel(pX,pY)==WHITE){
                        obst.x  =pX;
                        obst.y  = pY;
                        break;
                    }


                }




            }else{
                int y = m.y;
                pX = b.x;
                if(m.y>b.y){
                    for(;y>=b.y;y--){
                        if(getpixel(pX,pY)==GREEN||getpixel(pX,pY)==WHITE){
                        obst.x  =pX;
                        obst.y  = pY;
                        break;
                        }

                    }

                }else{
                    for(;y<=b.y;y++){
                        if(getpixel(pX,pY)==GREEN||getpixel(pX,pY)==WHITE){
                        obst.x  =pX;
                        obst.y  = pY;
                        break;
                        }

                    }

                }
                */







        // line(obst.x,obst.y,b.x,b.y);
        line(m.x,m.y,b.x,b.y);

    }

};




class Player {
    string name;
    char nameBuf[15];
    string team;
    Position currPos;
    CCircle playerCircles[2];
    int no;
    bool inPossession;
    int     playerId;


public:
    static int playerIdCount;
    Player(Position p,string n, int t ) {
        playerIdCount++;
        playerId = playerIdCount;

        name = n;

        currPos = p;
        //nameBuf="";
        inPossession= false;

        //tring tmp = "cat";
        //char tab2[1024];
        strcpy(nameBuf, name.c_str());

        int playerColor;
        if(t==1) {

            ////cout<<"creating player 1 BROWN_BLUE";
            team = "Player-1"  ;
            playerColor = BLUE;
            CCircle bigC(p,PLAYER_SIZE,BLACK,7);
            CCircle smallC(p,PLAYER_SIZE,BLUE);

            playerCircles[0] = bigC;
            playerCircles[1] = smallC;
            //
        } else {
            ////cout<<"Creating Player 2  YELLOW_RED";
            team = "Player-2";
            playerColor = RED;

            CCircle bigC(p,PLAYER_SIZE,BLACK,7);
            CCircle smallC(p,PLAYER_SIZE,playerColor);

            playerCircles[0] = bigC;
            playerCircles[1] = smallC;


        }


        // CCircle(p,PLAYER_SIZE,playerColor);
    }

    Player() {
        name = "notSet";
        team = "notSet";
        Position ps(0,0);
        currPos = ps;
        inPossession= false;

        playerIdCount++;
        playerId = playerIdCount;
    }

    int getId() {
        return playerId;
    }
    void setData(Position p,string n, int t,int num) {
        name = n;
        no = num;
        currPos = p;
        if(t==1)
            team="Player-1";
    }

    void erasePlayer() {
        CCircle(currPos,PLAYER_SIZE+7,GREEN);
    }

    void createPlayer() {


        Position p = this->currPos;
        if(team =="Player-1") {

            //////cout<<"creating player 1 BROWN_BLUE";
            //team = "Player-1";

            CCircle bigC(p,PLAYER_SIZE,BLACK,7);
            CCircle smallC(p,PLAYER_SIZE,BLUE);

            playerCircles[0] = bigC;
            playerCircles[1] = smallC;

        } else {
            //  ////cout<<"Creating Player 2  YELLOW_RED";
            team = "Player-2";

            CCircle bigC(p,PLAYER_SIZE,BLACK,7);
            CCircle smallC(p,PLAYER_SIZE,RED);

            playerCircles[0] = bigC;
            playerCircles[1] = smallC;
        }

        strcpy(nameBuf, name.c_str());
        // //cout<<"\nnameBuf holds"<<nameBuf;


        int n =15;
        setcolor(BROWN);
        settextstyle(3,HORIZ_DIR,2);
        outtextxy(currPos.x-n-20,currPos.y-n,nameBuf);

    }

    Position getCurrPos() {
        return currPos;
    }

    void setCurrPos(Position p) {
        currPos = p;
    }

    void shift(Position newPos) {

        playerCircles[0].shift(newPos,7);
        playerCircles[1].shift(newPos);


        currPos=newPos;
        playerCircles[0].setCenter(newPos);
        playerCircles[1].setCenter(newPos);

        strcpy(nameBuf, name.c_str());
        // //cout<<"\nnameBuf holds"<<nameBuf;

        int n =15;
        setcolor(BROWN);
        settextstyle(3,HORIZ_DIR,2);
        outtextxy(currPos.x-n-20,currPos.y-n,nameBuf);
    }

    int getNo() {
        return no;
    }

    void show() {
        Position p = this->currPos;
        if(team =="Player-1") {

            //////cout<<"creating player 1 BROWN_BLUE";
            //team = "Player-1";

            CCircle bigC(p,PLAYER_SIZE,BLACK,7);
            CCircle smallC(p,PLAYER_SIZE,BLUE);

            // playerCircles[0] = bigC;
            // playerCircles[1] = smallC;

        } else {
            //  ////cout<<"Creating Player 2  YELLOW_RED";
            //team = "Player-2";

            CCircle bigC(p,PLAYER_SIZE,BLACK,7);
            CCircle smallC(p,PLAYER_SIZE,RED);

            //   playerCircles[0] = bigC;
            // playerCircles[1] = smallC;
        }
        int n =15;
        setcolor(BROWN);
        settextstyle(3,HORIZ_DIR,2);
        outtextxy(currPos.x-n-20,currPos.y-n,nameBuf);

    }

    bool operator==(Player p) {
        if(this->playerId==p.getId())
            return true;
        else
            return false;
    }


    string getName() {
        return name;
    }

    void setPossessStat(bool s) {
        int i=0;
        //clientTeam[i].set
        inPossession  = s;
    }

    bool getPossessStat() {
        return inPossession;
    }
    void shoot();
    void accuratePass(Player p);
    void accuratePass(Position p);
    void throughPass(Player p);
    void runto(Position p);
//    friend Player findPlayerAt(Player team[],Position p){
    //      int i=0;

    //    for(in)

    //return  0//;
    // }





//    friend void animate(&player);


};
Player serverTeam[5];
Player clientTeam[5];
Player tempClientTeam[5];
Player tempServerTeam[5];
const int BALL_SIZE = 26;
int Player::playerIdCount=0;


Position prevBallPos;
class Ball {
    Position currPos;
    Position mouseSeq[2];
    Position ballSeq[2];
    Player inLegOf;


public:
    bool isBallWon;
    bool isClientBallMoved;
    bool isServerBallMoved;
    bool isServerMissPassed;
    bool isClientMissPassed;
    bool isBallMoved;
    static int seqNo;
    void setCurrPos(Position cp) {
        currPos = cp;
    }

    Player getInLegOf() {
        return inLegOf;
    }
    void setInLegOf(Player pl) {
        inLegOf  = pl;
    }
    void drawBall(Position m, Position p,Player player,bool psLine=false) {

        Position currBall;


        float xBall,yBall;
        float len = m.getDistanceFrom(p);
        //////cout<<"\n Length between Mouse and Player= "<< len;
        float rBtoP = BALL_SIZE+PLAYER_SIZE+7;
        xBall = p.x+(rBtoP/len) *(m.x-p.x);
        yBall = p.y+(rBtoP/len) * (m.y-p.y);


        if(player.getName()=="notSet") {
            //////cout<<"\n Inside DrawBall PlayerPos notSet";
            currPos =currBall=p;
            //////cout<<"\nCurrBall=";
            //currBall.showCoor();
            //////cout<<"\n Position p=";
//            p.showCoor();

            xBall = p.x;
            yBall = p.y;

            setcolor(BROWN);
            //circle(p.x,p.y,PLAYER_SIZE+7);
            //delay(10000);
        } else {
            //    Position currBall(xBall, yBall);

            currBall.x = xBall;
            currBall.y = yBall;

            currPos = currBall;
        }


        if(seqNo>=1) {

            //////cout<<"\nSequence is >>THAN 1";
            mouseSeq[1] = mouseSeq[0]; // past mouse position
            mouseSeq[0] = m;// present mouse position

            ballSeq[1] = ballSeq[0];
            ballSeq[0] = currBall;

        } else {
            //////cout<<"\n Sequence is 0";
            mouseSeq[0] = mouseSeq[1] = m;
            ballSeq[0] = ballSeq[1] = currBall;


        }
        //erase line created in previous mouse position
        seqNo++;
        if(psLine)
            PassLine(mouseSeq[1],ballSeq[1],GREEN);

        CCircle(ballSeq[1],BALL_SIZE,GREEN);
        //delay(1000);




        if(psLine)
            PassLine(m,currBall,COLOR(453,766,23));

        CCircle(Position((int)xBall,(int)yBall),BALL_SIZE,COLOR(51,0,51));
        CCircle(Position((int)xBall,(int)yBall),BALL_SIZE-5,COLOR(102,0,102),5);
        //player.show();
        prevBallPos = currPos;




    }

    void drawBallAtCurrPos() {
        mouseSeq[1] = mouseSeq[0];
        mouseSeq[0] = prevBallPos;

        ballSeq[1] = ballSeq[0];
        ballSeq[0] = currPos;

        CCircle(ballSeq[1],BALL_SIZE,GREEN);
        CCircle(ballSeq[0],BALL_SIZE,COLOR(51,0,51));
        CCircle(ballSeq[0],BALL_SIZE-5,COLOR(102,0,102),5);

    }
    void drawPassedBall() {
        //Position prevBallPos  = prevBall.getCurrPos();
        drawBall(prevBallPos,currPos,inLegOf,false);
        //prevBall=mainBall.getCurrPos();
    }
    Position getCurrPos() {
        return currPos;
    }
};

Ball mainBall;
Ball prevBall;
int Ball::seqNo = 0;
//Ball prevBall ;

int  setAllFalse( Player team[]) {
    int i =0;
    for(; i<5; i++) {
        serverTeam[i].setPossessStat(false);
        clientTeam[i].setPossessStat(false);
    }

    return 0;

}


Player& playerAt(Player team[],Position p) {
    int i =0;


    for(; i<=5; i++) {

        if(i==5) throw p;

        Position checkPos = team[i].getCurrPos();
        // ////cout<<"\n name of the curent checkPosition player is:"<<team[i].getName();

        if(checkPos.getDistanceFrom(p)<=PLAYER_SIZE) {

            Player& pl=team[i];
            ////cout<<"\n The clicked player is:"<<pl.getName()<< "("<<pl.getId()<<")";
            return pl;

            //break;

        }
    }

    Player temp;
    temp.setCurrPos(p);
    Player& tempPl = temp;
    //cout<<" name of temppl palyer is:"<<tempPl.getName();
    tempPl.setCurrPos(p);
    //

    //cout<<"\n Clicked player is not known, returning tempPl";
    return tempPl;
}
//SOCKET m_socket;
Player& nearestFrom(Player team[],Position p) {
    int dis = team[0].getCurrPos().getDistanceFrom(p);
    //  //cout<<"\n dis from"<<team[0].getName()<<" = "<<dis;
    //Player nearest = team[4];
    int i=1;
    int index =0;
    for(; i<5; i++) {


        int tempDis = team[i].getCurrPos().getDistanceFrom(p);
        ////cout<<"\n tempDis from"<<team[i].getName()<<" = "<<tempDis;
        if(dis>tempDis) {
            dis=tempDis;
            index =i;
            //nearest = team[i];
            //  //cout<<"\n nearest ONe value changed\n";
        }


    }

//    cout<<"nearest serverPlayer is:"<<nearest.getName()<<" and is at:";
    //  nearest.getCurrPos().showCoor();
    //exit(23);

    cout<<"\n (before returning team[index] NearestPlayer is :"<<team[index].getName()<<" (id-"<<team[index].getId()<<") "<<endl;
    return (team[index]);


}


class DisplayBoard {
    Position CenterPos;
    Position Start;
    Position End;

    int length;
    int breadth;
    string title;
    char Content[3];
    int thick;
    int Color;

public:
    DisplayBoard(){}
    DisplayBoard(Position c, int l, int b,int color,int thick=-1) {
        Position st(c.x-l/2,c.y-b/2);
        Position en(c.x+l/2,c.y+b/2);

        this->thick = thick;
        length = l;
        breadth  = b;

        Start  = st;
        End  = en;

        Color = color;

    }

    void setBoardInfo(Position c, int l, int b,int color,int thick=-1){
        Position st(c.x-l/2,c.y-b/2);
        Position en(c.x+l/2,c.y+b/2);

        this->thick = thick;
        length = l;
        breadth  = b;

        Start  = st;
        End  = en;

        Color = color;
    }

    void showBoard() {
        RRectangle board(Start,End, Color, thick);
    }

     void display(string st,int col = COLOR(255,204,204)) {
        string convSt   = st;

        int k = 0;
        char ch ='r';
        char content[500];



        k=0;

        while(ch!='\0') {
            ch = convSt[k];
            content[k]=ch;
            k++;
        }

        setcolor(col);
        settextstyle(8,HORIZ_DIR,3);
        outtextxy(Start.x+10,(Start.y+End.y)/2,"............................................................");
        outtextxy(Start.x+10,(Start.y+End.y)/2,content);

    }





    void setTitle(string s, int color) {
        title = s;
        char text[25] ;
        int i =0;
        char ch='r';
//        ////cout<<"\nInside display board";
        while(ch!='\0') {

            ch= s[i];
            //////cout<<ch;
            text[i] = ch;
            i++;
        }
//            ////cout<<"\n\ntext:"<<text;
        setcolor(color);
        outtextxy(Start.x+20,Start.y-3,text);
    }



    void display(int i,int col=GREEN) {
        //  ////cout<<"\nValue of i is:"<<i;
        if(i>0&& i<1000) {


            stringstream stream;
            //   stream.empty();
            stream.clear();
            stream.str("");
            // ////cout<<"\nThe uninitialized stream is:"<<stream;
//            str.flush();
            /*
                        if(i<10) {
                            stream<<'0'<<i;
                            //////cout<<"\n i<10";
                        } else if(i<100) {
                            stream<<'00'<<i;
                            //////cout<<"\n i<100";
                        } else {
                            //////cout<<"\n i>100";
                            stream<<i;
                        }


                    */

            stream<<i;


            string convSt   = stream.str();

            //  ////cout<<"\n\ tstring stream returned::"<<convSt;
//        str.close

//        content = (char)  temp_str.c_str()


            int k = 0;
            char ch ='r';
            char content[6];



            k=0;
            // k++;
            while(ch!='\0') {
                ch = convSt[k];
                //  ////cout<<"\nch="<<ch;
                content[k]=ch;
                k++;

            }


//            return 0;


            //delay(3000);

            // ////cout<<"\ncontent:"<<content;

            setcolor(WHITE);
            settextstyle(6,HORIZ_DIR,5);


            if(breadth==0) {
                //RRectangle(End,Position(End.x+30,End.y+30),GREEN);
                //int col = BLUE;
                //setcolor(col);
                setcolor(col);
                outtextxy(End.x-60,End.y-20,"......");
                outtextxy(End.x-60,End.y-20,content);



            } else {

                outtextxy((Start.x+End.x)/2,(Start.y+End.y)/2,content);
            }
        } else {
            //RRectangle(End,Position(End.x+30,End.y+30),GREEN);
            //int col = BLUE;
            //setcolor(col);
            if(breadth==0) {
                setcolor(col);
                outtextxy(End.x-60,End.y-20,"......");
                outtextxy(End.x-60,End.y-20,"0");



            } else {

                outtextxy((Start.x+End.x)/2,(Start.y+End.y)/2,"0");
            }
        }






    }

};
DisplayBoard commentBoard;


class Transmission {
    Player changesAttempted[5];
    bool isAnyPlayerMoved;
    int myPresentChangedIndex[5];
    bool isAnythingReceieved;
    // Player OtherTeam[5];
    string serverRawInfo;

    Ball ball;


public:

    Transmission() {
        int i =0;
        for(; i<5; i++)
            myPresentChangedIndex[i] = -1;
        isAnyPlayerMoved  = false;
    }
    void setMyChanges( int changedInd[]) {
        int i =0;
        // ////cout<<"\n\nChanges:: of ";
        for(; i<5; i++) {

            int pos =changedInd[i];
            if(pos>-1) {


                myPresentChangedIndex[pos] = pos;
                isAnyPlayerMoved= true;

                //////cout<<"\n"<<clientTeam[pos].getName()<<"["<<pos<<"] has been set to \n";
                //clientTeam[pos].getCurrPos().showCoor();

            }

        }

        /*
        ////cout<<"\n The Changes set are";
        i=0;
        for(; i<5; i++) {
            int pos = myPresentChangedIndex[i];
            ////cout<<"\n myPresentChangedIndex["<<i<<"]="<<pos;

            if(false) {

                ////cout<<"\n"<<clientTeam[pos].getName()<<"["<<pos<<"] has been set to \n";
                clientTeam[pos].getCurrPos().showCoor();
            }
        }


        //delay(50000);

        */
    }



    int receiveOppChanges() {
        int i =1;
        int bytesRecv;
        //string serverMsg;
        ////cout<<"\nTrying to recieve the Server Info...";
        char recvBuf[100] = "";
        bytesRecv = recv( m_socket, recvBuf, 100, 0 );
        if(bytesRecv>=3) {
            cout<<"\n Received Server Info successfully...";
            serverRawInfo = recvBuf;
            cout<<"\n serverRawCode is::"<<serverRawInfo;
            isAnythingReceieved = true;
            return 1;

        } else {
            isAnythingReceieved = false;
            cout<<"\n No data was recieved";
            return 0;
        }
        serverRawInfo = recvBuf;


    }

    void decode() {
        if(isAnythingReceieved) {
            string toDecode = serverRawInfo;
//        string toDecode = "1-456,311/2-245,222/4-127,442/B9-999,666/";
            //cout<<"\n String to decode is"<<toDecode;
            string indivInfoColl[6];
            char indivInfo[15]="";
            //string indv;


            char ch = '2';
            int i =0,j=0;
            int pNo =0;
            ////cout<<"\n";
            while(1) {

                ch=toDecode[i+j];
                if(ch=='\0') {
                    ////cout<<"\n EOF found";
//                indv = indivInfo;
                    //pNo--;
                    break;
                } else {
                    if(ch=='/') {
                        ////cout<<"\n indivInfo::"<<indivInfo;
                        indivInfoColl[pNo] = indivInfo;
                        int lp =0;
                        for(; lp<15; lp++) {
                            indivInfo[lp] ='\0';
                        }
//                    indivInfo.clear();

                        //           ////cout<<endl<<"indivInfo["<<pNo<<"] ="<<indivInfoColl[pNo];
                        i = i+j+1;
                        j=0;
                        pNo++;
                    } else {
                        //////cout<<"\nch="<<ch;
                        indivInfo[j]=ch;
                        j++;

                    }
                }
            }




            ////cout<<"\n Loop exited with total numbers of players info is:"<<pNo;

            //initalize the tempclientPlayers to lastcclinetChanges
            int k =0;
            //  for(; k<5; k++) {
            //    tempServerTeam[k] = serverTeam[k];
            //}
            //create objects of iti = pNo;
            i =0;
            ////cout<<"\n\nUpdating the serverTeam";
            for(; i<pNo; i++) {
                char cInd[2]="";
                char cX[5]="";
                char cY[5]="";
                char ch='f';

                bool isBall = false;


                int ind;
                int x;
                int y;

                //string temp = indivInfoCall[i-1];
//            ////cout<<"\nFlag 1";
                ch = indivInfoColl[i][0];
                //////cout<<"\nCharacter index value is:"<<ch;
//            ////cout<<"\nFlag 2";

                ;
                // ////cout<<"\n String is storing::"<<st.c_str();
                // st.empty();
                if(ch=='B') {
                    mainBall.isBallWon= false;
                    mainBall.isServerBallMoved = true;
                    cInd[0] =indivInfoColl[i][1];
                    isBall = true;
                } else
                    cInd[0] = ch;

                //////cout<<"\nst[0]="<<st[0];


                ind= atoi(cInd);
                if(isBall) {
                    //////cout<<"\n The index of the Player with Ball is:"<<ind;
                    ////cout<<"\n inLegOf serverTeam["<<ind<<"] = "<< serverTeam[ind].getName();
                } else {}
                // ////cout<<"\n The index of the Player is:"<<ind;

//            st.clear();
                //          st = "";

                //            ch = indivInfoColl[i-1][2];
                if(!isBall)
                    j =2;
                else
                    j =3;


                int k = 0;
                while(1) {
                    //////cout<<"\nFinding x";
                    ch = indivInfoColl[i][j];
                    if(ch==',') break;
                    else {
                        cY[k] = ch;
                    }

                    j++;
                    k++;
                }

                x = atoi(cY);
                if(isBall) {}
                //cout<<"\n X pos of Ball is is:"<<x;
                else {

                }
                ////////cout"\n X pos of current Player is:"<<x;


                //for y
                j++;

                k=j;

                while(1) {

                    ch = indivInfoColl[i][j];
                    ////////cout"\nvalue of chY:"<<ch;
                    if(ch=='\0') break;
                    else {
                        cX[j-k] = ch;
                    }

                    j++;

                }
                ////////cout"\nValue of CY is:"<<cX;
                y = atoi(cX);

                if(isBall) {

                }
                ////cout"\n y pos of Ball is:"<<y;
                else {}
                ////////cout"\n y pos of current Player is:"<<y;

                Position currPos(x,y);
                if(ind==9) {
                    commentBoard.display("Congrats!!! your opponent has Miss-Passed the ball to you");
                    ////cout"\n Server has misspassed the ball";
                    Player& nearestOne = nearestFrom(clientTeam,currPos);
                    int ndex = nearestOne.getNo();

                    setAllFalse(clientTeam);
                    clientTeam[ndex].setPossessStat(true);
                    //cout<<"\n clinetTeam["<<ndex<<"].getPossessionStat = "<<clientTeam[ndex].getPossessStat();
                    //cout<<"\n ClientTeam["<<ndex<<"].getId() = "<<clientTeam[ndex].getId();
                    //cout<<"\n nearestOne.getId()= "<< nearestOne.getId();

//                delay(40000);

                    Position newPos = nearestOne.getCurrPos();
                    mainBall.setCurrPos(currPos);
                    mainBall.setInLegOf(nearestOne);
                    //nearestOne.setPossessStat(true);
                    mainBall.isServerMissPassed = true;
                    mainBall.drawBall(currPos,newPos,nearestOne);


                } else if(isBall) {
                    //////cout"\n Setting the Ball Info";
                    mainBall.setCurrPos(currPos);
                    Player inBallPlayer =serverTeam[ind];
                    mainBall.setInLegOf(inBallPlayer);
                    inBallPlayer.setPossessStat(true);
                } else {
                    tempServerTeam[ind].setCurrPos(currPos);
                    //////cout"\n updating the position of "<<tempServerTeam[ind].getName()<<" to\n\t";
                    tempServerTeam[ind].getCurrPos().showCoor();

                    tempServerTeam[ind].createPlayer();
                }

                if(isBall) {}
                ////cout"\nBall Is created\n\n";
                else {}
                ////////cout"\nObject Is created\n\n";



                //



                ////////cout"\nThe first index is:"<<myNum;

            }


        }
    }


    int sendInfo() {
//send ball info
        char* sendBuf;//[100];
//        int bx = ball.getCurrPos().x;

        stringstream strs,tempStream;

        bool inSearch= true;
        int indexToSend;
        int jl=0;

        //////cout<<"";
        ////cout<<"\n creating the Send Buf from client changes";

        for(; jl<5; jl++) {

            indexToSend = myPresentChangedIndex[jl];
            if(indexToSend>-1) {
                //////cout<<"\nvalue of Changed Player  index is:"<<myPresentChangedIndex[jl];
                //add to string stream
                tempStream<<jl<<'-'<<clientTeam[indexToSend].getCurrPos().x<<','<<clientTeam[indexToSend].getCurrPos().y<<'/';
                //////cout<<"\nclientTeam["<<jl<<"].x="<<clientTeam[indexToSend].getCurrPos().x;

            }
        }

        if(mainBall.isBallMoved) {

            if(mainBall.isClientMissPassed) {
                cout<<"\n Client the missPassed Info";
                tempStream<<'B'<<9<<'-'<<mainBall.getCurrPos().x<<','<<mainBall.getCurrPos().y<<'/';

                //cout<<"\n serverTeam[";
                //.cout<<"\n serverTeam["<<<<"].getId() = "<<serverTeam[ind].getId();
            } else {
                cout<<"\n Client has accurately passed the ball to another client player";
                tempStream<<'B'<<mainBall.getInLegOf().getNo()<<'-'<<mainBall.getCurrPos().x<<','<<mainBall.getCurrPos().y<<'/';
            }
        } else if(!isAnyPlayerMoved) {
            tempStream<<"02";
        }
//        if(mainBall.isClientBallMoved) {
//            if(mainBall.isClientMissPassed) {
//                cout<<"\n Trying to send the Client Misspassed Info";
//                tempStream<<'B'<<9<<'-'<<mainBall.getCurrPos().x<<','<<mainBall.getCurrPos().y<<'/';
//                mainBall.isClientBallMoved = false;
//                mainBall.isClientMissPassed =false;
//            } else {
//                cout<<"\n Ball is accurately passed to client player, sending it Server";
//                tempStream<<'B'<<mainBall.getInLegOf().getNo()<<'-'<<mainBall.getCurrPos().x<<','<<mainBall.getCurrPos().y<<'/';
//            }
//
//        } else {
//            cout<<"\n No data of ball is sent to server";
//        }

        ////cout<<"\n SendBuf Created";


        string temp_str = tempStream.str();
        sendBuf = (char*)  temp_str.c_str();

        cout<<"\n Info to send to server is:\n\t"<<sendBuf;
        //////cout<<"\nSending index of "<<serverTeam[toSend].getName()<<" is "<<sendBuf;
        int bytesSent=0;
        bytesSent = send(m_socket,sendBuf,strlen(sendBuf),0);

        if(bytesSent>=5)
            cout<<"\nInfo Sent successfully...\n\n";
        else
            cout<<"\n No data was sent to the sever\n\n";
    }


};
int main() {

    int changedList[5];
    mainBall.isBallWon  = false;
    mainBall.isBallMoved = false;
    mainBall.isClientBallMoved = false;
    mainBall.isServerMissPassed = false;
    mainBall.isClientMissPassed = false;
    prevBallPos = mainBall.getCurrPos();

    //Transmission controls;
    bool sendOnly = false;
    sendOnly  = true;
    bool receiveOnly = false;
    receiveOnly = true;
    bool  sendAndRecieve = false;




    bool initWinSock =false;
    initWinSock = true;


    // Initialize WinSock
    if(initWinSock) {
        WSADATA wsaData;
        int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
        if ( iResult != NO_ERROR )
            printf("Error at WSAStartup()\n");


        // alsaasdfasCreate a socket.

        m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
        if ( m_socket == INVALID_SOCKET ) {
            printf( "Error at socket(): %ld\n", WSAGetLastError() );
            WSACleanup();
            return 99;
        }


        // Connect to a server.
        sockaddr_in clientService;
        clientService.sin_family = AF_INET;

        char serverIp[40] ="192.168.137.1";
        string userServerIp="";

        cout<<"\nTrying Initalizing the clinet:-";
        cout<<"\n Do you want to enter the Ip Address:Host Ip address [Y/N]\n";
        char usr ='5';

        // cin>>usr;
        if(usr=='y'|| usr=='Y') {

            cout<<"\n Please enter  IPaddress of Server you are connected through Wifi-hotspot\n";
            cin>>userServerIp;
            //cout<<"\n...Setting the IP address of the Host";

            strcpy(serverIp, userServerIp.c_str());
            cout<<"\n Entering "<<serverIp<<" as the Local Host\n\n";

        } else {
            cout<<"\nyou opted to run on Default Ip address set by program itself "<<serverIp;
            //serverIp = "192.168.137.1";
        }
        clientService.sin_addr.s_addr = inet_addr( serverIp );
        clientService.sin_port = htons( 27015 );
        if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
            printf( "\nFailed to connect.\n" );
            cout<<"\nSorrry.... Right now, No Server is Listening at IPAddress you entered";
            cout<<"\n Terminating the Game in 10 Secs...Please allow the FIREWALL to use TCP/IP";
            delay(10000);
            WSACleanup();
            return 88;
        }
    }
//*/

    // Send and receive data.
    //int bytesSent;
    /*
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[50] = "This is client";
    char recvbuf[50] = "";
    int bytesSent = send( m_socket, sendbuf, strlen(sendbuf), 0 );
    printf( "Bytes Sent: %ld\n", bytesSent );
    while( bytesRecv == SOCKET_ERROR )
    {
    bytesRecv = recv( m_socket, recvbuf, 32, 0 );
    if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET )
    {
        printf( "Connection Closed.\n");
        break;
    }
    if (bytesRecv < 0)
        return 77;
    printf( "Bytes Recv: %ld\n", bytesRecv );

    ////cout<<"\n The message received is:"<<recvbuf;
    */




    int gdriver=DETECT,gmode;
    char driver[]="C:\\TC\\BGI";
    initgraph(&gdriver,&gmode,driver);
    initwindow(1350,710,"Client Game [Opponent Game]");

    //Finding the screen center and endPoint
    int maxX= getmaxx();
    int maxY= getmaxy();
    Position endOfScreen(maxX,maxY);
    Position midScreen(maxX/2,maxY/2);
    Position origin(0,0);

    //creating the fustal field

    Position fieldStart = origin.shift(10,60);
    Position fieldEnd =endOfScreen.shift(-10,-60);
    Position fieldCenter = fieldStart.midPointFrom(fieldEnd);

    RRectangle background(fieldStart,fieldEnd, GREEN);
    //  background.shiftVertical(120);
    RRectangle outline(fieldStart,fieldEnd,WHITE,LINE_THICKNESS);
    \
    Position pm1(fieldCenter.x-3,fieldStart.y);
    Position pm2(fieldCenter.x+2,fieldEnd.y);
    RRectangle midline(pm1,pm2,WHITE);

    CCircle(fieldCenter,25,WHITE,LINE_THICKNESS);

    Position pem1(fieldStart.x,fieldCenter.y);
    Position pem2(fieldEnd.x, fieldCenter.y);
    EEllipse(pem1, -88, 88, 130,180,WHITE,LINE_THICKNESS);
    EEllipse(pem2, 90, -90, 130,180,WHITE,LINE_THICKNESS);
    //Field creation completes here




    serverTeam[0].setData(Position(400,175),"Bale",1,0);//
    serverTeam[1].setData(Position(578,393),"Marcelo",1,1);//2
    serverTeam[2].setData(Position(100,393),"Ramos",1,2);//3
    serverTeam[3].setData(Position(400,580),"Kroos",1,3);//4
    serverTeam[4].setData(Position(306,393),"Kane",1,4);//5

    int xs =300;
    clientTeam[0].setData(Position(800+xs,175),"Di Maria",2,0);
    clientTeam[1].setData(Position(978+xs,393),"Hazard",2,1);
    clientTeam[2].setData(Position(500+xs,393),"Muller",2,2);
    clientTeam[3].setData(Position(800+xs,580),"Reus",2,3);
    clientTeam[4].setData(Position(706+xs,393),"Pogba",2,4);

    int k =0;
    for(; k<5; k++) {
        tempServerTeam[k] = serverTeam[k];
        //////cout<<"\n tempServer["<<k<<"] = ";
        //tempServerTeam[k].getCurrPos().showCoor();

    }



    Player prevPlayer[5];
    Ball lastBall;

    int as =0;
    for(; as<5; as++) {
        serverTeam[as].setPossessStat(false);

    }

    Player& Bale = serverTeam[0];
    Bale.setPossessStat(true);



    //show the first ball
    Position ran(654,634);
    int fmx = mousex();
    int fmy = mousey();
    mainBall.drawBall(Position(fmx,fmy),Bale.getCurrPos(),Bale,false);


    k = 0;
    for(; k<5; k++) {
        serverTeam[k].createPlayer();
        clientTeam[k].createPlayer();
        changedList[k] = -1;
        prevPlayer[k] = clientTeam[k];
        //serverTeam[k].setPlayerNo(k);
    }





    settextstyle(6,HORIZ_DIR,2);
    Position timeBoardCenter(fieldEnd.x-200,fieldStart.y-25);

    DisplayBoard timeBoard(timeBoardCenter, 300,0,WHITE,5);
    // timeBoard.showBoard();
    timeBoard.setTitle("time remaining:",COLOR(500,123,645));

    Position distanceBoardCenter(fieldStart.x+150,fieldStart.y-25);
    DisplayBoard disBoard(distanceBoardCenter, 300, 0,RED,3);
    disBoard.setTitle("distance left:",COLOR(500,123,645));

    Position scoreBoardCenter((fieldEnd.x)/2-fieldStart.x/2,fieldStart.y-30);
    DisplayBoard scoreBoard(scoreBoardCenter,300,50,COLOR(3453,321,75),2);
    scoreBoard.showBoard();
    settextstyle(6,HORIZ_DIR,3);
    scoreBoard.setTitle("Score:",COLOR(234,614,737));


    Position commentBoardCenter(midScreen.x,fieldEnd.y+30);
    commentBoard.setBoardInfo(commentBoardCenter, 1000,50,COLOR(64,64,64),3);
    commentBoard.showBoard();
    commentBoard.setTitle("Commentary:",COLOR(192,192,192));
    commentBoard.display("your Opponent won the toss to start the Ball");


    //Mouse Events
    int totalTime=0;
    while(totalTime<100) {
        //cout<<"\n On Phase:"<<totalTime;
        bool isMouseClicked = false,isMouseReleased =true,isRBClicked;
        int x, y;

        int i =0;





        int kj = 0;
        //Player& selectedPlayer;
        time_t  startTime,currTime;
        time(&startTime);
        bool isTimeUp = false;

        //Ball ball;
        int timeGiven =12;
        float disRem;
        float disGiven =disRem = 999;
        timeBoard.display(totalTime);
        disBoard.display(disRem);

        Position prevPos;
        int tempDisRem=0;


        disBoard.display(disRem);
        int lp =0;

        mainBall.isBallWon = false;
        mainBall.isBallMoved = false;



        while (!isTimeUp) {
            kj++;
            // ////cout<<"\n Listening click for"<<kj<<"time\n";
            time(&currTime);
            int timeRem = timeGiven-(-startTime+currTime);
            //timeBoard.display(timeRem);

            // ////cout<<"\nTimeReamining:"<<timeRem<<endl;

            if(timeRem<1)
                isTimeUp=true;


            time_t lastClick;
            isMouseClicked=ismouseclick(WM_LBUTTONDOWN);
            isRBClicked = ismouseclick(WM_RBUTTONDOWN);
            //isMouseReleased = ismouseclick(WM_LBUTTONUP);


            //////cout<<"\nListening Ended";
            //int playerNo;
            if(isMouseClicked|| isRBClicked) {
                if(isMouseClicked) {
//                ////cout<<"\n Left Button clicked";
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    // delay(4000);
                } else if(isRBClicked) {
//                ////cout<<"\n Right button is clicked";
                    getmouseclick(WM_RBUTTONDOWN, x, y);
                }
                Position clickPos(x,y);
                int j =0;



                for(; j<5; j++) {

                    Position p = clientTeam[j].getCurrPos();
                    int dis = p.getDistanceFrom(clickPos);


                    //cout<<"\n\n Before checking the player at cliked position";
                    i =0;
                    //cout<<"\n ";
                    for(; i<5; i++) {
                        // //cout<<"\n serverTeam["<<i<<"]."<<serverTeam[i].getName()<<"("<<serverTeam[i].getId()<<") possession = "<<serverTeam[i].getPossessStat();

                        //    //cout<<"\n clientTeam["<<i<<"]."<<clientTeam[i].getName()<<"("<<clientTeam[i].getId()<<") possession = "<<clientTeam[i].getPossessStat();
                    }
                    i=0;

                    if(dis<=PLAYER_SIZE) {

                        time(&lastClick);
                        Player temp = clientTeam[j];
                        int ndex = temp.getNo();

                        Player & selectedPlayer = clientTeam[ndex];
                        string reqName = selectedPlayer.getName();
                        //cout<<"\n The selected Player is::"<<reqName<<"("<<selectedPlayer.getId()<<")"<<" possessStat = "<<selectedPlayer.getPossessStat() ;
                        i=3;
                        //cout<<"\n clientTeam["<<i<<"]."<<clientTeam[i].getName()<<"("<<clientTeam[i].getId()<<") possession = "<<clientTeam[i].getPossessStat();
                        i=0;

                        int playerNo=j;

                        Position prevPos = clientTeam[j].getCurrPos();

                        int lk =0;
                        char sendBuf[15];
                        for(; lk<10; lk++)
                            sendBuf[lk] = reqName[lk];

                        while(1) {
                            int timeRem = timeGiven-(-startTime+currTime);
                            if(timeRem<1) {
                                isTimeUp=true;
                                timeBoard.display(0);
                                break;
                            }
                            isMouseReleased = ismouseclick(WM_LBUTTONUP);
                            time(&currTime);




                            //control the ball
                            if(isRBClicked) {
                                clearmouseclick(WM_RBUTTONDOWN);

                                //selectedPlayer.
                                if(selectedPlayer.getPossessStat()) {

                                    commentBoard.display("Hey!! that player doesn't have the Ball");

                                } else {

                                      commentBoard.display("Lets see to whom will you PASS the Ball");
                                    //cout<<"\n "<<selectedPlayer.getName()<<" is not in possession";
                                    break;
                                }
                                while(1) {

                                    time(&currTime);
                                    timeRem = timeGiven-(-startTime+currTime);



                                    if(timeRem<1) {
                                        isTimeUp =true;
                                        timeBoard.display(0);
                                        break;
                                    }


                                    int msx = mousex();
                                    int msy = mousey();

                                    Position mousePos(msx,msy);
                                    Position pPos = selectedPlayer.getCurrPos();
                                    tempDisRem = disRem-prevPos.getDistanceFrom(mousePos);
                                    //disBoard.display(tempDisRem);
                                    mainBall.drawBall(mousePos,pPos,selectedPlayer,false);
                                    isMouseClicked=ismouseclick(WM_LBUTTONDOWN);

                                    //move the ball
                                    if(isMouseClicked) {



                                        disRem = tempDisRem;
                                        //disBoard.display(disRem);
                                        getmouseclick(WM_LBUTTONDOWN, x, y);
                                        Position passPosition(x,y);
                                        try {
                                            Player& passedPlayer  = playerAt(clientTeam,passPosition);

                                            ////cout<<"\n";
//                                        //cout<<"\n passedPlayer ="<<passedPlayer.getName()<<"("<<passedPlayer.getId()<<")";
//                                        //cout<<"\n Terminate the execution";
                                            //delay(5000);
//


                                            //Pass the ball to the player
                                            if(passedPlayer.getName()!="notSet") {
                                                //cout<<"\n \t Ball is Passed to player";
                                                ////cout<<"\n passedPlayer ="<<passedPlayer.getName()<<"("<<passedPlayer.getId()<<")";

                                                      commentBoard.display(" Great!!! Nice pass");
                                                prevBallPos=mainBall.getCurrPos();
                                                prevBall = mainBall;

                                                setAllFalse(clientTeam);
                                                setAllFalse(serverTeam);
                                                //selectedPlayer.setPossessStat(false);
                                                int index =passedPlayer.getNo();
                                                clientTeam[index].setPossessStat(true);

                                                mainBall.isBallMoved = true;
                                                mainBall.isClientBallMoved=true;
                                                mainBall.isClientMissPassed= false;
                                                mainBall.drawBall(pPos,passedPlayer.getCurrPos(),passedPlayer,false);

                                            }

                                        } catch(Position p) {

                                             commentBoard.display("Poorly passed ball,you have MissPassed the ball");
                                            //////cout<<"\n The iD THE  clinet team is";

                                            k=0;
                                            for(; k<5; k++) {
                                                //    //cout<<"\n"<<clientTeam[k].getName()<<"("<<clientTeam[k].getId()<<")"<<clientTeam[k].getPossessStat();
                                            }
                                            ////cout<<"\n RunTime error is caught";
                                            //cout<<"\n You have MISSPASSED and the nearest client team players will recive the ball";
                                            Player & nearestOne = nearestFrom(serverTeam,p);
                                            nearestOne.setPossessStat(true);
                                            int ind = nearestOne.getId();

                                            serverTeam[ind].setPossessStat(true);
                                            ////cout<<"Possession Stat of the clientTeam("<<ind<<")"<<serverTeam[ind].getPossessStat();
                                            prevBall = mainBall;
                                            mainBall.isBallMoved = true;
                                            mainBall.isClientBallMoved = true;
                                            mainBall.isBallWon = false;
                                            mainBall.isClientMissPassed = true;
                                            mainBall.isServerMissPassed  = false;
                                            //mainBall.setPosition()
                                            mainBall.drawBall(p,nearestOne.getCurrPos(),nearestOne);
                                            cout<<"\n CLinet has mispassed";
                                        }

                                        clearmouseclick(WM_LBUTTONDOWN);
                                        clearmouseclick(WM_RBUTTONDOWN);
                                        break;
                                    }
                                }

                                break;
                            }

                            else if(isMouseReleased) {

                                commentBoard.display("Wow !! Wonderful Run");
                                clearmouseclick(WM_LBUTTONDOWN);
                                clearmouseclick(WM_LBUTTONUP);
                                isMouseReleased = false;
                                tempDisRem = disRem-selectedPlayer.getCurrPos().getDistanceFrom(prevPos);
                                disRem = tempDisRem;
                                //disBoard.display(disRem);
                                changedList[playerNo] = playerNo;

                                CREATE_FIELD_LINES
                                CREATE_ALL_PLAYERS
                                break;

                            } else {

                                 commentBoard.display("This run seems like a lethal strategy");
                                int msx = mousex();
                                int msy = mousey();

                                int pad = 50;
                                if(msx>fieldEnd.x-pad) msx=fieldEnd.x-pad;
                                if(msx<fieldStart.x+pad) msx=fieldStart.x+pad;

                                if(msy<fieldStart.y+pad) msy=fieldStart.y+pad;
                                if(msy>fieldEnd.y-pad) msy=fieldEnd.y-pad;

                                Position currMousePos(msx, msy);
                                selectedPlayer.setCurrPos(currMousePos);

                                selectedPlayer.shift(currMousePos);
                                tempDisRem = disRem-selectedPlayer.getCurrPos().getDistanceFrom(prevPos);
                                //disBoard.display(tempDisRem);
                            }

                            isRBClicked = ismouseclick(WM_RBUTTONDOWN);
                        }
                        break;
                    }
                    if(j==4) {
                        clearmouseclick(WM_LBUTTONUP);
                        clearmouseclick(WM_LBUTTONDOWN);
                        //cout<<"\nBlank Space";
                    }
                    clearmouseclick(WM_LBUTTONUP);
                    clearmouseclick(WM_LBUTTONDOWN);

                }

                clearmouseclick(WM_LBUTTONUP);
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }


        Transmission trans;
        if(true) {

            //cout<<"\nTrying to recieve the message and trying to decode the message";
            if(trans.receiveOppChanges())
                trans.decode();
            //cout<<"\nDecoding finished";

        } else {
            cout<<"\n Decoding skipped this time";
        }

        i =0;
        for(; i<5; i++) {
            //          //cout<<"\n serverTeam["<<i<<"]."<<serverTeam[i].getName()<<"("<<serverTeam[i].getId()<<") possession = "<<serverTeam[i].getPossessStat();
//
            //        //cout<<"\n clientTeam["<<i<<"]."<<clientTeam[i].getName()<<"("<<clientTeam[i].getId()<<") possession = "<<clientTeam[i].getPossessStat();
        }
        i=0;


        // //cout<<"\n The selected Player is::"<<reqName<<"("<<selectedPlayer.getId()<<")"<<" possessStat = "<<selectedPlayer.getPossessStat() ;
        if(true) {
            ////cout<<"\nSetting the Changes";
            trans.setMyChanges(changedList);
            ////cout<<"\n Sending the Info";
            trans.sendInfo();

            ////cout<<"\n sendInfo() call completed";
        }


        lp=0;
        for(; lp<5; lp++)
            serverTeam[lp].erasePlayer();



        lp =0;

        CREATE_FIELD_LINES
        CREATE_ALL_PLAYERS

        if((!mainBall.isBallWon) || !mainBall.isServerMissPassed) {

            commentBoard.display("your opponent is Playing well");
            mainBall.drawBallAtCurrPos();
//            cout<<"\n Server has the ball and hasn't misspassed the ball";
            //  cout<<"\n \n Setting the mainBall.isMissPassed = false";
            mainBall.isServerMissPassed = false;
        } else {
           commentBoard.display("You are a KILLER ATTACKER");
        }



        k=0;
        for(; k<5; k++) {
            serverTeam[k]=tempServerTeam[k];
            changedList[k] =-1;
        }
        k=0;




        totalTime ++;
    }


    //cout<<"\n ENtire game is terminated";
    getch();
    closegraph();



    return 0;

}


