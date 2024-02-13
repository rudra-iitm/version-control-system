#if !defined (VCS_CLASS_H)
#define VCS_CLASS_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include "commit_node_list.h"
using namespace std;

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define END "\033[0m"

class vcsClass {
    public:
        commitNodeList list;
        void vcsInit();
        void vcsAdd();
        void vcsAdd(string files[], int arrSize);
        void vcsCommit(string msg);
        void vcsRevert(string commitHash);
        void vcsLog();
};

void vcsClass::vcsInit() {
    filesystem::create_directory(".vcs");
    filesystem::create_directory(".vcs/staging_area");
    filesystem::create_directory(".vcs/commits");
}

void vcsClass::vcsAdd() {
    const auto copyOptions = filesystem::copy_options::update_existing | filesystem::copy_options::recursive;

    for (const auto &dirEntry : filesystem::directory_iterator(filesystem::current_path())) {
        auto fileName = filesystem::path(dirEntry).filename();
        if (fileName != "vcs" && fileName != ".vcs") {
            if (filesystem::is_directory(fileName))
                filesystem::copy(dirEntry, filesystem::current_path() / ".vcs" / "staging_area" / fileName, copyOptions);
            else
                filesystem::copy(dirEntry, filesystem::current_path() / ".vcs" / "staging_area" / "", copyOptions);
        }
    }
}

void vcsClass::vcsAdd(string files[], int arrSize) {
    const auto copyOptions = filesystem::copy_options::update_existing | filesystem::copy_options::recursive;

    for (int i = 0; i < arrSize; i++) {
        if (filesystem::exists(files[i])) {
            int last_index = files[i].find_last_of('/');
            if (last_index != string::npos) {
                auto newDir = filesystem::current_path() / ".vcs" / "staging_area" / files[i].substr(0, last_index);
                filesystem::create_directories(newDir);
                filesystem::copy(filesystem::current_path() / files[i], filesystem::current_path() / ".vcs" / "staging_area" / files[i], copyOptions);
            } else {
                if (filesystem::is_directory(files[i]))
                    filesystem::copy(filesystem::current_path() / files[i], filesystem::current_path() / ".vcs" / "staging_area" / files[i], copyOptions);
                else
                    filesystem::copy(filesystem::current_path() / files[i], filesystem::current_path() / ".vcs" / "staging_area", copyOptions);
            }
        }
        else
            cout << files[i] << RED "does not exist!" END << endl;
    }
}

void vcsClass::vcsCommit(string msg) { list.addOnTail(msg); }

void vcsClass::vcsRevert(string commitHash) { list.revertCommit(commitHash); }

void vcsClass::vcsLog() { list.printCommitList(); }

#endif