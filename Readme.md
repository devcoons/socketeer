###### Version: 0.1
Socketeer - Linux Library for distr. applications
==================

  - [Synopsis](#synopsis)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [API](#api)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)


## Synopsis

This Project is a linux shared library for Linux. It provides a simple API for applications and services which desire to communicate via sockets.
You may also use the Example, which is a simple application acting as a server or client.

## Requirements

[ NONE ]

## Installation

Download the source code and copy both header and source files to your project's folder.
```
$ download as zip
$ extract the project
$ cd "Library/Source Code"/
$ sudo make
$ sudo make install
```

## API

```
std::string socketeer_server_getstr(Parameters* parameters)

bool socketeer_server(int port,void(*callback)(Parameters * parameters, void * object))
bool socketeer_client(std::string hostname,int port,std::string message)

bool socketeer_server_is_active(int port)
```

## Usage

Make sure you have included the header file.
```
#include <socketeer.h>
```

Add the proper flag to your compiler
```
-lsocketeer
```

To set In-bound communication: Create Callback function like the following and initialize the socket server
```
    void callback(Parameters* parameters,void * obj)
    {
		std::string temp = socketeer_server_getstr(parameters);	
        std::cout<<temp;
    }
    ...
    ...
    if(socketeer_server(8000,callback) == false)
    {
    	exit(1);
    }
```

To send a message to another application
```
if(socketeer_client("127.0.0.1",8000,"my message here")==false)
{
    exit(1);
}
```

## Contributing
One of the easiest ways to contribute is to participate in discussions and discuss issues. You can also contribute by submitting pull requests with code changes. Please log a new issue in the appropriate section [Issues] or by e-mail.
The best way to get your bug fixed is to be as detailed as you can be about the problem.  Providing a minimal project with steps to reproduce the problem is ideal. 

Here are questions you can answer before you file a bug to make sure you're not missing any important information.

1. Did you read the documentation?
2. Did you include the command you executed in the issue?
3. What are the EXACT steps to reproduce this problem?
4. What package versions are you using?

## License

The MIT License (MIT)

Copyright (c) 2019 Io. D

www.devcoons.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
