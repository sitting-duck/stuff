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
    # as we travel down the tree, categories will be removed from the training set local to a particular node
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

                if line == "\n": #skip blank lines
                    continue

                tokens = line.split()
                tokenized_data_buffer.append(tokens)
            return tokenized_data_buffer

    @staticmethod
    def get_category(category, training_data):
        categories = Training_Data.get_categories()
        return categories[category]

    @staticmethod
    def get_categories(training_data):
        return Training_Data.create_categories_from_training_set(training_data)

    @staticmethod
    def create_categories_from_training_set(training_set):

        categories = {}

        # last column before the class column
        last_category_column = Training_Data.get_index_of_class_column(training_set)

        for i in range(1, last_category_column):
            current_category = Training_Data.create_category_tuple_from_column(i, training_set)
            name = current_category[0]
            attribute_dictionary = current_category[1]
            categories[name] = attribute_dictionary

        return categories

    # returns a tuple such that the first item is the category name for the given
    # column in the training set, and the second item is a dictionary of the attributes
    # for that category and the frequency that attribute is classified as each class type
    @staticmethod
    def create_category_tuple_from_column(index, training_set):

        # the name of the category
        category_name = Training_Data.get_category_name_from_column(index, training_set)

        # for every every unique attribute in this column, create a dictionary with a dictionary inside of
        # if containing all the unique class types and their counts set to zero
        # what this data structure is essentially saying is that this category has these attributes, and
        # they have not been classified as any type any number of times
        # so their count is of course initialized to zero
        attribute_dictionary = Training_Data.create_attribute_dictionary_from_column(index, training_set)

        return (category_name, attribute_dictionary)

    @staticmethod
    def create_attribute_dictionary_from_column(index, training_set):
        attribute_dictionary = {}
        for unique_attribute_name in Training_Data.get_unique_attribute_names_from_column(index, training_set):
            attribute_dictionary[unique_attribute_name] = {'n' : 0, 'y' : 0}
        return attribute_dictionary

    @staticmethod
    def get_category_name_from_column(index, training_set):
        column = Training_Data.get_column(index, training_set)
        return copy.deepcopy(column[0])

    # this is a classification problem, so this function will mine from the training data set given the set of types
    # any training instance can be classified as
    @staticmethod
    def get_set_of_unique_class_types(training_set):
        last_column_index = Training_Data.get_index_of_class_column(training_set)
        return Training_Data.get_unique_attribute_names_from_column(last_column_index, training_set)

    @staticmethod
    def get_number_of_training_examples_of_class_type(type, training_set):
        num_of_specified_type = 0
        class_values = Training_Data.get_class_values_for_training_set(training_set)
        for value in class_values:
            if value == type:
                num_of_specified_type += 1
        return num_of_specified_type

    # simply returns the count of training examples classified as each class type
    @staticmethod
    def get_class_type_frequency_dictionary(reduced_training_set, training_set = []):

        proportion_to_class_type_for_training_set = {}

        if training_set != []:
            class_types = Training_Data.get_set_of_unique_class_types(training_set)
            for type in class_types:
                num_of_type = Training_Data.get_number_of_training_examples_of_class_type(type, reduced_training_set)
                proportion_to_class_type_for_training_set[type] = num_of_type
        else:
            class_types = Training_Data.get_set_of_unique_class_types(training_set)
            for type in class_types:
                num_of_type = Training_Data.get_number_of_training_examples_of_class_type(type, training_set)
                proportion_to_class_type_for_training_set[type] = num_of_type

        return proportion_to_class_type_for_training_set

    @staticmethod
    def get_class_type_frequency_dictionary_for_all_categories(training_set):
        categories = Training_Data.get_category_names(training_set)

        dictionary = {}
        for category in categories:
            dictionary[category] = Training_Data.get_class_type_frequency_dictionary_for_category(category, training_set)

        return dictionary

    # returns a dictionary that contains all the attributes for the given category and
    # the count that each attribute has been classified as each class type
    @staticmethod
    def get_class_type_frequency_dictionary_for_category(category, training_set):

        # if the category doesn't exist in the current training set throw an error
        assert Training_Data.has_category(category, training_set) == True, 'error: training set does not have category %s' % category

        # get the list of unique attributes for the given category
        attributes = Training_Data.get_unique_attributes_for_category(category, training_set)

        class_type_frequency_dictionary = {}

        for attribute in attributes:
            class_type_frequency_attribute_tuple = Training_Data.get_class_type_frequency_for_attribute_tuple(category, attribute, training_set)
            attribute_name = class_type_frequency_attribute_tuple[0]
            attribute_frequency_dictionary = class_type_frequency_attribute_tuple[1]
            class_type_frequency_dictionary[attribute_name] = attribute_frequency_dictionary

        return class_type_frequency_dictionary

    # this function is going to return a tuple with the attribute name as the first item and a dictionary
    # containing the count of attributes classified as each class type for the given attribute.
    # this will later be used to compute the conditional entropy of a category
    @staticmethod
    def get_class_type_frequency_for_attribute_tuple(category, attribute, training_set):

        #get all the training examples where the column contains the given attribute
        single_attribute_training_set = Training_Data.get_training_set_for_single_attribute(category, attribute, training_set)

        # get class type frequency dictionary on the training set we just made that only concerns our given attribute
        class_type_frequency = Training_Data.get_class_type_frequency_dictionary(single_attribute_training_set)

        return (attribute, class_type_frequency)

    @staticmethod
    def get_number_of_training_examples_for_attribute(category, attribute, training_set):
        return len(Training_Data.get_training_set_for_single_attribute(category, attribute, training_set)) - 1

    @staticmethod
    def get_training_set_for_single_attribute(category, attribute, training_set):
        reduced_training_set = []
        category_column = Training_Data.get_column_for_category(category, training_set)

        reduced_training_set.append(training_set[0])
        i = 0
        for item in category_column:
            if item == attribute:
                reduced_training_set.append(training_set[i])
            i += 1

        return reduced_training_set

    @staticmethod
    def get_unique_attributes_for_category(category, training_set):

        if category == None:
            return []

        index = Training_Data.get_index_of_column_for_category(category, training_set)
        return sorted(Training_Data.get_unique_attribute_names_from_column(index, training_set))

    # note: this is referring to the actual column data, not just the attribute data.
    # the data is still pretty raw when this function is called
    @staticmethod
    def get_unique_attribute_names_from_column(index, training_set):

        column = copy.deepcopy(Training_Data.get_column(index, training_set))

        #delete the category name from this data column
        del column[0]

        # add all names not seen before to the list of attr names
        # note: attribute names cannot be the same as a category name
        known_attribute_names = []
        for item in column:
            if item not  in known_attribute_names and item not in Training_Data.get_category_names(training_set):
                known_attribute_names.append(item)

        return known_attribute_names

    @staticmethod
    def has_category(category, training_set):
        return category in Training_Data.get_category_names(training_set)

    @staticmethod
    def get_category_names(training_set):
        temp_row = copy.deepcopy(Training_Data.get_row(0, training_set))
        #del temp_row[0]
        del temp_row[-1]

        return temp_row

    @staticmethod
    def get_class_values_for_training_set(training_set):
        class_column = Training_Data.get_class_column_for_training_set(training_set)
        del class_column[0]
        return class_column

    @staticmethod
    def get_counter_name(training_set):
        temp_row = copy.deepcopy(Training_Data.get_row(0, training_set))
        return temp_row[0]

    # do not confuse class with category.  Class is what we classify a training example as
    # a category is a variable that can have an attribute value.
    # the value of the attributes for the categories of a training example determine what the
    # classification is of the training example
    @staticmethod
    def get_class_name(training_set):
        temp_row = copy.deepcopy(Training_Data.get_row(0, training_set))
        return temp_row[-1]

    @staticmethod
    def get_row(index, training_set):
        return training_set[index]

    @staticmethod
    def get_column(index, training_set):
        temp_column = []
        for row in training_set:
            temp_column.append(row[index])
        return temp_column

    @staticmethod
    def get_column_for_category(category, training_set):
        index = Training_Data.get_index_of_column_for_category(category, training_set)
        return Training_Data.get_column(index, training_set)

    @staticmethod
    def get_index_of_column_for_category(category, training_set):

        # throw exception if category is not in this training set
        assert Training_Data.has_category(category, training_set) == True, 'error: category %s doesn"t exist for training set' % category

        # + 1 is added here because the first column is reserved for training example id, thus
        # incrementing the column of every category
        return Training_Data.get_category_names(training_set).index(category)

    @staticmethod
    def get_class_column_for_training_set(training_set):
        return copy.deepcopy(Training_Data.get_column(Training_Data.get_index_of_class_column(training_set), training_set))

    @staticmethod
    def get_index_of_class_column(training_set):
        return len(training_set[0]) - 1

    @staticmethod
    def get_number_training_examples(training_set):
        return len(training_set) - 1

    @staticmethod
    def is_homogeneous(training_set):

        class_types = Training_Data.get_set_of_unique_class_types(training_set)
        if len(class_types) > 1:
            return False
        else:
            return True

    @staticmethod
    def get_training_set_with_category_removed(category, training_set):
        index = Training_Data.get_index_of_column_for_category(category, training_set)

        temp_set = copy.deepcopy(training_set)
        for row in temp_set:
            del row[index]
        return copy.deepcopy(temp_set)

    @staticmethod
    def get_lowest_alpha_category(categories):
        categories_in_alphabetical_order = sorted(categories)
        return categories_in_alphabetical_order[0]
