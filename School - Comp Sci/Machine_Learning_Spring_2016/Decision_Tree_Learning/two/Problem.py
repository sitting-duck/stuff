
from Training_Data import Training_Data

class Problem:

    training_data = Training_Data()

    def __init__(self):
        pass

    def calculate_entropy_for_training_set(self):
        class_values = self.training_data.get_class_values_for_training_set()
        num_values = len(class_values)

        proportion_to_class_type_for_training_set = self.training_data.get_proportion_to_class_type_for_training_set_dictionary()

        for key, value in proportion_to_class_type_for_training_set.iteritems():
            pass
            #Hi = (-1)*(value/num_values)(math.log(, 2))*(value/num_values)

    def get_categories(self):
        return self.training_data.get_categories()

    def get_tokenized_data(self):
        return self.training_data.get_tokenized_data()

