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
A C++ standalone command-line program that can run a word count MapReduce workflow on text files retrieved from the user provided directory path, and outputs results to user specified output directory path.

### Arguments
Expected arguments are as follows:

	 -input 	<input path>: 		This is the path where the text files reside.
	 
	 -output 	<output path>: 		This is the path where the MapReduced result files will be placed.
	 
	 -temp 		<temp path>: 		This is the permitted temporary file location for MapReduce to utilize.
	 
Optional Arguments:

	 -rut		< value >		    This flag when set will run unit tests prior to application run. Currently value does not matter, will run if flag with any value is present.
	
	
### Phase 1: 
The program runs as a single process that will take an input directory where text files are stored and will ultimately produce a single output file that contains a list of words and their associated counts in the originating input files.

## Application Structure
This section describes the application structure.

### Classes
	 Workflow			- Executes the main business logic for the MapReduce application.
	 
	 Executive			- Contains the main function and any additional utility functions/data required.
	 
	 MapReduceUtils		- Util class to store common util functions.
	 
	 FileManagement		- Handles all filesystem related functionallity.
	 
	 Map				- Is given data from a file (does not parse the file itself) and outputs a separate temporary file that holds (word, 1) for each occurrence of every word.
	 
	 Sorter				- Sorts temporary file data prior to reduce call.
	 
	 Reduce				- Is given sorted data from the intermediate file and reduces the results by aggregating the values.
	 
### Unit Tests
	Unit tests are stored under the /test directory and are run on the main class functionallity.