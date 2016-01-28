
from Category import Category
import copy

class Training_Data:

    data = []

    categories = []

    def __init__(self, file_data):
        for line in file_data:
            self.data.append(copy.deepcopy(line))
        self.categories = self.get_categories_from_data()

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

    def get_entropy_for_category(self, category_index):
        pass

    def get_unique_attributes_for_category_number(self, index):
        attrs = []
        column = self.get_column_from_data(index)
        del column[0]

        for attr in column:
            if attr not in attrs:
                attrs.append(attr)
        return attrs

    def get_number_of_training_examples(self):
        num_lines = 0
        for line in self.data:
            num_lines += 1
        return num_lines

    def get_column_from_data(self, column_number):
        temp_column = []
        for row in copy.deepcopy(self.data):
            row_tokens = row.split()
            temp_column.append(row_tokens[column_number])
        return temp_column