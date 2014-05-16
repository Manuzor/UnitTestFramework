#!/bin/env python

import os
import re
from glob import glob
from shutil import copy2

destination_root = os.environ.get("POTOO_API")

roots = {
	"output" : [ "bin32", "bin64", "lib32", "lib64", ],
	"source/cut" : [ "include", ],
}

# A list of patterns to check if a file should be installed or not.
# The absolute file names will be checked against these patterns.
# Note: On Windows, the file names will have backslashes, not forward slashes
ignored_files = (
	r"\.ilk",
	r"\.exp",
	r"\.gitkeep",
	r"cut-samples\..+",
	r"cut-detail/",
	r"stdafx\.h",
)

def is_ignored(f):
	for pattern in ignored_files:
		if re.search(pattern, f):
			return True
	return False

def create_dirs(d):
	if os.path.exists(d):
		return
	os.makedirs(d)

def main():
	print("Destination root: {0}".format(destination_root))
	if destination_root is None:
		print("Invalid destination_root")
		exit(-1)

	buf = []

	working_dir = os.getcwd()
	for root in roots.keys():
		os.chdir(os.path.join(working_dir, root))
		for subdir in roots[root]:
			for currentDir, dirs, files in os.walk(subdir):
				for f in files:
					source = os.path.normpath(os.path.join(working_dir, root, currentDir, f))
					if is_ignored(source):
						continue
					targetDir = os.path.normpath(os.path.join(destination_root, currentDir))
					create_dirs(targetDir)

					target = os.path.normpath(os.path.join(targetDir, f))
					copy2(source, target)
					print("{0} => {1}".format(source, target))

if __name__ == '__main__':
	main()