# libstatsd
This library is still being written. 

libstatsd is a C library for sending stats data to a statsd server. statsd is a network 
daemon that runs on Node.js. It was written by the engineers at Etsy and can be 
cloned from git://github.com/etsy/statsd.git. 

## Installing
### Cloning from github
If you have cloned this project from github the first thing that needs to be done is to
run the command 

```
autoreconf --install
```
This will run the GNU autotools suite on the project and generate the configure file. After
this you can run 

```
./configure && make
sudo make install
```
This will install the library, headers, and a binary called statsd-cli.

### Downloading from jamesslocum.com
You can download official release version from jamesslocum.com. Once you download
the archive you can install it like any other Unix program.

```
tar -zxvf libstatsd-X.Y.Z.tar.gz
cd libstatsd-X.Y.Z
./configure
make
sudo make install
```

### Installing on windows
The ultimate goal is to make this library cross platform. Currently I have no automated
way to build or install a windows version of the library. I will post info on compiling
and installing on windows when I have a solid method of doing so. 

## Library Usage
### including and linking
Once the library has been installed, you can use it by including the statsd.h header
file and linking against libstatsd.
```c
#include <stdio.h>
#include <statsd.h>

int main(int argc, char* argv[]){
   //program that uses statsd...
   return 0;
}
```

```bash
gcc --std=c99 prog.c -o prog -lstatsd
```
### Initializing the client object
Before any stats can be sent to the server, you must first build a client
object. The Statsd data type has been created for this purpose. There are two ways to 
initialize the object.

```c
int statsd_new(Statsd **stats, const char* serverAddress, int port, const char* nameSpace, const char* bucket);
int statsd_init(Statsd* statsd, const char* server, int port, const char* nameSpace, const char* bucket);
```
The first way will use malloc to allocate new memory for the Statsd client object. The 
second way can be used for static allocation. 

```c
Statsd *stats = NULL;
int ret = statsd_new(&stats, "localhost", STATSD_PORT, "application.test", "times");
if (ret != STATSD_SUCCESS){
   //Error
   return ret;
}
```
If you have used statsd_new() to dynamically create a client object, you must call
statsd_release() to free the resources and avoid memory leaks. 

### Stat types and usage

### Batching

### Errors

## Command line

## License
This project is available for use under the MIT license.

Copyright (c) 2013 James Slocum (jamesslocum.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
