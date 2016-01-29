
import fileinput

class Problem:

    tokenized_data = []

    #every category will contain an attribute dictionary
    categories = {}

    def __init__(self):
        self.tokenized_data =self. get_tokenized_data()

    def get_tokenized_data(self):
        tokenized_data = []
        data = fileinput.input()
        for line in data:
            tokens = line.split()
            tokenized_data.append(tokens)
        return tokenized_data

    def get_categories(self):
        pass

    def get_category_names(self):
        temp_row = self.get_row(0)
        del temp_row[0]
        del temp_row[-1]
        return temp_row

    def get_row(self, index):
        return self.tokenized_data[index]

    def get_column(self, index):
        temp_column = []
        for row in self.tokenized_data:
            temp_column.append(row[index])
        return temp_column