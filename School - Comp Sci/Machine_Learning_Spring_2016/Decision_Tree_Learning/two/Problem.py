
from Training_Data import Training_Data

class Problem:

    training_data = Training_Data()

    #every category will contain an attribute dictionary
    categories = {}

    def __init__(self):
        pass

    def create_categories(self):
        pass

    def create_category_from_column(self, index):
        column = self.get_column()

    def get_unique_attribute_names(self):

        pass

    def get_tokenized_data(self):
        return self.training_data.get_tokenized_data()

