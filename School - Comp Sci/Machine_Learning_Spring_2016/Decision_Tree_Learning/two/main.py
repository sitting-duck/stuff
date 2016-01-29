
__author__ = 'ashley tharp'

from Problem import Problem

def main():

    problem = Problem()

    run_tests(problem)

def run_tests(problem):
    test_get_tokenized_data(problem)
    test_get_row(problem)
    test_get_column(problem)
    test_get_category_names(problem)

def test_get_tokenized_data(problem):
    tokenized_data = problem.get_tokenized_data()
    assert len(tokenized_data[0]) == 6, "improper row length"
    assert len(tokenized_data) == 15, "improper column length"

def test_get_row(problem):
    test_row = ['Day', 'Outlook', 'Temp', 'Humidity', 'Wind', 'PlayTennis']
    assert problem.training_data.get_row(0) == test_row, 'get_row is broken'

def test_get_column(problem):
    test_column = ['Day', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14']
    assert problem.training_data.get_column(0) == test_column, 'get_column is broken'

def test_get_category_names(problem):
    test_names = ['Outlook', 'Temp', 'Humidity', 'Wind']
    assert problem.training_data.get_category_names() == test_names, 'get_category_names_is_broken'

if __name__ == '__main__':
    main()