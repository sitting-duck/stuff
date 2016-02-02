
class Category:

    name = ""

    attributes = []

    def __init__(self, name, attributes):
        self.name = name
        self.attributes = attributes

    def print_me(self):
        print self.name
        for attr in self.attributes:
            attr.print_me()