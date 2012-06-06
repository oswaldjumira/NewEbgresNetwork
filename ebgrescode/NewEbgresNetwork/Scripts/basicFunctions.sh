#!/bin/bash

function testCreateDirectory()
{
	local directory=$1
	if  test -d $directory; then
		echo "$directory already exists.";
	else
		echo "Creating $directory"
		mkdir $directory;
	fi
}

function updateFileVersionNumber()
{
	local file=$1
	if test -e $file; then
		echo "$file exists updating the version number."
		currentVersion=$(cat $file)
		newVersion=$(( $currentVersion + 1))

		echo "Current version is $currentVersion updating to $newVersion."
		echo "$newVersion" > $file;
	else
		echo "$file does not exist."
		echo "Initialising version to 0."
		echo "0" > $file;
	fi
}

function createDatedVersionedArchive()
{
	local version=$3
	local directory=$2
	local baseName=$1
	
	archiveName="$baseName.$version.$(date +%d_%b_%y_%H%M).zip"

	cd $directory

	directoryBaseName=$(basename $directory)
	cd ..
	zip -rv ./$archiveName ./$directoryBaseName
}
