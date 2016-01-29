
class Attribute:

    name = ""

    class_count_vector = []

    numclasses = 0

    def __init__(self, name, num_classes):
        self.name = name
        self.num_classes = num_classes

        if len(self.class_count_vector) != self.num_classes:
            for i in range(0,num_classes):
                self.class_count_vector.append(0)


    def increment_for_class_by_index(self, class_index):
        self.class_count_vector[class_index] += 1

    def print_me(self):
        print self.name
        print self.class_count_vector
