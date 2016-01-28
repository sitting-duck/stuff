
class Category:

    name = ""

    attributes = []

    class_count_vector = []

    def __init__(self, name, attributes):
        self.name = name
        self.attributes = attributes

        class_count_vector_index = 0
        while class_count_vector_index < len(self.attributes):
            self.class_count_vector = 0

    def print_me(self):
        print self.name
        print self.attributes
        print self.class_count_vector