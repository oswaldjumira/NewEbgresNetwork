#!/bin/bash

source ./basicFunctions.sh

#Go up directory tree to project folder

cd ..

projectFolder=$(pwd)

testCreateDirectory $projectFolder/LogFiles

logFolder="$projectFolder/LogFiles"

updateFileVersionNumber $logFolder/version.txt

versionNumber=$(cat $logFolder/version.txt)

createDatedVersionedArchive "Ebgres_Network" $projectFolder $versionNumber
