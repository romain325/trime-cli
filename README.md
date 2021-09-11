# trime-cli

Trime is a time tracker tool, here is the cli.  
His purpose is to be as minimalistic as possible so that tracking your time doesn't become a whole activity on its own.

## Installation

### Cli Installation

Clone the project, get in the folder and run "make", then an executable called trime will appear, your cli is ready to go.  
If you get some error, be sure that you have the libcurl and libcurl-dev installed.

### Firebase configuration

> If you've already done that with another trime interface don't do it again

**Configuration of the project name will came later, I'm just lazy atm**
Create a new firebase project called trime-tracker, in the "Firestore Database", select trime-tracker and create a new collection called trime.
You're ready to go!  

## Usage

For help type: `trime help`

### tracking

To start tracking a certain activity you can simply type `trime track <act_name>`, then do your shit like a grown old man.
Once done type `trime stop <act_name>` and your current activity is now finished

### tagging

You can add tag to your activities (for better display in the graphical interface).  

> the graphical interface should be out soon

By running `trime tag add <act> <tag>` you add a new tag to your activity.
And simply by running `trime tag rm <act> <tag>` you remove the specified tag from an activity

### syncing

In order to sync your data with firestore, type `trime sync <action>`.
You can sync the tag with the action `tag`, the activities with the action `act` or both with the action `both`

## Developement

The app is really minimalistic as I don't like fat and time-consuming time tracking tool  
But if you want to request me new options, my dms are wide open  
