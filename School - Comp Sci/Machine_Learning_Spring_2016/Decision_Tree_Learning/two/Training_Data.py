import fileinput
import copy

class Training_Data:

    # this holds the initial training set gathered from file.
    # subsets of this training set will be passed down the decision tree
    # because there is some sense of change of state as we traverse the tree,
    # but this variable will hold the entirety of the training data
    training_set = []

    #this holds the set of all categories and their attributes and the counts for each
    # attribute of each class type for the initial training set gathered from file
    # you can think of this dictionary as the initial snapshot of the categories for the training data
    # as we travel down the tree, categoris will be removed from the training set local to a particular node
    # so it is useful to have the initial entire category set stored here
    categories = {}

    def __init__(self):
        self.training_set =self. get_training_set()

    def get_training_set(self):

        # if data has already been collected from file return it
        if self.training_set != []:
            return self.training_set
        # else collect and tokenize the data from the file and store it in
        # a 2D list
        else:
            tokenized_data_buffer = []
            data_from_file = fileinput.input()
            for line in data_from_file:
                tokens = line.split()
                tokenized_data_buffer.append(tokens)
            return tokenized_data_buffer

    def get_category(self, category, training_data):
        categories = self.get_categories()
        return categories[category]

    def get_categories(self, training_data):
        return self.create_categories_from_training_set(training_data)

    def create_categories_from_training_set(self, training_set):

        categories = {}
        # last column before the class column
        #todo: this indexing doesn't make sense
        last_category_column = self.get_index_of_class_column(training_set)

        for i in range(1, last_category_column):
            current_category = self.create_category_tuple_from_column(i, training_set)
            name = current_category[0]
            attribute_dictionary = current_category[1]
            categories[name] = attribute_dictionary

        return categories

    # returns a tuple such that the first item is the category name for the given
    # column in the training set, and the second item is a dictionary of the attributes
    # for that category and the frequency that attribute is classified as each class type
    def create_category_tuple_from_column(self, index, training_set):

        # the name of the category
        category_name = self.get_category_name_from_column(index, training_set)

        # for every every unique attribute in this column, create a dictionary with a dictionary inside of
        # if containing all the unique class types and their counts set to zero
        # what this data structure is essentially saying is that this category has these attributes, and
        # they have not been classified as any type any number of times
        # so their count is of course initialized to zero
        attribute_dictionary = self.create_attribute_dictionary_from_column(index, training_set)

        return (category_name, attribute_dictionary)

    def create_attribute_dictionary_from_column(self, index, training_set):
        attribute_dictionary = {}
        for unique_attribute_name in self.get_unique_attribute_names_from_column(index, training_set):
            attribute_dictionary[unique_attribute_name] = {'n' : 0, 'y' : 0}
        return attribute_dictionary

    def get_category_name_from_column(self, index, training_set):
        column = self.get_column(index, training_set)
        return copy.deepcopy(column[0])

    # this is a classification problem, so this function will mine from the training data set given the set of types
    # any training instance can be classified as
    def get_set_of_unique_class_types(self, training_set):
        last_column_index = self.get_index_of_class_column(training_set)
        return self.get_unique_attribute_names_from_column(last_column_index, training_set)

    def get_number_of_training_examples_of_class_type(self, type, training_set):
        num_of_specified_type = 0
        class_values = self.get_class_values_for_training_set(training_set)
        for value in class_values:
            if value == type:
                num_of_specified_type += 1
        return num_of_specified_type

    # simply returns the count of training examples clasified as each class type
    def get_class_type_frequency_dictionary(self, training_set):
        class_types = self.get_set_of_unique_class_types(training_set)

        proportion_to_class_type_for_training_set = {}
        for type in class_types:
            num_of_type = self.get_number_of_training_examples_of_class_type(type, training_set)
            proportion_to_class_type_for_training_set[type] = num_of_type
        return proportion_to_class_type_for_training_set

    # returns a dictionary that contains all the attributes for the given category and
    # the count that each attribute has been classified as each class type
    def get_class_type_frequency_dictionary_for_category(self, category, training_set):

        # if the category doesn't exist in the current training set throw an error
        assert self.has_category(category, training_set) == False, 'error: training set does not have category %s' % category

        # get the list of unique attributes for the given category
        self.g

    # this function is going to return a tuple with the attribute name as the first item and a dictionary
    # containing the count of attributes classified as each class type for the given attribute.
    # this will later be used to compute the conditional entropy of a category
    def get_proportion_to_class_type_for_attribute_tuple(self, category, attribute, training_set):

        #get the column
        category_column = self.ge

        #get all the training examples where the column contains the given attribute

        # get class type frequency dictionary on the training set we just made that only concerns our given attribute

        # todo: finish

    # note: this is referring to the actual column data, not just the attribute data.
    # the data is still pretty raw when this function is called
    def get_unique_attribute_names_from_column(self, index, training_set):

        column = copy.deepcopy(self.get_column(index, training_set))

        #delete the category name from this data column
        del column[0]

        # add all names not seen before to the list of attr names
        # note: attribute names cannot be the same as a category name
        known_attribute_names = []
        for item in column:
            if item not  in known_attribute_names and item not in self.get_category_names(training_set):
                known_attribute_names.append(item)

        return known_attribute_names

    def has_category(self, category, training_set):
        return category in self.get_category_names(training_set)

    def get_category_names(self, training_set):
        temp_row = copy.deepcopy(self.get_row(0, training_set))
        del temp_row[0]
        del temp_row[-1]
        return temp_row

    def get_class_values_for_training_set(self, training_set):
        class_column = self.get_class_column_for_training_set(training_set)
        del class_column[0]
        return class_column

    def get_counter_name(self, training_set):
        temp_row = copy.deepcopy(self.get_row(0, training_set))
        return temp_row[0]

    def get_class_name(self, training_set):
        temp_row = copy.deepcopy(self.get_row(0, training_set))
        return temp_row[-1]

    def get_row(self, index, training_set):
        return training_set[index]

    def get_column(self, index, training_set):
        temp_column = []
        for row in training_set:
            temp_column.append(row[index])
        return temp_column

    def get_column_for_category(self, category, training_set):
        pass

    def get_index_of_column_for_category(self, category, training_set):

        #todo: throw exception if category doesn't exist
        categories = self.get_category_names(training_set)
        index = categories.index(category)
        return index


    def get_class_column_for_training_set(self, training_set):
        return copy.deepcopy(self.get_column(self.get_index_of_class_column(training_set), training_set))

    def get_index_of_class_column(self, training_set):
        return len(training_set[0]) - 1

    def get_number_training_examples(self, training_set):
        return len(training_set) - 1