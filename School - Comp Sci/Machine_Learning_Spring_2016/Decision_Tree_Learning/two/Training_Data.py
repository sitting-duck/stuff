import fileinput

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