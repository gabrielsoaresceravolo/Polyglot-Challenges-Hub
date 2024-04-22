import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
from tensorflow.keras.datasets import cifar10
from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras.layers import Dense, GlobalAveragePooling2D
from tensorflow.keras.models import Model, load_model
from tensorflow.keras.preprocessing.image import ImageDataGenerator

def load_cifar10_data():
    (x_train, y_train), (x_test, y_test) = cifar10.load_data()
    x_train = x_train.astype('float32') / 255.0
    x_test = x_test.astype('float32') / 255.0
    return (x_train, y_train), (x_test, y_test)

def build_model(num_classes):
    base_model = MobileNetV2(weights='imagenet', include_top=False)

    x = base_model.output
    x = GlobalAveragePooling2D()(x)
    x = Dense(1024, activation='relu')(x)
    predictions = Dense(num_classes, activation='softmax')(x)

    model = Model(inputs=base_model.input, outputs=predictions)

    for layer in base_model.layers:
        layer.trainable = False

    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

    return model

def train_model(model, x_train, y_train, x_test, y_test, batch_size=32, epochs=10):
    datagen_train = ImageDataGenerator(rotation_range=15, width_shift_range=0.1, height_shift_range=0.1,
                                       horizontal_flip=True)
    datagen_train.fit(x_train)

    history = model.fit(datagen_train.flow(x_train, y_train, batch_size=batch_size),
                        steps_per_epoch=len(x_train) // batch_size, epochs=epochs,
                        validation_data=(x_test, y_test))

    return history

def plot_history(history):
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(history.history['accuracy'], label='Training Accuracy')
    plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
    plt.title('Training and Validation Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(history.history['loss'], label='Training Loss')
    plt.plot(history.history['val_loss'], label='Validation Loss')
    plt.title('Training and Validation Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()

    plt.show()

def save_model(model, filename):
    model.save(filename)
    print(f"Model saved as '{filename}'.")

def load_saved_model(filename):
    model = load_model(filename)
    print(f"Model loaded from '{filename}'.")
    return model

def predict_image(model, image_path, class_names):
    img = Image.open(image_path)
    img = img.resize((32, 32))
    img_array = np.expand_dims(np.array(img), axis=0) / 255.0

    prediction = model.predict(img_array)
    predicted_class = class_names[np.argmax(prediction)]

    plt.imshow(img)
    plt.axis('off')
    plt.title(f"Predicted Class: {predicted_class}")
    plt.show()

def main():
    num_classes = 10
    class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer',
                   'dog', 'frog', 'horse', 'ship', 'truck']

    (x_train, y_train), (x_test, y_test) = load_cifar10_data()

    model = build_model(num_classes)

    print("Training the model...")
    history = train_model(model, x_train, y_train, x_test, y_test)

    print("Plotting training history...")
    plot_history(history)

    print("Model evaluation:")
    test_loss, test_acc = model.evaluate(x_test, y_test)
    print(f"Test Loss: {test_loss}")
    print(f"Test Accuracy: {test_acc}")


    save_model(model, 'cifar10_model.h5')

    loaded_model = load_saved_model('cifar10_model.h5')

    image_path = 'example_image.jpg'
    predict_image(loaded_model, image_path, class_names)

if __name__ == "__main__":
    main()
