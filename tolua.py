#!/usr/bin/env python
"""
" Copyright (c) 2013 Laurent Zubiaur
"
" http://www.pix2d.com/
"
" Permission is hereby granted, free of charge, to any person obtaining a copy
" of this software and associated documentation files (the "Software"), to deal
" in the Software without restriction, including without limitation the rights
" to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
" copies of the Software, and to permit persons to whom the Software is
" furnished to do so, subject to the following conditions:
" 
" The above copyright notice and this permission notice shall be included in
" all copies or substantial portions of the Software.
" 
" THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
" IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
" FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
" AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
" LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
" OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
" THE SOFTWARE.
"""

import os,sys,glob
import argparse
from subprocess import call

def main(argv=None):

    argv = (argv or sys.argv)[1:]

    parser = argparse.ArgumentParser(usage=("%(prog)s [--tolua|-t] directory"))

    parser.add_argument("directory",
        type=unicode,
        help="tolua++ packages directory")

    parser.add_argument("--tolua","-t",
        dest="tolua",
        type=unicode,
        help="tolua++ executable path")
    
    options, args = parser.parse_known_args(argv)

    if not os.path.isdir(options.directory):
        parser.error("Directory not found: '{0}'".format(options.directory))

    if options.tolua:
        if not os.path.isfile(options.tolua):
            parser.error("tolua++ executable not found: '{0}'".format(options.tolua))
    else:
        if not os.path.isfile('./tolua++'):
            parser.error("tolua++ not found in the current directory. Please provide the path of the tolua++ executable.")
        else:
            options.tolua = './tolua++'

    if options.directory:
        tolua(options.tolua,os.path.abspath(options.directory))

def tolua(tolua_exec,directory):
    """
    tolua command line:
    ./tolua++ -n "basename" -H filename.hpp -o filename.cpp filename.pkg
    """
    for filename in glob.glob(directory + '/*.pkg'):
        filename, fileExt = os.path.splitext(filename)
        basename = os.path.basename(filename)
        arg1 = basename
        arg2 = filename + ".hpp"
        arg3 = filename + ".cpp"
        arg4 = filename + ".pkg"
        sys.stdout.write("processing " + filename + ".pkg...   ")
        call([tolua_exec,"-n",arg1,"-H",arg2,"-o",arg3,arg4])
        print "done"

if __name__ == "__main__":
    sys.exit(main())
