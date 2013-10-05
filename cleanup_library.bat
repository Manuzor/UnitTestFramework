@echo off

set folder=library

mkdir _bak
copy %folder%\.gitignore _bak
rd %folder% /S /Q
mkdir %folder%
copy _bak\.gitignore %folder%
rd _bak /S /Q