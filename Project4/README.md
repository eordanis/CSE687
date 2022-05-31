<h1><img src="https://fastly.cdn.syracuse.edu/logos/syr_eng-comp-science_full.svg"></h1>


## Authors
Stephanie Eordanidis - sleordan@syr.edu

JT Washington - jwashi05.@syr.edu

## Course
CSE687 SP22 @ Syracuse University's College of Engineering and Computer Science online masters program

## Platform
This application was developed in the Visual Studio 2022 Community Edition IDE

## Install Requirements

### Boost
This project uses the Boost v1.78.0 library for logging and other various needs. Installation required. Refer to <a href="https://www.boost.org/doc/libs/1_78_0/more/getting_started/index.html">boost getting started</a> for more details on installation

### Google Test
This application uses the following version of Google Test to perform unit testings 
	-	Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn
	
This Google Test suite if not already installed can be installed via Tools -> NuGet Package Manager. Ensure the following version is installed: <img src="https://github.com/eordanis/CSE687/blob/main/img/ref_gg_test_2.PNG">
	
## Running in Visual Studio
If desired to run via Visual Studio:

1. Pull down the project and open in Visual Studio and right click on project solution and go to Properties
2. In Properties pane, navigate to the <i>Configuration Properties -> ... </i>
	1. <i>Referenced Packages</i> Ensure "Google Test" is shown. <img src="https://github.com/eordanis/CSE687/blob/main/img/ref_gg_test.PNG">
	2. <i>C/C++</i> Ensure you add your boost library directory to the <i>Additional Includes Directories</i> path. Note that %(AdditionalIncludeDirectories) is also included. <img src="https://github.com/eordanis/CSE687/blob/main/img/cpp_add_inc_dir.PNG">
	3. <i>Linker</i> Ensure you add your boost library directory to the <i>Additional Library Directories</i> path. Note that %(AdditionalIncludeDirectories) is also included. <img src="https://github.com/eordanis/CSE687/blob/main/img/linker_add_lib_dir.PNG">
	
## Application - MapReduce
A C++ standalone command-line program that can run a word count MapReduce workflow on text files retrieved from the user provided directory path, and outputs results to user specified output directory path. This phase of the application takes in the map and reduce dll files and utilizes their functions.

### Arguments
Expected arguments are as follows:

	 -input 	<input path>: 		This is the path where the text files reside.
	 
	 -output 	<output path>: 		This is the path where the MapReduced result files will be placed.
	 
	 -temp 		<temp path>: 		This is the permitted temporary file location for MapReduce to utilize.
	 
	 -dll       <dll path>:         This is the directory path in which both MapDLL.dll & ReduceDLL.dll are located.    
	 
Optional Arguments:

	 -threads	<number of threds)  If this flag is present, if valid value is passed, thread count will be set to indicated value. Else default of 1 thread is set.

	 -rut						    If this flag is present, tests will be run instead of application.
	 
	 -help							If this flag is present, usage statement is shown to user and application exits
	
### Phase 4: 
The program runs as as a single process that will take input text files and will ultimately produce a single output file that contains a list of words and their associated counts in the originating input files. This phase of the application takes in the map and reduce dll files and utilizes their functions.
The map and reduce functionallity however will run on multiple threads. Two new classes were introduced to handle thread capture/creation/handling.

There are five required arguments: input path, temp path, output path, mapDLL.dll path and reduceDLL.dll path.
 
* Input path is the directory where input text files are stored.

* The temp path is the path where the intermediary temporary .dat files are stored. Note, if the temporary file of the same name exists (ie previous run) then these files are overwritten. The temp files contain the initial token/key work mapping. Example behavior: (word,1).

* The output path is the path where the sorted and reduced intermediaary file results are stored. These output files are date/timestamped. Example behavior: (word,1)(second,1)(word,1) ->  (second,1)(word,2)

* The dll path is the path where the MapDLL.dll & ReduceDLL.dll files can be found.

Example.

Input   Text File: <input path>/demo.txt                                            <- I am but a humble developer. I wish to continue striving for success!. Success is important for developers.

Temp    Text File: <temp path>/demo_2022-04-28_18-16-56.dat                         <-(i,1)\n(am,1)\n)(but,1)\n(a,1)\n(humble,1)\n(developer,1)\n(i,1)\n(wish,1)\n(to,1)\n(continue,1)\n(striving,1)\n(for,1)\n(success,1)\n(success,1)\n(is,1)\n(important,1)\n(for,1)\n(developers,1)\n

Output  Text File: <temp path>/demo__2022-04-28_18-16-56_2022-04-28_18-18-13.txt    <-(a,1)\n(am,1)\n(but,1)\n(continue,1)\n(developer,1)\n(developers,1)\n(for,2)\n(humble,1)\n(i,2)\n(important,1)\n(is,1)\n(for,1)\n(striving,1)\n(success,2)\n(to,1)\n(wish,1)\n

## Application Structure
This section describes the application structure.

### Classes
	 Workflow           - Executes the main business logic for the MapReduce application.
	 
	 Executive          - Contains the main function and any additional utility functions/data required.
	 
	 MapReduceUtils     - Util class to store common util functions.
	 
	 FileManagement     - Handles all filesystem related functionallity.
	 
	 ExecuteThread		- Handles map/reduce thread routing & creation.
	 
	 Threading			- Handles map/reduce specific logic per thread.
	 
### DLLs
	 
	 Map                - Is given data from a file (does not parse the file itself) and outputs a separate temporary file that holds (word, 1) for each occurrence of every word.
	 	 
	 Reduce             - Is given sorted data from the intermediate file and reduces the results by aggregating the values.
	 
### Unit Tests
	Unit tests are stored under the /test directory and are run on the main class functionallity.
	
	FileManagementTest     - Unit tests for FileManagement class.
	 
	MapTest                - Unit tests for Map class.
	 	 
	ReduceTest             - Unit tests for Reduce class.