class Transmission {
    Player changesAttempted[5];
    int myPresentChangedIndex[5];
    // Player OtherTeam[5];
    string serverRawInfo;

    Ball ball;


public:

    Transmission() {
        int i =0;
        for(; i<5; i++)
            myPresentChangedIndex[i] = -1;
    }



    void setMyChanges( int changedInd[]) {
        int i =0;
        // //cout<<"\n\nChanges:: of ";
        for(; i<5; i++) {

            int pos =changedInd[i];
            if(pos>-1) {


                myPresentChangedIndex[pos] = pos;

                ////cout<<"\n"<<clientTeam[pos].getName()<<"["<<pos<<"] has been set to \n";
                //clientTeam[pos].getCurrPos().showCoor();

            }

        }

        /*
        //cout<<"\n The Changes set are";
        i=0;
        for(; i<5; i++) {
            int pos = myPresentChangedIndex[i];
            //cout<<"\n myPresentChangedIndex["<<i<<"]="<<pos;

            if(false) {

                //cout<<"\n"<<clientTeam[pos].getName()<<"["<<pos<<"] has been set to \n";
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
        //cout<<"\nTrying to recieve the Server Info...";
        char recvBuf[100] = "";
        bytesRecv = recv( m_socket, recvBuf, 100, 0 );
        if(bytesRecv>=5) {
            //cout<<"\n Received Server Info successfully...";
            serverRawInfo = recvBuf;
            //cout<<"\n serverRawCode is::"<<serverRawInfo;
            return 1;

        } else {
            //cout<<"\n No data was recieved";
            return 0;
        }


        ////cout<<"\n Received Info is:\n\t"<<recvBuf;

        serverRawInfo = recvBuf;


    }

    void decode() {
        //string toDecode = serverRawInfo;
        string toDecode = "1-456,311/2-245,222/4-127,442/B9-345,123/";
        //cout<<"\n String to decode is"<<toDecode;
        string indivInfoColl[6];
        char indivInfo[15]="";
        //string indv;


        char ch = '2';
        int i =0,j=0;
        int pNo =0;
        //cout<<"\n";
        while(1) {

            ch=toDecode[i+j];
            if(ch=='\0') {
                //cout<<"\n EOF found";
//                indv = indivInfo;
                //pNo--;
                break;
            } else {
                if(ch=='/') {
                    //cout<<"\n indivInfo::"<<indivInfo;
                    indivInfoColl[pNo] = indivInfo;
                    int lp =0;
                    for(; lp<15; lp++) {
                        indivInfo[lp] ='\0';
                    }
//                    indivInfo.clear();

                    //           //cout<<endl<<"indivInfo["<<pNo<<"] ="<<indivInfoColl[pNo];
                    i = i+j+1;
                    j=0;
                    pNo++;
                } else {
                    ////cout<<"\nch="<<ch;
                    indivInfo[j]=ch;
                    j++;

                }
            }
        }




        //cout<<"\n Loop exited with total numbers of players info is:"<<pNo;

        //initalize the tempclientPlayers to lastcclinetChanges
        int k =0;
        //  for(; k<5; k++) {
        //    tempServerTeam[k] = serverTeam[k];
        //}

        Bracket is missing here
        //create objects of iti = pNo;

        i =0;
        //cout<<"\n\nUpdating the serverTeam";
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
//            //cout<<"\nFlag 1";
            ch = indivInfoColl[i][0];
            ////cout<<"\nCharacter index value is:"<<ch;
//            //cout<<"\nFlag 2";

            ;
            // //cout<<"\n String is storing::"<<st.c_str();
            // st.empty();
            if(ch=='B') {
                mainBall.isBallWon= false;
                mainBall.isBallPassed = true;
                cInd[0] =indivInfoColl[i][1];
                isBall = true;
            } else
                cInd[0] = ch;

            ////cout<<"\nst[0]="<<st[0];


            ind= atoi(cInd);
            if(isBall) {
                ////cout<<"\n The index of the Player with Ball is:"<<ind;
                //cout<<"\n inLegOf serverTeam["<<ind<<"] = "<< serverTeam[ind].getName();
            } else {}
            // //cout<<"\n The index of the Player is:"<<ind;

//            st.clear();
            //          st = "";

            //            ch = indivInfoColl[i-1][2];
            if(!isBall)
                j =2;
            else
                j =3;


            int k = 0;
            while(1) {
                ////cout<<"\nFinding x";
                ch = indivInfoColl[i][j];
                if(ch==',') break;
                else {
                    cY[k] = ch;
                }

                j++;
                k++;
            }

            x = atoi(cY);
            if(isBall)
                cout<<"\n X pos of Ball is is:"<<x;
            else {

            }
            ////cout<<"\n X pos of current Player is:"<<x;


            //for y
            j++;

            k=j;

            while(1) {

                ch = indivInfoColl[i][j];
                ////cout<<"\nvalue of chY:"<<ch;
                if(ch=='\0') break;
                else {
                    cX[j-k] = ch;
                }

                j++;

            }
            ////cout<<"\nValue of CY is:"<<cX;
            y = atoi(cX);

            if(isBall)
                cout<<"\n y pos of Ball is:"<<y;
            else {}
            ////cout<<"\n y pos of current Player is:"<<y;

            Position currPos(x,y);

            if(ind==9) {

                cout<<"\n Server has misspassed the ball";
                Player& nearestOne = nearestFromPlayer(clientTeam,currPos);
                mainBall.setCurrPos(currPos);
                mainBall.setInLegOf(nearestOne);

            } else if(isBall) {
                //cout<<"\n Setting the Ball Info";
                mainBall.setCurrPos(currPos);
                Player inBallPlayer =serverTeam[ind];
                mainBall.setInLegOf(inBallPlayer);
            } else {
                tempServerTeam[ind].setCurrPos(currPos);
                //cout<<"\n updating the position of "<<tempServerTeam[ind].getName()<<" to\n\t";
                tempServerTeam[ind].getCurrPos().showCoor();

                tempServerTeam[ind].createPlayer();
            }

            if(isBall)
                cout<<"\nBall Is created\n\n";
            else {}
            ////cout<<"\nObject Is created\n\n";



            //



            ////cout<<"\nThe first index is:"<<myNum;

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

    ////cout<<"";
    //cout<<"\n creating the Send Buf from client changes";
    for(; jl<5; jl++) {

        indexToSend = myPresentChangedIndex[jl];
        if(indexToSend>-1) {
            ////cout<<"\nvalue of Changed Player  index is:"<<myPresentChangedIndex[jl];
            //add to string stream
            tempStream<<jl<<'-'<<clientTeam[indexToSend].getCurrPos().x<<','<<clientTeam[indexToSend].getCurrPos().y<<'/';
            ////cout<<"\nclientTeam["<<jl<<"].x="<<clientTeam[indexToSend].getCurrPos().x;

        }
    }

    //cout<<"\n SendBuf Created";


    string temp_str = tempStream.str();
    sendBuf = (char*)  temp_str.c_str();

    cout<<"\n Info to send to server is:\n\t"<<sendBuf;
    ////cout<<"\nSending index of "<<serverTeam[toSend].getName()<<" is "<<sendBuf;
    int bytesSent;
    bytesSent = send(m_socket,sendBuf,strlen(sendBuf),0);

    if(bytesSent>=5)
        cout<<"\nInfo Sent successfully...";
    else
        cout<<"\n No data was sent to the sever";
}

};
