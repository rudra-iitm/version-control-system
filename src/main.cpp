#include <iostream>

#include "header_files/vcs_class.h"
using namespace std;

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define END  "\033[0m"

int main(int argc, char *argv[]) {
    vcsClass vcsClassObj;
    if(argc >= 2) {
        string argument = string(argv[1]);
        //vcs init
        if (argument == "init") {
            vcsClassObj.vcsInit();
            cout <<GRN "vcs repository initialized successfully!" END<< endl;
        }
        //vcs add
        else if (argument == "add") {
            if(argc == 2) {     
                cout << RED "missing arguments!" <<endl;
                cout << "Provide a third argument e.g." << endl;
                cout << "vcs add <'.' | 'file_name'>" END << endl;
            }
            if(argc >= 3) {
                if(argc == 3) {
                    string argumentC = string(argv[2]);
                    if (argumentC == ".")
                        vcsClassObj.vcsAdd();
                    else {
                        string files[1] = {string(argv[2])};
                        vcsClassObj.vcsAdd(files, 1);
                    }
                } else {
                    string files[argc-2];
                    for (int i = 0; i < argc-2; i++)
                        files[i] = string(argv[i]); 
                    vcsClassObj.vcsAdd(files, argc-2);
                }
            }
        }
        //vcs commit
        else if (argument == "commit")
        {
            if(argc == 4) {   //[ vcs, commit, -m, "msg" ]
                string argumentC = string(argv[2]);    
                string argumentD = string(argv[3]);      
                if(argumentC == "-m") {
                    vcsClassObj.vcsCommit(argumentD);
                    cout << "files commited successfully" << endl;
                }
            } else {
                cout << RED "missing arguments!" <<endl;
                cout << "Provide with a message field e.g." << endl;
                cout << "vcs commit -m 'my commit message'" END << endl;
            }
        }
        // vcs revert
        else if(argument == "revert") {
            if(argc == 3) {
                string argumentC = string(argv[2]);
                if(argumentC == "HEAD") {
                    vcsClassObj.vcsRevert(argumentC);
                    cout << "The project is now at HEAD" << endl;
                } else {
                    vcsClassObj.vcsRevert(argumentC);
                    cout << "Reverted to <commit_id> commit" << endl;
                }
            } else {
                cout << RED "invalid arguments, should be like: " << endl;
                cout << "vcs revert <'HEAD'|'commit_hash'>" END<< endl;
            }
        }
        // //vcs log
        else if(argument == "log") {
            vcsClassObj.vcsLog();
        }
        //vcs status
        // else if(argument == "status")
        // {
        //     vcsClassObj.vcsStatus();
        // }
        //wrong arguments
        else {
            cout << RED "Invalid arguments" END << endl;
        }
    } else {
        cout << YEL "vcs is version control system made by rudra, this project is a clone of that original system with minimal features \n\n";
        cout << "Usage: " << endl;
        cout << "vcs init                           ->   initialize an empty vcs repository in the current dir" << endl;
        cout << "vcs add <'.'|'file_name'>          ->   add the files to staging area" << endl;
        cout << "vcs commit <m 'commit message'>    ->   commit your staging files" << endl;
        cout << "vcs revert <'HEAD'|'commit_hash'>  ->   rollback to a specific commit" END << endl;
    }
}
