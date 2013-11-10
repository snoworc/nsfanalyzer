nsfanalyzer
===========

Code refactoring tool

NSFAnalyzer is a developer's tool designed to help you find code dependencies and to assist you with refactoring. You can scan single or multiple databases on  remote domino servers or your local machine.
 
NSFAnalyzer will find any code:
JavaScript
HTML
CSS
@Formula
LotusScript
Java 
Selective replication formulas, code inside actions, agents, button code, etc.
Database script, hide/when formulas, etc, etc, etc.
ACLs, hotspot formulas, etc, etc, etc
 
Example of usage:
You are assigned to a new application and need to enhance an existing design. But the application has many design elements. You can use this tool to quickly find code / code dependencies you wish to work with, etc.
You are migrating from Notes to Exchange. Part of your plan will be to replace functionality of applications that send email. But you do not know which applications or where exactly the current email functionality is. Searching on tokens related to mail functionality, such as ".send" or" @MailSend", should help.
 
Verified in R5.x, R6.x, R7.x, R8.x
 
Note: If you are installing a newer version of this product, go to Control Panel and remove the existing installed version before you install the new version. It will be called "NSFAnalyzer" in your 'Add/Remove' programs list.

Configuration File Settings

The configuration for this tool is: 
<executable-path>\settings.xml

All of the configuration settings correspond to the user interface options. To save this settings.xml file, select your desired options and choose File \ Save Settings from the menu.


XML Configuration Layout
===========
 <nowiki>
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<NSFAnalyze>
        <OutputFormat>csv</OutputFormat>
        <OutputFile>C:\tbnscanner_design.csv</OutputFile>
        <Server>CN=MyServer/O=MyOrg/C=US</Server>
        <Database>AgentRunner.nsf</Database>
        <Include>
                <Enabled>yes</Enabled>
                <Recurse>no</Recurse>
                <FolderList>
                        <Folder>i1</Folder>
                        <Folder>i2</Folder>
                </FolderList>
        </Include>
        <Exclude>
                <Enabled>yes</Enabled>
                <Recurse>yes</Recurse>
                <FolderList>
                        <Folder>e1</Folder>
                        <Folder>e2</Folder>
                </FolderList>
        </Exclude>
        <KeywordList>
                <Keyword>k1</Keyword>
                <Keyword>k2</Keyword>
        </KeywordList>
        <AnalyzeData>no</AnalyzeData>
        <ExactMatch>yes</ExactMatch>
        <AutoLaunch>yes</AutoLaunch>
	<FindMultipleTokensInNote>yes</FindMultipleTokensInNote>
</NSFAnalyze>
 </nowiki>

Description

<OutputFormat>: Specifies output file format.

Valid values are:

    * html
    * csv 

<OutputFile>: Specifies output file location.

<Server>: Specifies the server to scan.

<Database>: Specifies the database to scan. Leave blank to scan all databases on the server.

<Include> / <Exclude> sections: The configuration file may have either one enabled, but not both.

<Enabled>: Indicates the state of the checkbox of the option

Valid values are:

    * yes
    * no 

<Recurse>: Indicates the state of the checkbox of the option

Valid values are:

    * yes
    * no 

<FolderList>: Specifies the folders to either only include or exclude.

<KeywordList>: Specifies the keywords to search for in the database design. e.g.

<AnalyzeData>: Indicates whether or not to additionally scan all data in the database.

Valid values are:

    * yes
    * no 

<ExactMatch>: Indicates whether or not to search for exact matches only. If part of the source code is not in the design, such as %include "\\mycodePath\mycode.lss", it is considered a Possible Match because the analyzer cannot review the code. Possible matches are recorded so the developer doing a scan knows which dependencies s/he needs to manually review.

Valid values are:

    * yes
    * no 

<AutoLaunch>: Indicates whether or not to launch open the output file when the scan is done.

Valid values are:

    * yes
    * no 

<FindMultipleTokensInNote>: Indicates whether or not to stop scanning a note after at least one item (or item part) matches a search token. 

Example: Form has a field called FieldA and FieldB. Both have a formula of "[Developers]". If this setting is no, you will only get one "hit" for the form in your search results. The scan finds either FieldA or FieldB first, records the hit, and skips to the next note.

If the settings is yes, you would get multiple hits for the form (two or more). The reason you might get more than 2, is because the field data is buried in a series of composite data chunks. When this setting is set to "yes", then we keep scanning ALL of the composite data in $Body until we rich the end of the buffer.
So the field formulas are included, plus any composite data text found, or other composite data structures.

If the setting is "no" and a hit is found inside a composite data field, then we stop scanning the composite data buffer after the first hit. So, as you may guess, setting this to "no" will produce a faster scan time.

Valid values are:

    * yes
    * no 
