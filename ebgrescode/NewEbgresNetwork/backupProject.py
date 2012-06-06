#! /usr/bin/env python3.1
# -*- coding: utf-8 -*-

import os
import os.path

versionFileName = ".version"

versionFilePath = os.path.abspath(versionFileName)

if (not os.path.exists(versionFilePath)):
    with open(versionFilePath, 'w') as versionFile:
        startVersionNumber = 1
        versionFile.write(str(startVersionNumber)+"\n")
    