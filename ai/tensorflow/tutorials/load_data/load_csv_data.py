import functools
import numpy as np
import tensorflow as tf

LABEL_COLUMN = 'survived'
LABELS = [0, 1]

def get_dataset(file_path, **kwargs):
    dataset = tf.data.experimental.make_csv_dataset(
            file_path,
            batch_size=5, # artificially small to make examples easier to show
            label_name=LABEL_COLUMN,
            na_value="?",
            num_epochs=1,
            ignore_errors=True,
            **kwargs)
    return dataset


def show_batch(dataset):
    for batch, label in dataset.take(1):
        for key, value in batch.items():
            print("{:20s}: {}".format(key, value.numpy()))

# Here's a simple function that will pack together all the columns
def pack(features, label):
    return tf.stack(list(features.values()), axis=-1), label

# Define a more general preprocessor that selects a list of numeric features and packs them into a single column
class PackNumericFeatures(object):
    def __init__(self, names):
        self.names = names

    def __call__(self, features, labels):
        numeric_features = [features.pop(name) for name in self.names]
        numeric_features = [tf.cast(feat, tf.float32) for feat in numeric_features]
        numeric_features = tf.stack(numeric_features, axis=-1)
        features['numeric'] = numeric_features

        return features, labels

def main(): 

    TRAIN_DATA_URL = "https://storage.googleapis.com/tf-datasets/titanic/train.csv"
    TEST_DATA_URL = "https://storage.googleapis.com/tf-datasets/titanic/eval.csv"

    train_file_path = tf.keras.utils.get_file("train.csv", TRAIN_DATA_URL)
    test_file_path = tf.keras.utils.get_file("eval.csv", TEST_DATA_URL)

    raw_train_data = get_dataset(train_file_path)
    raw_test_data = get_dataset(test_file_path)

    # Make numpy values easier to read
    np.set_printoptions(precision=3, suppress=True)

    ### Load Data
    # You can load this using pandas, and pass the NUmPy arrays to Tensorflow. If you need to scale up to a large set of files, or need a loader that 
    # integrates with Tensorflow and tf.data then use the tf.data.experimental.make_csv_dataset function.

    # the only column you need to identify explicitly is the one with the value that the model is intended to predict.
    

    # Now read the CSV data from the file and create a dataset.

    # (for the full documentation, see tf.data.experimental.make_csv_dataset)

    ### Data Preprocessing
    # A CSV file can contain a variety of data types. Typically you want to convert from those mixed types to a fixed length vector before feeding the data into your model

    # Tensorflow has a built in system for describing common input conversions: tf.feature_column. 

    # You can preprocess your data using any tool you like (like nltk or sklearn) and just pass the processed output to Tensorflow

    # The primary advantage of doing the preprocessing inside your model is that when you export the model it includes the preprocessing. 
    # This way you can pass the raw data directly to your model. 
    
    # Continuous Data
    # If your data is already in an appropriate numeric format, you can pack the data into a vector before passing it off to the model: 
    SELECT_COLUMNS = ['survived', 'age', 'n_siblings_spouses', 'parch', 'fare']
    DEFAULTS = [0, 0.0, 0.0, 0.0, 0.0]
    temp_dataset = get_dataset(train_file_path, 
                                select_columns=SELECT_COLUMNS,
                                column_defaults=DEFAULTS)

    show_batch(temp_dataset)

    example_batch, labels_batch = next(iter(temp_dataset))

    packed_dataset = temp_dataset.map(pack)

    for features, labels in packed_dataset.take(1):
        print(features.numpy())
        print()
        print(labels.numpy())

    # If you have mixed datatypes you may want to separate out these simple-numeric fields. The tf.feature_column api can handle them, but this incurs some overhead and should
    # be avoided unless really necessary.

    example_batch, labels_batch = next(iter(temp_dataset))

    NUMERIC_FEATURES = ['age', 'n_siblings_spouses', 'parch', 'fare']

    packed_train_data = raw_train_data.map(
            PackNumericFeatures(NUMERIC_FEATURES))

    packed_test_data = raw_test_data.map(
            PackNumericFeatures(NUMERIC_FEATURES))

    show_batch(packed_train_data)

    example_batch, labels_batch = next(iter(packed_train_data))

    ### Data Normalization
    # continuous data should always be normalized

    import pandas as pd
    desc = pd.read_csv(train_file_path)[NUMERIC_FEATURES].describe()

    MEAN = np.array(desc.T['mean'])
    STD = np.array(desc.T['std'])

    def normalize_numeric_data(data, mean, std):
        # center the data
        return (data-mean)/std

    # now create a numeric column. The tf.feature_columns.numeric_column API accepts a normalizer_fn argument, which will be run on each batch. 


if __name__ == '__main__':
    main()
