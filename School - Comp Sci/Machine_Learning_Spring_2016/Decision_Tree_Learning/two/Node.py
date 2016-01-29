
class Node:

    name = ''

    parent = ''

    def __init__(self):
        pass

    def set_as_root(self):
        assert self.parent == '' or self.parent == 'none', 'error: cannot set node: ' + self.name + 'as root. Node already has a parent. Root cannot have a parent node.'
        parent = 'none'
        return True

    def is_root(self):
        return self.parent == 'none'