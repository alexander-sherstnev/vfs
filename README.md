# Virtual File System

Virtual File System - academic application which implemented for BSUIR university.

### Requirements
- Boost library
- wxWidgets

### Installation & Build

MacOS:
``` 
brew install boost
brew install wxwidgets

generate project via cmake
build
```

### Run

OS mode:
```
./VFSManager -vfs os -root <path to root folder> [-plugin] [libwxVFSPlugin]
```

Block mode:
```
./VFSManager -vfs block -db <path to db file SQLite3> [-plugin] [libwxVFSPlugin]
```
