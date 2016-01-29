
from __future__ import division
import math
from Training_Data import Training_Data

class Problem:

    training_data = Training_Data()

    def __init__(self):
        pass

    def calculate_entropy_for_training_set(self):

        proportion_to_class_type_for_training_set = self.training_data.get_proportion_to_class_type_for_training_set_dictionary()
        num_values = self.training_data.get_number_training_examples()

        sum = 0.0
        Pi = 0.0
        Hi = 0.0
        ratio = 0.0

        for key, value in proportion_to_class_type_for_training_set.iteritems():
            #print "val:" + str(value) + "numval: " + str(num_values) + "frac: " + str(float(value/num_values))

            # todo: create if for log0

            Pi = float(value)/float(num_values)

            # for the edge case of log(0) (convenient loophole for computing entropy)
            if Pi == 0.0:
                sum += 0.0
            else:
                sum += float(-1.0)*float(Pi)*(float(round(math.log(Pi, 2), 3)))
            sum = round(sum, 3)

        return round(sum, 3)

    def get_categories(self):
        return self.training_data.get_categories()

    def get_tokenized_data(self):
        return self.training_data.get_tokenized_data()

