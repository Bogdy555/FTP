# FTP

![Example](./ReadMe%20Resources/Example.png)

FTP is a server that enables file sharing. It has support for Windows (7 - 11) and Linux (Ubuntu).

# Requirements

For Windows builds use MSVC. It is recomanded to use the Visual Studio files as a build system.

For Linux builds use GNU GCC. It is recomanded to use the bash scripts for compilation.

# How to use

If you want to host the server you will have to run the following command:

``` bash
FTP_Server ip port working_directory password
```

Once you are done hosting you should type exit in the command prompt/terminal and hit enter.

When you want to connect to the server you will use the following command:

``` bash
FTP_Client ip port action
```

The *action* could be 1 of the following:

* list_files password
* download password file_name
* upload password file_name
* remove password file_name

# Features

* Simple and quick
* Reliable
* Light weight
* Cross platform
