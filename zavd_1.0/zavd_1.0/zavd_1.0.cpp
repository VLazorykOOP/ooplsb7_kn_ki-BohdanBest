#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

// Клас Автомобіль
class Car {
public:
    string model;
    string number;
    bool isBroken;

    Car(string model, string number) {
        this->model = model;
        this->number = number;
        this->isBroken = false;
    }

    void markAsBroken() {
        this->isBroken = true;
    }

    void markAsFixed() {
        this->isBroken = false;
    }
};

// Клас Водій
class Driver {
public:
    string name;
    Car* car;
    bool isWorking;

    Driver(string name, Car* car) {
        this->name = name;
        this->car = car;
        this->isWorking = true;
    }

    void markAsNotWorking() {
        this->isWorking = false;
    }

    void markAsWorking() {
        this->isWorking = true;
    }

    void markTripAsDone() {
        this->car->markAsFixed();
    }

    void markCarAsBroken() {
        this->car->markAsBroken();
    }
};

// Клас Подорож
class Trip {
public:
    string from;
    string to;
    Driver* driver;
    Car* car;

    Trip(string from, string to, Driver* driver, Car* car) {
        this->from = from;
        this->to = to;
        this->driver = driver;
        this->car = car;
    }
};

// Клас Диспетчер
class Dispatcher {
public:
    vector<Driver*> drivers;
    vector<Car*> cars;
    vector<Trip*> trips;

    void addDriver(Driver* driver) {
        this->drivers.push_back(driver);
    }

    void addCar(Car* car) {
        this->cars.push_back(car);
    }

    void assignCarToDriver(Driver* driver, Car* car) {
        driver->car = car;
    }

    void assignTripToDriver(Driver* driver, Car* car) {
        if (driver->isWorking && !car->isBroken) {
            string from, to;
            cout << "Введіть місце відправлення: ";
            cin >> from;
            cout << "Введіть місце прибуття: ";
            cin >> to;

            Trip* trip = new Trip(from, to, driver, car);
            this->trips.push_back(trip);

            cout << "Рейс призначено для водія " << driver->name << endl;
            driver->markTripAsDone();
        }
        else {
            cout << "Водій не може виконати рейс" << endl;
        }
    }

    void markDriverAsNotWorking() {
        int index;
        cout << "Виберіть водія: " << endl;
        for (int i = 0; i < drivers.size(); i++) {
            cout << i + 1 << ". " << drivers[i]->name << endl;
        }
        cin >> index;

        if (index > 0 && index <= drivers.size()) {
            Driver* driver = drivers[index - 1];
            driver->markAsNotWorking();
            cout << "Водій " << driver->name << " позначено як не працюючий" << endl;
        }
        else {
            cout << "Невірний вибір" << endl;
        }
    }

    void markDriverAsWorking() {
        int index;
        cout << "Виберіть водія: " << endl;
        for (int i = 0; i < drivers.size(); i++) {
            cout << i + 1 << ". " << drivers[i]->name << endl;
        }
        cin >> index;

        if (index > 0 && index <= drivers.size()) {
            Driver* driver = drivers[index - 1];
            driver->markAsWorking();
            cout << "Водій " << driver->name << " позначено як працюючий" << endl;
        }
        else {
            cout << "Невірний вибір" << endl;
        }
    }

    void markCarAsBroken() {
        int index;
        cout << "Виберіть автомобіль: " << endl;
        for (int i = 0; i < cars.size(); i++) {
            cout << i + 1 << ". " << cars[i]->model << " (" << cars[i]->number << ")" << endl;
        }
        cin >> index;

        if (index > 0 && index <= cars.size()) {
            Car* car = cars[index - 1];
            car->markAsBroken();
            cout << "Автомобіль " << car->model << " (" << car->number << ") позначено як пошкоджений" << endl;
        }
        else {
            cout << "Невірний вибір" << endl;
        }
    }

    void markCarAsFixed() {
        int index;
        cout << "Виберіть автомобіль: " << endl;
        for (int i = 0; i < cars.size(); i++) {
            cout << i + 1 << ". " << cars[i]->model << " (" << cars[i]->number << ")" << endl;
        }
        cin >> index;

        if (index > 0 && index <= cars.size()) {
            Car* car = cars[index - 1];
            car->markAsFixed();
            cout << "Автомобіль " << car->model << " (" << car->number << ") позначено як справний" << endl;
        }
        else {
            cout << "Невірний вибір" << endl;
        }
    }

    void saveToFile(string filename) {
        ofstream file(filename);

        for (Trip* trip : trips) {
            file << "Водій: " << trip->driver->name << endl;
            file << "Автомобіль: " << trip->car->model << " (" << trip->car->number << ")" << endl;
            file << "Місце відправлення: " << trip->from << endl;
            file << "Місце прибуття: " << trip->to << endl;
            file << endl;
        }

        file.close();
    }

    void printDrivers() {
        for (Driver* driver : drivers) {
            cout << "Водій: " << driver->name << endl;
            cout << "Автомобіль: " << driver->car->model << " (" << driver->car->number << ")" << endl;
            cout << "Стан автомобіля: " << (driver->car->isBroken ? "Пошкоджений" : "Справний") << endl;
            cout << "Стан водія: " << (driver->isWorking ? "Працює" : "Не працює") << endl;
            cout << endl;
        }
    }

    void addNewDriver() {
        string name, model, number;
        cout << "Введіть ім'я нового водія: ";
        cin >> name;
        cout << "Введіть модель автомобіля: ";
        cin >> model;
        cout << "Введіть номер автомобіля: ";
        cin >> number;

        Car* car = new Car(model, number);
        Driver* driver = new Driver(name, car);

        this->addCar(car);
        this->addDriver(driver);
    }
};

int main() {
    SetConsoleOutputCP(1251);
    // Створюмо автомобілі
    Car* car1 = new Car("BMW", "AA1234BB");
    Car* car2 = new Car("Mercedes", "BC5678DE");

    // Створюємо водіїв
    Driver* driver1 = new Driver("Іван", car1);
    Driver* driver2 = new Driver("Петро", car2);

    // Створюємо диспетчера
    Dispatcher* dispatcher = new Dispatcher();

    // Додаємо автомобілі та водіїв до диспетчера
    dispatcher->addCar(car1);
    dispatcher->addCar(car2);
    dispatcher->addDriver(driver1);
    dispatcher->addDriver(driver2);

    // Призначаємо автомобілі водіям
    dispatcher->assignCarToDriver(driver1, car1);
    dispatcher->assignCarToDriver(driver2, car2);

    // Приначаємо рейси водіям
    dispatcher->assignTripToDriver(driver1, car1);
    dispatcher->assignTripToDriver(driver2, car2);

    // Позначємо автомобіль як пошкоджений
    dispatcher->markCarAsBroken();

    // Позначаємо водія як не працюючого
    dispatcher->markDriverAsNotWorking();

    // Виводимо інформацію про водіїв на екран
    cout << "Інформація про водіїв:" << endl;
    dispatcher->printDrivers();

    // Оператор switch для додаткових функцій
    int choice;
    do {
        cout << "Оберіть дію:" << endl;
        cout << "1. Позначити автомобіль як справний" << endl;
        cout << "2. Позначити водія як працюючого" << endl;
        cout << "3. Переглянути інформацію про водіїв" << endl;
        cout << "4. Додати нового водія" << endl;
        cout << "5. Вийти" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            dispatcher->markCarAsFixed();
            break;
        case 2:
            dispatcher->markDriverAsWorking();
            break;
        case 3:
            cout << "Інформація про водіїв:" << endl;
            dispatcher->printDrivers();
            break;
        case 4:
            dispatcher->addNewDriver();
            cout << "Новий водій доданий" << endl;
            break;
        case 5:
            cout << "До побачення!" << endl;
            break;
        default:
            cout << "Невірний вибір" << endl;
            break;
        }
    } while (choice != 5);

    // Зберігаємо інформацію про подорожі у файл
    dispatcher->saveToFile("trips.txt");

    // Очищаємо пам'ять
    delete car1;
    delete car2;
    delete driver1;
    delete driver2;
    delete dispatcher;

    return 0;
}