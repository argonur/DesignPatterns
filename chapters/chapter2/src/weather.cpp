#include <iostream>
#include <list>

class Observer {
    public:
        virtual ~Observer() = default;
        virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject {
    public:
        virtual ~Subject() = default;
        virtual void registerObserver(Observer* o) = 0;
        virtual void removeObserver(Observer* o) = 0;
        virtual void notifyObservers() = 0;
};

class DisplayElement{
    public:
        virtual ~DisplayElement() = default;
        virtual void display() = 0;

};

class WeatherData : public Subject {
    private:
        std::list<Observer*> m_observers;
        float m_temperature;
        float m_humidity;
        float m_pressure;

    public:
        WeatherData() : m_observers(), m_temperature(0), m_humidity(0), m_pressure(0)
        {

        }

        void registerObserver(Observer* o) override {
            m_observers.push_back(o);
        }

        void removeObserver(Observer* o) override {
            m_observers.remove(o);
        }

        void notifyObservers() override {
            for(auto observer : m_observers)
            {
                observer->update(m_temperature, m_humidity, m_pressure);
            }
        }

        void measurementsChanged(){
            notifyObservers();
        }

        void setMeasurements(float temperature, float humidity, float pressure){
            m_temperature = temperature;
            m_humidity = humidity;
            m_pressure = pressure;
            measurementsChanged();
        }

};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
    private:
        float m_temperature;
        float m_humidity;
        Subject* m_weatherData;

    public:
        CurrentConditionsDisplay(Subject* weatherData) : m_temperature(0), m_humidity(0), m_weatherData(weatherData)
        {
            m_weatherData->registerObserver(this);
        }

        CurrentConditionsDisplay(const CurrentConditionsDisplay&) = default;
        CurrentConditionsDisplay& operator=(const CurrentConditionsDisplay&) = default;

        void update(float temperature, float humidity, float pressure) override {
            m_temperature = temperature;
            m_humidity = humidity;
            (void)pressure; // just to avoid compilation fail
            display();
        }

        void display() override {
            std::cout << "Current conditions: " << m_temperature << "°C" << " and " << m_humidity << "% humidity" << std::endl;
        }

};

int main(void)
{
    std::cout << "chapter 2" << std::endl;

    WeatherData weatherData;
    CurrentConditionsDisplay currentDisplay(&weatherData);
    //TODO: implement the other three displays

    weatherData.setMeasurements(12.0, 65.0, 29.2);
    weatherData.setMeasurements(20.0, 55.0, 29.2);
    weatherData.setMeasurements(24.0, 45.0, 29.2);

}