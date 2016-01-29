
__author__ = 'ashley tharp'

from Problem import Problem

def main():

    problem = Problem()

    run_tests(problem)

def run_tests(problem):
    run_training_data_tests(problem)
    run_problem_tests(problem)

def run_problem_tests(problem):
    pass

def run_training_data_tests(problem):
    test_get_tokenized_data(problem)
    test_get_row(problem)
    test_get_column(problem)
    test_get_category_names(problem)
    test_get_unique_attribute_names_from_column(problem)

def test_get_tokenized_data(problem):
    tokenized_data = problem.get_tokenized_data()
    assert len(tokenized_data[0]) == 6, "improper row length"
    assert len(tokenized_data) == 15, "improper column length"

def test_get_row(problem):
    test_row = ['Day', 'Outlook', 'Temp', 'Humidity', 'Wind', 'PlayTennis']
    assert problem.training_data.get_row(0) == test_row, 'get_row is broken'

def test_get_column(problem):
    test_column_0 = ['Day', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14']
    assert problem.training_data.get_column(0) == test_column_0, 'get_column is broken on column 0'

    test_column_1 = ['Outlook', 's', 's', 'o', 'r', 'r', 'r', 'o', 's', 's', 'r', 's', 'o', 'o', 'r']
    assert problem.training_data.get_column(1) == test_column_1, 'get_column is broken on column 1'

    test_column_2 = ['Temp', 'h', 'h', 'h', 'm', 'c', 'c', 'c', 'm', 'c', 'm', 'm', 'm', 'h', 'm']
    assert problem.training_data.get_column(2) == test_column_2, 'get_column is broken on column 2'

    test_column_3 = ['Humidity', 'h', 'h', 'h', 'h', 'n', 'n', 'n', 'h', 'n', 'n', 'n', 'h', 'n', 'h']
    assert problem.training_data.get_column(3) == test_column_3, 'get_column is broken on column 3'

    test_column_4 = ['Wind', 'w', 's', 'w', 'w', 'w', 's', 's', 'w', 'w', 'w', 's', 's', 'w', 's']
    assert problem.training_data.get_column(4) == test_column_4, 'get_column is broken on column 4'

def test_get_category_names(problem):
    test_names = ['Outlook', 'Temp', 'Humidity', 'Wind']
    assert problem.training_data.get_category_names() == test_names, 'get_category_names_is_broken'

def test_get_unique_attribute_names_from_column(problem):
    test_unique_names_for_outlook = ['s', 'o', 'r']
    test_unique_names_for_temp = ['h', 'm', 'c']
    test_unique_names_for_humidity = ['h', 'n']
    test_unique_names_for_wind = ['w', 's']

    output_for_column_1 = problem.training_data.get_unique_attribute_names_from_column(1)
    output_for_column_2 = problem.training_data.get_unique_attribute_names_from_column(2)
    output_for_column_3 = problem.training_data.get_unique_attribute_names_from_column(3)
    output_for_column_4 = problem.training_data.get_unique_attribute_names_from_column(4)

    assert output_for_column_1 == test_unique_names_for_outlook, 'get_unique attrbute names broke for outlook'
    assert output_for_column_2 == test_unique_names_for_temp, 'get_unique attrbute names broke for temp'
    assert output_for_column_3 == test_unique_names_for_humidity, 'get_unique attrbute names broke for humidity'
    assert output_for_column_4 == test_unique_names_for_wind, 'get_unique attrbute names broke for wind'

if __name__ == '__main__':
    main()