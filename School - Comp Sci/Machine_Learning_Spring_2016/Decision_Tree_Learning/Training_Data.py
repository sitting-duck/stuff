
from Category import Category
import copy

class Training_Data:

    data = []

    categories = []

    class_category = Category

    def __init__(self, file_data):
        for line in file_data:
            self.data.append(copy.deepcopy(line))
        self.categories = self.get_categories_from_data()
        print self.categories
        self.class_category = self.categories[-1]
        del self.categories[-1]

        print 'stuck yet?'
        self.get_entropy_for_category_number(1)
        print 'got past?'

    def get_categories_from_data(self):
        categories = []
        category_names = self.get_category_names()
        category_index = 1

        while category_index < len(category_names):
            name = category_names[category_index]
            attrs = self.get_unique_attributes_for_category_number(category_index)
            new_category = Category(name, attrs)
            categories.append(new_category)
            category_index += 1
        return categories

    def get_category_names(self):
        return self.data[0].split()

    def get_entropy_for_category(self, category):
        pass

    def get_entropy_for_category_number(self, category_index):
        column = self.get_columns()[category_index]
        print "len(col): " + str(len(column))
        class_column = self.get_columns()[-1]

        row_index = 0
        class_category_index = 0
        attr_index = 0

        while row_index < len(column):
            while attr_index < len(self.categories[category_index].attributes):
                while class_category_index < len(self.class_category.attributes):
                    if class_column[row_index] == class_column[class_category_index]:
                        self.categories[attr_index].class_count_vector[class_category_index] += 1
                    class_category_index += 1
                    print 'cci: ' + class_category_index
                attr_index += 1
            row_index += 1

        self.print_categories()

    def get_unique_attributes_for_category_number(self, index):
        attrs = []
        column = self.get_column_from_data_without_category_name(index)
        del column[0]

        for attr in column:
            if attr not in attrs:
                attrs.append(attr)
        return attrs

    def get_columns(self):
        columns = []
        column_index = 1

        while column_index <= len(self.categories) + 1:
            columns.append(self.get_column_from_data_without_category_name(column_index))
            column_index += 1
        return columns

    def get_number_of_training_examples(self):
        num_lines = 0
        for line in self.data:
            num_lines += 1
        return num_lines

    def get_line_tokens(self, line):
        return line.split()

    def get_column_from_data(self, column_number):
        temp_column = []
        for row in copy.deepcopy(self.data):
            row_tokens = row.split()
            temp_column.append(row_tokens[column_number])
        return temp_column

    def get_column_from_data_without_category_name(self, column_number):
        temp_column = self.get_column_from_data(column_number)
        del temp_column[0]
        return temp_column

    def print_categories(self):
        for category in self.categories:
            category.print_me()
