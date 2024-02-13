
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

## Behind the scenes of VCS
```
./vcs add <filename>
```

<div align="center">
<img src="https://github.com/Rudra-IITM/version-control-system/blob/main/public/assets/vcs_add.png" align="center" style="width: 50%, height: 50%" />
</div> 

