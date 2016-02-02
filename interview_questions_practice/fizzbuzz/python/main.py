
__author__ = 'ashley tharp'


def main():
    """
    The Fizz-Buzz test is an interview question designed to help filter out the 99.5% of programming job candidates who
     cant seem to program their way out of a wet paper bag. The text of the programming assignment is as follows:

    Write a program that prints the numbers from 1 to 100. But for multiples of three print Fizz instead of the number
    and for the multiples of five print Buzz. For numbers which are multiples of both three and five print FizzBuzz.
    """

    print_string = ""

    for i in range(1, 100 + 1):
        if i % 3 == 0:
            print_string += "Fizz"
        if i % 5 == 0:
            print_string += "Buzz"
        if print_string == "":
            print_string = str(i)
        print print_string
        print_string = ""

if __name__ == '__main__':
    main()
