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

