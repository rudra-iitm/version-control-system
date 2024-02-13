
# Version Control System

## Overview
Version control systems are software utilities designed to aid software teams in overseeing alterations to source code across time. These systems efficiently manage your code, enabling you to trace the project's history. My project is a simplified imitation of the widely used version control system 'Git'.

## Features
- Efficiently manage your code by creating distinct versions of the project.
- Work on various modules of the project independently, without relying on others' contributions.
- Monitor the project's history.
- Simplify bug detection in case applications malfunction due to issues.


## Run Locally

Clone the project

```bash
    git clone https://github.com/Rudra-IITM/version-control-system
```

Go to the project directory

```bash
    cd version-control-system
```
### Compile main.cpp

```bash
    g++ src/main.cpp -o vcs -std=c++17
```
- This will create a executable of main.cpp named 'vcs'.

- Copy this executable where you want to use version-control-system

## Supported Commands
Initializes a new version control repository.
```bash
    ./vcs init
```

Adds all files in the current directory to the staging area.
```bash
    ./vcs add .
```

Adds a specific file to the staging area.
```bash
    ./vcs add <filename>
```

Commits the staged changes with a specified commit message.
```bash
    ./vcs commit -m 'commit msg'
```

Reverts the project to the state of a specific commit.
```bash
    ./vcs revert <commit_id>
```

Reverts the project to the state of the latest commit.
```bash
    ./vcs revert HEAD
```

Displays the commit history of the project.
```bash
    ./vcs log
```

## Behind the scenes of VCS

<div align="center">
<img src="https://github.com/Rudra-IITM/version-control-system/blob/main/public/assets/vcs_arch.png" align="center" width='500px' />
</div> 

- All functions operate based on the command line arguments.
- This works by using ```argc``` & ```*argv[]``` in main function.
- ```argc``` & ```*argv[]``` are how command line arguments are passed to main() in C and C++
- With each commit, a new directory is created
- and hence every time an instance of the program runs it iterates through linked list
nodes created using directory paths.


