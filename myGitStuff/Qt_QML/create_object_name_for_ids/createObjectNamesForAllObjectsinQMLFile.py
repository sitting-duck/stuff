import re, string
import argparse

def main(args):
    """

    :return:
    """
    if args.tagWhichObjects == "only-with-id":
        tagOnlyWithId(args)
    if args.tagWhichObjects == "all-objects":
        tagAllObjects(args)

def tagAllObjects(args, objectStack=[], lines=[]):

    # if this is first call we grab lines from file
    if lines == []:
        # open the file
        inputFile = open(args.fileUrl, 'r+')

        # grab the lines from the file and put them in a list
        lines = inputFile.readlines()

    numNested = -1
    # wherever there is an "id:" token, make an objectName: property in the next line with the same id string
    for lineIndex in range(0, len(lines)):
        line = lines[lineIndex]

        #a curly bracket indicates a new object
        if '{' in line and ':' not in line:
            numNested += 1
            currentType = getCurrentObjectType(lines, lineIndex)
            howMany = sum(1 for currentObject in objectStack if currentObject['type'] == currentType)
            currentPossibleTag = currentType + str(howMany)
            currentObject = { 'type' : currentType, 'possibleTag' : currentPossibleTag}
            objectStack.append(currentObject)

        # if we have reached a '}' that means we have completed the last object on the stack
        if '}' in line:
            #find the first '{' in the lines before it and and that should be the text block for that object
            numNested -= 1
            currentObjectLineIndex = lineIndex
            codeBlock = []
            while True:
                currentObjectLineIndex -= 1
                currentCodeLine = lines[currentObjectLineIndex]
                if '}' in currentCodeLine:
                    numNested += 1
                if '{' in currentCodeLine:
                    if numNested == 0:
                        break;
                # we found an entire object
                    numNested -= 1

                codeBlock.append(lines[currentObjectLineIndex])
            print "CODE BLOCK"
            for codeLine in codeBlock:
                print codeLine


            #see if the id tag is in that text block
            hasIdTag = False
            currentIdTagIndex = -1
            for i in range(currentObjectLineIndex, lineIndex):
                currentCodeLine = lines[i]
                print currentCodeLine
                if 'id: ' in currentCodeLine:
                    hasIdTag = True
                    currentIdTagIndex = i

            if hasIdTag == True:
                objectNameLine = getObjectNameLine(lines[currentIdTagIndex])
                newLine = lines[currentIdTagIndex] + objectNameLine
                lines[lineIndex] = newLine
                print newLine
            else:
                idTagString = objectStack[-1]['possibleTag']
                customIdTag = "id: " + idTagString + "\n"
                objectNameLine = 'objectName: "' + idTagString + '"\n'
                whitespace = getLeadingWhiteSpaceOnLine(lines, currentObjectLineIndex - 1)
                newLine = whitespace + customIdTag + whitespace + objectNameLine
                lines[lineIndex] = newLine
                print newLine

    writeToFile(args, inputFile, lines)

#def findMatchingCurlyBraceAndReturnCodeBlock(lines):


def getLeadingWhiteSpaceOnLine(lines, lineIndex):

    numSpace = 0
    line = lines[lineIndex]
    for i in range(0, len(line)):
        if line[i] == ' ':
            numSpace += 1
        else:
            break # break at the first non space

    return line[0 : numSpace]

def getWhiteSpaceBasedOnNumNestedObjects(numNested):
    whitespace = ""
    for i in range(0, numNested):
        whitespace += " "
    return whitespace

def getCurrentObjectType(lines, lineIndex):
    #grab the name of the type in front of it
    lineBefore = lines[lineIndex - 1]
    currentLine = lines[lineIndex]

    lineBeforeTokens = lineBefore.split()
    currentLineTokens = currentLine.split()

    #if the first token is '{' then we know the type is on the line before
    if currentLineTokens[0] == '{':
        currentType = lineBeforeTokens[0]
    else:
        # at this point we can assume the type and the '}' are on the same line
        currentType = currentLineTokens[0]

    # use regex to scrub all non alpha numeric characters eg. beginning of a comment
    # such as '/*Rectangle {'. (yes, this eve works inside comments, it is just a text parser
    # after all
    newcurrentType = re.sub('[^0-9a-zA-Z]+', '', currentType)

    return newcurrentType

def tagOnlyWithId(args):
    # open the file
    inputFile = open(args.fileUrl, 'r+')

    # grab the lines from the file and put them in a list
    lines = inputFile.readlines()

    # wherever there is an "id:" token, make an objectName: property in the next line with the same id string
    for lineIndex in range(0, len(lines)):
        line = lines[lineIndex]
        if "id: " in line:
            print line,
            objectNameLine = getObjectNameLine(line)
            print objectNameLine
            newLine = line + objectNameLine
            lines[lineIndex] = newLine

    writeToFile(args, inputFile, lines)

def writeToFile(args, inputFile, lines):
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

def getObjectNameLine(line):
    """
    creates the object name string from the id string
    :param line: line from file containing 'id: ' tag eg. 'id: mtId'
    :return: line with object name string eg. 'objectName: "myId"'
    """
    objectNameString = ""
    tokens = line.split()
    for i in range(0, len(tokens)):
        if tokens[i] == "id:":
            idString = tokens[i+1]
            whitespace = getLeadingWhiteSpace(line)
            objectNameString = whitespace + 'objectName: "' + idString + '"'
    return objectNameString


def getLeadingWhiteSpace(line):
    whitespace = ""
    for i in range(0, len(line) - 1):
        if line[i] is '\t' or line[i] is ' ':
            whitespace += line[i]

    return whitespace[:-1]

def parseCommandLineArgs():
     # inititalize the argument parser so we can get the arguments from the command line
    parser = argparse.ArgumentParser(description = 'Adds objectName: tags to qml objects in qml files automagically')

    # grab the argument for the file output flag. The file output flag can be either
    # -make-new-copy or -in-place.
    # the -make-new-copy flag will output a new file with the proper object names for every qml
    # object with a defined id.
    # the -in-place flag will out edit the file in place.
    # the file output flag is required and the program will not run if it is not specified.
    parser.add_argument('fileOutputFlag', help="in-place or make-new-copy")

    parser.add_argument('tagWhichObjects', help="all-objects or only-with-id. \n specifies whether you want to add tags \
                                                to every object or only objects that have already been given an id tag.\
                                                objects without an id tag will be given one based on their type, which \
                                                class they are in and which module they are in")

    # grab the file name for the qml file we are adding object names for
    parser.add_argument('fileUrl', help="the file you want to process")

    # parse the args and put them in args
    args = parser.parse_args()

    return args

if __name__ == "__main__":

    args = parseCommandLineArgs()

    main(args)
