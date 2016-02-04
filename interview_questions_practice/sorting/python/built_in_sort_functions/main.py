
__author__ = 'Ashley Tharp'


def main():
    """
        This program goes over the basic sorting functionality in Python
    """

    # sorting strings
    sorted_strings = sorted("Let's sort this string".split(), key=str.lower)

    print "sorted strings: " + str(sorted_strings)

    # sorting complex objects
    student_tuples = \
        [
            ('john', 'A', 15),
            ('jane', 'B', 12),
            ('dave', 'B', 10),
        ]

    students_sorted_by_age = sorted(student_tuples, key=lambda student: student[2])
    print "students sorted by age: " + str(students_sorted_by_age)

    # sorting strings by length
    print "strings by length: " +\
          str(sorted("aaaaaa aaaaa aaaa a aaaaa aaa s sdkj skjdfksj soashfasksdk fsdhfkj fbd osdf".split(), key=len))



if __name__ == '__main__':
    main()
