<h1><img src="https://fastly.cdn.syracuse.edu/logos/syr_eng-comp-science_full.svg"></h1>

## Authors
Stephanie Eordanidis - sleordan@syr.edu

JT Washington - jwashi05.@syr.edu

## Course
CSE687 SP22 @ Syracuse University's College of Engineering and Computer Science online masters program

## Platform
This application was developed in the Visual Studio 2022 Community Edition IDE

## Requirement
This project uses the Boost v1.78.0 library for logging and other various needs. Installation required. Refer to <a href="https://www.boost.org/doc/libs/1_78_0/more/getting_started/index.html">boost getting started</a> for more details on installation

## Application - MapReduce
A C++ standalone command-line program that can run a word count MapReduce workflow on text files retrieved from the user provided directory path, and outputs results to user specified output directory path.

### Arguments
Expected arguments are as follows:

	 -input 	<input path>: 		This is the path where the text files reside.
	 
	 -output 	<output path>: 		This is the path where the MapReduced result files will be placed.
	 
	 -temp 		<temp path>: 		This is the permitted temporary file location for MapReduce to utilize.
	
	
### Phase 1: 
The program runs as a single process that will take an input directory where text files are stored and will ultimately produce a single output file that contains a list of words and their associated counts in the originating input files.

### Phase 2:
TBD

### Phase 3:
TBD

### Phase 4:
TBD

## Application Structure
This section describes the application structure.

### Classes
	 Workflow			- Executes the main business logic for the MapReduce application.
	 
	 Executive			- Contains the main function and any additional utility functions/data required.
	 
	 FileManagement		- Handles all filesystem related functionallity.
	 
	 Map				- Is given data from a file (does not parse the file itself) and outputs a separate temporary file that holds (word, 1) for each occurrence of every word.
	 
	 Sorter				- Sorts temporary file data prior to reduce call.
	 
	 Reduce				- Is given sorted data from the intermediate file and reduces the results by aggregating the values.