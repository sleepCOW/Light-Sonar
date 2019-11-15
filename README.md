# Light Sonar
 *Simple line counter*
* * *

*   Quick Start
*   Usage

# Quick Start
To be continued...

# Usage
 
## One or more files

Light Sonar can scan one or more files with such commands:
<pre>
LSonar file.extension
</pre>
<pre>
LSonar file1.extension file2.extension ...
</pre>
**Examples**
<pre>
PS B:\GitRepositories\NewArmy\Utils\Units> LSonar Unit.cpp                                                              
Time used: 0 ms
--------------------------------------------------------------------------------
| Extensions   | Files         | Lines         | Blanks        | Total         |
--------------------------------------------------------------------------------
| .cpp         | 1             | 89            | 19            | 108           |
--------------------------------------------------------------------------------
| SUM          | 1             | 89            | 19            | 108           |
--------------------------------------------------------------------------------
</pre>
<pre>
PS B:\GitRepositories\NewArmy\Utils\Units> LSonar Unit.cpp B:\GitRepositories\hello.cpp                                 
Time used: 0 ms
--------------------------------------------------------------------------------
| Extensions   | Files         | Lines         | Blanks        | Total         |
--------------------------------------------------------------------------------
| .cpp         | 2             | 99            | 20            | 119           |
--------------------------------------------------------------------------------
| SUM          | 2             | 99            | 20            | 119           |
--------------------------------------------------------------------------------
</pre>

## One or more directories
To scan directory and all subdirectories use this commands:
<pre>
LSonar directoryPath
</pre>
To scan more than one directory use:
<pre>
LSonar directoryPath1 directoryPath2 ...
</pre>
<b>WARNING</b> If you pass directory without additional extension arguments the programm will scan ALL extension and subdirectories that could be found and opened!
<pre>
PS B:\> LSonar B:\GitRepositories\NewArmy\Utils\Units                                                                   
Time used: 2 ms
--------------------------------------------------------------------------------
| Extensions   | Files         | Lines         | Blanks        | Total         |
--------------------------------------------------------------------------------
| .cpp         | 7             | 237           | 57            | 294           |
--------------------------------------------------------------------------------
| .h           | 7             | 122           | 47            | 169           |
--------------------------------------------------------------------------------
| SUM          | 14            | 359           | 104           | 463           |
--------------------------------------------------------------------------------
</pre>

**A single directory with list of extensions**
<pre>
PS B:\> LSonar B:\GitRepositories .cpp .h .py                                                                           
Time used: 119 ms
--------------------------------------------------------------------------------
| Extensions   | Files         | Lines         | Blanks        | Total         |
--------------------------------------------------------------------------------
| .cpp         | 86            | 2651          | 599           | 3250          |
--------------------------------------------------------------------------------
| .h           | 56            | 914           | 275           | 1189          |
--------------------------------------------------------------------------------
| .py          | 23            | 323           | 87            | 410           |
--------------------------------------------------------------------------------
| SUM          | 165           | 3888          | 961           | 4849          |
--------------------------------------------------------------------------------
</pre>
<b>NOTE:</b> if some of your extensions could't be found the result table won't contain it!

## Files and directories
You can combine commands to scan directories and single files together:
<pre>
LSonar directoryPath .extension1 .extension2 file.extension ...
</pre>
<b>Note:</b> order doesn't matter
**Example**
<pre>
PS B:\GitRepositories\NewArmy\Utils\Units> LSonar B:\GitRepositories\ .py .h Unit.cpp                                   
Time used: 107 ms
--------------------------------------------------------------------------------
| Extensions   | Files         | Lines         | Blanks        | Total         |
--------------------------------------------------------------------------------
| .cpp         | 1             | 89            | 19            | 108           |
--------------------------------------------------------------------------------
| .h           | 56            | 914           | 275           | 1189          |
--------------------------------------------------------------------------------
| .py          | 23            | 323           | 87            | 410           |
--------------------------------------------------------------------------------
| SUM          | 80            | 1326          | 381           | 1707          |
--------------------------------------------------------------------------------
</pre>
<b>Note:</b> extensions of single files won't be added for scan, as you can see <b>only</b> 1 cpp file have been scanned, not <b>ALL</b> of them!
