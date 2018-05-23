

#include <cstdlib>
#include <unistd.h>
#include "JoinCommand.h"

JoinCommand ::JoinCommand(vector<GameInfo>* games, pthread_mutex_t &mutex) : Command() {
    gamesList = games;
    this->mutex = mutex;
}

void JoinCommand::execute(vector<string> args) {
    //args[0] - the later (second) client socket, args[1] - room name

    //Get client info into 'int client'
    string str = args[0];
    int secondClient = atoi(str.c_str());
    int firstClient = 0;
    string nameOfGame = args[1];
    cout << "argument room name: " << nameOfGame << endl;

    //Search for the game
    vector<GameInfo>::iterator it;
    bool found = false;
    pthread_mutex_lock(&mutex);
    for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
        //Compare the input name to the names in the game list
        if ((*it).getName() == nameOfGame) {
            if (it->wasStarted()) {
                char running[this->msgLength] = "-1There is a running game with this name!";
                ssize_t n = write(secondClient, &running, sizeof(running));
                if (n == -1) {
                    throw "Error on writing to socket";
                }
                //We don't want to continue
                close(secondClient); // close the connection because maybe he won't continue
                pthread_mutex_unlock(&mutex);
                return;
            }
            cout << "iterator room name: " << (*it).getName() << endl;
            found = true;
            //1 for signing that it's OK
            char msg[this->msgLength] = "1Connecting to game...\n";
            ssize_t n = write(secondClient , msg, sizeof(msg));
            if (n == -1) {
                throw "Error on writing to socket";
            }
            it->setStarted();
            firstClient = it->getFirstClient();

//            gamesList->erase(it);
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    //if not found
    if (!found) {
        char msg[this->msgLength] = "-1There is no game with this name!\n";
        ssize_t n = write(secondClient , msg, sizeof(msg));
        if (n == -1) {
            throw "Error on writing to socket";
        }
        //We don't want to continue
        //At the end, the player get the list, and we close the socket
        close(secondClient);
        return;
    }

    //int firstClient = it->getFirstClient();
    cout << "client: " << firstClient << endl;
    //set the second client
    it->setSecondClient(secondClient);

    //Gives the priorities

    int turn =1;
    // give 1 to the first client
    ssize_t n = write(firstClient, &turn, sizeof(turn));
    if(n == -1) {
        cout << "Error writing to socket who's turn it is." << endl;
    }
    turn ++;
    n = write(secondClient, &turn, sizeof(turn));
    if(n == -1) {
        cout << "Error writing to socket who's turn it is." << endl;
    }
    //Handeling the game
    int i = 0;
    bool flag = true;
    while(flag){
        if (i % 2 == 0) {
            flag = doMove(firstClient, secondClient);

        } else {
            flag = doMove(secondClient, firstClient);

        }
        i++;
    }

    pthread_mutex_lock(&mutex);
    // Close communication with the client
    close(firstClient);
    close(secondClient);

    //Erase the game from the list
    gamesList->erase(it);
    pthread_mutex_unlock(&mutex);
}

bool JoinCommand::doMove(int fromSocket, int toSocket) {
    int move[2];
    ssize_t n = read(fromSocket, move, sizeof(move));
    if (n == -1) {
        cout << "Error reading " << endl;
        return false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return false;
    }
    cout << "Got move: " << move[0] + 1 << "," << move[1] + 1 << endl;
    if ((move[0] == -1) && (move[1] == -1)) {
        //
        n = write(toSocket, move, sizeof(move));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
        }

        if (n == 0) {
            cout << "Client disconnected" << endl;
        }
        //
        return false;
    }


    n = write(toSocket, &move, sizeof(move));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    cout << "Sent move: " << move[0] + 1 << "," << move[1] + 1 << endl;
}