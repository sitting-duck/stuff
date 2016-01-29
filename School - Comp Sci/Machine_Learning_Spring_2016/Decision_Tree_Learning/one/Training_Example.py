
class Training_Example:

    example_number = 0

    attrbute_values_vector = []

    class_value = None

    def __init__(self, example_number, attribute_values_vector, class_value):
        self.example_number = example_number
        self.attrbute_values_vector = attribute_values_vector
        self.class_value = class_value

    def print_me(self):
        print "num: " + str(self.example_number)
        print "attrs: " + str(self.attrbute_values_vector)
        print "class: " + str(self.class_value)
