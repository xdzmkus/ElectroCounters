# ElectroCounters
C++ Application to retreive date and time from Electrical Counters via TCP/IP and storing data in MySQL database

## Visual Studio setup

https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-cmd

Set up vcpkg.

Generate a manifest file and add dependencies.

Run the following command to create a vcpkg manifest file (vcpkg.json):

> vcpkg new --application

The vcpkg new command adds a vcpkg.json file and a vcpkg-configuration.json file in the project's directory.

Add the poco[mysql] package as a dependency:

> vcpkg add port libmysql poco[mysql]

Your vcpkg.json should now contain:

	{
	  "dependencies": [
		"libmysql",
		{
		  "name": "poco",
		  "features": [
			"mysql"
		  ]
		}
	  ]
	}

Add path to VCPKG into CMakePresets.json

	  "cacheVariables": {
		"CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

## Ubuntu

> sudo apt-get install build-essential gcc g++ cmake pkg-config ninja-build

Install vcpkg

> sudo apt-get install curl zip unzip tar

> cd ~

> git clone https://github.com/microsoft/vcpkg.git

> cd vcpkg && ./bootstrap-vcpkg.sh

> cd ..

Configure the VCPKG_ROOT environment variable

> export VCPKG_ROOT=~/vcpkg

> export PATH=$VCPKG_ROOT:$PATH

Build Application

> git clone https://github.com/xdzmkus/ElectroCounters.git

> cd ElectroCounters

> cmake --preset=Ubuntu

> cmake --build build

Edit and Copy ElectroCounters/config.ini to 'build/ElectroCounters' directory

> cp ElectroCounters/config.ini build/ElectroCounters/

Run application:

> cd ./build/ElectroCounters && ./ElectroCounters



