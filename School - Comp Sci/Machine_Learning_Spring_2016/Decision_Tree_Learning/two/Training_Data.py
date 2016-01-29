import fileinput
import copy

class Training_Data:

    tokenized_data = []

    def __init__(self):
        self.tokenized_data =self. get_tokenized_data()

    def get_tokenized_data(self):

        # if data has already been collected from file return it
        if self.tokenized_data != []:
            return self.tokenized_data
        # else collect the data from the file
        else:
            temp_tokenized_data = []
            data = fileinput.input()
            for line in data:
                tokens = line.split()
                temp_tokenized_data.append(tokens)
            return temp_tokenized_data

    def create_categories(self):
            pass

    def create_category_from_column(self, index):
        column = self.get_column()
        name = column[0]

    # note: this is referring to the actual column data, not just the attribute data.
    # the data is still pretty raw when this function is called
    def get_unique_attribute_names_from_column(self, index):

        column = self.get_column(index)

        # add all names not seen before to the list of attr names
        # note: attribute names cannot be the same as a category name
        known_attribute_names = []
        for item in column:
            if item not  in known_attribute_names and item not in self.get_category_names():
                known_attribute_names.append(item)

        return known_attribute_names

    def get_category_names(self):
        temp_row = copy.deepcopy(self.get_row(0))
        del temp_row[0]
        del temp_row[-1]
        return temp_row

    def get_counter_name(self):
        temp_row = copy.deepcopy(self.get_row(0))
        return temp_row[0]

    def get_class_name(self):
        temp_row = copy.deepcopy(self.get_row(0))
        return temp_row[-1]

    def get_row(self, index):
        return self.tokenized_data[index]

    def get_column(self, index):
        temp_column = []
        for row in self.tokenized_data:
            temp_column.append(row[index])
        return temp_column