
import itertools
import operator

def main():

    # this project is so that I can practice using the python itertools library

    my_dict = {'0' : ['0', '0', '0', '0'], '1' : ['1', '1', '1'], '2' : ['2']}

    for key, value in my_dict.iteritems():
        print "key: " + key + " value: " + str(value)

    greatest_current_key = ''
    greatest_num_items = 0

    #determine what the greatest number of items is
    for key, value in my_dict.iteritems():
        if len(value) > greatest_num_items:
            greatest_num_items = len(value)

    #find all keys with that many items
    # in the case of a tie we will take the lowest alpha key
    keys = []
    for key, value in my_dict.iteritems():
        if len(value) == greatest_num_items:
            keys.append(key)

    most_common = sorted(keys)[0]

    print most_common








#def most_common()

if __name__ == '__main__':
    main()
