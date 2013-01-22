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

This will install the library, headers, and a binary called statsd-cli.a

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

## Command line

## License

