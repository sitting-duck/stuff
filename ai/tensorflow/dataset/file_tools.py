import os
import logging
logging.basicConfig(filename='fileio.txt', level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

# paths: an array of filepaths
def files(paths, valid_file_extensions):
    outlist = []	
    for path in paths:
        for (root, directories, filenames) in os.walk(str(path)):
            for filename in filenames:
                _, ext = os.path.splitext(filename)
                if ext in valid_file_extensions:
                    outlist.append( os.path.join(root, filename) )
    logging.debug('outlist: ', outlist)
    return outlist
            
