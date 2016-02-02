
class Attribute:

    name = ""

    class_count_vector = []

    #numclasses = 0

    def __init__(self, name):
        self.name = name

        #if len(self.class_count_vector) != self.num_classes:
        #    for i in range(0,num_classes):
        #        self.class_count_vector.append(0)

    def increment_for_class_by_index(self, class_index):
        #if(class_index < self.numclasses - 1):
        self.class_count_vector[class_index] += 1

    def print_me(self):
        print self.name
        print self.class_count_vector
