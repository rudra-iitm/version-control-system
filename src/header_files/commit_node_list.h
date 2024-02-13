#if !defined(COMMIT_NODE_LIST_H)
#define COMMIT_NODE_LIST_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <ctime>
#include <vector>

using namespace std;

string gen_random(const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

string get_time()
{
    time_t t = std::time(0); // get time now
    tm *now = std::localtime(&t);
    string dateTime = to_string(now->tm_year + 1900) + "/" +
                      to_string(now->tm_mon + 1) + "/" +
                      to_string(now->tm_mday) + " " +
                      to_string(now->tm_hour) + ":" +
                      to_string(now->tm_min) + "\n";

    return dateTime;
}
class commitNode
{
private:
    string commitID;
    string commitMsg;
    string next_commitID;
    commitNode *next;

    void createCommitNode()
    {
        // create a dir for new commit to store info about the commit
        filesystem::create_directory(filesystem::current_path() / ".vcs" / "commits" / commitID);

        // construct a path to file commitInfo.txt
        auto path = filesystem::current_path() / ".vcs" / "commits" / commitID / "commitInfo.txt";

        // write info about commit in commitInfo.txt
        ofstream write(path.string());
        write << "1." + commitID + "\n" +
                     "2." + commitMsg + "\n" +
                     "3." + get_time() + "\n";

        // construct a path for staging area
        auto STAGING_AREA_PATH = filesystem::path(filesystem::current_path() / ".vcs" / "staging_area");

        // defines options for copying files
        const auto copyOptions = filesystem::copy_options::update_existing | filesystem::copy_options::recursive;

        // moving staged changes into the commit
        filesystem::copy(STAGING_AREA_PATH, filesystem::current_path() / ".vcs" / "commits" / commitID / "Data", copyOptions);
    }

public:
    commitNode() : next(nullptr){};

    commitNode(string commitID, string commitMsg) : commitID(commitID), commitMsg(commitMsg), next(nullptr)
    {
        createCommitNode();
    }

    commitNode(string commitID) : commitID(commitID), next(nullptr)
    {
        checkNextCommitID();
    }

    void revertCommitNode(string hash)
    {
        filesystem::create_directories(filesystem::current_path() / ".vcs" / "commits" / getCommitID() / "Data");
        auto nextCommitPath = filesystem::current_path() / ".vcs" / "commits" / getCommitID() / "commitInfo.txt";
        auto copyFrom = filesystem::current_path() / ".vcs" / "commits" / hash / "Data";
        ofstream write(nextCommitPath.string());
        write << "1." + commitID + "\n" +
                     "2." + commitMsg + "\n" +
                     "3." + get_time() + "\n";
        const auto copyOptions = filesystem::copy_options::recursive;
        filesystem::copy(copyFrom, filesystem::current_path() / ".vcs" / "commits" / getCommitID() / "Data", copyOptions);
    }

    void readNodeInfo()
    {
        string info;

        // construct a path to commitInfo.txt
        auto path = filesystem::current_path() / ".vcs" / "commits" / getCommitID() / "commitInfo.txt";

        // reads commitInfo.txt
        ifstream file(path.string());
        while (getline(file, info))
        {
            if (info[0] == '1')
                this->setCommitID(info.substr(2));
            if (info[0] == '2')
                this->setCommitMsg(info.substr(2));
        }
    }

    string getCommitMsg() { return this->commitMsg; }

    string getCommitID() { return this->commitID; }

    void setCommitMsg(string commitMsg) { this->commitMsg = commitMsg; }

    void setCommitID(string commitID) { this->commitID = commitID; }

    void setNext(commitNode *node) { this->next = node; }

    commitNode *getNext() { return this->next; }

    void setNextCommitID(string _commitID) { this->next_commitID = _commitID; }

    void writeNextCommitID(string _commitID)
    {
        setNextCommitID(_commitID);
        auto path = filesystem::current_path() / ".vcs" / "commits" / getCommitID() / "nextCommitInfo.txt";
        ofstream write(path.string());
        write << _commitID;
    }

    string checkNextCommitID()
    {
        filesystem::path tempPath(filesystem::current_path() / ".vcs" / "commits" / getCommitID() / "nextCommitInfo.txt");
        bool exists = filesystem::exists(tempPath);
        if (exists)
        {
            string info;
            ifstream file(tempPath);
            while (getline(file, info))
            {
                this->next_commitID = info;
                break;
            }
            file.close();
            return next_commitID;
        }
        return "";
    }

    string getNextCommitID() { return this->next_commitID; }
};

class commitNodeList
{
private:
    commitNode *HEAD;
    commitNode *TAIL;

    bool checkHead()
    {
        auto tempDir = filesystem::current_path() / ".vcs" / "commits" / "0x1111";
        return filesystem::exists(tempDir);
    }

public:
    commitNodeList()
    {
        setHead(nullptr);
        setTail(nullptr);

        if (checkHead())
            setHead(new commitNode("0x1111"));
    }

    commitNode *getHead() { return this->HEAD; }

    commitNode *getTail() { return this->TAIL; }

    void setHead(commitNode *HEAD) { this->HEAD = HEAD; }

    void setTail(commitNode *TAIL) { this->TAIL = TAIL; }

    void addOnTail(string msg)
    {
        if (!checkHead())
        {
            commitNode *newNode = new commitNode("0x1111", msg);
            setHead(newNode);
        }
        else
        {
            string commitID = gen_random(8);
            commitNode *currNode = getHead();

            while (currNode)
            {
                string nextCommitId = currNode->checkNextCommitID();

                if (nextCommitId.length() < 8)
                {
                    commitNode *newNode = new commitNode(commitID, msg);
                    currNode->writeNextCommitID(commitID);
                    currNode = NULL;
                }
                else
                {
                    commitNode *newNode = new commitNode();
                    newNode->setCommitID(nextCommitId);
                    currNode = newNode;
                }
            }
        }
    }

    void revertCommit(string commitHash)
    {
        commitNode *commitNodeToRevert;

        if (!checkHead())
            cout << "Nothing to revert" << endl;
        else
        {
            bool error = true;
            string commitID = gen_random(8);
            commitNode *currNode = getHead();
            while (currNode)
            {
                string nextCommitId = currNode->checkNextCommitID();
                if (commitHash == currNode->getCommitID())
                {
                    commitNodeToRevert = currNode;
                    error = false;
                }

                if (nextCommitId.length() < 8)
                {
                    if (!error)
                    {
                        commitNodeToRevert->readNodeInfo();
                        commitNode *newNode = new commitNode();
                        newNode->setCommitID(commitID);
                        newNode->setCommitMsg(commitNodeToRevert->getCommitMsg());
                        newNode->revertCommitNode(commitNodeToRevert->getCommitID());

                        currNode->writeNextCommitID(commitID);
                    }
                    currNode = NULL;
                }
                else
                {
                    commitNode *newNode = new commitNode();
                    newNode->setCommitID(nextCommitId);
                    currNode = newNode;
                }

                if (error)
                    cout << "does not match any Commit Hash" << endl;
            }
        }
    }

    void printCommitList()
    {
        commitNode *currNode = getHead();
        while (currNode != NULL)
        {
            string nextCommitId = currNode->checkNextCommitID();
            filesystem::path commitPath(filesystem::current_path() / ".vcs" / "commits" / currNode->getCommitID() / "commitInfo.txt");
            string info;
            ifstream file(commitPath.string());
            while (getline(file, info))
            {
                if (info[0] == '1')
                    cout << "Commit ID:    " << info.substr(2) << endl;
                if (info[0] == '2')
                    cout << "Commit Msg:   " << info.substr(2) << endl;
                if (info[0] == '3')
                    cout << "Date & Time:  " << info.substr(2) << endl;
            }
            file.close();
            cout << "============================\n\n";

            if (nextCommitId.length() < 8)
                currNode = NULL;
            else
            {
                commitNode *newNode = new commitNode();
                newNode->setCommitID(nextCommitId);
                currNode = newNode;
            }
        }
    }
};
#endif