
import argparse

def main(fileOutputFlag, fileUrl):
    """

    :return:
    """
    # grab the command line args
    args = parseCommandLineArgs()

    # open the file
    inputFile = open(args.fileUrl, 'r+')

    # grab the lines from the file and put them in a list
    lines = inputFile.readlines()
    #for line in lines:
    #    print line

    # wherever there is an "id:" token, make an objectName: property in the next line with the same id string
    for lineIndex in range(0, len(lines)):
        line = lines[lineIndex]
        if "id: " in line:
            print line,
            tokens = line.split()
            for i in range(0, len(tokens)):
                if tokens[i] == "id:":
                    idString = tokens[i+1]
                    whitespace = getLeadingWhiteSpace(line)
                    objectNameString = whitespace + 'objectName: "' + idString + '"'
                    print objectNameString
                    newLine = line + objectNameString
                    lines[lineIndex] = newLine
                    #lines.insert(lineIndex + 1, objectNameString)
                    #del lines[lineIndex + 1]

    if args.fileOutputFlag == "make-new-copy":
        inputFileNameTokens = inputFile.name.split('/')
        inputFileName = inputFileNameTokens[len(inputFileNameTokens) -1]
        newFile = open("new_" + inputFileName, 'w')
        inputFile.close()
        for lineIndex in lines:
            newFile.write("%s\n" % lineIndex)
        newFile.close()

    if args.fileOutputFlag == "inline":
        inputFile.truncate()
        for lineIndex in lines:
            inputFile.write("%s\n", lineIndex)
        inputFile.close()

def getLeadingWhiteSpace(line):
    whitespace = ""
    for i in range(0, len(line) - 1):
        if line[i] is '\t' or line[i] is ' ':
            whitespace += line[i]

    return whitespace[:-1]

def parseCommandLineArgs():
    """
    grabs the arguments from the command line and returns them in a triple.
    the command line arguments are '<--make-new-copy | --in-place> <path/to/file.qml>'
    :return: a triple containing the command line args
    """



    #print "la args" + args[0] + args[1] + args[2]
    #assert(len(args) == 2 'error: incorrect command line args.  Correct call is <--make-new-copy | --in-place> <path/to/file.qml>')

    return args

if __name__ == "__main__":
    # inititalize the argument parser so we can get the arguments from the command line
    parser = argparse.ArgumentParser(description = 'boop')

    # grab the argument for the file output flag. The file output flag can be either
    # -make-new-copy or -in-place.
    # the -make-new-copy flag will output a new file with the proper object names for every qml
    # object with a defined id.
    # the -in-place flag will out edit the file in place.
    # the file output flag is required and the program will not run if it is not specified.
    parser.add_argument('fileOutputFlag', help="-in-place or -make-new-copy")

    # grab the file name for the qml file we are adding object names for
    parser.add_argument('fileUrl', help="the file you want to process")

    # parse the args and put them in args
    args = parser.parse_args()

    main(args.fileOutputFlag, args.fileUrl)
