#include <iostream>
#include <string>
#include <memory>
#include <list>


class Pizza
{
    private:

    std::string m_name;
    std::string m_dough;
    std::string m_sauce;
    std::list<std::string> m_toppings;

    public:

    virtual ~Pizza() = default;

    Pizza(const std::string& name, const std::string& dough, const std::string& sauce, const std::list<std::string>& toppings) :
        m_name(name), m_dough(dough), m_sauce(sauce), m_toppings(toppings)
    {

    }

    void prepare() const
    {
        std::cout << "Preparing " << getName() << std::endl;
        std::cout << "Tossing dough..." << std::endl;
        std::cout << "Adding sauce..." << std::endl;
        std::cout << "Adding toppings:" << std::endl;
        for(auto topping : m_toppings)
        {
            std::cout << "  " << topping << std::endl;
        }
    }

    void bake() const
    {
        std::cout << "Bake for 20 minutes at 200° C" << std::endl;
    }

    void cut() const
    {
        std::cout << "Cut pizza in diagonal slices" << std::endl;
    }

    void box() const
    {
        std::cout << "Place pizza into the box" << std::endl;
    }

    std::string getName() const
    {
        return m_name;
    }

};

class CheesePizza : public Pizza
{
    public: 
    CheesePizza() : Pizza("Cheese Pizza", "normal dough", "normal sauce", {"Grated Reggiano Cheese"})
    {

    }

};

class VeggiePizza : public Pizza
{
    public:
    VeggiePizza() : Pizza("Veggie Pizza", "dough", "sauce", {"Paprika", "Onion", "Olives", "Champignons"})
    {

    }

};

class SimplePizzaFactory
{
    public:

    std::shared_ptr<Pizza> createPizza(const std::string& pizzaType)
    {
        std::shared_ptr<Pizza> pizza = nullptr;

        if(pizzaType == "cheese")
        {
            pizza = std::make_shared<CheesePizza>();
        }
        /*
        else if(pizzaType == "pepperoni")
        {
            pizza = std::make_shared<PepperoniPizza>();
        }
        else if(pizzaType == "clam")
        {
            pizza = std::make_shared<ClamPizza>();
        }
        */
        else if(pizzaType == "veggie")
        {
            pizza = std::make_shared<VeggiePizza>();
        }

        return pizza;
    }

};

class PizzaStore
{
    private:
    std::shared_ptr<SimplePizzaFactory> m_factory;

    public:

    PizzaStore(std::shared_ptr<SimplePizzaFactory> factory) : m_factory(factory)
    {

    }

    std::shared_ptr<Pizza> orderPizza(std::string pizzaType)
    {
        std::shared_ptr<Pizza> pizza;

        pizza = m_factory->createPizza(pizzaType);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};


int main(void)
{
    std::shared_ptr<SimplePizzaFactory> factory = std::make_shared<SimplePizzaFactory>();
    PizzaStore pizzaStore(factory);
    
    pizzaStore.orderPizza("veggie");
    std::cout << std::endl;
    pizzaStore.orderPizza("cheese");
}
