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
 
I have two versions available in the Downloads / Releases section.
<release>-Install is the default install version.
<release>-Source is the source code. You can also install the application from the source code build as well, since one of the source code projects is the installer itself. To install from the Source build, go to either the release or the debug folder within the installer project, and run setup.exe (or the .msi file - either one is fine). The default install version uses the release build.
 
Example of usage:
You are assigned to a new application and need to enhance an existing design. But the application has many design elements. You can use this tool to quickly find code / code dependencies you wish to work with, etc.
You are migrating from Notes to Exchange. Part of your plan will be to replace functionality of applications that send email. But you do not know which applications or where exactly the current email functionality is. Searching on tokens related to mail functionality, such as ".send" or" @MailSend", should help.
 
Verified in R5.x, R6.x, R7.x, R8.x
 
Note: If you are installing a newer version of this product, go to Control Panel and remove the existing installed version before you install the new version. It will be called "NSFAnalyzer" in your 'Add/Remove' programs list.
